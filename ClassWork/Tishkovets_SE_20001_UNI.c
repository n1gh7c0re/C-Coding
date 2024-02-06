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


typedef enum { //��������� �� ����� �����
	CIRCLE,
	RECTAN,
	POLYG,
	NSHAPE
}shape_t;

typedef enum { //��������� �� ������
	RED,
	GREEN,
	BLUE,
	NCOLOR
}color_t;

//��������� ��� ��������
typedef struct {
	float R; //������
}circle_t;

typedef struct {
	float W; //������
	float H; //������
}rectan_t;

typedef struct {
	int n; //���������� ������
	float a; //������ �������
}polyg_t;

//��������� ������� ��������
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
	printf("�������� ������, ������ 5030102/20001, FIL, ���� ����� 3\n");

	char* FN = "uni_shapes03.bin";
	FILE* fp = fopen(FN, "rb");
	if (fp == NULL) { //�������� �� �������� �������� �����
		printf("������\n");
		getch(); //������� ������� ����� �������, ��������������� ������ ������� ������
		exit(-1); //������� �� ��������� � ����� -1
	}
	fseek(fp, 0, SEEK_END); //������������ � ����� �����
	int size = ftell(fp); //������ �������� �� ������ ����� (� ������)
	fseek(fp, 0, SEEK_SET); //������������ ������� � ������
	int length = size / sizeof(figure); //�������� ���������� ���������
	figure* Arr;
	Arr = (figure*)malloc(length * sizeof(figure)); //������ ������������ ������
	if (Arr) { //�������� �� NULL
		fread(Arr, sizeof(figure), length, fp); //��������� � ������ ���������� ��������� �����
	}
	printf("\n���������� ���������: %d", length);
	int count1 = 0, count2 = 0, count3 = 0; //����, �������������, �������������
	int count4 = 0, count5 = 0, count6 = 0; //�������, �������, �����
	float s1 = 0.0, s2 = 0.0, s3 = 0.0;
	if (Arr) { //�������� �� NULL
		//���� ����� � �� �������
		for (int i = 0; i < length; i++) { //��� ������
			if (Arr[i].vid == CIRCLE) {
				count1++;
				s1 += (double)Arr[i].nabor.CT.R * (double)Arr[i].nabor.CT.R * M_PI;
			}
		}
		for (int i = 0; i < length; i++) { //��� ���������������
			if (Arr[i].vid == RECTAN) {
				count2++;
				s2 += (float)Arr[i].nabor.RT.H * (float)Arr[i].nabor.RT.W;
			}
		}
		for (int i = 0; i < length; i++) { //��� ���������������
			if (Arr[i].vid == POLYG) {
				count3++;
				s3 += ((double)Arr[i].nabor.PT.a * (double)Arr[i].nabor.PT.a * (double)Arr[i].nabor.PT.n * cos(180 / (double)Arr[i].nabor.PT.n)) / (4 * (sin(180 / (double)Arr[i].nabor.PT.n)));
			}
		}
		//�����
		for (int i = 0; i < length; i++) { //��� ��������
			if (Arr[i].color == RED) {
				count4++;
			}
		}
		for (int i = 0; i < length; i++) { //��� ��������
			if (Arr[i].color == GREEN) {
				count5++;
			}
		}
		for (int i = 0; i < length; i++) { //��� ������
			if (Arr[i].color == BLUE) {
				count6++;
			}
		}
	}
	printf("\n������: %d\n���������������: %d\n���������������: %d", count1, count2, count3);
	printf("\n\n�������: %d\n�������: %d\n�����: %d", count4, count5, count6);
	printf("\n\n��������� �������\n������: %.2f\n���������������: %.2f\n���������������: %.2f", s1, s2, s3);
	fclose(fp); //��������� ����
	free(Arr); //����������� ������
	return 0;
}