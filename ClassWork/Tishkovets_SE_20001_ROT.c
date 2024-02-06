/*���������, ���������� ���������� �������� ������� �� �������� ����� ������� delta*/
#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#define N 9

void Fill(int arr[], int size) { //��������� ������ ������� �� 0 �� N
	for (int i = 0; i < size; i++) {
		arr[i] = i + 1;
	}
}

void Print(int arr[], int size) { //�������� ������
	for (int i = 0; i < size; i++) {
		printf("%i ", arr[i]);
	}
	printf("\n");
}

void Shift1(int arr[], int size) { //�������� �������� ������� �� ���� ������� �����
	int s = arr[0]; //��������������� ����������
	for (int i = 1; i < size; i++) {
		arr[i - 1] = arr[i];
	}
	arr[size - 1] = s;
}

void Shift_Ver1(int arr[], int size, int delta) { //���� �������� �������� ������� �����, �� ��� �� �������� ����� ������� delta
	for (int i = 0; i < (delta % size); i++) { //������ delta % size, ����� ������ ������, ����� delta >= N
		Shift1(arr, size);
	}
}

void Reverse(int arr[], int left, int right) { //��� ��� ������ ������ ��������� ��������� �������
	int l = right - left + 1;
	for (int i = left; i < left + l / 2; i++) {  //����� �������� � ����� �������:
		int t = arr[i];                          //arr[i] ^= arr[right - i + left];
		arr[i] = arr[right - i + left];          //arr[right - i + left] ^= arr[i];
		arr[right - i + left] = t;               //arr[i] ^= arr[right - i + left];
	}
}

void Shift_Ver2(int arr[], int size, int delta) { //������� ������������� ���� ������ ����� ����� � ������ �����
	if (delta != 0) {                             //������������ ������������ ����� ������ ����� �������� � �������
		delta %= size;                            //(�� ��������) ������ delta = 3 (��������). ���� 1 2 3 | 4 5 6 7 8 9
		Reverse(arr, 0, size - 1);                // 9 8 7 6 5 4 | 3 2 1 
		Reverse(arr, 0, size - delta - 1);        // 4 5 6 7 8 9 | 3 2 1  ���������� ����� ������ �� �����
		Reverse(arr, size - delta, size - 1);     // 4 5 6 7 8 9 | 1 2 3 
	}
}

int main(void) {
	setlocale(LC_CTYPE, "Russian");
	printf("�������� ������, ������ 5030102/20001, ROT\n");
	int arr[N];
	int delta; //��� � ���� ����� �������, �� ������� �������� ������ �������, �.�. �������� ������ �������
	printf("������� �����: ");
	scanf("%d", &delta);
	printf("������ ������:\n");
	Fill(arr, N);
	Print(arr, N);
	delta %= N; //��������� delta � ����� ��������� �� ��������� 0
	if (delta != 0) Shift_Ver1(arr, N, delta); //���� delta = 0, �� ������� � �� �������� ��������
	Print(arr, N);
	printf("������ ������:\n");
	Fill(arr, N);
	Print(arr, N);
	if (delta != 0) Shift_Ver2(arr, N, delta); //���������� 1-�� �������
	Print(arr, N);
	return 0;
}