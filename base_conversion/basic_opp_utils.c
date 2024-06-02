#include "./bigInt.h"

void	bigIntSameSign(BigInt_ptr resultat, BigInt_ptr a, BigInt_ptr b, bool sign);
void	doAddSameSign(t_opp operation, BigInt_ptr a, BigInt_ptr b, BigInt_ptr res);
void	doSubSameSign(t_opp operation, BigInt_ptr a, BigInt_ptr b, BigInt_ptr res);

/**
 * bigIntSameSign - allocation de la memoire du resultat et lancement
 * de l'Algo doAddOpp.
 * for addition: false sign
 * for substraction: true sign
*/
void	bigIntSameSign(BigInt_ptr resultat, BigInt_ptr a, BigInt_ptr b,
			bool sign)
{
	t_opp	operation;

	operation.borrow = 0;
	if (a->size < b->size)
		operation.maxSize = b->size;
	else
		operation.maxSize = a->size;
	if (sign == false)
		resultat->digits = (int *)malloc(sizeof(int) * (operation.maxSize + 1));
	else
		resultat->digits = (int *)malloc(sizeof(int) * operation.maxSize);
	resultat->size = operation.maxSize;
	resultat->base = BASE;
	resultat->sign = a->sign;
	if (sign == false)
		doAddSameSign(operation, a, b, resultat);
	else if (sign == true)
		doSubSameSign(operation, a, b, resultat);
}

/**
 * doAddOpp - Effectue l'operation de la operation naive, avec des nombres
 * de meme signe + ajustable au changement du BASE
*/
void	doAddSameSign(t_opp operation, BigInt_ptr a,
			BigInt_ptr b, BigInt_ptr resultat)
{
	for (int index = 0; index < operation.maxSize; index++)
	{
		if (index < a->size)
			operation.aDigit = a->digits[index];
		else
			operation.aDigit = 0;
		if (index < b->size)
			operation.bDigit = b->digits[index];
		else
			operation.bDigit = 0;
		operation.res = operation.aDigit + operation.bDigit + operation.borrow;
		resultat->digits[index] = operation.res % BASE;
		operation.borrow = operation.res / BASE;
	}
	if (operation.borrow != 0)
	{
		resultat->digits[resultat->size++] = operation.borrow;
	}
}

/**
 * doSubSameSign -
*/
void	doSubSameSign(t_opp operation, BigInt_ptr a,
			BigInt_ptr b, BigInt_ptr resultat)
{
	for (int index = 0; index < operation.maxSize; index++)
	{
		operation.aDigit = a->digits[index];
		if (index < b->size)
			operation.bDigit = b->digits[index];
		else
			operation.bDigit = 0;
		operation.res = operation.aDigit - operation.bDigit - operation.borrow;
		if (operation.res < 0)
		{
			operation.res += BASE;
			operation.borrow = 1;
		}
		else
			operation.borrow  = 0;
		resultat->digits[index] = operation.res;
	}
	while (resultat->size > 1 && resultat->digits[resultat->size - 1] == false)
	{
		resultat->size--;
	}
}
