/*��������� ������� ������� �������� ���� ������� �� �������� ���������� �� a �� b*/
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
	int m1 = m, k = 0; //k - ���������� ��� �������� ���������� ���� � ����� m
	do {
		m1 = m1 / 10;
		k++;
	} while (m1 > 0);
	printf("+");
	printf("%.*s", k + 2, "--------"); //������� �� ������ "-------" �� ��� ����, � ������ � ���������� k + 2
	printf("+----------+---------+---------+--------------+\n");
	printf("|");
	printf("%.*s", ((k + 2)/ 2), "      "); //������ "." �������� ��� ��������������� ������� �����
	printf("i");
	printf("%.*s", k - (((k + 2) / 2)) + 1, "      ");
	printf("|     x    |    f    |    g    |    delta     |\n");
	printf("+");
	printf("%.*s", k + 2, "--------"); //������ "*" �������� ��� ����� ������� ������ "-" (� + 2) ���
	printf("+----------+---------+---------+--------------+\n");
	for (int i = 0; i < m; i++) {
		double x = a + i * (b - a) / (m - 1);
		printf("| ");
		printf("%-*d", k, i); //���� "-" ��� ������������ �� ������ ����
		printf(" | % 7.5lf | %7.5lf | %7.5lf | % 7.5le |\n", x, f(x), g(x), f(x) - g(x));
	}//������ ����� 7.5 ��������� ���������� ������ � ������������� �����, � ������������� ������ �������� ������
}

int main(void) {
	setlocale(LC_CTYPE, "Russian");
	printf("�������� ������, ������ 5030102/20001, SER: ����� ����\n");
	double a = 101.0, b = 100.0;
	int m = 0;
	while (fabs(a) > 1) { //��������� ������ �����
		printf("������� a: ");
		scanf_s("%lf", &a);
		if (fabs(a) > 1) {
			printf("�������� ��������\n");
		}
	}
	while (fabs(b) > 1) { //��������� ������ �����
		printf("������� b: ");
		scanf_s("%lf", &b);
		if (fabs(b) > 1) {
			printf("�������� ��������\n");
		}
	}
	while (m < 1) {
		printf("������� m: ");
		scanf_s("%d", &m);
		if (m < 1) {
			printf("�������� ��������\n");
		}
	}
	PrintTable(a, b, m);
	return 0;
}