#ifndef CYNCOSA_WIN32_H
#define CYNCOSA_WIN32_H

/* Implement WIN32 */

#ifndef CYNCOSA_BACKEND
#define CYNCOSA_BACKEND
#endif
#include "cyncosa.h"

CYNCALL cynCOSA_result cynCOSA_win32_instance_create( cynCOSAHandle**, cynCOSA_flags );


#endif