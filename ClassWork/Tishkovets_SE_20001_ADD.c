/*Задание - сложить в столбик 2 числа с учётом переноса цифры в следующий разряд в случае переполнения*/
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <locale.h>
#define LENGTH 10

int Fill(int number, int digits[], int length) { //разбивает введённое число по цифрам
	int s = 0; //переменная s для подсчёта нулевых элементов массива
	for(int i = 0; i < length; i++){
		digits[i] = number % 10;
		number = number / 10;
	}
	for (int i = length - 1; i >= 0; i--) { //цикл для подсчёта нулевых элементов массива
		if (digits[i] == 0) {
			s += 1;
		} else break;
	}
	return length - s; //выводим разницу, так как необходимо количество значимых цифр
}

void Print(int const digits[], int length, int max) { //выводит массив из функции Fill в обратном порядке и без нулей
	int l =  0;                                       //то есть выводит исходное число, разбитое на цифры
	for(int i = 0;i < max - length; i++){
		printf("  ");
	}
	for (int i = length - 1; i >= 0; i--) {
		l = digits[i];
		printf("%i ", l);
	}
	printf("\n");
}

int Add(int const x[], int const y[], int xy[], int length) { //складывает 2 числа, но сумма пока что записана справа налево
	int m = 0, n = 0, s = 0; //переменная s аналогична переменной s в функции Fill
	for (int i = 0; i < length; i++) {
		m = x[i] + y[i];
		xy[i] = m % 10 + n;
		n = m / 10;
	}
	m = 0;
	for (int i = length - 1; i >= 0; i--) {
		if (xy[i] == 0) {
			m += 1;
		}
		else break;
	} 
	return length - m;
}

int Collect(int const digits[], int length) { //записывает сумму из функции Add в нужном порядке
	int n = 0;
	for (int i = length - 1; i >= 0; i--) {
		n *= 10;
		n += digits[i];
	}
	return n;
}

int main() {
	setlocale(LC_CTYPE, "Russian");
	printf("Тишковец Сергей, группа 5030102/20001, ADD: Сложение в столбик\n");
	int a = 0, b = 0, c = 0, f = 0, p = 0, x = 0;
	int A[LENGTH] = { 0 };
	int B[LENGTH] = { 0 };
	int C[LENGTH] = { 0 };
	printf("Введите первое число: ");
	scanf("%i", &a);
	printf("Введите второе число: ");
	scanf("%i", &b);
	f = Fill(a, A, LENGTH);
	p = Fill(b, B, LENGTH);
	x = Add(A, B, C, LENGTH);
	int max1 = f;
	if(max1 < p) {
		max1 = p;
	}
	if (max1 < x) {
		max1 = x;
	}
	c = a + b;
	int y = Collect(C, LENGTH);
	printf(" ");
	Print(A, f, max1);
	printf("+");
	Print(B, p, max1);
	printf(" ");
	for (int i = 0; i < max1; i++) {
		printf("--");
	}
	printf("\n ");
	Print(C, max1, x);
	return 0;
}