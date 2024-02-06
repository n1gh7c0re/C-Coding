/*Программа меняет местами соседние биты числа, записанного в двоичном виде*/
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <locale.h>
#include <stdio.h>
#include <limits.h>

typedef unsigned long long MaxInt;
typedef unsigned int integer_t;

int Tip(integer_t c) { //функция для определения размера
	int size = 0;
	if (c <= UCHAR_MAX) size = 8;
	if ((c <= USHRT_MAX) & (c > UCHAR_MAX)) size = 16;
	if ((c <= UINT_MAX) & (c > USHRT_MAX)) size = 32;
	if (c > UINT_MAX) size = 64;
	return size;
}

integer_t Zamena(integer_t c, int size) { //основная функция, которая меняет местами соседние биты
	for (int i = 0; i < (size / 2); i++) {
		if ((((c & (1 << (2 * i))) == 0) && ((c & (1 << ((2 * i) + 1))) != 0)) || (((c & (1 << (2 * i))) != 0) && ((c & (1 << ((2 * i) + 1))) == 0))) {
			c ^= (3 << (2 * i));
		}//ничего проще не придумал)))
	}
	return c;
}

void Dva(integer_t c, int size) { //функция для получения числа в двоичном виде
	int t[64] = { 0 }; //массив для записи двоичного числа
	for (int i = 0; i < size; i++) {
		t[i] = c % 2;
		c /= 2;
	}
	for (int j = size - 1; j >= 0; j--) { //для вывода двоичного числа
		if (j % 8 == 0) { //для разделения байт пробелом
			printf("%d ", t[j]);
		} else printf("%d", t[j]);
	}
}

integer_t Lenght(integer_t c) { //функция для определения длины числа
	int k = 0;
	do {
		c /= 10;
		k++;
	} while (c > 0);
	return k;
}

int main() {
	setlocale(LC_CTYPE, "Russian");
	printf("Тишковец Сергей, группа 5030102/20001, ДЗ2 - Обмен битов (32 бита), вариант BIT-5\n");
	MaxInt a = 0;
	do {
		printf("Введите число, не размер которого не превышает 32 бита: ");
		scanf("%llu", &a);
		if (a > UINT_MAX) { //проверка на число именно для нашего типа данных
			printf("Вы ввели некорректное число\n");
			break;
		}
		int s = Tip((integer_t)a); //сюда записывается размер
		integer_t b = Zamena((integer_t)a, s); //получившееся число
		integer_t m = Lenght((integer_t)a); //длина исходного числа
		integer_t n = Lenght(b); //длина получившегося числа
		integer_t dl = (m >= n) ? m : n; //так будет удобнее запомнить самое длинное из двух чисел
		//красивый вывод для 1-го числа
		printf("Вы ввели  : ");
		printf("%*u = ", dl, (integer_t)a); //задаём ширину для вывода числа с помощью флага ширины "*"
		printf("0x%X = ", (integer_t)a);
		Dva((integer_t)a, s);
		printf("\n");
		//красивый вывод для 2-го числа
		printf("Результат : ");
		printf("%*u = ", dl, b);
		printf("0x%X = ", b);
		Dva(b, s);
		printf("\n\n");
	} while ((integer_t)a != 0);
	return 0;
}