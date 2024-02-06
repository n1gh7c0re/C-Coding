#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <malloc.h>
#include <math.h>
#include <float.h>

typedef double fool_t; ///new type

/**
 * -----------------------------------
 * MATH FUNCTIONS
 * -----------------------------------
 */

/**
 * \brief Function performs the operation logical "and" (conjunction)
 * \param number1 pointer to the first number
 * \param number2 pointer to the second number
 * \return the minimum of two numbers
 */
fool_t foolAnd(fool_t number1, fool_t number2);

/**
 * \brief Function performs the operation logical "or" (disjunction)
 * \param number1 pointer to the first number
 * \param number2 pointer to the second number
 * \return the maximum of two numbers
 */
fool_t foolOr(fool_t number1, fool_t number2);

/**
 * \brief Function performs the logical "not" (negation) operation
 * \param number number itself
 * \return number: (1 - number)
 */
fool_t foolNot(fool_t number);

/**
 * \brief Funtion compares two numbers
 * \param number1 pointer to the first number
 * \param number2 pointer to the second number
 * \return 1 if first number is bigger than second, -1 if less and 0 of numbers are equal
 */
int foolCompare(const fool_t* number1, const fool_t* number2);

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
fool_t foolFromInt(int number);

/**
 * \brief Function converts "double" type number to "fool_t"
 * \param number - number itself
 * \return converted number
 */
fool_t foolFromDouble(double number);

/**
 * \brief Function converts "fool_t" type number to classic "int"
 * \param number number itself
 * \return converted number
 */
int foolAsInt(fool_t number);

/**
 * \brief Function converts "fool_t" type number to classic "double"
 * \param number number itself
 * \return converted number
 */
double foolAsDouble(fool_t number);

/**
 * \brief Function converts number as string (format: "fool[<number>]") to "fool_t" type
 * \param str number as string
 * \return converted number
 */
fool_t foolParse(const char* str);

/**
 * \brief Function converts number as "fool_t" type to string (format: "fool[<number>]")
 * \param number number itself
 * \return converted to string number
 */
char* foolFormat(fool_t number);

/**
 * -----------------------------------
 * CONSOLE INPUT/OUTPUT FUNCTIONS
 * -----------------------------------
 */

/**
 * \brief Function reads the number from the console "fool[<number>]" and converts to "fool_t"
 * \return read number as "fool_t" num
 */
fool_t foolRead();

/**
 * \brief Function writes the number in the console as "fool[<number>]"
 * \param number number itself
 */
void foolWrite(fool_t number);