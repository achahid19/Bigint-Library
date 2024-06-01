#ifndef BIGINT_H
# define BIGINT_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <unistd.h>

# define BASE 10 // La base est modifiable. (100, 1000...)

// L'ensemble des donnees du nombre entree.
typedef struct s_BigInt {
	int		base;
	int		*digits;
	int		size;
	bool	sign; // false pour positive, true pour negative
}   t_BigInt;

// Poiteur au node des donnees.
typedef t_BigInt *BigInt_ptr;

typedef struct s_opp {
	int	maxSize;
	int	aDigit;
	int	bDigit;
	int	res;
	int	borrow;
}	t_opp;

// Prototypes de l'ensemble des fonctions.

bool	initBigInt(BigInt_ptr num, const char *str);
void	printInt(BigInt_ptr num);
void	freeInt(BigInt_ptr num);
/* fonctionnalites de base */
	// Etape Une
void	bigIntAdd(BigInt_ptr resultat, BigInt_ptr a, BigInt_ptr b);
void	bigIntSub(BigInt_ptr resultat, BigInt_ptr a, BigInt_ptr b);
bool	bigIntEgal(BigInt_ptr a, BigInt_ptr b);
bool	bigIntLessThan(BigInt_ptr a, BigInt_ptr b);
	// Etapte deux
void	bigIntMult(BigInt_ptr resultat, BigInt_ptr a, BigInt_ptr b);
/* fonctionnalites utilities */
void	bigIntSameSign(BigInt_ptr resultat, BigInt_ptr a, BigInt_ptr b, bool sign);
void	doAddSameSign(t_opp operation, BigInt_ptr a, BigInt_ptr b, BigInt_ptr res);
void	doSubSameSign(t_opp operation, BigInt_ptr a, BigInt_ptr b, BigInt_ptr res);

#endif /* BIGINT_H */
