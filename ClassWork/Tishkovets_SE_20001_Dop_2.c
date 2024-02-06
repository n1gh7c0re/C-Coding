#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <locale.h>
#include <stdio.h>

void check(double x1, double x2, double x3) {
	const double x1_min = 1, x1_max = 100, x2_min = 1000, x2_max = 5000, x3_min = 0.1, x3_max = 0.5;
	setlocale(LC_CTYPE, "Russian");
	while ((x1 < x1_min) || (x1 > x1_max) || (x2 < x2_min) || (x2 > x2_max) || (x3 < x3_min) || (x3 > x3_max)) {
		printf("Неверно, введите три параметра: \n");
		scanf("%lf, %lf, %lf", &x1, &x2, &x3);
	}
}
int main() {
	double x1, x2, x3, s;
	const double x1_v = 10, x2_v = 0.9, x3_v = 100;
	setlocale(LC_CTYPE, "Russian");
	printf("Тишковец Сергей, группа 5030102/20001, Дополнительное задание\n");
	printf("Введите три параметра: \n");
	scanf("%lf, %lf, %lf", &x1, &x2, &x3);
	check(x1, x2, x3);
	s = (x1 * x1_v + x2 * x2_v + x3 * x3_v) / (x1_v + x2_v + x3_v);
	printf("Среднее взвешанное равно: %lf", s);
	return 0;
}