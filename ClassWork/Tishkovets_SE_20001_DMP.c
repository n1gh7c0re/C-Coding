/*ѕрограмма выводит на экран шестнадцатеричный дамб блока пам€ти*/
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <math.h>
#define ArrSize 9

void FillInt(int a[], int size) { //заполн€ет массив чЄтными числами, начина€ с 600
	for (int i = 0; i < ArrSize; i++) {
		a[i] = 600 + 2 * i;
	}
}

void FillDouble(double a[], int size) { //заполн€ет массив чЄтными числами, начина€ с 600
	for (int i = 0; i < ArrSize; i++) {
		a[i] = 600 + (2 * i);
	}
}

void PrintInt(int a[], int size) { //печатает массив
	for (int j = 0; j < ArrSize; j++) {
		printf("%d ", a[j]);
	}
}

void PrintDouble(double a[], int size) { //печатает массив
	for (int j = 0; j < ArrSize; j++) {
		printf("%lf ", a[j]);
	}
}

void MemoryDump(void const* ptr, int size) { //печатает последовательность байт указанного блока пам€ти в 16-ричном виде
	unsigned char* ptr1 = ptr;
	for (int i = 0; i < size; i++) {
		printf("%02x ", *(ptr1 + i)); //можно и printf("%02x ", ptr[i])
	}
}

void MemoryDumb1(void const* ptr, int size) { //то же самое, только в выводит красиво, разбива€ на строки по 16 байт
	unsigned char* ptr1 = ptr;
	for (int i = 0; i < size; i++) {
		if (i % 16 == 0) printf("%p: ", ptr1 + i);
		printf("%02x ", *(ptr1 + i));
		if (i % 16 == 15) printf("\n"); //условие дл€ перехода на следующую строку
	}
}

int main() {
	setlocale(LC_CTYPE, "Russian");
	printf("“ишковец —ергей, группа 5030102/20001, DMP\n");
	int x[ArrSize] = { 0 };
	double y[ArrSize] = { 0 };
	FillInt(x, ArrSize);
	FillDouble(y, ArrSize);
	PrintInt(x, ArrSize);
	printf("\n\n");
	PrintDouble(y, ArrSize);
	printf("\n\n");
	MemoryDump(x, sizeof(x));
	printf("\n\n");
	MemoryDump(y, sizeof(y));
	printf("\n\n");
	MemoryDumb1(x, sizeof(x));
	printf("\n\n");
	MemoryDumb1(y, sizeof(y));
	return 0;
}