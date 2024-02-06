/*��������� ������� ������ ����� ������� ����� � ������ � ������� ���*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#define MAX_SIZE 100

int strlen(char buf[]) { //������� ����� ������
	int cnt = 0;
	for (int i = 0; i < MAX_SIZE; i++) {
		if (buf[i] == '\0')
			break;
		cnt++;
	}
	return cnt;
}

int checkLetter(char s) { //��������� ����� �� ���� ������
	if ((('a' <= s) && (s <= 'z')) || (('0' <= s) && (s <= '9')) || (('A' <= s) && (s <= 'Z'))) return 1;
	else return 0;
}

void changeBuf(char buf[], const int start, const int end) { //������������ ������� �� `start` �� `end` � ������
	const int len = end - start + 1;
	for (int i = start; i <= end; i++) {
		buf[i - start] = buf[i];
	}
	buf[len] = '\0';
}

void findLongWord(char buf[]) { //���� ������� ������ � ����� ������ �������� ����� � �������� 'changeBuf'
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
	printf("�������� ������, ������ 5030102/20001, ��1 STR-12\n");
	char buf[MAX_SIZE];
	printf("������� ������: ");
	gets(buf);
	int len_str = strlen(buf);
	while (len_str != 0) {
		findLongWord(buf);
		printf("���������: %s\n", buf);
		printf("������� ������: ");
		gets(buf);
		len_str = strlen(buf);
	}
	printf("�� ����� ������ ������, ���-������ � ������ ���)");
	return 0;
}