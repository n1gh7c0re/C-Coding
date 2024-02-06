/*������� - ������� � ������� 2 ����� � ������ �������� ����� � ��������� ������ � ������ ������������*/
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <locale.h>
#define LENGTH 10

int Fill(int number, int digits[], int length) { //��������� �������� ����� �� ������
	int s = 0; //���������� s ��� �������� ������� ��������� �������
	for(int i = 0; i < length; i++){
		digits[i] = number % 10;
		number = number / 10;
	}
	for (int i = length - 1; i >= 0; i--) { //���� ��� �������� ������� ��������� �������
		if (digits[i] == 0) {
			s += 1;
		} else break;
	}
	return length - s; //������� �������, ��� ��� ���������� ���������� �������� ����
}

void Print(int const digits[], int length, int max) { //������� ������ �� ������� Fill � �������� ������� � ��� �����
	int l =  0;                                       //�� ���� ������� �������� �����, �������� �� �����
	for(int i = 0;i < max - length; i++){
		printf("  ");
	}
	for (int i = length - 1; i >= 0; i--) {
		l = digits[i];
		printf("%i ", l);
	}
	printf("\n");
}

int Add(int const x[], int const y[], int xy[], int length) { //���������� 2 �����, �� ����� ���� ��� �������� ������ ������
	int m = 0, n = 0, s = 0; //���������� s ���������� ���������� s � ������� Fill
	for (int i = 0; i < length; i++) {
		m = x[i] + y[i];
		xy[i] = m % 10 + n;
		n = m / 10;
	}
	m = 0;
	for (int i = length - 1; i >= 0; i--) {
		if (xy[i] == 0) {
			m += 1;
		}
		else break;
	} 
	return length - m;
}

int Collect(int const digits[], int length) { //���������� ����� �� ������� Add � ������ �������
	int n = 0;
	for (int i = length - 1; i >= 0; i--) {
		n *= 10;
		n += digits[i];
	}
	return n;
}

int main() {
	setlocale(LC_CTYPE, "Russian");
	printf("�������� ������, ������ 5030102/20001, ADD: �������� � �������\n");
	int a = 0, b = 0, c = 0, f = 0, p = 0, x = 0;
	int A[LENGTH] = { 0 };
	int B[LENGTH] = { 0 };
	int C[LENGTH] = { 0 };
	printf("������� ������ �����: ");
	scanf("%i", &a);
	printf("������� ������ �����: ");
	scanf("%i", &b);
	f = Fill(a, A, LENGTH);
	p = Fill(b, B, LENGTH);
	x = Add(A, B, C, LENGTH);
	int max1 = f;
	if(max1 < p) {
		max1 = p;
	}
	if (max1 < x) {
		max1 = x;
	}
	c = a + b;
	int y = Collect(C, LENGTH);
	printf(" ");
	Print(A, f, max1);
	printf("+");
	Print(B, p, max1);
	printf(" ");
	for (int i = 0; i < max1; i++) {
		printf("--");
	}
	printf("\n ");
	Print(C, max1, x);
	return 0;
}