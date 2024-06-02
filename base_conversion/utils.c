#include "./bigInt.h"


/**
 * printInt - affiche le nombre sur STDOUT (standard output)
 * @num: nombre
*/
void	printInt(BigInt_ptr num)
{
	// Protecter de dereferencer un pointeur NULL
	if (num == NULL || num->digits == NULL)
		return ;
	if (num->sign == true)
		printf("-");
	for (int index = num->size - 1; index >= 0; index--)
	{
		printf("%d", num->digits[index]);
	}
	printf("\n");
}

/**
 * freeInt - liberer la memoire occuper par le pointeur digits
 * @num: nombre
*/
void	freeInt(BigInt_ptr num)
{
	if (num == NULL)
		return ;
	if (num->digits != NULL)
		free(num->digits);
	num->digits = NULL;
}
