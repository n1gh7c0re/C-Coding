/*��������� ������ ������� �������� ���� �����, ����������� � �������� ����*/
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <locale.h>
#include <stdio.h>
#include <limits.h>

typedef unsigned long long MaxInt;
typedef unsigned int integer_t;

int Tip(integer_t c) { //������� ��� ����������� �������
	int size = 0;
	if (c <= UCHAR_MAX) size = 8;
	if ((c <= USHRT_MAX) & (c > UCHAR_MAX)) size = 16;
	if ((c <= UINT_MAX) & (c > USHRT_MAX)) size = 32;
	if (c > UINT_MAX) size = 64;
	return size;
}

integer_t Zamena(integer_t c, int size) { //�������� �������, ������� ������ ������� �������� ����
	for (int i = 0; i < (size / 2); i++) {
		if ((((c & (1 << (2 * i))) == 0) && ((c & (1 << ((2 * i) + 1))) != 0)) || (((c & (1 << (2 * i))) != 0) && ((c & (1 << ((2 * i) + 1))) == 0))) {
			c ^= (3 << (2 * i));
		}//������ ����� �� ��������)))
	}
	return c;
}

void Dva(integer_t c, int size) { //������� ��� ��������� ����� � �������� ����
	int t[64] = { 0 }; //������ ��� ������ ��������� �����
	for (int i = 0; i < size; i++) {
		t[i] = c % 2;
		c /= 2;
	}
	for (int j = size - 1; j >= 0; j--) { //��� ������ ��������� �����
		if (j % 8 == 0) { //��� ���������� ���� ��������
			printf("%d ", t[j]);
		} else printf("%d", t[j]);
	}
}

integer_t Lenght(integer_t c) { //������� ��� ����������� ����� �����
	int k = 0;
	do {
		c /= 10;
		k++;
	} while (c > 0);
	return k;
}

int main() {
	setlocale(LC_CTYPE, "Russian");
	printf("�������� ������, ������ 5030102/20001, ��2 - ����� ����� (32 ����), ������� BIT-5\n");
	MaxInt a = 0;
	do {
		printf("������� �����, �� ������ �������� �� ��������� 32 ����: ");
		scanf("%llu", &a);
		if (a > UINT_MAX) { //�������� �� ����� ������ ��� ������ ���� ������
			printf("�� ����� ������������ �����\n");
			break;
		}
		int s = Tip((integer_t)a); //���� ������������ ������
		integer_t b = Zamena((integer_t)a, s); //������������ �����
		integer_t m = Lenght((integer_t)a); //����� ��������� �����
		integer_t n = Lenght(b); //����� ������������� �����
		integer_t dl = (m >= n) ? m : n; //��� ����� ������� ��������� ����� ������� �� ���� �����
		//�������� ����� ��� 1-�� �����
		printf("�� �����  : ");
		printf("%*u = ", dl, (integer_t)a); //����� ������ ��� ������ ����� � ������� ����� ������ "*"
		printf("0x%X = ", (integer_t)a);
		Dva((integer_t)a, s);
		printf("\n");
		//�������� ����� ��� 2-�� �����
		printf("��������� : ");
		printf("%*u = ", dl, b);
		printf("0x%X = ", b);
		Dva(b, s);
		printf("\n\n");
	} while ((integer_t)a != 0);
	return 0;
}