/*Программа рисует траекторию движения тела, брошенного под углом к горизонту*/
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <locale.h>
#include "C:\Visual Studio\labengine\labengine.h"
#include <math.h>
#include <Windows.h>
#define GRAV 9.80665 //ускорение свободного падения

typedef struct { //структура координат точки
	double x;
	double y;
}point_t;

typedef struct { //структура для прямоугольной области, то есть для 2 точек прямоугольника
	point_t x1;
	point_t x2;
}rect_t;

point_t Transform(point_t p, rect_t const* from, rect_t const* to) { //преобразует координаты из экранной СК
	point_t s;														 //в математическую СК
	s.x = (p.x - from->x1.x) * (to->x2.x - to->x1.x) / (from->x2.x - from->x1.x) + to->x1.x; //для х
	s.y = (p.y - from->x1.y) * (to->x2.y - to->x1.y) / (from->x2.y - from->x1.y) + to->x1.y; //для у
	return s;
}

void DrawAxes(rect_t const* math, rect_t const* screen) { //рисует оси новой СК
	point_t a; //точка - начало координат
	a.x = 0;
	a.y = 0;
	point_t b = Transform(a, math, screen); //преобразует координаты
	LabDrawLine(screen->x1.x, b.y, screen->x2.x, b.y); //рисует горизонтальную ось
	LabDrawLine(b.x, screen->x1.y, b.x, screen->x2.y); //рисует вертикальную ось
	LabDrawFlush(); //отображает на экране
}

point_t VecSum(point_t a, point_t b) { //суммирует 2 вектора
	point_t c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return c;
}

point_t VecMult(point_t a, double n) { //умножает вектор на число
	point_t c;
	c.x = a.x * n;
	c.y = a.y * n;
	return c;
}

//рисует аналитическую траекторию движения 
void DrawAnalyticalPath(rect_t const* math, rect_t const* screen, point_t r0, point_t v0, point_t a0, double dt) {
	point_t b = Transform(r0, math, screen); //преобразует координаты
	point_t r, d;
	double tmax = -2 * v0.y / a0.y;
	for (double t = 0.0; t <= tmax; t += dt) {
		r = VecSum(VecSum(r0, VecMult(v0, t)), VecMult(a0, t * t * 0.5));
		point_t d = Transform(r, math, screen); //преобразует координаты
		LabDrawLine(b.x, b.y, d.x, d.y); //рисует линию
		b = d;
		LabDrawFlush(); //отображает на экране
	}
}

//рисует траекторию движения, но с учетом действия силы тяжести
void DrawEulerPath(rect_t const* math, rect_t const* screen, point_t r0, point_t v0, point_t a0, double dt) {
	point_t r, d;
	point_t sk = { 0.0, 0.0 }; //начало радиус-вектора
	point_t fk = { 0.0, 0.0 }; //конец радиус-вектора
	point_t dv = { 0.0, 0.0 }; //изменение скорости
	point_t dr = { 0.0, 0.0 }; //изменение радиус-вектора
	double t = 0.0; //время

	do {
		t += dt;

		v0 = VecSum(v0, dv); //находит измененную скорость

		dv = VecMult(a0, dt); //находит изменение скорости

		r0 = VecSum(r0, VecMult(v0, dt)); //находит измененный радиус-вектор

		fk = r0;

		point_t b = Transform(sk, math, screen); //преобразует координаты начала
		point_t d = Transform(fk, math, screen); //преобразует координаты конца
		sk = fk; //присваивает координаты конца координатам начала для следующей итерации

		LabDrawLine(b.x, b.y, d.x, d.y);
		LabDrawFlush(); //отображает на экране
	} while (fk.y > 0); //чтобы траектория ниже оси не опускалась
}

//рисует траекторию движения синхронно с течением времени
void SimulateEulerPath(rect_t const* math, rect_t const* screen, point_t r0, point_t v0, point_t a0) {
	point_t r, d;
	point_t sk = { 0.0, 0.0 }; //начало радиус-вектора
	point_t fk = { 0.0, 0.0 }; //конец радиус-вектора
	point_t dv = { 0.0, 0.0 }; //изменение скорости
	point_t dr = { 0.0, 0.0 }; //изменение радиус-вектора
	double t = 0.0; //время

	LARGE_INTEGER freq, start, end;

	QueryPerformanceFrequency(&freq); //получает частоту процесссора
	QueryPerformanceCounter(&start); //запоминает время начала
	QueryPerformanceCounter(&end); //запоминает время конца
	double dt = (double)(end.QuadPart - start.QuadPart) / (double)freq.QuadPart; //находит разницу во времени
																				 //между началом итерации и концом
	do {
		v0 = VecSum(v0, dv); //находит измененную скорость

		dv = VecMult(a0, dt); //находит изменение скорости

		r0 = VecSum(r0, VecMult(v0, dt)); //находит измененный радиус-вектор

		fk = r0;

		point_t b = Transform(sk, math, screen); //преобразует координаты начала
		point_t d = Transform(fk, math, screen); //преобразует координаты конца
		sk = fk; //присваивает координаты конца координатам начала для следующей итерации

		LabDrawLine(b.x, b.y, d.x, d.y); //рисует линию
		LabDrawFlush(); //отображает на экране
		QueryPerformanceCounter(&end); //запоминает время конца итерации
		dt = (double)(end.QuadPart - start.QuadPart) / (double)freq.QuadPart; //находит разницу во времени (в секундах)
																			  //между началом итерации и концом
		start = end;
		t += dt;
	} while (fk.y > 0); //чтобы траектория ниже оси не опускалась
}

int main(void)
{
	if (LabInit())
	{
		double width = LabGetWidth(); //ширина
		double height = LabGetHeight(); //высота

		point_t sys1; //верхняя левая точка прямоугольника в экранных координатах
		sys1.x = 0;
		sys1.y = 0;
		point_t sys2; //нижняя правая точка прямоугольника в экранных координатах
		sys2.x = width;
		sys2.y = height;
		point_t sys3; //верхняя левая точка прямоугольника в математичеких координатах
		sys3.x = -3;
		sys3.y = 28;
		point_t sys4; //нижняя правая точка прямоугольника в математичеких координатах
		sys4.x = 41;
		sys4.y = -5;

		rect_t screen, math;
		//записывает координаты 2 точек в структуру для "экранного" прямоугольника
		screen.x1 = sys1;
		screen.x2 = sys2;
		//записывает координаты 2 точек в структуру для "математического" прямоугольника
		math.x1 = sys3;
		math.x2 = sys4;

		DrawAxes(&math, &screen); //рисует координатные оси

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

		LabSetColor(LABCOLOR_GREEN); //цвет
		DrawAnalyticalPath(&math, &screen, r0, v0, a0, dt1);
		DrawAnalyticalPath(&math, &screen, r0, v0, a0,dt2);

		LabSetColor(LABCOLOR_RED); //цвет
		DrawEulerPath(&math, &screen, r0, v0, a0, dt1);
		DrawEulerPath(&math, &screen, r0, v0, a0, dt2);

		LabSetColor(LABCOLOR_YELLOW); //цвет
		SimulateEulerPath(&math, &screen, r0, v0, a0);

		LabInputKey(); //ждёт нажатия клавиши
		LabTerm();
	}
	return 0;
}