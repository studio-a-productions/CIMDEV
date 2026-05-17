#include <math.h>
/* 
	[CIM:DOC]
	It does not matter if you use CIM_USE_LOWERCASE in the implementation, but for simplicity, we don't.	
*/
#define CIM_IMPLEMENT
#include "cim.h"

CIMDEF CCONST CBOOL CIM_STD_BOOL_TRUE =		(CBOOL)1U;
CIMDEF CCONST CBOOL CIM_STD_BOOL_FALSE =	(CBOOL)0U;


CIMDEF CFLOAT CIMCALL CIM_STD_SQRT_FUNC(CFLOAT f) {
	return sqrtf(f);
}

CIMDEF CDOUBLE CIMCALL CIM_STD_LSQRT_FUNC(CDOUBLE d) {
	return sqrt(d);
}