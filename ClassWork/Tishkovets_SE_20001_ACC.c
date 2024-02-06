#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <malloc.h>
#define SIZE 10

typedef int binary_op_t(int sk, int ak); //переопредел€ет тип int

typedef struct { //создает структуру
	binary_op_t* func2; //бинарна€ операци€
	char* str2; //текст
	int Rez; //с чего начинать
}SN;

int Random(int a, int b) { //генерирует числа из отрезка от а до b
	int x = a + rand() % (b - a + 1); //задает границы
	return x;
}

int Fill(int size, int a, int b) { //заполн€ет массив
	int* Arr = NULL;
	Arr = (int*)malloc(size * sizeof(int)); //создаЄт динамический массив
	if (Arr) {
		for (int i = 0; i < size; i++) {
			Arr[i] = Random(-10, 10); //заполн€ет рандомными числами
		}
	}
	return Arr; //возвращает указатель на массив
}

void Print(int arr[], int size) { //печатает массив
	for (int i = 0; i < size; i++) {
		printf("%d\t", arr[i]); //через tab
	}
}

int BinarySum(int sk, int ak) { //операци€ сложени€
	return sk + ak;
}

int BinaryMax(int sk, int ak) { //максимальное значение
	if (sk > ak) return sk;
	else return ak;
}

int BinaryNeg(int sk, int ak) { //количество отрицательных
	return sk + (ak < 0);
}

int Accumulate(int const a[], int n, int s0, binary_op_t* op) { //обходит массив, вызыва€ операци€ op
	for (int i = 0; i < n; i++) {
		s0 = op(s0, a[i]); //op - нека€ бинарна€ операци€, работает через указатель
	}					   //s0 - переменна€ накопитель
	return s0;
}

int main() {
	setlocale(LC_CTYPE, "Russian");
	printf("“ишковец —ергей, группа 5030102/20001, ACC\n");
	srand(time(NULL)); //чтобы каждый раз генерировались другие числа
	int* Arr = Fill(SIZE, -10, 10); //получает созданный массив
	Print(Arr, SIZE);
	int Sum = Accumulate(Arr, SIZE, 0, BinarySum); //получает сумму
	int Max = Accumulate(Arr, SIZE, -10, BinaryMax); //получает максимальное значение
	int Neg = Accumulate(Arr, SIZE, 0, BinaryNeg); //получает количество отрицательных
	printf("\n\n—умма: %d\nћаксимальное: %d\n оличество отрицательных: %d\n", Sum, Max, Neg);
	printf("\n\n");

	//создает массив структур
	SN FuncArr[3] = { {BinarySum, "—умма: ", 0}, {BinaryMax, "ћаксимальное: ", -10}, {BinaryNeg, " оличество отрицательных: ", 0} };
	for (int i = 0; i < 3; i++) { //цикл
		SN a = FuncArr[i]; //чтобы короче писать потом
		a.Rez = Accumulate(Arr, SIZE, a.Rez, a.func2);
		printf("%s%d\n", a.str2, a.Rez); //выводит и текст, и значени€
	}
	return 0;
}