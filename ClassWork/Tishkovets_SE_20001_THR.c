/*��������� ������ ���������� �������� ����, ���������� ��� ����� � ���������*/
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <locale.h>
#include "C:\Visual Studio\labengine\labengine.h"
#include <math.h>
#include <Windows.h>
#define GRAV 9.80665 //��������� ���������� �������

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
	LabDrawLine(screen->x1.x, b.y, screen->x2.x, b.y); //������ �������������� ���
	LabDrawLine(b.x, screen->x1.y, b.x, screen->x2.y); //������ ������������ ���
	LabDrawFlush(); //���������� �� ������
}

point_t VecSum(point_t a, point_t b) { //��������� 2 �������
	point_t c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return c;
}

point_t VecMult(point_t a, double n) { //�������� ������ �� �����
	point_t c;
	c.x = a.x * n;
	c.y = a.y * n;
	return c;
}

//������ ������������� ���������� �������� 
void DrawAnalyticalPath(rect_t const* math, rect_t const* screen, point_t r0, point_t v0, point_t a0, double dt) {
	point_t b = Transform(r0, math, screen); //����������� ����������
	point_t r, d;
	double tmax = -2 * v0.y / a0.y;
	for (double t = 0.0; t <= tmax; t += dt) {
		r = VecSum(VecSum(r0, VecMult(v0, t)), VecMult(a0, t * t * 0.5));
		point_t d = Transform(r, math, screen); //����������� ����������
		LabDrawLine(b.x, b.y, d.x, d.y); //������ �����
		b = d;
		LabDrawFlush(); //���������� �� ������
	}
}

//������ ���������� ��������, �� � ������ �������� ���� �������
void DrawEulerPath(rect_t const* math, rect_t const* screen, point_t r0, point_t v0, point_t a0, double dt) {
	point_t r, d;
	point_t sk = { 0.0, 0.0 }; //������ ������-�������
	point_t fk = { 0.0, 0.0 }; //����� ������-�������
	point_t dv = { 0.0, 0.0 }; //��������� ��������
	point_t dr = { 0.0, 0.0 }; //��������� ������-�������
	double t = 0.0; //�����

	do {
		t += dt;

		v0 = VecSum(v0, dv); //������� ���������� ��������

		dv = VecMult(a0, dt); //������� ��������� ��������

		r0 = VecSum(r0, VecMult(v0, dt)); //������� ���������� ������-������

		fk = r0;

		point_t b = Transform(sk, math, screen); //����������� ���������� ������
		point_t d = Transform(fk, math, screen); //����������� ���������� �����
		sk = fk; //����������� ���������� ����� ����������� ������ ��� ��������� ��������

		LabDrawLine(b.x, b.y, d.x, d.y);
		LabDrawFlush(); //���������� �� ������
	} while (fk.y > 0); //����� ���������� ���� ��� �� ����������
}

//������ ���������� �������� ��������� � �������� �������
void SimulateEulerPath(rect_t const* math, rect_t const* screen, point_t r0, point_t v0, point_t a0) {
	point_t r, d;
	point_t sk = { 0.0, 0.0 }; //������ ������-�������
	point_t fk = { 0.0, 0.0 }; //����� ������-�������
	point_t dv = { 0.0, 0.0 }; //��������� ��������
	point_t dr = { 0.0, 0.0 }; //��������� ������-�������
	double t = 0.0; //�����

	LARGE_INTEGER freq, start, end;

	QueryPerformanceFrequency(&freq); //�������� ������� �����������
	QueryPerformanceCounter(&start); //���������� ����� ������
	QueryPerformanceCounter(&end); //���������� ����� �����
	double dt = (double)(end.QuadPart - start.QuadPart) / (double)freq.QuadPart; //������� ������� �� �������
																				 //����� ������� �������� � ������
	do {
		v0 = VecSum(v0, dv); //������� ���������� ��������

		dv = VecMult(a0, dt); //������� ��������� ��������

		r0 = VecSum(r0, VecMult(v0, dt)); //������� ���������� ������-������

		fk = r0;

		point_t b = Transform(sk, math, screen); //����������� ���������� ������
		point_t d = Transform(fk, math, screen); //����������� ���������� �����
		sk = fk; //����������� ���������� ����� ����������� ������ ��� ��������� ��������

		LabDrawLine(b.x, b.y, d.x, d.y); //������ �����
		LabDrawFlush(); //���������� �� ������
		QueryPerformanceCounter(&end); //���������� ����� ����� ��������
		dt = (double)(end.QuadPart - start.QuadPart) / (double)freq.QuadPart; //������� ������� �� ������� (� ��������)
																			  //����� ������� �������� � ������
		start = end;
		t += dt;
	} while (fk.y > 0); //����� ���������� ���� ��� �� ����������
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
		sys2.x = width;
		sys2.y = height;
		point_t sys3; //������� ����� ����� �������������� � ������������� �����������
		sys3.x = -3;
		sys3.y = 28;
		point_t sys4; //������ ������ ����� �������������� � ������������� �����������
		sys4.x = 41;
		sys4.y = -5;

		rect_t screen, math;
		//���������� ���������� 2 ����� � ��������� ��� "���������" ��������������
		screen.x1 = sys1;
		screen.x2 = sys2;
		//���������� ���������� 2 ����� � ��������� ��� "���������������" ��������������
		math.x1 = sys3;
		math.x2 = sys4;

		DrawAxes(&math, &screen); //������ ������������ ���

		double v = 20;
		double dt1 = 0.5;
		double dt2 = 1;
		point_t a0, v0, r0;
		a0.x = 0;
		a0.y = -GRAV;
		v0.x = v * cos(M_PI / 3);
		v0.y = v * sin(M_PI / 3);
		r0.x = 0;
		r0.y = 0;

		LabSetColor(LABCOLOR_GREEN); //����
		DrawAnalyticalPath(&math, &screen, r0, v0, a0, dt1);
		DrawAnalyticalPath(&math, &screen, r0, v0, a0,dt2);

		LabSetColor(LABCOLOR_RED); //����
		DrawEulerPath(&math, &screen, r0, v0, a0, dt1);
		DrawEulerPath(&math, &screen, r0, v0, a0, dt2);

		LabSetColor(LABCOLOR_YELLOW); //����
		SimulateEulerPath(&math, &screen, r0, v0, a0);

		LabInputKey(); //��� ������� �������
		LabTerm();
	}
	return 0;
}