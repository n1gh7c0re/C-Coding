/*Программа получает на вход строку (или строфу) неизвестной длины и разбивает на строки такой длины
которая не превосходит введенного пользователем числа*/
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <stdlib.h>

char* Readline(int* length) { //посимвольно получает динамическую строку с её реальной длиной
	*length = 0; //изначально 0 - пустая строка
	int size = 1; //всегда есть символ '\0'
	char* str = (char*)malloc(sizeof(char)); //создаёт динамический массив
	char c = getchar(); //считывает символ
	if (c == '\n') {
		printf("\nВы ввели пустую строку");
		exit(0); //выходит из программы с кодом 0
	}

	while (1) { //типо "бесконечный цикл"
		str[(*length)++] = c; //записывает считанный символ в массив
		if (*length >= size) { //условие для увеличения размера массива
			size += 1;
			str = (char*)realloc(str, sizeof(char) * (size)); //увеличивает размер массива
			if (str == NULL) { //проверка на случай, если realloc вернет NULL
				printf("Ошибка\n");
				exit(0); //выходит из программы с кодом 0
			}
		}
		c = getchar(); //считывает символ

		if (c == '\n') {
			str[(*length)++] = ' '; //заменяет символ '\n' на пробел 
			if (*length >= size) { //условие для увеличения размера массива
				size += 1;
				str = (char*)realloc(str, sizeof(char) * (size)); //увеличивает размер массива 
				if (str == NULL) { //проверка на случай, если realloc вернет NULL 
					printf("Ошибка\n");
					exit(0); //выходит из программы с кодом 0 
				}
			}
			c = getchar(); //считывает символ
			if (c == '\n') break; //условие для обозначения конца ввода строфы
		}
	}
	str[(*length)] = '\0'; //вроде как это делается автоматически, но ладно
	return str; //возвращает указатель на строку
}

int СheckLetter(char s) { //проверяет буква ли этот символ
	if ((('a' <= s) && (s <= 'z')) || (('0' <= s) && (s <= '9')) || (('A' <= s) && (s <= 'Z'))) return 1;
	else return 0;
}

char* NewArray(char* str, int* length, int* length1) { //создает еще один массив, но уже без повторяющихся пробелов
	int cnt = 0;
	for (int i = 1; i <= *length; i++) { //вычисляет длину массива без повторения пробелов
		if ((*(str + i) == ' ') && (*(str + i - 1) == ' ')) {
			cnt += 0;
		}
		else cnt += 1;
	}
	*length1 = cnt;
	char* NewArr = (char*)malloc(sizeof(char) * cnt); //создаёт динамический массив нужного размера
	//т.е. без лишних пробелов
	int j = 0;
	while (j < cnt - 1) { //условие для нового массива
		for (int i = 1; i <= *length + 1; i++) {
			if ((*(str + i) == ' ') && (*(str + i - 1) == ' ')) { //если 2 пробела подряд
				NewArr[j] = str[i];
			}
			else {
				NewArr[j] = str[i - 1];
				j += 1;
			}
		}
	}
	NewArr[j - 1] = '\0';

	//для проверки
	/*for (int i = 0; i < cnt; i++) {
		printf("%c", NewArr[i]);
	}*/
	return NewArr; //возвращает указатель на новый массив без лишних пробелов
}

void FormatText(char const* str, int const width, int* length) { //разбивает массив длины length на строки шириной width
	int count = 0; //счетчик для длины слова
	int c = 0; //счетчик для длины заполненной строки
	int i = 0;
	while (str[i] != '\0') {
		for (int j = 0; j < *length; j++) { //считает длину слова
			if (СheckLetter(str[(i + j)])) {
				count += 1;
			}
			else break;
		}

		if (count != 0) { //если все таки слово
			if (count > width) { //условие на случай чересчур большого слова
				printf("\nДлина слова превышает ширину строки");
				exit(0); //выходит из программы с кодом 0
			}

			if ((width - c) < count) { //условие для переноса слова на следующую строку при нехватке места
				printf("\n");
				c = 0;
			}
			c += count; //увеличивает заполненность строки

			for (int k = 0; k < count; k++) { //печатает слово
				printf("%c", str[(i + k)]);
			}

			i += count;
			count = 0;
		}
		else { //если просто символ
			if ((width - c) == 0) { //условие для переноса символа на следующую строку при нехватке места
				printf("\n");
				c = 0;
			}
			c += 1; //увеличивает заполненность строки

			printf("%c", str[i]); //печатает символ

			i += 1;
			count = 0;
		}
	}
}

int main(void) {
	setlocale(LC_CTYPE, "Russian");
	printf("Тишковец Сергей, группа 5030102/20001, ДЗ2 DST-11\n");
	int width = 0;
	char a;
	printf("Введите ширину строки: ");
	scanf("%d", &width);
	scanf("%c", &a); //для дальнейшей корректной работы программы - "съедает" символ '\n' в буфере
	int len, NewLen; //количество символов в строке
	printf("\nВведите строку:\n");
	char* Arr = Readline(&len); //вызывает функцию, используя указатель на длину
	char* NewArr = NULL;
	while (1) {
		printf("\nРезультат: \n");
		NewArr = NewArray(Arr, &len, &NewLen);
		FormatText(NewArr, width, &NewLen);
		printf("\nВведите строку:\n");
		Arr = Readline(&len);
	}
	free(Arr);
	return 0;
}