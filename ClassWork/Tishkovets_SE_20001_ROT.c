/*Программа, циклически сдвигающая элементы массива на заданное число позиций delta*/
#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#define N 9

void Fill(int arr[], int size) { //заполняет массив числами от 0 до N
	for (int i = 0; i < size; i++) {
		arr[i] = i + 1;
	}
}

void Print(int arr[], int size) { //печатает массив
	for (int i = 0; i < size; i++) {
		printf("%i ", arr[i]);
	}
	printf("\n");
}

void Shift1(int arr[], int size) { //сдвигает элементы массива на одну позицию влево
	int s = arr[0]; //вспомогательная переменная
	for (int i = 1; i < size; i++) {
		arr[i - 1] = arr[i];
	}
	arr[size - 1] = s;
}

void Shift_Ver1(int arr[], int size, int delta) { //тоже сдвигает элементы массива влево, но уже на заданное число позиций delta
	for (int i = 0; i < (delta % size); i++) { //именно delta % size, чтобы учесть случай, когда delta >= N
		Shift1(arr, size);
	}
}

void Reverse(int arr[], int left, int right) { //это уже другой способ сдвигания элементов массива
	int l = right - left + 1;
	for (int i = left; i < left + l / 2; i++) {  //можно записать и таким образом:
		int t = arr[i];                          //arr[i] ^= arr[right - i + left];
		arr[i] = arr[right - i + left];          //arr[right - i + left] ^= arr[i];
		arr[right - i + left] = t;               //arr[i] ^= arr[right - i + left];
	}
}

void Shift_Ver2(int arr[], int size, int delta) { //сначала разворачиваем весь массив потом левые и правые части
	if (delta != 0) {                             //относительно воображаемой черты идущей после элемента с номером
		delta %= size;                            //(не индексом) сдвига delta = 3 (например). Было 1 2 3 | 4 5 6 7 8 9
		Reverse(arr, 0, size - 1);                // 9 8 7 6 5 4 | 3 2 1 
		Reverse(arr, 0, size - delta - 1);        // 4 5 6 7 8 9 | 3 2 1  результаты после каждой из строк
		Reverse(arr, size - delta, size - 1);     // 4 5 6 7 8 9 | 1 2 3 
	}
}

int main(void) {
	setlocale(LC_CTYPE, "Russian");
	printf("Тишковец Сергей, группа 5030102/20001, ROT\n");
	int arr[N];
	int delta; //это и есть число позиций, на которое сдвигаем каждый элемент, т.е. величина сдвига массива
	printf("Введите сдвиг: ");
	scanf("%d", &delta);
	printf("Первый способ:\n");
	Fill(arr, N);
	Print(arr, N);
	delta %= N; //подчищаем delta и сразу проверяем на равенство 0
	if (delta != 0) Shift_Ver1(arr, N, delta); //если delta = 0, то функцию и не придется вызывать
	Print(arr, N);
	printf("Второй способ:\n");
	Fill(arr, N);
	Print(arr, N);
	if (delta != 0) Shift_Ver2(arr, N, delta); //аналогично 1-ой функции
	Print(arr, N);
	return 0;
}