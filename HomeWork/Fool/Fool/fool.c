#include "fool.h"

/**
 * -----------------------------------
 * MATH FUNCTIONS
 * -----------------------------------
 */

/**
 * \brief Auxiliary function that returns a number in a new interval
 * \param n number itself
 * \return a number in the range from 0 to 1
 */
fool_t NewNumber(fool_t n) {
	return n / 10000;
}

/**
 * \brief Function performs the operation logical "and" (conjunction)
 * \param number1 pointer to the first number
 * \param number2 pointer to the second number
 * \return the minimum of two numbers between 0 and 1
 */
fool_t foolAnd(fool_t number1, fool_t number2) {
	return (fabs(NewNumber(number1)) < fabs(NewNumber(number2))) ? fabs(NewNumber(number1)) : fabs(NewNumber(number2));
}

/**
 * \brief Function performs the operation logical "or" (disjunction)
 * \param number1 pointer to the first number
 * \param number2 pointer to the second number
 * \return the maximum of two numbers between 0 and 1
 */
fool_t foolOr(fool_t number1, fool_t number2) {
	return (fabs(NewNumber(number1)) > fabs(NewNumber(number2))) ? fabs(NewNumber(number1)) : fabs(NewNumber(number2));
}

/**
 * \brief Function performs the logical "not" (negation) operation
 * \param number number itself
 * \return (1 - number) between 0 and 1
 */
fool_t foolNot(fool_t number) {
	return (NewNumber(number) > 0) ? (1 - NewNumber(number)): (1 + NewNumber(number));
}

/**
 * \brief Funtion compares two numbers
 * \param number1 pointer to the first number
 * \param number2 pointer to the second number
 * \return 1 if first number is bigger than second, -1 if less and 0 of numbers are equal
 */
int foolCompare(const fool_t* number1, const fool_t* number2) {
	int res = foolAsInt(*number1 - *number2);
	return (res > 0) ? 1 : (res < 0 ? -1 : 0);
}

/**
 * -----------------------------------
 * CONVERT FUNCTIONS
 * -----------------------------------
 */

 /**
  * \brief Function converts "int" type number to "fool_t"
  * \param number number itself
  * \return converted number
  */
fool_t foolFromInt(int number) {
	return (fool_t)number;
}

/**
 * \brief Function converts "double" type number to "fool_t"
 * \param number - number itself
 * \return converted number
 */
fool_t foolFromDouble(double number) {
	return number;
}

/**
 * \brief Function converts "fool_t" type number to classic "int"
 * \param number number itself
 * \return converted number
 */
int foolAsInt(fool_t number) {
	if (number > INT_MAX) return INT_MAX;
	if (number < INT_MIN) return INT_MIN;
	return (int)number;
}

/**
 * \brief Function converts "fool_t" type number to classic "double"
 * \param number number itself
 * \return converted number
 */
double foolAsDouble(fool_t number) {
	return (double)number;
}

/**
 * \brief Function converts number as string (format: "fool[<number>]") to "fool_t" type
 * \param str number as string
 * \return converted number
 */
fool_t foolParse(const char* str) {
	fool_t number = 0.0;
	int i = 0, sign = 1;
	if (*str != 'f') {
		printf("Incorect format");
		exit(-1);
	}
	str += 5; ///so that "fool[" is not read
	if (str[i] == '-') {
		sign = -1;
		i++;
	}
	else if (str[i] == '+') i++;
	///reading the integer part
	while (str[i] != '\0' && str[i] != '.' && str[i] != ']') {
		number = number * 10 + sign * (str[i] - '0');
		i++;
	}
	if (str[i] == '.') i++;
	///reading the float part
	for (int j = 1; str[i] != ']'; j++) {
		number = number + sign * (str[i] - '0') * pow(10, -j);
		if (str[i] == '\0') break;
		i++;
	}

	return number;
}

/**
 * \brief Auxiliary function that writes array elements in reverse order
 * \param str number as string
 * \param len number its lenght
 */
void reverse(char* str, int len) {
	int i = 0, j = len - 1, temp;
	while (i < j) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

/**
 * \brief Auxiliary function that writes an integer digit by digit to an array
 * \param x number itself
 * \param str number as string
 * \param d is the number of digits required in the output
 * \return lenght of string
 */
int intToStr(int x, char* str, int d) {
	int i = 0;
	while (x) {
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}
	while (i < d) str[i++] = 0;

	reverse(str, i);
	str[i] = '\0';
	return i;
}

/**
 * \brief Auxiliary function that writes a floating-point number to an array
 * \param n number itself
 * \param res number as string
 * \return lenght of number
 */
int ftoa(fool_t n, char* res) {
	///extracts the integer part
	int ipart = (int)n;
	///extracts the float part
	fool_t fpart = n - (fool_t)ipart;
	///converts the integer part of a number to a string
	int i = intToStr(ipart, res, 0);
	int j = -1;
	///if the float part is not equal to 0
	if (fpart != 0) {
		res[i] = '.'; ///adds dot
		fpart = fpart * 100; ///because 2 digits after dot
		j = intToStr((int)fpart, res + i + 1, 2);
	}
	return i + j + 1;
}

/**
 * \brief Function converts number as "fool_t" type to string (format: "fool[<number>]")
 * \param number number itself
 * \return converted to string number
 */
char* foolFormat(fool_t number) {
	int sign = 1;
	if (number < 0) {
		sign = -1;
		number = -number;
	}
	char str1[50];
	int k = ftoa(number, str1);
	
	char* str = malloc(sizeof(fool_t) * (k + 8));
	if (str == NULL) return "ERROR IN MEMORY ALLOCATION";
	///fills the array
	str[0] = 'f';
	str[1] = 'o';
	str[2] = 'o';
	str[3] = 'l';
	str[4] = '[';
	if (sign == -1) str[5] = '-';
	if (sign == 1) str[5] = '+';
	for (int i = 0; i < k; i++) {
		str[i + 6] = str1[i];
	}
	str[k + 6] = ']';
	str[k + 7] = '\0';

	return str;
}

/**
 * -----------------------------------
 * CONSOLE INPUT/OUTPUT FUNCTIONS
 * -----------------------------------
 */

 /**
  * \brief Function reads the number from the console "fool[<number>]" and converts to "fool_t"
  * \return read number as "fool_t" num
  */
fool_t foolRead() {
	char num[100];
	fgets(num, 100, stdin);

	int i = 0;

	while (num[i] != '\n' && num[i] != '\0') i++;
	num[i] = '\0';
	return foolParse(num);
}

/**
 * \brief Function writes the number in the console as "fool[<number>]"
 * \param number number itself
 */
void foolWrite(fool_t number) {
	char* pNewStr = foolFormat(number);
	printf("%s", foolFormat(number));
	free(pNewStr);
}