#define CYN_IMPLEMENT


/* create backend */
#ifndef CYNCOSA_BACKEND
#define CYNCOSA_BACKEND
#endif
#include "cyncosa.h"


/*
    While cynCOSA itself is a single-header, for ease of implementation,
        it will use cynCOSA_(platform) headers to include the actual 
        implementation of platform instructions.
    The reasoning behind this is that otherwise you may create problems.
*/

#include "cyncosa_win32.h"

cynCOSAGlobalState cynCOSAState = { { CNULL, 0U }, CNULL, 0U, 0U, CYNCOSA_RESULT_COMPLETED };


CYNCALL CVOID cynCOSA_InstanceCreate( cynstance* instance_p, cynCOSA_platform platform) {
    cynCOSA_result res = CYNCOSA_RESULT_NONE;
    cynCOSAHandle* newHandle = CNULL;
    if (!cynCOSAState.cynsts) res = cynCOSA_InitHandleBuffer();
    if (res < CYNCOSA_RESULT_FAILED) {
        newHandle = cynCOSA_GetNewHandle(&res);
    
        if (res < CYNCOSA_RESULT_FAILED && newHandle != CNULL)
            switch (platform) {
            case CYNCOSA_PLATFORM_WIN32:
                cynCOSA_win32_instance_create( &newHandle, CYNCOSA_FLAGS_NONE );
                
                break;
            case CYNCOSA_PLATFORM_MACOS:
                CIM_PRINTF("HELP!!!");
            }
    }
    else {
        instance_p->context = CNULL;
        instance_p->result = res;
    }
}

CYNCALL cynCOSAHandle* cynCOSA_GetNewHandle(cynCOSA_result* result) {
    cynCOSA_result res = CYNCOSA_RESULT_NONE;
    cynCOSAHandle* newHandle = CNULL;
    if ( cynCOSAState.handles.size < cynCOSAState.cynsts*1.3F ) 
        res = cynCOSA_LargenHandleBuffer();
    
    if (res != CYNCOSA_RESULT_FAILED) {
        newHandle = cynCOSAState.handles.stor[cynCOSAState.cynsts];
    }

    *result = res;
    return newHandle;
    
}

CYNCALL cynCOSA_result cynCOSA_LargenHandleBuffer() {
    CCONST CIZE new_size = cynCOSAState.handles.size*1.5F;
    cynCOSAHandle** temp_buffer = CIM_REALLOC(cynCOSAState.handles.stor, CIZEOF(cynCOSAHandle*)*new_size);
    
    if (!temp_buffer) return CYNCOSA_RESULT_FAILED;

    cynCOSAState.handles.stor = temp_buffer;
    cynCOSAState.handles.size = new_size;
    return CYNCOSA_RESULT_COMPLETED;
}

CIMCALL cynCOSA_result cynCOSA_InitHandleBuffer() {

}