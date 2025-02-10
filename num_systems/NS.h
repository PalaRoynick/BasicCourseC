//-----------------------------------------------------------------------------
//
// C learning excercise course
//
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
#include <assert.h>
#include <stdio.h>

int print_converted(unsigned n, unsigned base)
{
    assert ((base <= 10) && (base >= 2));
    int digits[32];
    int i = 0;
    while (n > 0)
    {
        digits[i] = n % base;
	n /= base;
	i += 1;
    }
    // вывод на экран
    for (int j = i - 1; j >= 0; j--)
    {
        printf("%d", digits[j]);
    }
    printf("\n");
    return 0;
}