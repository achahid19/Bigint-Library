#include "./bigInt.h"

void	karatsubaMult(BigInt_ptr result, BigInt_ptr x, BigInt_ptr y);
void splitBigInt(BigInt_ptr source, BigInt_ptr low, BigInt_ptr high, int pos);

/**
 * karatsubaMult -
*/
void	karatsubaMult(BigInt_ptr result, BigInt_ptr x, BigInt_ptr y)
{
	int	m;
	BigInt_ptr low1, high1, low2, high2, z0, z1, z2, temp1, temp2;

	if (x->size == 1 || y->size == 1)
	{
		bigIntMult(result, x, y); // Use naive multiplication for small numbers
		return;
	}
	m = x->size / 2;
	low1 = (BigInt_ptr)malloc(sizeof(t_BigInt));
	high1 = (BigInt_ptr)malloc(sizeof(t_BigInt));
	low2 = (BigInt_ptr)malloc(sizeof(t_BigInt));
	high2 = (BigInt_ptr)malloc(sizeof(t_BigInt));
	z0 = (BigInt_ptr)malloc(sizeof(t_BigInt));
	z1 = (BigInt_ptr)malloc(sizeof(t_BigInt));
	z2 = (BigInt_ptr)malloc(sizeof(t_BigInt));
	temp1 = (BigInt_ptr)malloc(sizeof(t_BigInt));
	temp2 = (BigInt_ptr)malloc(sizeof(t_BigInt));

	splitBigInt(x, low1, high1, m);
	splitBigInt(y, low2, high2, m);

	karatsubaMult(z0, low1, low2);
	karatsubaMult(z2, high1, high2);

	bigIntAdd(temp1, low1, high1);
	bigIntAdd(temp2, low2, high2);
	karatsubaMult(z1, temp1, temp2);

	bigIntSub(temp1, z1, z0);
	bigIntSub(temp1, temp1, z2);

	for (int i = 0; i < 2 * m; i++)
	{
		bigIntAdd(z2, z2, temp1);
	}
	for (int i = 0; i < m; i++)
	{
		bigIntAdd(z0, z0, z2);
	}

	bigIntAdd(result, z0, z2);

	freeInt(low1);
	freeInt(high1);
	freeInt(low2);
	freeInt(high2);
	freeInt(z0);
	freeInt(z1);
	freeInt(z2);
	freeInt(temp1);
	freeInt(temp2);
}

/**
 * splitBigInt -
*/
void splitBigInt(BigInt_ptr source, BigInt_ptr low, BigInt_ptr high, int pos)
{
	initBigInt(low, "0");
	initBigInt(high, "0");
	low->size = pos;
	high->size = source->size - pos;
	memcpy(low->digits, source->digits, pos * sizeof(int));
	memcpy(high->digits, source->digits + pos, high->size * sizeof(int));
}
