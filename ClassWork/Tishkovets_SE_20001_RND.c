/*��������� ���������� ��������� �����, ��������� � ������ ����������� �� �������������*/
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <math.h>

//////////////////////////////////////////////////////////////////////////////

/**
 * ���������� ������������ ��������� �����, ���������� �������������
 * �� ������������ ��������� [a, b).
 *
 * @param a - ������ �������
 * @param b - ������� �������
 *
 * @return ��������� ����� �� a �� b (�� ������� ������� �������).
 */
double Random(double a, double b) {
	// TODO: 1. ��������� �������.
	double x = rand(); //���������� ��������� ����� �� 0 �� RAND_MAX
	x = a + (x / RAND_MAX) * (b - a);
	return x;
}

/**
 * ��������� ������ ���������� �������������� ���������� �������.
 *
 * @param arr - ������
 * @param size - ���������� ��������� � �������
 * @param a - ������ �������
 * @param b - ������� ������� (�� ���������� � ��������)
 *
 * @see Random()
 */

void FillRandom(double arr[], int size, double a, double b) {
	// TODO: 1. ��������� �������.
	for (int i = 0; i < size; i++) {
		arr[i] = Random(a, b);
	}
}

/**
 * �������� �������� ������� � �������.
 *
 * @param arr - ������
 * @param size - ���������� ��������� � �������
 */

void Print(double const arr[], int size) {
	// TODO: 1. ��������� �������.
	for (int i = 0; i < size; i++) {
		printf("%f\n", arr[i]);
	}
}

//////////////////////////////////////////////////////////////////////////////

/**
 * ������ ����������� �������� ��������� �������.
 *
 * ��������� ������ counters[] �� ��������� �������� ��������� ������� arr[],
 * �����������, ������� �� ������ � ��������������� �����������
 * ������� ��������� [a, b). �������� �������, �� ���������� � ���������
 * �������� �� a �� b ������������.
 *
 * @param arr - ������
 * @param size - ���������� ��������� � �������
 * @param a - ������ �������
 * @param b - ������� ������� (�� ���������� � ��������)
 * @param counters - ����������� ������
 * @param numCounters - ���������� ������������� ��������
 */

void BuildHistogram(double const arr[], int size,
	double left, double right, int counters[], int numCounters) {
	// TODO: 2. ��������� ������ ��� �����������.
	for (int i = 0; i < numCounters; i++) { //����������, ��� � ������� ����� ���� 5 �����
		counters[i] = 0;
	}
	for (int i = 0; i < size; i++) {
		if ((left <= arr[i]) && (arr[i] < right)) {
			int num = (arr[i] - left) / (right - left) * numCounters; //���������� ����� int
			counters[num]++;                                          //����� ���������� ������������
		}                                                             //��� ����� �����
	}
}

/**
 * �������� �������� ������� ����� ������� � �������� �������.
 *
 * @param counters     ������
 * @param numCounters  ���������� ��������� � �������
 */

void PrintHistogram(int counters[], int numCounters) {
	// TODO: 2. ��������� ������ ��� �����������.
	for (int i = 0; i < numCounters; i++) {
		printf("%d\t", counters[i]); //������� ����� Tab
	}
}

#define HIST_CHAR_BAR 'o'
#define HIST_CHAR_SPACE 183 //����� �� ���������

/**
 * �������� �������������� ����������� �������� ��������� �������.
 *
 * @param counters - ������ ����������, ���������� ���������� ���������, �������� � ��������������� �����������
 * @param numCounters - ���������� ������������� ��������
 * @param width - ������ ������ ���� ������ �����������, � �����������
 */

void DrawHistogram(int counters[], int numCounters, int width) {
	// TODO: 3. ��������� ���������.
	int max = counters[0];
	for (int i = 0; i < numCounters; i++) { //���������� ����� ������ �������� �����
		if (counters[i + 1] > counters[i]) {
			max = counters[i + 1];
		}
	}
	for (int i = 0; i < numCounters; i++) {
		printf("%i ", i + 1);
		for (int j = 1; j <= (counters[i] * width) / max; j++) {
			printf("%c", HIST_CHAR_BAR);
		}
		for (int k = 1; k <= width - ((counters[i] * width) / max); k++) {
			printf("%c", HIST_CHAR_SPACE);
		}
		printf("\n");
	}
}

//////////////////////////////////////////////////////////////////////////////

int main(void) {
	const int PRINT_MAX = 20;
	const double RANDOM_MIN = 0.2;
	const double RANDOM_MAX = 0.6;
	const double HIST_MIN = 0.0;
	const double HIST_MAX = 1.0;
	const int HIST_LINES = 5;
	const int HIST_LENGTH = 16;
	int size = 10;
	double* numbers = NULL;
	int* hist = NULL;
	setlocale(LC_CTYPE, "Russian");
	// TODO: 0. �������� �� ��������� �����. ����������� ��������� � �����.
	/*for (int i = 0; i < 10; i++) {
		printf("%d\n", rand(0));
	}*/
	// ��� ������� ����� ��������������� ���� ������� ������ ������
	// ...
	// ������������� � ������������
	printf("�������� ������, ������ 5030102/20001, RND: ��������� �����\n������� ���������� �����: ");
	scanf("%i", &size);
	// �������� ������
	numbers = malloc(size * sizeof(double));
	hist = malloc(HIST_LINES * sizeof(int));
	// ��������� �������
	printf("\n����������� �� (������ %i �����):\n", PRINT_MAX);
	FillRandom(numbers, size, RANDOM_MIN, RANDOM_MAX);
	Print(numbers, size < PRINT_MAX ? size : PRINT_MAX);
	printf("\n");
	// ��������� ����������� ����������� ��������� ��������
	BuildHistogram(numbers, size, HIST_MIN, HIST_MAX, hist, HIST_LINES);
	PrintHistogram(hist, HIST_LINES);
	printf("\n\n�����������:\n");
	DrawHistogram(hist, HIST_LINES, HIST_LENGTH);
	// ���������� ������
	free(hist);
	free(numbers);
	return 0;
}