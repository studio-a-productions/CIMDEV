#include <stdio.h>

#define CIM_USE_LOWERNAME
#include "cim.h"

int main() {
	cfloat myvar = 4.001F;

	printf("%f : %f", myvar, cim_sqrt(myvar));
	return 0;
}