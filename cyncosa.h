#ifndef CYNCOSA_H
#define CYNCOSA_H

#define CIM_USE_ADV

/* 
    For all purposes, we just want cyncosa to work, 
    so that's why we use the cimport, but you may 
    also use base CIM if you can assure long = 32 bits, etc. 
    
*/
#include "cyncosa_cimport.h"

#ifndef CYNDEF
#ifdef CYN_IMPLEMENT
#define CYNDEF
#else
#define CYNDEF CIMEXTR
#endif
#endif

/* currently empty, but defined for future use when filled in */
#define CYNCALL

/* cyn_version: 0x (xx)major, (xxx)minor, (xx)patch */
#define cyn_version ((CUINT32)(0x0100000))

/*
    cynCOSA uses "instances", which contain their own platform information.
    cynstance = cynCOSA instance.
    A "cynstance" contains only a result and a CVOID* to the actual body content.

    cynCOSA does not keep track of instances, it is up to the user to define safe methods to store the CVOID* until the program is finished.

    Ifn't be known, CYNCALL is used for further compiler optimisation when needed, so it may be optimised. It is not the same as "CIMCALL", as CIMCALL is the clib-style call.

    If you don't want to use global state, you may use the lowercase variants (see documentation)

*/

typedef enum cynCOSA_result {
    CYNCOSA_RESULT_COMPLETED = 0,
    CYNCOSA_RESULT_FAILED,
    CYNCOSA_RESULT_PARTIAL
} cynCOSA_result;

typedef struct cynstance {
    CVOID* context;
    cynCOSA_result result;
} cynstance;

typedef enum cynCOSA_platform { /* platform = windowing platform/system */
    CYNCOSA_PLATFORM_WIN32 = 0, /* No GAPI support if enabled for a window */
    CYNCOSA_PLATFORM_WIN32_GL, /* OpenGL GAPI support when enabled per window */
    CYNCOSA_PLATFORM_WIN32_VK, /* Vulkan GAPI support when enabled per window */
    CYNCOSA_PLATFORM_WIN32_D3D, /* Direct3D GAPI support when enabled per window */
    CYNCOSA_PLATFORM_WIN32_GXL, /* of course our own future GAPI: GXL */
    CYNCOSA_PLATFORM_MACOS
    /* More CYNCOSA_PLATFORM_* flags */
} cynCOSA_platform;

typedef enum cynCOSA_winattr {
    CYNCOSA_WINATTR_TITLE, /* No get*/
    CYNCOSA_WINATTR_POS, 
    CYNCOSA_WINATTR_POS_X,
    CYNCOSA_WINATTR_POS_Y,
    CYNCOSA_WINATTR_SIZE,
    CYNCOSA_WINATTR_WIDTH,
    CYNCOSA_WINATTR_HEIGHT,
    CYNCOSA_WINATTR_MINSIZE,
    CYNCOSA_WINATTR_MAXSIZE,
    CYNCOSA_WINATTR_MINWIDTH,
    CYNCOSA_WINATTR_MAXWIDTH,
    CYNCOSA_WINATTR_MINHEIGHT,
    CYNCOSA_WINATTR_MAXHEIGHT,
    CYNCOSA_WINATTR_PIXELFORMAT
} cynCOSA_winattr;

/*
* experiment
typedef struct cynCOSA_bytetime {
        CUINT32 qsec;
        CUINT16 days;
        CUINT8 hours, minutes;
} cynCOSA_bytetime;
*/

/* Window flags */

/* Center makes pos an offset from screen center */
#define CYNCOSA_WIN_POS_CENTER  (1U << 0U)
/* Create a window without a border/titlebar */
#define CYNCOSA_WIN_BORDER_NONE (1U << 1U)
/* Show the window on creation */
#define CYNCOSA_WIN_SHOWN       (1U << 2U)
/* Does the window use the platform's GAPI? */
#define CYNCOSA_WIN_GAPI        (1U << 3U)
/* Sets the window's background to black on redraw without content, otherwise undefined */
#define CYNCOSA_WIN_BACK        (1U << 4U)
/* Allocates a 256x256 RGBA sprite buffer for the window (alpha is bit, regardless of pixelformat) */
#define CYNCOSA_WIN_SPRITE      (1U << 5U)

typedef CCHAR* cynstr;
typedef CVOID* cynCOSAWindow;
typedef CBYTE cynCOSAWinPixelFormat;

typedef struct cynCOSAWinInfo {
    cynstr title;
    CUINT32 x;
    CUINT32 y;
    CUINT16 width;
    CUINT16 height;
    CUINT16 width_min;  /* cyncosa min req width is 120px, if lower, defaults to 120px */
    CUINT16 width_max;
    CUINT16 height_min; /* cyncosa min req height is 1px, if lower, defaults to 1px */
    CUINT16 height_max;
    cynCOSAWinPixelFormat pxlf;
} cynCOSAWinInfo;

typedef CCONST CUINT64  cynCOSA_lflags;
typedef CCONST CUINT32  cynCOSA_flags;
typedef CCONST CUINT8   cynCOSA_sflags;

/* Making a cynstance also sets it if no Cur is set */
/* It is not recommended to manually poke into cynstances as their internal structure remains unknown (platform specific) */
/* It is possible to create instances with different platform flags */

/* Creates a cynstance (cyn instance): */
/* 
    Attribute instance_p should be a valid address
    Attribute platform takes the platform flag
    Behaviour:
    * Upon creation, checks if there's a current global and if not sets itself as the global cynstance
    * If failed, check the result member of the cynstance (if cynstance is not zero)
    * If no platform is specified, the function takes this as a critical error
*/
CYNDEF CYNCALL CVOID cynCOSA_InstanceCreate(cynstance* instance_p,cynCOSA_platform platform);
/* Creates a cynstance (cyn instance) with extra flags: */
/* 
    Attribute instance_p should be a valid address
    Attribute platform takes a valid platform flag
    Attribute flags must be a valid bitmask pattern (using "|" )
    Behaviour:
    * Upon creation, checks if there's a current global and if not sets itself as the global cynstance
    * If failed, check the result member of the cynstance (if cynstance is not zero)
    * If no platform is specified, the function takes this as a critical error 
*/
CYNDEF CYNCALL CVOID cynCOSA_InstanceCreateS(cynstance* instance_p, cynCOSA_platform, cynCOSA_flags flags); /* Create Specific */
/* Sets the current global reference instance for cynCOSA */
/*
    Attribute instance_p should be a valid pointer to a cynstance
    Behaviour:
    * Switches the global context, any call after this will use this instance's context
*/
CYNDEF CYNCALL CVOID cynCOSA_InstanceCurSet(cynstance* instance_p);
/* Returns the current instance, CNULL if none */
CYNDEF CYNCALL cynstance* cynCOSA_InstanceCurGet();
/* Cleans up all tracked cynstance resources of the current global context */
/* 
    Behaviour:
    * Any tracked resources get destroyed, and thus calls functions like WindowDestroyAll()
    * It'll set the cynstance* to CNULL, which you can check with InstanceCurGet, this doesn't account for the input cynstance* from its creation.
*/
CYNDEF CYNCALL CVOID cynCOSA_InstanceDestroy();

/*
    Window memory is part of the instance memory, and thus belongs inside the CVOID* of set intance.
    The instance backend keeps a list of windows, but losing a window variable means you lose access to the specific contents of that window, 
        as cyncosa does not provide any sort of "access" to interface memory, as the structure is defined per instance, per platform, per implimentation.
    When using the "global instance" functions, caution need be present when operating on windows, as these functions will assume that these windows are
        part of the global instance, and thus access its memory and structure that way. Faulty use may result in undefined behaviour.
*/

/* Creates a window */
/*
    Attribute winfo need be a valid pointer to a wininfo struct
    Attribute winflags is a bit-field flag
    Behaviour:
    * Creates a window using the global context's platform definition
    * Allocates resources within the global instance and adds itself into it's winlist
    * On failure, cynCOSAWindow will be zero/NULL and adds error to the global context's result
*/
CYNDEF CYNCALL cynCOSAWindow cynCOSA_WindowCreate(cynCOSAWinInfo* winfo, cynCOSA_flags winsflags);
/* Updates a window to fetch events */
/* 
    Attribute window must be valid window pointer within the global instance
    Behaviour:
    * Allows the registering of new key inputs (changes) and the window's events at the time of calling
*/
CYNDEF CYNCALL CVOID cynCOSA_WindowUpdate(cynCOSAWindow window);
/* Updates all windows from the global instance */
/* 
    !This is not recommended as it takes a long time to execute!
*/
CYNDEF CYNCALL CVOID cynCOSA_WindowUpdateAll();
/* Destroys a window and its resources */
/* 
    Attribute window should be valid within the global context
    Behaviour:
    * Destroys (closes) a window and its resources (not including a instance's global GAPI context)
*/
CYNDEF CYNCALL CVOID cynCOSA_WindowDestroy(cynCOSAWindow window);
/* Destroys all windows of the global instance */
/*
    This function is also called within cynCOSA_InstanceDestroy, though it remains best practice to destroy individual windows when they are no longer needed.
*/
CYNDEF CYNCALL CVOID cynCOSA_WindowDestroyAll();

/* Retruns if the window closed/destroyed */
/* 
    Attribute window must be a window that has/had been created, regardless if it has been destroyed/closed
*/
CYNDEF CYNCALL CBOOL cynCOSA_WindowGetClosed(cynCOSAWindow window);
/* Sets the window to a specific WinInfo */
/* 
    Attribute window must be a valid window within global context
    Attribute winfo must point to assigned WinInfo memory
    NOTE: There is, unlike individual attributes, no get-er for WinInfo, thus a user should always have a mental model of the attributes present
*/
CYNDEF CYNCALL CVOID cynCOSA_WindowSetInfo(cynCOSAWindow window, cynCOSAWinInfo* winfo);
/* Sets a window's specific attribute */
/* 
    Attribute window has to be a valid window within global context
    Attribute winattr must be of the enum cynCOSA_winattr
    Attribute winattr_p shall point to whatever memory fits the winattr (see documentation for layouts)
    Behaviour:
    * Calls internal functions for these attributes, which translate to the specific platform's functions
*/
CYNDEF CYNCALL CVOID cynCOSA_WindowSetAttr(cynCOSAWindow window, cynCOSA_winattr winattr, CVOID* winattr_p);
/* Returns a CVOID* to the specific winattr's memory (must be freed) */
/* 
    Attribute window shall be valid within the global context
    Attribute winattr should be a valid get attribute (see docs if a winattr is not supported for get)
    Behaviour:
    * Allocates memory for the specific winattr type, which should be freed by the caller
    * Only has access to specific parts, so check whether attributes are get-able (eg. title is not supported for get)
*/
CYNDEF CYNCALL CVOID*cynCOSA_WindowGetAttr(cynCOSAWindow window, cynCOSA_winattr winattr);
/* Shows a window */
/* 
    Attribute window should be a valid window within the global context
    Attribute show_window should be a valid CBOOL (CIM boolean)
*/
CYNDEF CYNCALL CVOID cynCOSA_WindowShow(cynCOSAWindow window, CBOOL show_window);



/* These functions do not use global type */
/* Documentation coming soon for these */


CYNDEF CYNCALL CVOID cynCOSA_instance_create(cynstance* instance_p, cynCOSA_platform platform);
CYNDEF CYNCALL CVOID cynCOSA_instance_createspecific(cynstance* instance_p, cynCOSA_platform platform, cynCOSA_flags flags);
CYNDEF CYNCALL CVOID cynCOSA_instance_destroy(cynstance* instance_p);

CYNDEF CYNCALL cynCOSAWindow cynCOSA_window_create(cynstance* instance_p, cynCOSAWinInfo* winfo, cynCOSA_flags winsflags);
CYNDEF CYNCALL CVOID cynCOSA_window_update(cynstance* instance_p, cynCOSAWindow window);
CYNDEF CYNCALL CVOID cynCOSA_window_updateall(cynstance* instance_p);
CYNDEF CYNCALL CVOID cynCOSA_window_destroy(cynstance* instance_p, cynCOSAWindow window);
CYNDEF CYNCALL CVOID cynCOSA_window_destroyall(cynstance* instance_p);

CYNDEF CYNCALL CVOID cynCOSA_window_getclosed(cynstance* instance_p, cynCOSAWindow window);
CYNDEF CYNCALL CVOID cynCOSA_window_setinfo(cynstance* instance_p, cynCOSAWindow window, cynCOSAWinInfo*);
CYNDEF CYNCALL CVOID cynCOSA_window_setattr(cynstance* instance_p, cynCOSAWindow window, cynCOSA_winattr winattr, CVOID* winattr_p);

#endif