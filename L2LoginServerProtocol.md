This page describes the client/server protocol used by the login server and L2 client.

# Intro #

The base structure for all packets is.

```
| 2 bytes |   up to 65533 bytes   |
-----------------------------------
| Length  |         Data          |
-----------------------------------
```

All integers are little endian.

Other than the first packet sent by the login server, all packets are check summed and then encrypted with blowfish using the key "_;5.]94-31==-%xT!^[$\000"._

# Sending a packet #

Here is an example packet (The game guard authentication response packet).
```
char packet[5] = {0x0b, 0x0b, 0x00, 0x00, 0x00};
```

  1. Add 4 bytes to the end for the checksum (bringing our packet length to 9).
  1. Pad the packet with 0x00s so that the length is a multiple of 8 (we add 7 0x00s and get a packet length of 16).
> > Our packet would now look like this (Already made the packet 3.2x as large! way to go L2!!!).
```
char packet[16] = {0x0b, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
```
  1. Do the checksum (because apparently TCP's checksum just doesn't cut it...).
```
bool checksum(char* data, int data_len)
{
	long chksum = 0;
	int count = data_len - 4;
	int i = 0;
	for (i = 0; i < count; i += 4)
	{
		long ecx = data[i] & 0xff;
		ecx |= (data[i + 1] << 8) & 0xff00;
		ecx |= (data[i + 2] << 0x10) & 0xff0000;
		ecx |= (data[i + 3] << 0x18) & 0xff000000;
		
		chksum ^= ecx;
	}

	long ecx = data[i] &0xff;
	ecx |= (data[i + 1] << 8) & 0xff00;
	ecx |= (data[i + 2] << 0x10) & 0xff0000;
	ecx |= (data[i + 3] << 0x18) & 0xff000000;

	data[i] = chksum &0xff;
	data[i + 1] = (chksum >>0x08) & 0xff;
	data[i + 2] = (chksum >>0x10) & 0xff;
	data[i + 3] = (chksum >>0x18) & 0xff;

	return ecx == chksum;	
}
```

> I'm to lazy to go do the checksum, so lets pretend it just came out to be 0.
  1. Add 2 bytes as the length (including the 2 bytes you're adding) to the front of the packet (little endian).
> > Now our packet should look like this.
```
char packet[18] = {0x12, 0x00, 0x0b, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
```
  1. And your packet is ready to be sent (after getting 3.6x as large... and even better is it's not secure AT ALL...)

  1. Now we encrypt the packet (NOT including the length) with blowfish using the key `"_;5.]94-31==-%xT!^[$\000"`. I'm to lazy to go encrypt it, so lets pretend it came out like so.
```
char packet[18] = {0x12, 0x00, 0xf5, 0x45, 0xfa, 0x4b, 0x00, 0xa9, 0x56, 0x73, 0xb7, 0xde, 0xad, 0xbe, 0xef, 0x13, 0x37, 0x00};
```

> It is now ready to be sent. Which brings us to the next part.

# Receiving a packet #

Let's take that packet we just sent and receive it.

  1. Take the first two bytes off and use them as the length of the packet (little endian).
  1. Decrypt the packet using the key `"_;5.]94-31==-%xT!^[$\000"`.
  1. The first byte is the packet type, the rest of the data is packet dependent data.

# An example login process #

  1. Client connects via TCP on port 2106.
  1. Server sends the init packet containing the scrambled RSA public modulus.
  1. (Optional) Client sends a gameguard authentication request.
  1. (Optional) Server sends a gameguard authentication response.
  1. Client sends encrypted username and password.
  1. Server either says the login was right, or sends the proper rejection response.
  1. Client requests the server list.
  1. Server sends the server list.
  1. Client requests to play on a game server.
  1. Server asks the game server if the client can play, then tells the client what the server said.
  1. Client either connects to the game server, or disconnects from the login server.