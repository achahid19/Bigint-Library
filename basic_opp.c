#include "bigInt.h"

void	bigIntAdd(BigInt_ptr resultat, BigInt_ptr a, BigInt_ptr b);
void	bigIntSub(BigInt_ptr resultat, BigInt_ptr a, BigInt_ptr b);
bool	bigIntEgal(BigInt_ptr a, BigInt_ptr b);
bool	bigIntLessThan(BigInt_ptr a, BigInt_ptr b);

/**
 * bigIntAdd - check le signe des deux nombres et en fonction de ce dernier
 * une fonction s'execute.
 * "A + B" est le seul cas considere avec A >= 0 et B >= 0
*/
void	bigIntAdd(BigInt_ptr resultat, BigInt_ptr a, BigInt_ptr b)
{
	if (!a || !b || !resultat)
		return ;
	resultat->digits = NULL;
	if (a->sign == b->sign)
		bigIntSameSign(resultat, a, b, false);
	else
		dprintf(2, "Erreur: Seul les nombres positives sont acceptes en addition\n");
}

/**
 * bigIntSub -
 * "A - B" on considere que A est toujours superieur ou egale a B
 * avec A >= 0 et B >= 0
*/
void bigIntSub(BigInt_ptr resultat, BigInt_ptr a, BigInt_ptr b)
{
	if (!a || !b || !resultat)
		return ;
	if (a->sign == b->sign && bigIntLessThan(b, a) == true)
		bigIntSameSign(resultat, a, b, true);
	else
		dprintf(2, "Erreur: Seul les nombres positives sont acceptes en substraction avec A >= B\n");
}

/**
 * bigIntEgal - check est ce que le nombre a
 * est egale au nombre b et returne un boolean
 * @a: nombre1
 * @b: nombre2
 * 
 * Return: true si juste sinon false
*/
bool	bigIntEgal(BigInt_ptr a, BigInt_ptr b)
{
	if (a == NULL || b == NULL)
	{
		return (false);
	}
	if (a->size != b->size || a->sign != b->sign)
	{
		return (false);
	}
	for (int index = 0; index < a->size; index++)
	{
		if (a->digits[index] != b->digits[index])
		{
			return (false);
		}
	}
	return (true);
}

/**
 * binIntLessThan - check si le nombre a est inferieur
 * au nombre b
 * @a: nombre1
 * @b: nombre2
 * 
 * Return: true si juste sinon false
*/
bool	bigIntLessThan(BigInt_ptr a, BigInt_ptr b)
{
	if (a == NULL || b == NULL)
	{
		return (false);
	}
	if (a->sign != b->sign)
	{
		return (a->sign);
	}
	else if (a->size != b->size)
	{
		if (a->size < b->size)
			return (true);
		else
			return (false);
	}
	for (int index = a->size - 1; index >= 0; index--)
	{
		if (a->digits[index] != b->digits[index])
		{
			if (a->digits[index] < b->digits[index])
				return (true);
			else
				return (false);
		}
	}
	return (false);
}
