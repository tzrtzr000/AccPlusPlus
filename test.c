#include <stdio.h>


float subtract(float in1, float in2)
{
	float ret = 0.0;
	asm ("fsubr %2, %0" : "=&t" (ret) : "%0" (in1), "u" (in2));
    return ret;
}

int main(void){
	float a1, a2, a3;
	a1 = 0.03;
	a2 = 0.02;
	a3 = a1 - a2;
	//a3 = subtract(a2, a1);
	printf("a3 is %lf\n", a3);

	return 0;
}