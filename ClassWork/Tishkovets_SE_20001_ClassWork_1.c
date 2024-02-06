/*1-я классная работа во 2 семестре - содержит 3 задания*/
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#define SIZE 3

void Print(int* Arr, int size) { //выводит массив на экран
	for (int i = 0; i < size; i++) {
		printf("%d ", Arr[i]);
	}
	printf("\n");
}

int* PlusArr(int* iLArr1, int* iLArr2, int size) { //суммирует элементы двух массивов
	int* Arr = NULL;
	Arr = (int*)malloc(size * sizeof(int));
	if (Arr) {
		for (int i = 0; i < size; i++) {
			Arr[i] = iLArr1[i] + iLArr2[i];
		}
	}
	return Arr; //возвращает указатель на массив
}

int Sum(int* a, int* b) { //находит сумму двух чисел (уже измененная под 5 пункт)
	return *a + *b;
}

int NeSum(int* a, int* b) { //находит разность двух чисел (уже измененная под 5 пункт)
	*b ^= *a; //обмен значений с помощью XOR
	*a ^= *b;
	*b ^= *a;
	return *a - *b; 
}

int main() {
	setlocale(LC_CTYPE, "Russian");
	printf("Тишковец Сергей, группа 5030102/20001, ClassWork_1\n\t1-е Задание\n");
	//1-е Задание: работа с переменными и указателями на них
	double a = 5.5; //1-я
	double* dp1 = &a; //присваивает значение указателю
	int b = 10; //2-я
	int* dp2 = &b; //присваивает значение указателю
	printf("1-е значение: %lf\nАдрес: %p\nРазмер: %d байт\n", *dp1, dp1, sizeof(dp1)); //указатели
	printf("2-е значение: %d\nАдрес: %p\nРазмер: %d байт\n\n", *dp2, dp2, sizeof(dp2));
	printf("1-я переменная: %lf\nРазмер: %d байт\n", a, sizeof(a)); //переменные
	printf("2-я переменная: %d\nРазмер: %d байт\n\n", b, sizeof(b));
	*dp1 = 2.2; //новые значения
	*dp2 = 3;
	printf("Новые значения:\n1-я: %lf\n2-я: %d\n", *dp1, *dp2);
	printf("---------------------------\n\t2-е Задание\n");
	//2-е Задание: получение третьего массива, полученного суммированием двух исходных
	int iArr1[SIZE] = { 11, 13, 15 }; //1-й массив
	int iArr2[SIZE] = { 12, 14, 16 }; //2-й массив
	Print(iArr1, SIZE);
	Print(iArr2, SIZE);
	int* Arr = PlusArr(iArr1, iArr2, SIZE); //получает указатель на созданный массив
	Print(Arr, SIZE); //печатает результат сложения двух массивов
	int sum = 0; //счётчик для суммы
	for (int j = 0; j < SIZE; j++) { //находит сумму элементов 3-го массива
		sum += Arr[j];
	}
	int* p = &Arr; //запоминает указатель
	Arr = (int*)realloc(Arr, (SIZE + 1) * sizeof(int)); //изменяет размер массива на 1
	if (Arr) { //если не 0
		*(Arr + SIZE) = sum; //записывает на последнее место сумму
		Print(Arr, SIZE + 1);
		free(Arr);
	}
	else {
		*(p + SIZE) = sum; //записывает на последнее место сумму
		Print(p, SIZE + 1);
		free(p);
	}
	printf("---------------------------\n\t3-е Задание\n");
	//3-е Задание: сумма и разность двух чисел
	int c = 0, d = 0, res = 0;
	printf("Введите первое число: ");
	scanf("%d", &c);
	printf("Введите второе число: ");
	scanf("%d", &d);
	int(*operation)(int*, int*); //определяет указатель на функцию
	operation = Sum; //указатель указывает на функцию Sum
	res = operation(&c, &d); //вызывает функцию (через указатели)
	printf("Сумма = %d\n", res);
	operation = NeSum; //указатель указывает на функцию NeSum
	res = operation(&c, &d); //вызывает функцию (через указатели)
	printf("Разность = %d\n", res);
	printf("Значения аргументов: %d и %d", c, d);
	return 0;
}