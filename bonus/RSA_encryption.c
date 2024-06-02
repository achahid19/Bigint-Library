#include "bigInt.h"

void rsaEncrypt(BigInt_ptr ciphertext, BigInt_ptr message,
		BigInt_ptr e, BigInt_ptr n);
void rsaDecrypt(BigInt_ptr message, BigInt_ptr ciphertext,
		BigInt_ptr d, BigInt_ptr n);

/**
 * rsaEncrypt -
*/
void rsaEncrypt(BigInt_ptr ciphertext, BigInt_ptr message,
		BigInt_ptr e, BigInt_ptr n)
{
    bigIntModExp(ciphertext, message, e, n);
}

/**
 * rsaDecrypt -
*/
void rsaDecrypt(BigInt_ptr message, BigInt_ptr ciphertext,
		BigInt_ptr d, BigInt_ptr n)
{
	bigIntModExp(message, ciphertext, d, n);
}
