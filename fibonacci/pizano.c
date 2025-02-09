#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// вычисление n-го числа Фибоначчи по модулю m
unsigned long long fib(unsigned n)
{
    if (n == 0)
        return 0;
    unsigned long long fst = 0, snd = 1;
    unsigned idx;
    for (idx = 2; idx <= n; idx++)
    {
        unsigned long long tmp = fst;
        fst = snd;
        snd = tmp + snd;
    }
    return snd;
}

int fib_mod(unsigned n, unsigned m)
{
    assert(m > 1);
    if (n == 0)
        return 0;
    int fst = 0; int snd = 1;
    unsigned idx;
    for (idx = 2; idx <= n; idx++)
    {
        int tmp = fst;
        fst = snd;
        snd = (tmp + snd) % m;
    }
    return snd;
}

int find_pizano_period(unsigned m)
{
    int is_01  = 0;
    int is_0   = 0;
    int is_1   = 0;
    int n      = 2;
    int cur    = 1;
    while (!is_01)
    {
        is_0 = (cur == 0) ? 1 : 0;
        cur = fib_mod(n, m);
        is_1 = (cur == 1) ? 1 : 0;
        is_01 = is_0 & is_1;
        n++;
    }
    return n - 2;
}

int main() {
    int m;
    scanf("%d", &m);

    int i = 0;
    for (; i < 20; i++)
        printf("%d ", fib_mod(i, m));

    assert(find_pizano_period(4) == 6);
    assert(fib_mod(100, 3) == fib_mod(100 % find_pizano_period(3), 3));
    
    printf("\nПериод пизано: %d\n", find_pizano_period(m));
}