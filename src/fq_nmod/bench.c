/*
 *      BENCHMARK
 *
 * Benchmark the functions 
 *
 *  - naive
 *  - normal_random
 *  - luneburg
 *  - lenstra
 *
 * in the field F_{p^d} where p is a fixed prime
 * number and d grows from 2 to max. In order to
 * `normal random` to work, we must have p > 2d(d-1).
 */

#include "main.h"

void main() {

    // variables
    timeit_t t;
    slong d = 2;
    fq_nmod_ctx_t field;
    fq_nmod_t res;

    // parameters of the benchmark
    fmpz_t p;
    fmpz_init(p);
    slong max;

    // Choice of parameters :
    fmpz_set_ui(p, 90001);
    max = 300;

    // We open the file `bench.txt`
    FILE *file;
    file = fopen("bench2.txt", "a");

    flint_fprintf(file, "d    naive    normal_random\n"); 


    while (d < max) {
	flint_printf("d : %wd\n", d);
        flint_fprintf(file, "%wd    ", d);

        fq_nmod_ctx_init(field, p, d, "X");
        fq_nmod_init(res, field);

        timeit_start(t);
        naive(res, field);
        timeit_stop(t);
        flint_fprintf(file, "%wd    ", t->wall);

        timeit_start(t);
        normal_random(res, field);
        timeit_stop(t);
        flint_fprintf(file, "%wd    \n", t->wall);

        fq_nmod_clear(res, field);
        fq_nmod_ctx_clear(field);

        d++;
    }

    // We close the file
    fclose(file);
}
