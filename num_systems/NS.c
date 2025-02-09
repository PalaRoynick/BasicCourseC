#include <stdlib.h>
#include <stdio.h>

#include "NS.h"

int main()
{
	int n, base, nitems;
	nitems = scanf("%d%d", &n, &base);
	if ((nitems != 2) || (base < 2) || (base > 10))
	{
		printf("Неправильный ввод! Введите два числа: раскладываемое и основание.\nОснование не может превышать 10 и быть меньше 2!");
		abort();
	}
	print_converted(n, base);
}
