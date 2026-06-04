#ifndef CIM_H
#define CIM_H

#if defined(__cplusplus)
#ifndef CIMEXTR
#define CIMEXTR extern "C"
#endif

#define CIM_VERSION_MAJ 1U
#define CIM_VERSION_MIN 0U
#define CIM_VERSION_PATCH 0U


#ifndef CCONSTEXPR
#define CCONSTEXPR constexpr
#endif

#else
#ifndef CIMEXTR
#define CIMEXTR extern
#endif

/* Because we do our parts for the cause! */
#ifndef CCONSTEXPR
#define CCONSTEXPR const
#endif

#endif

/*
	[CIM:DOC]
	CIM uses 'reserved names' for extern functions. The convention is CIM_STD_(name)_FUNC for std functions. To be sure, look at the list.

	C-std: CIM_STD_*_FUNC
	cim extra: CIM_ADV_*_*(_FUNC)
*/

#ifdef CIM_IMPLEMENT
#define CIMDEF
#else
#define CIMDEF CIMEXTR
#endif

#ifndef CIMCALL
#define CIMCALL 
#endif


#ifndef CIMSIGN
#define CIMSIGN signed
#endif

#ifndef CIMUNSIGN
#define CIMUNSIGN unsigned
#endif

#ifndef CCONST
#define CCONST const
#endif


/* We'd rather have a unsigned char, but compilers might complain. */
#ifndef CCHAR
#define CCHAR char
#endif

#ifndef CINT64
#define CINT64 CIMSIGN long long
#endif

#ifndef CINT32
#define CINT32 CIMSIGN long
#endif

#ifndef CINT16
#define CINT16 CIMSIGN short
#endif

#ifndef CINT8
#define CINT8 CIMSIGN char
#endif

#ifndef CUINT64
#define CUINT64 CIMUNSIGN long long
#endif

#ifndef CUINT32
#define CUINT32 CIMUNSIGN long
#endif

#ifndef CUINT16
#define CUINT16 CIMUNSIGN short
#endif

#ifndef CUINT8
#define CUINT8 CIMUNSIGN char
#endif

#ifndef CVOID
#define CVOID void
#endif

#ifndef CFLOAT
#define CFLOAT float
#endif 

#ifndef CDOUBLE
#define CDOUBLE double
#endif

#ifndef CINT
#define CINT CINT32
#endif

#ifndef CUINT
#define CUINT CUINT32
#endif

#ifndef CBYTE
#define CBYTE CUINT8
#endif

#ifndef CIZE
#define CIZE CUINT
#endif

#ifndef CBOOL
#define CBOOL CBYTE
#endif

#ifndef CTRUE
CIMDEF CCONST CBOOL CIM_STD_BOOL_TRUE;
#define CTRUE CIM_STD_BOOL_TRUE
#endif

#ifndef CFALSE
CIMDEF CCONST CBOOL CIM_STD_BOOL_FALSE;
#define CFALSE CIM_STD_BOOL_FALSE
#endif


#ifndef CIZEOF
// for systems where you need to work in bits, you could do *8
#define CIZEOF(a) (CIZE)(sizeof(a))
#endif


/*
	[CIM:DOC]
	If not overwriting these, you may implement functions as defined by CIMDEF.

	Use "CIM_IMPLEMENT" when you want to actually define these yourself, otherwise, to overwrite, you must pre-define these.

	These functions are binded to their CIM-internals, but instead of using "macro functions", these names are replaced with the actual function name. You need not worry about this when overwriting these.

	[CIM:VOC]
	Overwrite function:		to use #define (name) to redirect calls to your own internal logic or macros
	Implement function;		to create a "CIM_IMPLEMENT" file and defining the functions within.

*/

#ifdef __cplusplus
#ifndef CNULL
#define CNULL nullptr
#endif
#else
#ifndef CNULL
#define CNULL ((CVOID*)0)
#endif
#endif

#ifndef CIM_SQRT
CIMDEF CIMCALL CFLOAT CIM_STD_SQRT_FUNC(CFLOAT);
#define CIM_SQRT CIM_STD_SQRT_FUNC
#endif

#ifndef CIM_LSQRT
CIMDEF CIMCALL CDOUBLE CIM_STD_LSQRT_FUNC(CDOUBLE);
#define CIM_LSQRT CIM_STD_LSQRT_FUNC
#endif


/* Mem Alloc/Free */

#ifndef CIM_MALLOC
CIMDEF CIMCALL CVOID* CIM_STD_MALLOC_FUNC(CIZE);
#define CIM_MALLOC CIM_STD_MALLOC_FUNC
#endif

#ifndef CIM_CALLOC 
CIMDEF CIMCALL CVOID* CIM_STD_CALLOC_FUNC(CIZE, CIZE);
#define CIM_CALLOC CIM_STD_CALLOC_FUNC
#endif

#ifndef CIM_REALLOC
CIMDEF CIMCALL CVOID* CIM_STD_REALLOC_FUNC(CVOID*, CIZE);
#define CIM_REALLOC CIM_STD_REALLOC_FUNC
#endif

#ifndef CIM_FREE
CIMDEF CIMCALL CVOID CIM_STD_FREE_FUNC(CVOID*);
#define CIM_FREE CIM_STD_FREE_FUNC
#endif


#ifndef CIM_MCPY
CIMDEF CIMCALL CVOID* CIM_STD_MCPY_FUNC(CVOID*, CCONST CVOID*, CIZE);
#define CIM_MCPY CIM_STD_MCPY_FUNC
#endif

#ifndef CIM_MMOVE
CIMDEF CIMCALL CVOID* CIM_STD_MMOVE_FUNC(CVOID*, CCONST CVOID*, CIZE);
#define CIM_MMOVE CIM_STD_MMOVE_FUNC
#endif

#ifndef CIM_MSET
CIMDEF CIMCALL CVOID* CIM_STD_MSET_FUNC(CVOID*, CINT, CIZE);
#define CIM_MSET CIM_STD_MSET_FUNC
#endif

#ifndef CIM_MCMP
CIMDEF CIMCALL CVOID* CIM_STD_MCMP_FUNC(CCONST CVOID*, CCONST CVOID*, CIZE);
#define CIM_MCMP CIM_STD_MCMP_FUNC
#endif


#ifndef CIM_ROUND
CIMDEF CIMCALL CFLOAT CIM_STD_ROUND_FUNC(CFLOAT);
#define CIM_ROUND CIM_STD_ROUND_FUNC
#endif

#ifndef CIM_LROUND
CIMDEF CIMCALL CDOUBLE CIM_STD_LROUND_FUNC(CDOUBLE);
#define CIM_LROUND CIM_STD_LROUND_FUNC
#endif

#ifndef CIM_POW
CIMDEF CIMCALL CFLOAT CIM_STD_POW_FUNC(CFLOAT, CINT);
#define CIM_POW CIM_STD_POW_FUNC
#endif

#ifndef CIM_LPOW
CIMDEF CIMCALL CDOUBLE CIM_STD_LPOW_FUNC(CDOUBLE, CINT);
#define CIM_LPOW CIM_STD_LPOW_FUNC
#endif

/* has CIM not sined?*/
#ifndef CIM_SIN
CIMDEF CIMCALL CFLOAT CIM_STD_SIN_FUNC(CFLOAT);
#define CIM_SIN CIM_STD_SIN_FUNC
#endif

#ifndef CIM_LSIN
CIMDEF CIMCALL CDOUBLE CIM_STD_LSIN_FUNC(CDOUBLE);
#define CIM_LSIN CIM_STD_LSIN_FUNC
#endif

#ifndef CIM_COS
CIMDEF CIMCALL CFLOAT CIM_STD_COS_FUNC(CFLOAT);
#define CIM_COS CIM_STD_COS_FUNC
#endif

#ifndef CIM_LCOS
CIMDEF CIMCALL CDOUBLE CIM_STD_LCOS_FUNC(CDOUBLE);
#define CIM_LCOS CIM_STD_LCOS_FUNC
#endif

#ifndef CIM_TAN
CIMDEF CIMCALL CFLOAT CIM_STD_TAN_FUNC(CFLOAT);
#define CIM_TAN CIM_STD_TAN_FUNC
#endif

#ifndef CIM_LTAN
CIMDEF CIMCALL CDOUBLE CIM_STD_LTAN_FUNC(CDOUBLE);
#define CIM_LTAN CIM_STD_LTAN_FUNC
#endif

/* IO STUFF, should normally be handled by cynCOSA, but for debug  */

#ifndef CIM_PRINTF
CIMDEF CIMCALL CVOID CIM_STD_PRINTF_FUNC(CCONST CCHAR*, ...);
#define CIM_PRINTF CIM_STD_PRINTF_FUNC
#endif

/* Experimental, prefer the use of cyncosa (Cyn's Cross Operating System Abstruction) */
#ifndef CIM_EXIT
CIMDEF CIMCALL CVOID CIM_STD_EXIT_FUNC(CCONST CCHAR*, ...);
#define CIM_EXIT CIM_STD_EXIT_FUNC
#endif


/*
	[CIM:DOC]
	CIM's advanced math (vector)
*/
#if defined(CIM_USE_ADV_MATH) || defined(CIM_USE_ADV)

#ifndef CIM_ADV_MATH_VEC_GEN2
#define CIM_ADV_MATH_VEC_GEN2(vec_name, vec_type) typedef union vec_name { struct coord { vec_type x,y; }; vec_type val[2]; } vec_name
#endif
#ifndef CIM_ADV_MATH_VEC_GEN3
#define CIM_ADV_MATH_VEC_GEN3(vec_name, vec_type) typedef union vec_name { struct coord { vec_type x,y,z; }; struct col { vec_type r,g,b; }; vec_type val[3]; } vec_name
#endif
#ifndef CIM_ADV_MATH_VEC_GEN4
#define CIM_ADV_MATH_VEC_GEN4(vec_name, vec_type) typedef union vec_name { struct coord { vec_type x,y,z,w; }; struct col { vec_type r,g,b,a; }; vec_type val[4]; } vec_name
#endif

#ifndef CVFLOAT2
CIM_ADV_MATH_VEC_GEN2(CIM_ADV_MATH_VEC_FLOAT2, CFLOAT);
#define CVFLOAT2 CIM_ADV_MATH_VEC_FLOAT2
#endif
#ifndef CVFLOAT3
CIM_ADV_MATH_VEC_GEN3(CIM_ADV_MATH_VEC_FLOAT3, CFLOAT);
#define CVFLOAT3 CIM_ADV_MATH_VEC_FLOAT3
#endif
#ifndef CVFLOAT4
CIM_ADV_MATH_VEC_GEN4(CIM_ADV_MATH_VEC_FLOAT4, CFLOAT);
#define CVFLOAT4 CIM_ADV_MATH_VEC_FLOAT4
#endif

#ifndef CVDOUBLE2
CIM_ADV_MATH_VEC_GEN2(CIM_ADV_MATH_VEC_DOUBLE2, CDOUBLE);
#define CVDOUBLE2 CIM_ADV_MATH_VEC_DOUBLE2
#endif
#ifndef CVDOUBLE3
CIM_ADV_MATH_VEC_GEN3(CIM_ADV_MATH_VEC_DOUBLE3, CDOUBLE);
#define CVDOUBLE3 CIM_ADV_MATH_VEC_DOUBLE3
#endif
#ifndef CVDOUBLE4
CIM_ADV_MATH_VEC_GEN4(CIM_ADV_MATH_VEC_DOUBLE4, CDOUBLE);
#define CVDOUBLE4 CIM_ADV_MATH_VEC_DOUBLE4
#endif

#ifndef CVINT2
CIM_ADV_MATH_VEC_GEN2(CIM_ADV_MATH_VEC_INT2, CINT);
#define CVINT2 CIM_ADV_MATH_VEC_INT2
#endif
#ifndef CVINT3
CIM_ADV_MATH_VEC_GEN3(CIM_ADV_MATH_VEC_INT3, CINT);
#define CVINT3 CIM_ADV_MATH_VEC_INT3
#endif
#ifndef CVINT4
CIM_ADV_MATH_VEC_GEN4(CIM_ADV_MATH_VEC_INT4, CINT);
#define CVINT4 CIM_ADV_MATH_VEC_INT4
#endif

#ifndef CVUINT2
CIM_ADV_MATH_VEC_GEN2(CIM_ADV_MATH_VEC_UINT2, CUINT);
#define CVUINT2 CIM_ADV_MATH_VEC_UINT2
#endif
#ifndef CVUINT3
CIM_ADV_MATH_VEC_GEN3(CIM_ADV_MATH_VEC_UINT3, CUINT);
#define CVUINT3 CIM_ADV_MATH_VEC_UINT3
#endif
#ifndef CVUINT4
CIM_ADV_MATH_VEC_GEN4(CIM_ADV_MATH_VEC_UINT4, CUINT);
#define CVUINT4 CIM_ADV_MATH_VEC_UINT4
#endif

#ifndef CIM_INVSQRT
CIMDEF CFLOAT CIM_ADV_MATH_INVSQRT_FUNC(CFLOAT);
#define CIM_INVSQRT CIM_ADV_MATH_INVSQRT_FUNC
#endif

/* Non-vec related additions */

#ifndef CIM_POW_ADV
CIMDEF CIMCALL CFLOAT CIM_ADV_MATH_POW_FUNC(CFLOAT, CFLOAT);
#define CIM_POW_ADV CIM_ADV_MATH_POW_FUNC
#endif

#ifndef CIM_LPOW_ADV
CIMDEF CIMCALL CDOUBLE CIM_ADV_MATH_LPOW_FUNC(CDOUBLE, CDOUBLE);
#define CIM_LPOW_ADV CIM_ADV_MATH_LPOW_FUNC
#endif

#endif

#if defined(CIM_USE_ADV_BUFFERS) || defined(CIM_USE_ADV)
#ifndef CIM_ADV_BUF_GEN
#define CIM_ADV_BUF_GEN(buf_name, buf_type) typedef struct buf_name { buf_type* stor; CIZE size; } buf_name
#endif

#ifndef CBUFFER
CIM_ADV_BUF_GEN(CIM_ADV_BUF_GENERIC, CVOID);
#define CBGENERIC CIM_ADV_BUF_GENERIC
#endif

#ifndef CBINT
CIM_ADV_BUF_GEN(CIM_ADV_BUF_INT, CINT);
#define CBINT CIM_ADV_BUF_INT
#endif

#ifndef CBUINT
CIM_ADV_BUF_GEN(CIM_ADV_BUF_UINT, CUINT);
#define CBUINT CIM_ADV_BUF_UINT
#endif

#ifndef CBFLOAT
CIM_ADV_BUF_GEN(CIM_ADV_BUF_FLOAT, CFLOAT);
#define CBFLOAT CIM_ADV_BUF_FLOAT
#endif

#ifndef CBDOUBLE
CIM_ADV_BUF_GEN(CIM_ADV_BUF_DOUBLE, CDOUBLE);
#define CBDOUBLE CIM_ADV_BUF_DOUBLE
#endif

#endif



#ifdef CIM_USE_LOWERNAME
#define cint64	CINT64
#define cint32	CINT32
#define cint16	CINT16
#define cint8	CINT8

#define cuint64	CUINT64
#define cuint32 CUINT32
#define cuint16 CUINT16
#define cuint8	CUINT8

#define cfloat	CFLOAT
#define cdouble CDOUBLE

#define cvoid	CVOID

#define cint	CINT
#define cuint	CUINT

#define cbyte	CBYTE
#define cize	CIZE

#define cchar 		CCHAR

#define cnull	CNULL
#define ctrue	CTRUE
#define cfalse	CFALSE

#if defined(CIM_USE_ADV) || defined(CIM_USE_ADV_MATH)
#define cvfloat2 	CVFLOAT2
#define cvfloat3 	CVFLOAT3
#define cvfloat4 	CVFLOAT4

#define cvdouble2	CVDOUBLE2
#define cvdouble3	CVDOUBLE3
#define cvdouble4	CVDOUBLE4

#define cvint2 		CVINT2
#define cvint3 		CVINT3
#define cvint4 		CVINT4

#define cvuint2 	CVUINT2
#define cvuint3		CVUINT3
#define cvuint4		CVUINT4

#endif

#ifdef CIM_USE_SHORTNAME
#define csigned		CIMSIGN
#define cunsigned	CIMUNSIGN

#define csqrt		CIM_SQRT
#define clsqrt		CIM_LSQRT
#define cpw			CIM_POW
#define clpw		CIM_LPOW
#define csin     CIM_SIN
#define clsin    CIM_LSIN
#define ccos     CIM_COS
#define clcos    CIM_LCOS
#define ctan     CIM_TAN
#define cltan    CIM_LTAN

#define cmalloc		CIM_MALLOC
#define ccalloc		CIM_CALLOC
#define cfree		CIM_FREE
#define cmcpy		CIM_MCPY
#define cmmv		CIM_MMOVE
#define cmset		CIM_MSET

#if defined(CIM_USE_ADV) || defined(CIM_USE_ADV_MATH)
#define cvcgen2 CIM_ADV_MATH_VEC_GEN2
#define cvcgen3 CIM_ADV_MATH_VEC_GEN3
#define cvcgen4 CIM_ADV_MATH_VEC_GEN4

#define cqsqrt		CIM_INVSQRT

#define cpwadv	CIM_POW_ADV
#define clpwadv	CIM_LPOW_ADV

#endif

#else //-----------------------------------------
#define cim_signed		CIMSIGN
#define cim_unsigned	CIMUNSIGN

#define cim_sqrt	CIM_SQRT
#define cim_lsqrt	CIM_LSQRT
#define cim_pow		CIM_POW
#define cim_lpow	CIM_LPOW
#define cim_sin     CIM_SIN
#define cim_lsin    CIM_LSIN
#define cim_cos     CIM_COS
#define cim_lcos    CIM_LCOS
#define cim_tan     CIM_TAN
#define cim_ltan    CIM_LTAN

#define cim_malloc	CIM_MALLOC
#define cim_calloc	CIM_CALLOC
#define cim_free	CIM_FREE
#define cim_mcpy	CIM_MCPY
#define cim_mmove	CIM_MMOVE
#define cim_mset	CIM_MSET
#define cim_mcmp    CIM_MCMP


#if defined(CIM_USE_ADV) || defined(CIM_USE_ADV_MATH)
#define cvec_gen2 	CIM_ADV_MATH_VEC_GEN2
#define cvec_gen3 	CIM_ADV_MATH_VEC_GEN3
#define cvec_gen4 	CIM_ADV_MATH_VEC_GEN4

#define cim_powadv	CIM_POW_ADV
#define cim_lpowadv	CIM_LPOW_ADV

#define cim_invsqrt	CIM_INVSQRT

#endif
#endif

#endif

#endif