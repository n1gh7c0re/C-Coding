#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <locale.h>
#include "C:\Visual Studio\labengine\labengine.h"
#include <math.h>

typedef struct { //��������� ��������� �����
	double x;
	double y;
}point_t;

typedef struct { //��������� ��� ������������� �������, �� ���� ��� 2 ����� ��������������
	point_t x1;
	point_t x2;
}rect_t;

point_t Transform(point_t p, rect_t const* from, rect_t const* to) { //����������� ���������� �� �������� ��
	point_t s;														 //� �������������� ��
	s.x = (p.x - from->x1.x) * (to->x2.x - to->x1.x) / (from->x2.x - from->x1.x) + to->x1.x; //��� �
	s.y = (p.y - from->x1.y) * (to->x2.y - to->x1.y) / (from->x2.y - from->x1.y) + to->x1.y; //��� �
	return s;
}

void DrawAxes(rect_t const* math, rect_t const* screen) { //������ ��� ����� ��
	point_t a; //����� - ������ ���������
	a.x = 0;
	a.y = 0;
	point_t b = Transform(a, math, screen); //����������� ����������
	LabSetColor(LABCOLOR_GREEN); //����
	LabDrawLine(screen->x1.x, b.y, screen->x2.x, b.y); //������ �������������� ���
	LabDrawLine(b.x, screen->x1.y, b.x, screen->x2.y); //������ ������������ ���
	LabDrawFlush(); //���������� �� ������
}

labbool_t IsInsideDisk(point_t p) { //���������, ����� �� ����� ������ ���������� ������� r
	if ((p.x * p.x + p.y * p.y) <= 1) return LAB_TRUE;
	else return LAB_FALSE;
}

void DrawDisk(rect_t const* math, rect_t const* screen) { //������ ����
	point_t a; //����� - ������ ���������
	a.x = 0;
	a.y = 0;
	point_t b = Transform(a, math, screen); //����������� ����������
	point_t c, d;
	int r = 1;
	for (double i = screen->x1.x; i <= screen->x2.x; i++) { //����������� �� �����
		for (double j = screen->x1.y; j <= screen->x2.y; j++) { //����������� �� �������
			c.x = i;
			c.y = j;
			d = Transform(c, screen, math); //����������� ����������
			if (IsInsideDisk(d) == LAB_TRUE) { //�������� �������, ��� ����� ����� � �������� ���������� ������� r
				LabDrawPoint(i, j); //������ �����
			}
		}
	}
	LabDrawFlush(); //���������� �� ������
}

labbool_t IsInsideJulia(point_t p) { //��������� �������, ��� ����� ����������� ��������� �����
	point_t c; //���������
	//c.x = -0.12375;
	//c.y = 0.56508;
	c.x = -0.500934515513869749377; //��� ����� ��������
	c.y = -0.52287731735700945607;
	point_t res;
	int N = 100; //���������� ����� ��������
	int r = 2; //������
	for (int i = 0; i < N; i++) {
		res.x = p.x * p.x - p.y * p.y + c.x;
		res.y = p.x * p.y + p.x * p.y + c.y;
		p.x = res.x;
		p.y = res.y;
		if (res.x * res.x + res.y * res.y > (r * r)) return LAB_FALSE; //������� ��� ������ �� �����
	}
	return LAB_TRUE;
}

void DrawJulia(rect_t const* math, rect_t const* screen) { //������ ��������� �����
	point_t c, d;
	for (int i = screen->x1.x; i <= screen->x2.x; i++) { //����������� �� �����
		for (int j = screen->x1.y; j <= screen->x2.y; j++) { //����������� �� �������
			c.x = i;
			c.y = j;
			d = Transform(c, screen, math); //����������� ����������
			if (IsInsideJulia(d) == LAB_TRUE) { //�������� �������, ��� ����� ����������� ��������� �����
				LabDrawPoint(i, j); //������ �����
			}
		}
	}
	LabDrawFlush(); //���������� �� ������
}

int main(void)
{
	if (LabInit())
	{
		double width = LabGetWidth(); //������
		double height = LabGetHeight(); //������

		point_t sys1; //������� ����� ����� �������������� � �������� �����������
		sys1.x = 0;
		sys1.y = 0;
		point_t sys2; //������ ������ ����� �������������� � �������� �����������
		sys2.x = width / 2;
		sys2.y = height;
		point_t sys3; //������� ����� ����� �������������� � ������������� �����������
		sys3.x = -2;
		sys3.y = 3;
		point_t sys4; //������ ������ ����� �������������� � ������������� �����������
		sys4.x = 2;
		sys4.y = -3;

		rect_t screen, math;
		//���������� ���������� 2 ����� � ��������� ��� "���������" ��������������
		screen.x1 = sys1;
		screen.x2 = sys2;
		//���������� ���������� 2 ����� � ��������� ��� "���������������" ��������������
		math.x1 = sys3;
		math.x2 = sys4;

		DrawAxes(&math, &screen);
		DrawDisk(&math, &screen);

		rect_t screen_new;
		point_t an, bn; //���������� ����� ��� 2-� �� (� ������ ����� ����)
		an.x = width / 2;
		an.y = 0;
		bn.x = width;
		bn.y = height;
		screen_new.x1 = an;
		screen_new.x2 = bn;

		DrawAxes(&math, &screen_new);
		DrawJulia(&math, &screen_new);

		LabInputKey(); //��� ������� �������
		LabTerm();
	}
	return 0;
}