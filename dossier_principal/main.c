#include "bigInt.h"

/**
 * main - Entry point
*/
int main(void)
{
	t_BigInt nombre1, nombre2, resultat, mod;

    if (initBigInt(&nombre1, "55") == false)
		return (EXIT_FAILURE);
    if (initBigInt(&nombre2, "9") == false)
	{
		freeInt(&nombre1);
		return (EXIT_FAILURE);
	}
	if (initBigInt(&mod, "10") == false)
	{
		freeInt(&nombre1);
		freeInt(&nombre2);
		return (EXIT_FAILURE);
	}
	if (nombre1.digits != NULL)
    	printf("Premier Nombre: ");
   	printInt(&nombre1);
	if (nombre2.digits != NULL)
    	printf("Deuxieme Nombre: ");
	printInt(&nombre2);
	
	bigIntAdd(&resultat, &nombre1, &nombre2);
	printInt(&resultat);

	freeInt(&resultat);
	bigIntSub(&resultat, &nombre1, &nombre2);
	printInt(&resultat);

	bool egal = bigIntEgal(&nombre1, &nombre2);
	printf("nombre1 = nombre2 => %d || false: 0 && true: 1\n", egal);

	bool less = bigIntLessThan(&nombre1, &nombre2);
	printf("nombre1 < nombre2 => %d || flase: 0 && true: 1\n", less);

	/* ---------------------------Etape Une (DONE)------------------------ */

	printf("Mult naive: ");
	bigIntMult(&resultat, &nombre1, &nombre2);
	printInt(&resultat);

	printf("karatsuba Mult: ");
	karatsubaMult(&resultat, &nombre1, &nombre2);
	printInt(&resultat);

	/* ---------------------------Etape Deux (DONE)------------------------ */

	printf("Mod: ");
	bigIntMod(&resultat, &nombre1, &nombre2);
	printInt(&resultat);

	printf("ModExp: ");
	bigIntModExp(&resultat, &nombre1, &nombre2, &mod);
	printInt(&resultat);

	/* ---------------------------Etape Trois (DONE)------------------------ */

	freeInt(&nombre1);
	freeInt(&nombre2);
	freeInt(&resultat);
	freeInt(&mod);
    return (EXIT_SUCCESS);
}
