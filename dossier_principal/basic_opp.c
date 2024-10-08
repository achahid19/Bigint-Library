#include "bigInt.h"

void	bigIntAdd(BigInt_ptr resultat, BigInt_ptr a, BigInt_ptr b);
void	bigIntSub(BigInt_ptr resultat, BigInt_ptr a, BigInt_ptr b);
bool	bigIntEgal(BigInt_ptr a, BigInt_ptr b);
bool	bigIntLessThan(BigInt_ptr a, BigInt_ptr b);
void	bigIntMult(BigInt_ptr resultat, BigInt_ptr a, BigInt_ptr b);

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
	if (a->sign == b->sign && (bigIntLessThan(b, a) == true
		|| bigIntEgal(a, b) == true))
		bigIntSameSign(resultat, a, b, true);
	else
		dprintf(2, "Erreur: Seul les nombres positives sont acceptes en susstraction avec A >= B\n");
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

/**
 * bigIntMult -
*/
void	bigIntMult(BigInt_ptr resultat, BigInt_ptr a, BigInt_ptr b)
{
	int	res = 0;
	int	borrow;
	resultat->size = a->size + b->size;
	// calloc pour protecter contra les garbages values lors du stockage
	// des valeurs additionnees.
	resultat->digits = (int *)calloc(resultat->size, sizeof(int));
	if (a->sign == b->sign)
	{	
		if (a->sign == false)
			resultat->sign = false;
		else
			resultat->sign = true;
	}
	else
		resultat->sign = true;
	for (int index = 0; index < a->size; index++)
	{
		borrow = 0;
		for (int index1 = 0; index1 < b->size; index1++)
		{
			res = a->digits[index] * b->digits[index1] + resultat->digits[index + index1] + borrow;
			resultat->digits[index + index1] = res % 10;
			borrow = res / 10;
		}
		resultat->digits[index + b->size] += borrow;
	}
	while (resultat->size > 1 && resultat->digits[resultat->size - 1] == false)
		resultat->size--;
}
