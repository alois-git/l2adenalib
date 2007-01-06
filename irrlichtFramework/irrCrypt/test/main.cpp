#include <irrCrypt.h>
#include <iostream>
#include <hexdump.h>

using namespace std;

int main()
{
	irr::crypt::CCipherRSA rsa = irr::crypt::CCipherRSA();
	irr::crypt::CKeyParmsRSA rsakey(1024, irr::math::BigNum(65537));
	rsa.generateKey(&rsakey);
	int size = ((irr::crypt::CKeyRSA*)rsa.getKey())->n.to(0, 0);
	cout << "Size " << size << "\n";
	irr::c8* buff = new irr::c8[size];
	((irr::crypt::CKeyRSA*)rsa.getKey())->n.to((irr::u8*)buff, size);
	hexdump(buff, size);

	irr::u8 plain_text[128] = "Hi!";
	irr::u8 cipher_text[128];
	irr::u8 uncipher_text[128];

	cout << "Plain\n";
	hexdump((char*)plain_text, 128);
	rsa.encrypt(plain_text, 128, cipher_text, 128);
	cout << "Cipher\n";
	hexdump((char*)cipher_text, 128);
	rsa.decrypt(cipher_text, 128, uncipher_text, 128);
	cout << "Uncipher\n";
	hexdump((char*)uncipher_text, 128);

	system("PAUSE");
	return 0;
}
