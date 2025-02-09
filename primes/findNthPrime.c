#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <math.h>

struct sieve_t
{
    unsigned       order;
    unsigned char* sieve;
};

void fill_sieve(unsigned char* sieve, unsigned N)
{
    #ifdef BYTES
    for (unsigned i = 0; i < N / 8 + 2; i++)
        sieve[i] = 0;
    #else
    for (unsigned i = 0; i < N + 2; i++)
        sieve[i] = 0;
    #endif

    unsigned start = 2;
    while (start <= N)
    {
        for (unsigned i = start * start; i <= N; i += start)
            #ifdef BYTES
            sieve[i >> 3] |= (0x80 >> (i & 0x7));
            #else
            sieve[i] = 1;
            #endif
        start++;
        #ifdef BYTES
        for (; (sieve[start >> 3] & (0x80 >> (start & 0x7))) != 0; start++) {}
        #else
        for (; sieve[start] != 0; start++) {}
        #endif
    }
    
}

// 0 - prime
struct sieve_t init_sieve(unsigned N)
{
    #ifdef BYTES
    unsigned char* sieve = malloc((N / 8 + 2) * sizeof(unsigned char));
    #else
    unsigned char* sieve = malloc((N + 2) * sizeof(unsigned char));
    #endif

    if (!sieve)
    {
        printf("Error allocating sieve array!\n");
        abort();
    }

    fill_sieve(sieve, N);

    struct sieve_t s = {}; 
    s.order = N; 
    s.sieve = sieve;
    return s;
}

void draw_sieve(struct sieve_t s, unsigned numCols)
{
    unsigned N = s.order;
    printf("Решето Эрастофена для N = %d:\n", N);
    unsigned numRows = N / numCols;
    for (unsigned irow = 0; irow < numRows; irow++)
    {
        for (unsigned i = 0; i < numCols; i++)
        {
            unsigned num_order = irow * numCols + i;
            if (num_order < 2)
                printf("* ");
            else
                #ifdef BYTES
                printf("%d ", (s.sieve[num_order >> 3] & (0x80 >> (num_order & 0x7)))
                                                          >> (7 - (num_order & 0x7)));
                #else
                printf("%d ", s.sieve[num_order]);
                #endif
        }
        printf("\n");
    }
}

int is_prime(struct sieve_t* s, unsigned N)
{
    assert(N < s->order);
    #ifdef BYTES
    return (s->sieve[N]) ? 0 : 1;
    #else
    return ((s->sieve[N >> 3] & (0x80 >> (N & 0x7)))) ? 0 : 1;
    #endif
}

void free_sieve(struct sieve_t* ps)
{
    free(ps->sieve);
    ps->sieve = 0;
    ps->order = 0;
}

unsigned long long estimate_upper_bound(unsigned long N)
{
    assert(N >= 20);
    double dN = N;
    double estim = dN * (log(dN) + log(log(dN)));
    return (unsigned long long) round(estim);
}

unsigned findNthPrime(unsigned N)
{
    unsigned upper_bound = estimate_upper_bound(N);
    struct sieve_t s = init_sieve(upper_bound);

    unsigned zero_num = 0;
    unsigned zero_cnt = 0;
    while (zero_cnt < N + 2)
    {
        #ifdef BYTES
        int zero_cond = !(s.sieve[zero_num >> 3] & (0x80 >> (zero_num & 0x7)));
        #else
        int zero_cond = !(s.sieve[zero_num]);
        #endif
        if (zero_cond)
            zero_cnt++;
        zero_num++;
    }

    return zero_num - 1;
}

int main()
{
    struct sieve_t s = init_sieve(100);
    unsigned long num;
    draw_sieve(s, 10);

    // int a;
    // scanf("%d", &a);

    // if (is_prime(&s, a))
    //     printf("Число %d %s\n", a, "простое");
    // else
    //     printf("Число %d %s\n", a, "составное");

    assert(is_prime(&s, 97) == 1);
    printf("%d", findNthPrime(1000));
    //assert(findNthPrime(1000) == 7919);

    printf("Введите порядковый номер искомого простого числа: ");
    scanf("%ld", &num);
    printf("Это число: %d", findNthPrime(num));

    free_sieve(&s);
    return 0;
}
