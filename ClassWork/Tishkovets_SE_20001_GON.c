#define _USE_MATH_DEFINES
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "labengine\labengine.h"
#include <locale.h>
#include <math.h>
#include <malloc.h>

typedef struct { //структура дл€ многоугольника
	double angle; //начальный угол
	int Cx; //координаты центра
	int Cy;
	int R; //радиус описанной окружности
	int nCorners; //кол-во углов
} polyg_t;

void Draw(polyg_t a) { //отдельна€ функци€ дл€ рисовани€ многоугольника
	int b = a.Cx + a.R * cos(a.angle); //перва€ вершина, координата х
	int c = a.Cy + a.R * sin(a.angle); //перва€ вершина, координата у
	int b1 = 0, c1 = 0; //будущие координаты 2-й вершины
	for (int i = 0; i < a.nCorners; i++) {
		a.angle += (double)M_PI * 2 / a.nCorners; //изменение угла
		b1 = a.Cx + a.R * cos(a.angle); //те самые новые координаты
		c1 = a.Cy + a.R * sin(a.angle);
		LabDrawLine(b, c, b1, c1); //рисует линию
		LabDrawFlush(); //отображает на экране
		b = b1;
		c = c1;
	}
}

int main(void) {
	if (LabInit())
	{
		int width = LabGetWidth(); //узнает ширину экрана
		int height = LabGetHeight(); //узнает высоту экрана
		LabSetColor(LABCOLOR_GREEN); //цвет

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

		polyg_t n = { 0.0, width / 2, height / 2, height / 2, 5 }; //объ€вление структуры
		do
		{
			LabSetColor(LABCOLOR_GREEN); //цвет
			Draw(n); //вызывает функцию
			n.angle -= 0.05; //мен€ет угол дл€ вращени€ фигуры
			LabDrawFlush();
			LabDelay(5);
			LabClear(); //очищает экран
		} while (!LabInputKeyReady()); //ждет нажани€ клавиши
		LabTerm(); //закрывает окно
	}
	return 0;

}