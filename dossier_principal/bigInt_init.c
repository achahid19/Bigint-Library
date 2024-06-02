#include "./bigInt.h"

bool		initBigInt(BigInt_ptr num, const char *str);
static void	numBuffer(BigInt_ptr num, const char *str, int start);

/**
 * initBigInt - fonction qui gere l'initialisation
 * de l'ensemble des donnees declarees dans la struct
 * t_BigInt.
 * @num: nombre
 * @str: chaine de charactere
*/
bool	initBigInt(BigInt_ptr num, const char *str)
{
	int		length;
	size_t	start = 0;

	if (str == NULL || *str == '\0')
	{
		dprintf(2, "Valeur invalide (NULL)\n");
		return (false);
	}
	length = strlen(str);
	if (str[0] == '-')
	{
		num->sign = true;
		num->size = length - 1;
		start = 1;
	}
	else
	{
		num->sign = false;
		num->size = length;
	}
	numBuffer(num, str, start);
	return (true);
}

/**
 * num_buffer - constitue la memoire du nombre
 * et le stock en array.
 * @num: nombre
 * @str: chaine de charactere
*/
void	numBuffer(BigInt_ptr num, const char *str, int start)
{
	char	c;

	num->digits = (int *)malloc(sizeof(int) * num->size);
	if (num->digits == NULL)
	{
		dprintf(STDERR_FILENO, "Erreur d'allocation de memoire\n");
		return ;
	}
	for (int index = 0; index < num->size; index++)
	{
		c = str[index + start]; // index + start pour eviter le sign.
		if (isdigit(c) == false)
		{
			dprintf(STDERR_FILENO, "Caractere invalide: %c pour l'input: %s\n",
				str[index], str);
			free(num->digits);
			num->digits = NULL;
			return ;
		}
		// entree les digits en reverse pour faciliter les operations (addition...)
		num->digits[num->size - 1 - index] = str[index + start] - 48;
	}
	return ;
}
