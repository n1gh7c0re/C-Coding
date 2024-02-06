/*Программа выводит таблицу значений ряда Тейлора на заданном промежутке от a до b*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <locale.h>

long double f(long double x) {
	long double u = x * x;
	long double s = u;
	int i = 1;
	long double u_current = (u * (-1) * 4 * x * x) / ((2 * i + 1) * (2 * i + 2));
	while (s + u_current != s) {
		s += u_current;
		u = u_current;
		i++;
		u_current = (u * (-1) * 4 * x * x) / ((2 * i + 1) * (2 * i + 2));
	}
	return s;
}
double g(double x) {
	return sin(x) * sin(x);
}

void PrintTable(double a, double b, int m) {
	int m1 = m, k = 0; //k - переменная для подсчёта количества цифр в числе m
	do {
		m1 = m1 / 10;
		k++;
	} while (m1 > 0);
	printf("+");
	printf("%.*s", k + 2, "--------"); //выводит из строки "-------" не все тире, а только в количестве k + 2
	printf("+----------+---------+---------+--------------+\n");
	printf("|");
	printf("%.*s", ((k + 2)/ 2), "      "); //символ "." означает что рассматривается дробная часть
	printf("i");
	printf("%.*s", k - (((k + 2) / 2)) + 1, "      ");
	printf("|     x    |    f    |    g    |    delta     |\n");
	printf("+");
	printf("%.*s", k + 2, "--------"); //символ "*" означает что нужно вывести символ "-" (к + 2) раз
	printf("+----------+---------+---------+--------------+\n");
	for (int i = 0; i < m; i++) {
		double x = a + i * (b - a) / (m - 1);
		printf("| ");
		printf("%-*d", k, i); //знак "-" для выравнивания по левому краю
		printf(" | % 7.5lf | %7.5lf | %7.5lf | % 7.5le |\n", x, f(x), g(x), f(x) - g(x));
	}//пробел перед 7.5 позволяет записывать минусы у отрицательных чисел, у положительных просто остается пробел
}

int main(void) {
	setlocale(LC_CTYPE, "Russian");
	printf("Тишковец Сергей, группа 5030102/20001, SER: Сумма ряда\n");
	double a = 101.0, b = 100.0;
	int m = 0;
	while (fabs(a) > 1) { //проверяет модуль числа
		printf("Введите a: ");
		scanf_s("%lf", &a);
		if (fabs(a) > 1) {
			printf("Неверное значение\n");
		}
	}
	while (fabs(b) > 1) { //проверяет модуль числа
		printf("Введите b: ");
		scanf_s("%lf", &b);
		if (fabs(b) > 1) {
			printf("Неверное значение\n");
		}
	}
	while (m < 1) {
		printf("Введите m: ");
		scanf_s("%d", &m);
		if (m < 1) {
			printf("Неверное значение\n");
		}
	}
	PrintTable(a, b, m);
	return 0;
}