/*
 * CL2PacketCap.cpp - Uses pcap to capture l2 packets on the network.
 * Created February 9, 2007, by Michael 'Bigcheese' Spencer.
 *
 * Copyright (C) 2007 Michael Spencer
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Michael Spencer - bigcheesegs@gmail.com
 */

#ifdef ADENA_L2_CAP

#include <CL2PacketCap.h>
#include <pcap.h>
#include <hexdump.h>
#include <os.h>

namespace adena
{
namespace utility
{

void parseBuff(irr::c8* buff, irr::u32 buff_len, game_server::CCrypt* cc)
{
	static bool need_data = false;
	static irr::c8 old_data[65536];
	static irr::u32 old_data_size = 0;

	irr::u32 loc = 0;
	while(loc < buff_len)
	{
		if(need_data)
		{
			irr::u16 pack_size = 0;
			pack_size += (unsigned char)old_data[0];
			pack_size += ((unsigned char)(old_data[1]) * 256);
			irr::u32 data_needed = pack_size - old_data_size;
			memcpy(old_data + old_data_size, buff, data_needed);
			loc += data_needed;

			cc->decrypt(old_data + 2, pack_size - 2);
			if((old_data[2] & 0xff) < 0x10)
				printf("Packet size: %d Packet type: 0x0%x\n", pack_size, (old_data[2] & 0xff));
			else
				printf("Packet size: %d Packet type: 0x%x\n", pack_size, (old_data[2] & 0xff));

			need_data = false;
			continue;
		}
		irr::c8 temp[65536];
		irr::u16 pack_size = 0;
		pack_size += (unsigned char)buff[loc++];
		pack_size += ((unsigned char)(buff[loc++]) * 256);
		if((loc - 2) + pack_size >  buff_len)
		{
			// Rest of l2 packet in another l2 packet.
			memcpy(old_data, buff + (loc - 2), buff_len - (loc - 2));
			old_data_size = buff_len - (loc - 2);
			need_data = true;
			return;
		}
		memcpy(temp, buff + loc, pack_size - 2);
		loc += (pack_size - 2);
		cc->decrypt(temp, pack_size - 2);
		if((temp[0] & 0xff) < 0x10)
			printf("Packet size: %d Packet type: 0x0%x\n", pack_size, (temp[0] & 0xff));
		else
			printf("Packet size: %d Packet type: 0x%x\n", pack_size, (temp[0] & 0xff));
	}
}


void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	CL2PacketCap* caper = (CL2PacketCap*)param;
	irr::u16 src_port = 0;
	irr::u16 dst_port = 0;
	memcpy(&src_port, pkt_data + 0x22, 2);
	memcpy(&dst_port, pkt_data + 0x24, 2);
	src_port = irr::os::Byteswap::byteswap(src_port);
	dst_port = irr::os::Byteswap::byteswap(dst_port);
	// 0x36.
	if(src_port == 7777)
	{
		// Server packet
		if(((pkt_data[0x38] & 0xff) == 00) && caper->InCrypt == 0)
		{
			// KeyPacket
			printf("Got key packet!\n");
			memcpy(caper->Key, pkt_data + 0x3a, 8);
			caper->OutCrypt = new game_server::CCrypt(caper->Key);
			caper->InCrypt = new game_server::CCrypt(caper->Key);
			return;
		}
		if(caper->InCrypt != 0)
		{
			irr::c8 buff[64000];
			irr::u32 datalen = header->caplen - 0x36;
			if(datalen >= 2)
			{
				printf("Data len %d\n", datalen);
				memcpy(buff, pkt_data + 0x36, datalen);
				parseBuff(buff, datalen, caper->InCrypt);
			}
		}
	}else if(dst_port == 7777)
	{
		// Client packet
	}
};

CL2PacketCap::CL2PacketCap()
: InCrypt(0), OutCrypt(0)
{

};

CL2PacketCap::~CL2PacketCap()
{

};

void CL2PacketCap::run()
{
	pcap_if_t *alldevs;
	pcap_if_t *d;
	int inum;
	int i=0;
	pcap_t *adhandle;
	char errbuf[PCAP_ERRBUF_SIZE];
	
	/* Retrieve the device list */
	if(pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		fprintf(stderr,"Error in pcap_findalldevs: %s\n", errbuf);
		return;
	}
	
	/* Print the list */
	for(d=alldevs; d; d=d->next)
	{
		printf("%d. %s", ++i, d->name);
		if (d->description)
			printf(" (%s)\n", d->description);
		else
			printf(" (No description available)\n");
	}
	
	if(i==0)
	{
		printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
		return;
	}
	
	printf("Enter the interface number (1-%d):",i);
	scanf("%d", &inum);
	
	if(inum < 1 || inum > i)
	{
		printf("\nInterface number out of range.\n");
		/* Free the device list */
		pcap_freealldevs(alldevs);
		return;
	}
	
	/* Jump to the selected adapter */
	for(d=alldevs, i=0; i< inum-1 ;d=d->next, i++);
	
	/* Open the device */
	/* Open the adapter */
	if ((adhandle= pcap_open_live(d->name,	// name of the device
							 65536,			// portion of the packet to capture. 
											// 65536 grants that the whole packet will be captured on all the MACs.
							 1,				// promiscuous mode (nonzero means promiscuous)
							 1000,			// read timeout
							 errbuf			// error buffer
							 )) == NULL)
	{
		fprintf(stderr,"\nUnable to open the adapter. %s is not supported by WinPcap\n", d->name);
		/* Free the device list */
		pcap_freealldevs(alldevs);
		return;
	}
	
	printf("\nlistening on %s...\n", d->description);
	
	/* At this point, we don't need any more the device list. Free it */
	pcap_freealldevs(alldevs);
	
	/* start the capture */
	pcap_loop(adhandle, 0, packet_handler, (u_char*)this);
	
	pcap_close(adhandle);
};

}
}

#endif
