/*��������� �������� �� ���� ������ (��� ������) ����������� ����� � ��������� �� ������ ����� �����
������� �� ����������� ���������� ������������� �����*/
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <stdlib.h>

char* Readline(int* length) { //����������� �������� ������������ ������ � � �������� ������
	*length = 0; //���������� 0 - ������ ������
	int size = 1; //������ ���� ������ '\0'
	char* str = (char*)malloc(sizeof(char)); //������ ������������ ������
	char c = getchar(); //��������� ������
	if (c == '\n') {
		printf("\n�� ����� ������ ������");
		exit(0); //������� �� ��������� � ����� 0
	}

	while (1) { //���� "����������� ����"
		str[(*length)++] = c; //���������� ��������� ������ � ������
		if (*length >= size) { //������� ��� ���������� ������� �������
			size += 1;
			str = (char*)realloc(str, sizeof(char) * (size)); //����������� ������ �������
			if (str == NULL) { //�������� �� ������, ���� realloc ������ NULL
				printf("������\n");
				exit(0); //������� �� ��������� � ����� 0
			}
		}
		c = getchar(); //��������� ������

		if (c == '\n') {
			str[(*length)++] = ' '; //�������� ������ '\n' �� ������ 
			if (*length >= size) { //������� ��� ���������� ������� �������
				size += 1;
				str = (char*)realloc(str, sizeof(char) * (size)); //����������� ������ ������� 
				if (str == NULL) { //�������� �� ������, ���� realloc ������ NULL 
					printf("������\n");
					exit(0); //������� �� ��������� � ����� 0 
				}
			}
			c = getchar(); //��������� ������
			if (c == '\n') break; //������� ��� ����������� ����� ����� ������
		}
	}
	str[(*length)] = '\0'; //����� ��� ��� �������� �������������, �� �����
	return str; //���������� ��������� �� ������
}

int �heckLetter(char s) { //��������� ����� �� ���� ������
	if ((('a' <= s) && (s <= 'z')) || (('0' <= s) && (s <= '9')) || (('A' <= s) && (s <= 'Z'))) return 1;
	else return 0;
}

char* NewArray(char* str, int* length, int* length1) { //������� ��� ���� ������, �� ��� ��� ������������� ��������
	int cnt = 0;
	for (int i = 1; i <= *length; i++) { //��������� ����� ������� ��� ���������� ��������
		if ((*(str + i) == ' ') && (*(str + i - 1) == ' ')) {
			cnt += 0;
		}
		else cnt += 1;
	}
	*length1 = cnt;
	char* NewArr = (char*)malloc(sizeof(char) * cnt); //������ ������������ ������ ������� �������
	//�.�. ��� ������ ��������
	int j = 0;
	while (j < cnt - 1) { //������� ��� ������ �������
		for (int i = 1; i <= *length + 1; i++) {
			if ((*(str + i) == ' ') && (*(str + i - 1) == ' ')) { //���� 2 ������� ������
				NewArr[j] = str[i];
			}
			else {
				NewArr[j] = str[i - 1];
				j += 1;
			}
		}
	}
	NewArr[j - 1] = '\0';

	//��� ��������
	/*for (int i = 0; i < cnt; i++) {
		printf("%c", NewArr[i]);
	}*/
	return NewArr; //���������� ��������� �� ����� ������ ��� ������ ��������
}

void FormatText(char const* str, int const width, int* length) { //��������� ������ ����� length �� ������ ������� width
	int count = 0; //������� ��� ����� �����
	int c = 0; //������� ��� ����� ����������� ������
	int i = 0;
	while (str[i] != '\0') {
		for (int j = 0; j < *length; j++) { //������� ����� �����
			if (�heckLetter(str[(i + j)])) {
				count += 1;
			}
			else break;
		}

		if (count != 0) { //���� ��� ���� �����
			if (count > width) { //������� �� ������ �������� �������� �����
				printf("\n����� ����� ��������� ������ ������");
				exit(0); //������� �� ��������� � ����� 0
			}

			if ((width - c) < count) { //������� ��� �������� ����� �� ��������� ������ ��� �������� �����
				printf("\n");
				c = 0;
			}
			c += count; //����������� ������������� ������

			for (int k = 0; k < count; k++) { //�������� �����
				printf("%c", str[(i + k)]);
			}

			i += count;
			count = 0;
		}
		else { //���� ������ ������
			if ((width - c) == 0) { //������� ��� �������� ������� �� ��������� ������ ��� �������� �����
				printf("\n");
				c = 0;
			}
			c += 1; //����������� ������������� ������

			printf("%c", str[i]); //�������� ������

			i += 1;
			count = 0;
		}
	}
}

int main(void) {
	setlocale(LC_CTYPE, "Russian");
	printf("�������� ������, ������ 5030102/20001, ��2 DST-11\n");
	int width = 0;
	char a;
	printf("������� ������ ������: ");
	scanf("%d", &width);
	scanf("%c", &a); //��� ���������� ���������� ������ ��������� - "�������" ������ '\n' � ������
	int len, NewLen; //���������� �������� � ������
	printf("\n������� ������:\n");
	char* Arr = Readline(&len); //�������� �������, ��������� ��������� �� �����
	char* NewArr = NULL;
	while (1) {
		printf("\n���������: \n");
		NewArr = NewArray(Arr, &len, &NewLen);
		FormatText(NewArr, width, &NewLen);
		printf("\n������� ������:\n");
		Arr = Readline(&len);
	}
	free(Arr);
	return 0;
}