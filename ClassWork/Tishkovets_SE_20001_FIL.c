#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <math.h>
#include <malloc.h>
#include <conio.h> //��� getch()
#define SIZE 9

float Random(float const a, float const b) { //���������� ������������ ����� �� ������� �� � �� b
	return (float)rand() / RAND_MAX * (b - a) + a; //������ �������
}

void FillFloat(float arr[], int size, float const a, float const b) { //��������� ������
	for (int i = 0; i < size; i++) {
		arr[i] = Random(a, b); //��������� ���������� �������
	}
}

void PrintFloat(float arr[], int size) { //�������� ������ � ��������� ��������
	printf("{ ");
	for (int i = 0; i < size - 1; i++) {
		printf("%.1f, ", arr[i]);
	}
	printf("%.1f", arr[size - 1]);
	printf(" }\n");
}

void WriteText(char const* filename, float arr[], int length) { //��������� ������ � ��������� ���� .txt
	FILE* fp1 = fopen(filename, "w"); //������� � ��������� ��������� ���� ��� ������
	if (fp1 == NULL) { //�������� �� �������� �������� �����
		printf("������\n");
		getch(); //������� ������� ����� �������, ��������������� ������ ������� ������
		exit(-1); //������� �� ��������� � ����� -1
	}
	for (int i = 0; i < length; i++) { //��������� ���� ���������� �������
		fprintf(fp1, "%.1f ", arr[i]);
	}
	fclose(fp1); //��������� ����
}

void WriteBinary(char const* filename, float arr[], int length) { //��������� ������ � �������� ���� .bin
	FILE* fp2 = fopen(filename, "wb"); //������� � ��������� �������� ���� ��� ������
	if (fp2 == NULL) { //�������� �� �������� �������� �����
		printf("������\n");
		getch(); //������� ������� ����� �������, ��������������� ������ ������� ������
		exit(-1); //������� �� ��������� � ����� -1
	}
	fwrite(arr, sizeof(arr[0]), length, fp2); //��������� ���� ���������� �������
	fclose(fp2); //��������� ����
}

float* ReadText(char const* filename, int* length) { //������ ��, ��� ���� �������� � ��������� ����
	FILE* fp1 = fopen(filename, "r"); //������� � ��������� ��������� ���� ��� ������
	if (fp1 == NULL) { //�������� �� �������� �������� �����
		printf("������\n");
		getch(); //������� ������� ����� �������, ��������������� ������ ������� ������
		exit(-1); //������� �� ��������� � ����� -1
	}
	float* NewArray = NULL;
	NewArray = (float*)malloc(sizeof(float)); //������ ������������ ������
	float temp; //���������� ��� �������� ��������� ����������
	fscanf(fp1, "%f", &temp); //��������� � ����������
	while (!feof(fp1)) { //���������� "���� �� ����� �� ����� �����"
		*length += 1;
		NewArray = (float*)realloc(NewArray, (*length) * sizeof(float)); //���������� ������ �������
		if (NewArray == NULL) { //�������� �� ������, ���� realloc ������ NULL
			printf("������\n");
			return 0;
		}
		*(NewArray + (*length) - 1) = temp;
		fscanf(fp1, "%f", &temp);
	}
	fclose(fp1); //��������� ����
	return NewArray; //���������� ��������� �� ������
}


float* ReadBinary(char const* filename, int* length) {
	FILE* fp2 = fopen(filename, "rb"); //������� � ��������� �������� ���� ��� ������
	if (fp2 == NULL) { //�������� �� �������� �������� �����
		printf("������\n");
		getch(); //������� ������� ����� �������, ��������������� ������ ������� ������
		exit(-1); //������� �� ��������� � ����� -1
	}
	fseek(fp2, 0, SEEK_END); //������������ � ����� �����
	int size = ftell(fp2); //������ �������� �� ������ ����� (� ������)
	fseek(fp2, 0, SEEK_SET); //������������ ������� � ������
	*length = size / sizeof(float); //�������� ���������� ���������
	float* NewArr;
	NewArr = (float*)malloc((*length) * sizeof(float)); //������ ������������ ������
	fread(NewArr, sizeof(float), *length, fp2);
	fclose(fp2); //��������� ����
	return NewArr; //���������� ��������� �� ������
}

void FileDump(char const* filename) { //������� ���� ������
	FILE* fp;
	int c, i = 0;
	fp = fopen(filename, "rb");
	if (fp == NULL) { //�������� �� �������� �������� �����
		printf("������\n");
		getch(); //������� ������� ����� �������, ��������������� ������ ������� ������
		exit(-1); //������� �� ��������� � ����� -1
	}
	rewind(fp); //���������� ��������� ������� ������� ����� � ������
	while (!feof(fp)) { //���������� "���� �� ����� �� ����� �����"
		c = fgetc(fp); //��������� �� ������ � ����������
		if (c == EOF) //�������� �� ��������� �����
			break;
		if (i % 16 == 0)
			printf("%p :", ftell(fp) - 1); //������� �������� �� ������ ����� � ������
		printf("%02X ", c); //������� 16-������ ���� �� �����
		i++;
		if (i % 16 == 0) //������� �� ����� ������
			printf("\n");
	}
	fclose(fp); //��������� ����
}

int main() {
	setlocale(LC_CTYPE, "Russian");
	printf("�������� ������, ������ 5030102/20001, FIL\n");
	srand(time(NULL)); //����� ������ ��� �������������� ������ �����
	FILE* fp1; //���������� �����
	FILE* fp2;
	float* Arr = NULL;
	Arr = (float*)malloc(SIZE * sizeof(float)); //������ ������������ ������

	FillFloat(Arr, SIZE, 0.0, 100.0); //�������� ��������� ������
	printf("�������� ������:\n");
	PrintFloat(Arr, SIZE);
	WriteText("array.txt", Arr, SIZE);
	WriteBinary("array.bin", Arr, SIZE);

	float* NewArr1; //1 ����� ������
	int l1 = 0; //����� 1 ������ �������
	NewArr1 = ReadText("array.txt", &l1); //�������� ����� ����� ���������
	printf("�������� � ���������� �����:\n");
	PrintFloat(NewArr1, l1);
	free(NewArr1); //����������� ������

	float* NewArr2; //2 ����� ������
	int l2 = 0; //����� 2 ������ �������
	NewArr2 = ReadBinary("array.bin", &l2); //�������� ����� ����� ���������
	printf("�������� � ��������� �����:\n");
	PrintFloat(NewArr2, l2);
	free(NewArr2); //����������� ������

	printf("\n16-������ ���� ��� ���������:\n");
	FileDump("array.bin");
	printf("\n16-������ ���� ��� ����������:\n");
	FileDump("array.txt");
	return 0;
}