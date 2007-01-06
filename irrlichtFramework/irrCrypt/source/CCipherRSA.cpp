/*
 * CCipherRSA.cpp - RSA Cipher interface.
 * Created November 23, 2006, by Michael 'Bigcheese' Spencer.
 */

#include <CCipherRSA.h>

namespace irr
{
namespace crypt
{

CKeyParmsRSA::CKeyParmsRSA(u32 nbits, math::BigNum &e)
: bits(nbits), e(e)
{

};

CKeyParmsRSA::~CKeyParmsRSA()
{

};

//=============================================================================

CKeyRSA::CKeyRSA()
{

};

CKeyRSA::~CKeyRSA()
{

};

ByteStream<>* CKeyRSA::serialize()
{
	return NULL;
};

void CKeyRSA::deserialize(irr::ByteStream<> &bs)
{

};

//=============================================================================

CCipherRSA::CCipherRSA()
{

};

CCipherRSA::~CCipherRSA()
{

};

ECRYPT_Cipher_Ret CCipherRSA::encrypt(u8* in, u32 in_size, u8* out, u32 out_size)
{
	math::BigNum plain_text(0);
	plain_text.from(in, in_size);
	math::BigNum cipher_text = plain_text.modExp(((CKeyRSA*)Key)->e, ((CKeyRSA*)Key)->n);
	cipher_text.to(out, out_size);
	return ECR_OK;
};

ECRYPT_Cipher_Ret CCipherRSA::decrypt(u8* in, u32 in_size, u8* out, u32 out_size)
{
	math::BigNum cipher_text(0);
	cipher_text.from(in, in_size);
	math::BigNum plain_text = cipher_text.modExp(((CKeyRSA*)Key)->d, ((CKeyRSA*)Key)->n);
	plain_text.to(out, out_size);
	return ECR_OK;
};

IKey* CCipherRSA::generateKey(irr::crypt::IKeyParms *parms, IRng* rng)
{
	CKeyRSA* key = new CKeyRSA();
	math::BigNum p(0);
	math::BigNum q(0);
	math::BigNum g, p1, q1, phi;
	u32 p_bits, q_bits;

	bool prime = false;

	key->bits = ((CKeyParmsRSA*)parms)->bits;
	key->e = ((CKeyParmsRSA*)parms)->e;

	p_bits = key->bits / 2;
	q_bits = key->bits - p_bits;

	do
	{
		p.randPrime(p_bits);
		q.randPrime(q_bits);

		p.setBit(p_bits - 1, 1);
		q.setBit(q_bits - 1, 1);
		p.setBit(p_bits - 2, 1);
		q.setBit(q_bits - 2, 1);

		if(q > p)
		{
			g = p;
			p = q;
			q = g;
		}

		p1 = --p;
		q1 = --q;

		if((p1.gcd(key->e) == math::BigNum(1)) && (q1.gcd(key->e) == math::BigNum(1)))
			NULL;
		else
			continue;

		key->n = p * q;
		phi = p1 * q1;
		key->d = key->e.modInv(phi);
		prime = true;
	}while(!prime);

	Key = key;
	return Key;
};

IKey* CCipherRSA::getKey()
{
	return Key;
};

ECRYPT_Cipher_Ret CCipherRSA::setKey(IKey* key)
{
	return ECR_OK;
};

}
}
