#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <math.h>
#include <malloc.h>
#include <conio.h> //для getch()
#define SIZE 9

float Random(float const a, float const b) { //генерирует вещественные числа из отрезка от а до b
	return (float)rand() / RAND_MAX * (b - a) + a; //задает границы
}

void FillFloat(float arr[], int size, float const a, float const b) { //заполняет массив
	for (int i = 0; i < size; i++) {
		arr[i] = Random(a, b); //заполняет рандомными числами
	}
}

void PrintFloat(float arr[], int size) { //печатает массив с фигурными скобками
	printf("{ ");
	for (int i = 0; i < size - 1; i++) {
		printf("%.1f, ", arr[i]);
	}
	printf("%.1f", arr[size - 1]);
	printf(" }\n");
}

void WriteText(char const* filename, float arr[], int length) { //сохраняет массив в текстовый файл .txt
	FILE* fp1 = fopen(filename, "w"); //создает и открывает текстовый файл для записи
	if (fp1 == NULL) { //проверка на успешное открытие файла
		printf("Ошибка\n");
		getch(); //ожидает нажатие любой клавиши, приостанавливая работу консоли вывода
		exit(-1); //выходит из программы с кодом -1
	}
	for (int i = 0; i < length; i++) { //заполняет файл элементами массива
		fprintf(fp1, "%.1f ", arr[i]);
	}
	fclose(fp1); //закрывает файл
}

void WriteBinary(char const* filename, float arr[], int length) { //сохраняет массив в бинарный файл .bin
	FILE* fp2 = fopen(filename, "wb"); //создает и открывает бинарный файл для записи
	if (fp2 == NULL) { //проверка на успешное открытие файла
		printf("Ошибка\n");
		getch(); //ожидает нажатие любой клавиши, приостанавливая работу консоли вывода
		exit(-1); //выходит из программы с кодом -1
	}
	fwrite(arr, sizeof(arr[0]), length, fp2); //заполняет файл элементами массива
	fclose(fp2); //закрывает файл
}

float* ReadText(char const* filename, int* length) { //читает то, что было записано в текстовый файл
	FILE* fp1 = fopen(filename, "r"); //создает и открывает текстовый файл для чтения
	if (fp1 == NULL) { //проверка на успешное открытие файла
		printf("Ошибка\n");
		getch(); //ожидает нажатие любой клавиши, приостанавливая работу консоли вывода
		exit(-1); //выходит из программы с кодом -1
	}
	float* NewArray = NULL;
	NewArray = (float*)malloc(sizeof(float)); //создаёт динамический массив
	float temp; //переменная для хранения считанной информации
	fscanf(fp1, "%f", &temp); //считывает в переменную
	while (!feof(fp1)) { //аналогично "пока не дошли до конца файла"
		*length += 1;
		NewArray = (float*)realloc(NewArray, (*length) * sizeof(float)); //увеличивет размер массива
		if (NewArray == NULL) { //проверка на случай, если realloc вернет NULL
			printf("Ошибка\n");
			return 0;
		}
		*(NewArray + (*length) - 1) = temp;
		fscanf(fp1, "%f", &temp);
	}
	fclose(fp1); //закрывает файл
	return NewArray; //возвращает указатель на массив
}


float* ReadBinary(char const* filename, int* length) {
	FILE* fp2 = fopen(filename, "rb"); //создает и открывает бинарный файл для чтения
	if (fp2 == NULL) { //проверка на успешное открытие файла
		printf("Ошибка\n");
		getch(); //ожидает нажатие любой клавиши, приостанавливая работу консоли вывода
		exit(-1); //выходит из программы с кодом -1
	}
	fseek(fp2, 0, SEEK_END); //перематывает в конец файла
	int size = ftell(fp2); //узнает смещение от начала файла (в байтах)
	fseek(fp2, 0, SEEK_SET); //перематывает обратно в начало
	*length = size / sizeof(float); //получает количество элементов
	float* NewArr;
	NewArr = (float*)malloc((*length) * sizeof(float)); //создаёт динамический массив
	fread(NewArr, sizeof(float), *length, fp2);
	fclose(fp2); //закрывает файл
	return NewArr; //возвращает указатель на массив
}

void FileDump(char const* filename) { //выводит дамп памяти
	FILE* fp;
	int c, i = 0;
	fp = fopen(filename, "rb");
	if (fp == NULL) { //проверка на успешное открытие файла
		printf("Ошибка\n");
		getch(); //ожидает нажатие любой клавиши, приостанавливая работу консоли вывода
		exit(-1); //выходит из программы с кодом -1
	}
	rewind(fp); //перемещает указатель текущей позиции файла в начало
	while (!feof(fp)) { //аналогично "пока не дошли до конца файла"
		c = fgetc(fp); //считавает по байтно в переменную
		if (c == EOF) //проверка на окончание файла
			break;
		if (i % 16 == 0)
			printf("%p :", ftell(fp) - 1); //выводит смещение от начала файла в байтах
		printf("%02X ", c); //выводит 16-ричный дамп на экран
		i++;
		if (i % 16 == 0) //перевод на новую строку
			printf("\n");
	}
	fclose(fp); //закрывает файл
}

int main() {
	setlocale(LC_CTYPE, "Russian");
	printf("Тишковец Сергей, группа 5030102/20001, FIL\n");
	srand(time(NULL)); //чтобы каждый раз генерировались другие числа
	FILE* fp1; //обозначает файлы
	FILE* fp2;
	float* Arr = NULL;
	Arr = (float*)malloc(SIZE * sizeof(float)); //создаёт динамический массив

	FillFloat(Arr, SIZE, 0.0, 100.0); //получает созданный массив
	printf("Исходный массив:\n");
	PrintFloat(Arr, SIZE);
	WriteText("array.txt", Arr, SIZE);
	WriteBinary("array.bin", Arr, SIZE);

	float* NewArr1; //1 новый массив
	int l1 = 0; //длина 1 нового массива
	NewArr1 = ReadText("array.txt", &l1); //передает длину через указатель
	printf("Считанно с текстового файла:\n");
	PrintFloat(NewArr1, l1);
	free(NewArr1); //освобождает память

	float* NewArr2; //2 новый массив
	int l2 = 0; //длина 2 нового массива
	NewArr2 = ReadBinary("array.bin", &l2); //передает длину через указатель
	printf("Считанно с бинарного файла:\n");
	PrintFloat(NewArr2, l2);
	free(NewArr2); //освобождает память

	printf("\n16-ричный дамп для бинарного:\n");
	FileDump("array.bin");
	printf("\n16-ричный дамп для текстового:\n");
	FileDump("array.txt");
	return 0;
}