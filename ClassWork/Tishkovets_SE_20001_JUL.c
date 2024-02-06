#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <locale.h>
#include "C:\Visual Studio\labengine\labengine.h"
#include <math.h>

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
	LabSetColor(LABCOLOR_GREEN); //цвет
	LabDrawLine(screen->x1.x, b.y, screen->x2.x, b.y); //рисует горизонтальную ось
	LabDrawLine(b.x, screen->x1.y, b.x, screen->x2.y); //рисует вертикальную ось
	LabDrawFlush(); //отображает на экране
}

labbool_t IsInsideDisk(point_t p) { //проверяет, лежит ли точка внутри окружности радиуса r
	if ((p.x * p.x + p.y * p.y) <= 1) return LAB_TRUE;
	else return LAB_FALSE;
}

void DrawDisk(rect_t const* math, rect_t const* screen) { //рисует диск
	point_t a; //точка - начало координат
	a.x = 0;
	a.y = 0;
	point_t b = Transform(a, math, screen); //преобразует координаты
	point_t c, d;
	int r = 1;
	for (double i = screen->x1.x; i <= screen->x2.x; i++) { //пробегается по иксам
		for (double j = screen->x1.y; j <= screen->x2.y; j++) { //пробегается по игрекам
			c.x = i;
			c.y = j;
			d = Transform(c, screen, math); //преобразует координаты
			if (IsInsideDisk(d) == LAB_TRUE) { //проверка условия, что точка лежит в пределах окружности радуиса r
				LabDrawPoint(i, j); //рисует точку
			}
		}
	}
	LabDrawFlush(); //отображает на экране
}

labbool_t IsInsideJulia(point_t p) { //проверяет условие, что точка принадлежит множеству Жюлиа
	point_t c; //константа
	//c.x = -0.12375;
	//c.y = 0.56508;
	c.x = -0.500934515513869749377; //так будет красивее
	c.y = -0.52287731735700945607;
	point_t res;
	int N = 100; //предельное число итераций
	int r = 2; //радиус
	for (int i = 0; i < N; i++) {
		res.x = p.x * p.x - p.y * p.y + c.x;
		res.y = p.x * p.y + p.x * p.y + c.y;
		p.x = res.x;
		p.y = res.y;
		if (res.x * res.x + res.y * res.y > (r * r)) return LAB_FALSE; //условие для выхода из цикла
	}
	return LAB_TRUE;
}

void DrawJulia(rect_t const* math, rect_t const* screen) { //рисует множество Жюлиа
	point_t c, d;
	for (int i = screen->x1.x; i <= screen->x2.x; i++) { //пробегается по иксам
		for (int j = screen->x1.y; j <= screen->x2.y; j++) { //пробегается по игрекам
			c.x = i;
			c.y = j;
			d = Transform(c, screen, math); //преобразует координаты
			if (IsInsideJulia(d) == LAB_TRUE) { //проверка условия, что точка принадлежит множеству Жюлиа
				LabDrawPoint(i, j); //рисует точку
			}
		}
	}
	LabDrawFlush(); //отображает на экране
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
		sys2.x = width / 2;
		sys2.y = height;
		point_t sys3; //верхняя левая точка прямоугольника в математичеких координатах
		sys3.x = -2;
		sys3.y = 3;
		point_t sys4; //нижняя правая точка прямоугольника в математичеких координатах
		sys4.x = 2;
		sys4.y = -3;

		rect_t screen, math;
		//записывает координаты 2 точек в структуру для "экранного" прямоугольника
		screen.x1 = sys1;
		screen.x2 = sys2;
		//записывает координаты 2 точек в структуру для "математического" прямоугольника
		math.x1 = sys3;
		math.x2 = sys4;

		DrawAxes(&math, &screen);
		DrawDisk(&math, &screen);

		rect_t screen_new;
		point_t an, bn; //координаты точек для 2-й СК (в правой части окна)
		an.x = width / 2;
		an.y = 0;
		bn.x = width;
		bn.y = height;
		screen_new.x1 = an;
		screen_new.x2 = bn;

		DrawAxes(&math, &screen_new);
		DrawJulia(&math, &screen_new);

		LabInputKey(); //ждёт нажатия клавиши
		LabTerm();
	}
	return 0;
}