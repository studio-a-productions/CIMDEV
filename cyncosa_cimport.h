#ifndef CYNCOSA_CIMPORT_H
#define CYNCOSA_CIMPORT_H

/* This is the interface between CIM and cyncosa */
/* Meaning that, we overwrite here (^>^) */

#ifndef CYNCOSA_USE_CIM_BASE
#include <stdint.h> /* gone be cimtypes */

#define CINT64	int64_t
#define CINT32	int32_t
#define CINT16	int16_t
#define CINT8	int8_t

#define CUINT64	uint64_t
#define CUINT32	uint32_t
#define CUINT16	uint16_t
#define CUINT8	uint8_t

#endif

/* ofc this is needed */
#include "cim.h"

#endif