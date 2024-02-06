#include <fool.h>

int main() {
	printf("Enter first number in the format 'fool[1234.56]'\n");
	fool_t num1 = foolRead();
	printf("Enter second number in the format 'fool[1234.56]'\n");
	fool_t num2 = foolRead();
	printf("Result of the function foolAsInt\n");
	printf("%i\n", foolAsInt(num1));
	printf("Result of the function foolAsDouble\n");
	printf("%.2lf\n", foolAsDouble(num1));
	printf("Result of the function foolAnd\n");
	printf("%.2lf\n", foolAsDouble(foolAnd(num1, num2)));
	printf("Result of the function foolOr\n");
	printf("%.2lf\n", foolAsDouble(foolOr(num1, num2)));
	printf("Result of the function foolNot\n");
	printf("%.2lf\n", foolAsDouble(foolNot(num1)));
	printf("Result of the function foolCompare\n");
	printf("%i\n", foolAsInt(foolCompare(&num1, &num2)));
	printf("Result of the function foolFormat\n");
	printf("%s\n", foolFormat(num1));
	printf("Result of the function foolWrite\n");
	foolWrite(num2);
	printf("\n");
	char* str = "fool[15.86]";
	printf("Result of the function foolParse\n");
	printf("%.2lf\n", foolAsDouble(foolParse(str)));

	free(foolFormat(num1));
	return 0;
}