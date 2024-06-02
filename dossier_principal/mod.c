#include "./bigInt.h"

void	bigIntMod(BigInt_ptr res, BigInt_ptr a, BigInt_ptr b);
void	bigIntModExp(BigInt_ptr result, BigInt_ptr base,
				BigInt_ptr exp, BigInt_ptr mod);

/**
 * bigIntMod -
*/
void    bigIntMod(BigInt_ptr res, BigInt_ptr a, BigInt_ptr b)
{
	BigInt_ptr	tmp;
	t_opp		opp;

	opp.borrow = 0;
	opp.res = 0;
	res->size = a->size;
	opp.maxSize = res->size;
	res->sign = a->sign;
	res->digits = (int *)malloc(sizeof(int) * res->size);
	memcpy(res->digits, a->digits, sizeof(int) * res->size);
	while (bigIntLessThan(res, b) == false)
	{
		tmp = malloc(sizeof(t_BigInt));
		tmp->size = opp.maxSize;
		tmp->digits = calloc(tmp->size, sizeof(int));
		doSubSameSign(opp, res, b, tmp);
		freeInt(res);
		res->size = tmp->size;
		res->sign = tmp->sign;
		res->digits = tmp->digits;
		free(tmp);
	}
}

/**
 * bigIntModExp -
 */
void bigIntModExp(BigInt_ptr result, BigInt_ptr base, BigInt_ptr exp, BigInt_ptr mod)
{
	BigInt_ptr	one, baseMod, tmp, expDiv2;
	int			carry = 0, current;
	
	one = malloc(sizeof(t_BigInt));
	initBigInt(one, "1");
	
	baseMod = malloc(sizeof(t_BigInt));
	bigIntMod(baseMod, base, mod);
	initBigInt(result, "1");
	while (!bigIntEgal(exp, one))
	{
		if (exp->digits[0] % 2 == 1)
		{
			tmp = malloc(sizeof(t_BigInt));
			bigIntMult(tmp, result, baseMod);
			bigIntMod(result, tmp, mod);
			freeInt(tmp);
		}
		expDiv2 = malloc(sizeof(t_BigInt));
		initBigInt(expDiv2, "0");
		expDiv2->size = exp->size;
		expDiv2->digits = (int *)malloc(expDiv2->size * sizeof(int));
		for (int i = exp->size - 1; i >= 0; i--)
		{
			current = exp->digits[i] + carry * 10;
			expDiv2->digits[i] = current / 2;
			carry = current % 2;
		}
		while (expDiv2->size > 1 && expDiv2->digits[expDiv2->size - 1] == 0)
				expDiv2->size--;
		tmp = malloc(sizeof(t_BigInt));
		bigIntMult(tmp, baseMod, baseMod);
		bigIntMod(baseMod, tmp, mod);
		freeInt(tmp);
		freeInt(exp);
		*exp = *expDiv2;
		free(expDiv2);
	}
	freeInt(baseMod);
	freeInt(one);
}
