#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <malloc.h>
#define SIZE 10

typedef int binary_op_t(int sk, int ak); //�������������� ��� int

typedef struct { //������� ���������
	binary_op_t* func2; //�������� ��������
	char* str2; //�����
	int Rez; //� ���� ��������
}SN;

int Random(int a, int b) { //���������� ����� �� ������� �� � �� b
	int x = a + rand() % (b - a + 1); //������ �������
	return x;
}

int Fill(int size, int a, int b) { //��������� ������
	int* Arr = NULL;
	Arr = (int*)malloc(size * sizeof(int)); //������ ������������ ������
	if (Arr) {
		for (int i = 0; i < size; i++) {
			Arr[i] = Random(-10, 10); //��������� ���������� �������
		}
	}
	return Arr; //���������� ��������� �� ������
}

void Print(int arr[], int size) { //�������� ������
	for (int i = 0; i < size; i++) {
		printf("%d\t", arr[i]); //����� tab
	}
}

int BinarySum(int sk, int ak) { //�������� ��������
	return sk + ak;
}

int BinaryMax(int sk, int ak) { //������������ ��������
	if (sk > ak) return sk;
	else return ak;
}

int BinaryNeg(int sk, int ak) { //���������� �������������
	return sk + (ak < 0);
}

int Accumulate(int const a[], int n, int s0, binary_op_t* op) { //������� ������, ������� �������� op
	for (int i = 0; i < n; i++) {
		s0 = op(s0, a[i]); //op - ����� �������� ��������, �������� ����� ���������
	}					   //s0 - ���������� ����������
	return s0;
}

int main() {
	setlocale(LC_CTYPE, "Russian");
	printf("�������� ������, ������ 5030102/20001, ACC\n");
	srand(time(NULL)); //����� ������ ��� �������������� ������ �����
	int* Arr = Fill(SIZE, -10, 10); //�������� ��������� ������
	Print(Arr, SIZE);
	int Sum = Accumulate(Arr, SIZE, 0, BinarySum); //�������� �����
	int Max = Accumulate(Arr, SIZE, -10, BinaryMax); //�������� ������������ ��������
	int Neg = Accumulate(Arr, SIZE, 0, BinaryNeg); //�������� ���������� �������������
	printf("\n\n�����: %d\n������������: %d\n���������� �������������: %d\n", Sum, Max, Neg);
	printf("\n\n");

	//������� ������ ��������
	SN FuncArr[3] = { {BinarySum, "�����: ", 0}, {BinaryMax, "������������: ", -10}, {BinaryNeg, "���������� �������������: ", 0} };
	for (int i = 0; i < 3; i++) { //����
		SN a = FuncArr[i]; //����� ������ ������ �����
		a.Rez = Accumulate(Arr, SIZE, a.Rez, a.func2);
		printf("%s%d\n", a.str2, a.Rez); //������� � �����, � ��������
	}
	return 0;
}