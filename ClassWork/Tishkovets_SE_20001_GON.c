#define _USE_MATH_DEFINES
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "labengine\labengine.h"
#include <locale.h>
#include <math.h>
#include <malloc.h>

typedef struct { //��������� ��� ��������������
	double angle; //��������� ����
	int Cx; //���������� ������
	int Cy;
	int R; //������ ��������� ����������
	int nCorners; //���-�� �����
} polyg_t;

void Draw(polyg_t a) { //��������� ������� ��� ��������� ��������������
	int b = a.Cx + a.R * cos(a.angle); //������ �������, ���������� �
	int c = a.Cy + a.R * sin(a.angle); //������ �������, ���������� �
	int b1 = 0, c1 = 0; //������� ���������� 2-� �������
	for (int i = 0; i < a.nCorners; i++) {
		a.angle += (double)M_PI * 2 / a.nCorners; //��������� ����
		b1 = a.Cx + a.R * cos(a.angle); //�� ����� ����� ����������
		c1 = a.Cy + a.R * sin(a.angle);
		LabDrawLine(b, c, b1, c1); //������ �����
		LabDrawFlush(); //���������� �� ������
		b = b1;
		c = c1;
	}
}

int main(void) {
	if (LabInit())
	{
		int width = LabGetWidth(); //������ ������ ������
		int height = LabGetHeight(); //������ ������ ������
		LabSetColor(LABCOLOR_GREEN); //����

		/*float angle = 0;
		int r = height / 2;
		int x, y;
		LabSetColor(LABCOLOR_GREEN);
		do
		{
			x = r * cos(angle);
			y = r * sin(angle);
			LabDelay(10);
			LabClear();
			LabDrawLine(width / 2, height / 2, width / 2 + x, height / 2 - y);
			angle += 0.01;
			LabDrawFlush();
		} while (!LabInputKeyReady());*/

		polyg_t n = { 0.0, width / 2, height / 2, height / 2, 5 }; //���������� ���������
		do
		{
			LabSetColor(LABCOLOR_GREEN); //����
			Draw(n); //�������� �������
			n.angle -= 0.05; //������ ���� ��� �������� ������
			LabDrawFlush();
			LabDelay(5);
			LabClear(); //������� �����
		} while (!LabInputKeyReady()); //���� ������� �������
		LabTerm(); //��������� ����
	}
	return 0;

}