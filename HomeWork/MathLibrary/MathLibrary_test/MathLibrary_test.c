#pragma warning (disable: 4996)
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "MathLibrary.h"
#include "pch.h"

#define MIN_SIZE 50
#define MAX_SIZE 10000
#define STEP_SIZE 100
#define REPEAT_COUNT 5

//функция для записи времени всех четырех сортировок для определенного размера массива
double* time_mean(int A[], int n) {
	int i, j, k, count = 0;
	double* times = (double*)malloc(sizeof(double) * 4);

	LARGE_INTEGER freq, start, end;
	QueryPerformanceFrequency(&freq);
	//загружает библиотеку
	void* dll = LoadLibrary(L"../x64\\Debug\\MathLibrary.dll");
	//проверка на NULL
	if (dll == NULL) {
		printf("Ошибка загрузки библиотеки\n");
		exit(-1);
	}

	sort_info_t* List;
	//доступ к адресу GetSortList()
	List = GetProcAddress(dll, "GetSortList")(&count);
	//проверка на NULL
	if (List == NULL) {
		printf("Ошибка доступа к адресу GetSortList()\n");
		exit(-1);
	}

	for (j = 0; j < count; j++) { //цикл по количеству сортировок
		times[j] = 0;
		for (k = 0; k < REPEAT_COUNT; k++) { //цикл по количеству повторений одной сортировки
			srand(0); //чтобы числа при повторной сортировке были те же
			for (i = 0; i < n; i++) { //заполняет массив случайными числами
				A[i] = rand();
			}

			QueryPerformanceCounter(&start); //запоминает время начала выполнения сортировки
			(*(List + j)).sort(A, n);
			QueryPerformanceCounter(&end); //запоминает время конца выполнения сортировки
			//находит время в секундах на исполнение сортировки
			double dt = (double)(end.QuadPart - start.QuadPart) / (double)freq.QuadPart;
			//записывает время на выполнение сортировки
			times[j] += dt;
		}
		times[j] = times[j] / REPEAT_COUNT; //среднее арифметическое
	}
	FreeLibrary(dll); //освобождает переменную dll от «утомительной» связи с библиотекой
	return times;
}

int main() {
	setlocale(LC_ALL, "Russian"); //чтобы числа считывались с запятой
	FILE* f; //файл для записи
	fopen_s(&f, "data.csv", "w");
	//проверка на NULL
	if (f == NULL) {
		printf("Ошибка открытия файла\n");
		exit(1);
	}
	//через ';' - чтобы разделялось на ячейки в Эксель-файле
	fprintf(f, "Размер;Слева направо;Справа налево;Бинарные вставки;Попарные вставки\n");

	time_t t;
	int A[MAX_SIZE];
	double* time;

	int i, n = MIN_SIZE;
	while (n < MAX_SIZE) {
		time = time_mean(A, n);
		fprintf(f, "%d;", n);
		for (i = 0; i < 4; i++) {
			fprintf(f, "%lf;", *(time + i));
		}
		fprintf(f, "\n");
		n += STEP_SIZE;
	}

	free(time);
	fclose(f);
	return 0;
}