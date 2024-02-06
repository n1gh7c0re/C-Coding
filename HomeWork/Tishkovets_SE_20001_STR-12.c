/*Программа находит первое самое длинное слово в строке и выводит его*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#define MAX_SIZE 100

int strlen(char buf[]) { //Считает длину строки
	int cnt = 0;
	for (int i = 0; i < MAX_SIZE; i++) {
		if (buf[i] == '\0')
			break;
		cnt++;
	}
	return cnt;
}

int checkLetter(char s) { //Проверяет буква ли этот символ
	if ((('a' <= s) && (s <= 'z')) || (('0' <= s) && (s <= '9')) || (('A' <= s) && (s <= 'Z'))) return 1;
	else return 0;
}

void changeBuf(char buf[], const int start, const int end) { //Переписывает участок от `start` до `end` в начало
	const int len = end - start + 1;
	for (int i = start; i <= end; i++) {
		buf[i - start] = buf[i];
	}
	buf[len] = '\0';
}

void findLongWord(char buf[]) { //Ищет индексы начала и конца самого длинного слова и вызывает 'changeBuf'
	int start = 0;
	int end = 100;
	int max_len = 0;
	int cur_len = 0;
	int len_str = strlen(buf);
	for (int i = 0; i < len_str; i++) {
		if (checkLetter(buf[i])) {
			cur_len += 1;
		}
		else {
			if (cur_len > max_len) {
				end = i - 1;
				start = end - cur_len + 1;
				max_len = cur_len;
			}
			cur_len = 0;
		}
	}
	if (cur_len > max_len) {
		end = len_str - 1;
		start = end - cur_len + 1;
		max_len = cur_len;
	}
	changeBuf(buf, start, end);
}

int main(void) {
	setlocale(LC_CTYPE, "Russian");
	printf("Тишковец Сергей, группа 5030102/20001, ДЗ1 STR-12\n");
	char buf[MAX_SIZE];
	printf("Введите строку: ");
	gets(buf);
	int len_str = strlen(buf);
	while (len_str != 0) {
		findLongWord(buf);
		printf("Результат: %s\n", buf);
		printf("Введите строку: ");
		gets(buf);
		len_str = strlen(buf);
	}
	printf("Вы ввели пустую строку, как-нибудь в другой раз)");
	return 0;
}