#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <malloc.h>
#include <conio.h>


typedef enum { //структура из типов фигур
	CIRCLE,
	RECTAN,
	POLYG,
	NSHAPE
}shape_t;

typedef enum { //структура из цветов
	RED,
	GREEN,
	BLUE,
	NCOLOR
}color_t;

//структуры для площадей
typedef struct {
	float R; //радиус
}circle_t;

typedef struct {
	float W; //ширина
	float H; //высота
}rectan_t;

typedef struct {
	int n; //количество сторон
	float a; //размер стороны
}polyg_t;

//структура наборов размеров
typedef union {
	circle_t CT;
	rectan_t RT;
	polyg_t PT;
}shapestr_t;

typedef struct {
	shape_t vid;
	color_t color;
	shapestr_t nabor;
}figure;

int main() {
	setlocale(LC_CTYPE, "Russian");
	printf("Тишковец Сергей, группа 5030102/20001, FIL, файл номер 3\n");

	char* FN = "uni_shapes03.bin";
	FILE* fp = fopen(FN, "rb");
	if (fp == NULL) { //проверка на успешное открытие файла
		printf("Ошибка\n");
		getch(); //ожидает нажатие любой клавиши, приостанавливая работу консоли вывода
		exit(-1); //выходит из программы с кодом -1
	}
	fseek(fp, 0, SEEK_END); //перематывает в конец файла
	int size = ftell(fp); //узнает смещение от начала файла (в байтах)
	fseek(fp, 0, SEEK_SET); //перематывает обратно в начало
	int length = size / sizeof(figure); //получает количество элементов
	figure* Arr;
	Arr = (figure*)malloc(length * sizeof(figure)); //создаёт динамический массив
	if (Arr) { //проверка на NULL
		fread(Arr, sizeof(figure), length, fp); //считывает в массив содержимое бинарного файла
	}
	printf("\nКоличество элементов: %d", length);
	int count1 = 0, count2 = 0, count3 = 0; //круг, прямоугольник, многоугольник
	int count4 = 0, count5 = 0, count6 = 0; //красный, зеленый, синий
	float s1 = 0.0, s2 = 0.0, s3 = 0.0;
	if (Arr) { //проверка на NULL
		//типы фигур и их площади
		for (int i = 0; i < length; i++) { //для кругов
			if (Arr[i].vid == CIRCLE) {
				count1++;
				s1 += (double)Arr[i].nabor.CT.R * (double)Arr[i].nabor.CT.R * M_PI;
			}
		}
		for (int i = 0; i < length; i++) { //для прямоугольников
			if (Arr[i].vid == RECTAN) {
				count2++;
				s2 += (float)Arr[i].nabor.RT.H * (float)Arr[i].nabor.RT.W;
			}
		}
		for (int i = 0; i < length; i++) { //для многоугольников
			if (Arr[i].vid == POLYG) {
				count3++;
				s3 += ((double)Arr[i].nabor.PT.a * (double)Arr[i].nabor.PT.a * (double)Arr[i].nabor.PT.n * cos(180 / (double)Arr[i].nabor.PT.n)) / (4 * (sin(180 / (double)Arr[i].nabor.PT.n)));
			}
		}
		//цвета
		for (int i = 0; i < length; i++) { //для красного
			if (Arr[i].color == RED) {
				count4++;
			}
		}
		for (int i = 0; i < length; i++) { //для зеленого
			if (Arr[i].color == GREEN) {
				count5++;
			}
		}
		for (int i = 0; i < length; i++) { //для синего
			if (Arr[i].color == BLUE) {
				count6++;
			}
		}
	}
	printf("\nКругов: %d\nПрямоугольников: %d\nМногоугольников: %d", count1, count2, count3);
	printf("\n\nКрасных: %d\nЗеленых: %d\nСиних: %d", count4, count5, count6);
	printf("\n\nСуммарная площадь\nКругов: %.2f\nПрямоугольников: %.2f\nМногоугольников: %.2f", s1, s2, s3);
	fclose(fp); //закрывает файл
	free(Arr); //освобождает память
	return 0;
}