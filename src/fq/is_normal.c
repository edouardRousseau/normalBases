#include "main.h"

/*
 * Test if the element α is normal in F_{p^d}/F_p. 
 *
 * For that purpose, we will check if Q =  X^d - 1 and
 * P are relatively primes. P is a polynomial that
 * depends only on α.
 *
 * P = \sum_{i=0}^{d-1} α^{p^{i-1}}X^i
 *
 */

int is_normal(const fq_t elem, const fq_ctx_t field) {

	// We create the variables
	fq_poly_t P, Q, gcd; 
	slong d, i;
	d = fq_ctx_degree(field);

	// We initialize the polynomials
	fq_poly_init(P, field);
	fq_poly_init(Q, field);
	fq_poly_init(gcd, field);

	// We create a variable coef belonging to F_{p^n}
	fq_t coef;
	fq_init(coef, field);

	// coef = 1
	fq_one(coef, field);

	// We set Q to X^d
	fq_poly_set_coeff(Q, d, coef, field);

	// coef = -1
	fq_neg(coef, coef, field);

	// We set Q to X^n - 1
	fq_poly_set_coeff(Q, 0, coef, field);

	// coef = α
	fq_set(coef, elem, field);

	// We set P to α
	fq_poly_set_coeff(P, 0, coef, field);


	/* And using the Frobenius homomorphism, we set P to the polynomial
	 described at the beginning. */
	for (i = 1; i < d; i++) {
		fq_frobenius(coef, coef, 1, field);
		fq_poly_set_coeff(P, i, coef, field);
	}

	// We set gcd to gcd(P, Q)
	fq_poly_gcd(gcd, P, Q, field);

	// We compute a nonzero value if gcd = 1
	int b = fq_poly_is_one(gcd, field);

	// We clear the variables, except gcd that is needed
	fq_poly_clear(P, field);
	fq_poly_clear(Q, field);
	fq_poly_clear(gcd, field);
	fq_clear(coef, field);

	return b;
}
