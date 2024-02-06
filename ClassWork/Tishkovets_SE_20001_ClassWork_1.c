/*1-� �������� ������ �� 2 �������� - �������� 3 �������*/
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#define SIZE 3

void Print(int* Arr, int size) { //������� ������ �� �����
	for (int i = 0; i < size; i++) {
		printf("%d ", Arr[i]);
	}
	printf("\n");
}

int* PlusArr(int* iLArr1, int* iLArr2, int size) { //��������� �������� ���� ��������
	int* Arr = NULL;
	Arr = (int*)malloc(size * sizeof(int));
	if (Arr) {
		for (int i = 0; i < size; i++) {
			Arr[i] = iLArr1[i] + iLArr2[i];
		}
	}
	return Arr; //���������� ��������� �� ������
}

int Sum(int* a, int* b) { //������� ����� ���� ����� (��� ���������� ��� 5 �����)
	return *a + *b;
}

int NeSum(int* a, int* b) { //������� �������� ���� ����� (��� ���������� ��� 5 �����)
	*b ^= *a; //����� �������� � ������� XOR
	*a ^= *b;
	*b ^= *a;
	return *a - *b; 
}

int main() {
	setlocale(LC_CTYPE, "Russian");
	printf("�������� ������, ������ 5030102/20001, ClassWork_1\n\t1-� �������\n");
	//1-� �������: ������ � ����������� � ����������� �� ���
	double a = 5.5; //1-�
	double* dp1 = &a; //����������� �������� ���������
	int b = 10; //2-�
	int* dp2 = &b; //����������� �������� ���������
	printf("1-� ��������: %lf\n�����: %p\n������: %d ����\n", *dp1, dp1, sizeof(dp1)); //���������
	printf("2-� ��������: %d\n�����: %p\n������: %d ����\n\n", *dp2, dp2, sizeof(dp2));
	printf("1-� ����������: %lf\n������: %d ����\n", a, sizeof(a)); //����������
	printf("2-� ����������: %d\n������: %d ����\n\n", b, sizeof(b));
	*dp1 = 2.2; //����� ��������
	*dp2 = 3;
	printf("����� ��������:\n1-�: %lf\n2-�: %d\n", *dp1, *dp2);
	printf("---------------------------\n\t2-� �������\n");
	//2-� �������: ��������� �������� �������, ����������� ������������� ���� ��������
	int iArr1[SIZE] = { 11, 13, 15 }; //1-� ������
	int iArr2[SIZE] = { 12, 14, 16 }; //2-� ������
	Print(iArr1, SIZE);
	Print(iArr2, SIZE);
	int* Arr = PlusArr(iArr1, iArr2, SIZE); //�������� ��������� �� ��������� ������
	Print(Arr, SIZE); //�������� ��������� �������� ���� ��������
	int sum = 0; //������� ��� �����
	for (int j = 0; j < SIZE; j++) { //������� ����� ��������� 3-�� �������
		sum += Arr[j];
	}
	int* p = &Arr; //���������� ���������
	Arr = (int*)realloc(Arr, (SIZE + 1) * sizeof(int)); //�������� ������ ������� �� 1
	if (Arr) { //���� �� 0
		*(Arr + SIZE) = sum; //���������� �� ��������� ����� �����
		Print(Arr, SIZE + 1);
		free(Arr);
	}
	else {
		*(p + SIZE) = sum; //���������� �� ��������� ����� �����
		Print(p, SIZE + 1);
		free(p);
	}
	printf("---------------------------\n\t3-� �������\n");
	//3-� �������: ����� � �������� ���� �����
	int c = 0, d = 0, res = 0;
	printf("������� ������ �����: ");
	scanf("%d", &c);
	printf("������� ������ �����: ");
	scanf("%d", &d);
	int(*operation)(int*, int*); //���������� ��������� �� �������
	operation = Sum; //��������� ��������� �� ������� Sum
	res = operation(&c, &d); //�������� ������� (����� ���������)
	printf("����� = %d\n", res);
	operation = NeSum; //��������� ��������� �� ������� NeSum
	res = operation(&c, &d); //�������� ������� (����� ���������)
	printf("�������� = %d\n", res);
	printf("�������� ����������: %d � %d", c, d);
	return 0;
}