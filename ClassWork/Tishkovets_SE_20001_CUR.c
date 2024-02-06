#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <locale.h>
#include "C:\Visual Studio\labengine\labengine.h"
#include <math.h>

void Lesenka(int x1, int y1, int x2, int y2, int n) { //������ �������
	int x = (x2 + x1) / 2;
	int y = (y2 + y1) / 2;
	if (n == 0) { //��� �������� �����������
		LabSetColor(LABCOLOR_GREEN); //����
		LabDrawLine(x1, y1, x2, y1); //������ �����
		LabDrawLine(x2, y1, x2, y2); //������ �����
		LabDrawFlush(); //���������� �� ������
	}
	else { //��������, ����� �������� ����
		Lesenka(x1, y1, x, y, n - 1);
		Lesenka(x, y, x2, y2, n - 1);
	}
}

void Koha(int x1, int y1, int x2, int y2, int n) { //������ ������ ����
	int x3 = x1 - (x1 - x2) / 3;
	int x5 = x1 - (x1 - x2) / 3 * 2;
	int y3 = y1 - (y1 - y2) / 3;
	int y5 = y1 - (y1 - y2) / 3 * 2;
	int x4 = (x1 + x2) / 2 + sqrt(3) / 6 * (y2 - y1); //"�������" ������������
	int y4 = (y1 + y2) / 2 + sqrt(3) / 6 * (x1 - x2);
	if (n == 0) { //��� �������� ����������� - ������ ������
		LabDrawLine(x1, y1, x2, y2); //������ �����
		LabDrawFlush(); //���������� �� ������
	}
	else { //�������� - ������ ��� 4 ������
		Koha(x1, y1, x3, y3, n - 1);
		Koha(x3, y3, x4, y4, n - 1);
		Koha(x4, y4, x5, y5, n - 1);
		Koha(x5, y5, x2, y2, n - 1);
	}
}

int main(void)
{
	if (LabInit())
	{
		int width = LabGetWidth(); //������
		int height = LabGetHeight(); //������
		int n = 3;

		//Lesenka(0, 0, width, height, n);

		int i = 1;
		labkey_t key;
		Koha(0, height / 2, width, height / 2, n);
		while (i) {
			if (LabInputKeyReady() == LAB_TRUE) {
				key = LabInputKey();
				switch (key) {
				case LABKEY_ENTER: //������� �� ��������� ��� ������� ������� Enter
					i = 0;
					break;
				case LABKEY_UP: //����������� ����������� �� 1
					n++;
					LabClear();
					Koha(0, height / 2, width, height / 2, n);
					break;
				case LABKEY_DOWN: //��������� ����������� �� 1
					n--;
					LabClear();
					Koha(0, height / 2, width, height / 2, n);
					break;
				}
			}
		}
		LabTerm();
	}
	return 0;
}