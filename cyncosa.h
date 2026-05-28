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

/* */
#define CYNCOSA_CYNST_DEBUG (1U << 0U)
/* Ensure there is padding between elements */
#define CYNCOSA_CYNST_PADDING (1U << 1U)
/* Use error checking/context */
#define CYNCOSA_CYNST_ERCONTX (1U << 2U)
/* Does not allocate any resources for windows */
#define CYNCOSA_CYNST_BACKGROUND (1U << 3U)



typedef enum cynCOSA_winattr {
    CYNCOSA_WINATTR_TITLE,          /* Set only */
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
    CYNCOSA_WINATTR_PIXELFORMAT,
    CYNCOSA_WINATTR_FOCUS,          /* Get only */
    CYNCOSA_WINATTR_KEYATLAS_SIZE,  /* Get only */
} cynCOSA_winattr;

typedef enum cynCOSA_stdkeys {
    CYNCOSA_KEY_A = 0,
    CYNCOSA_KEY_B,
    CYNCOSA_KEY_C,
    CYNCOSA_KEY_D,
    CYNCOSA_KEY_E,
    CYNCOSA_KEY_F,
    CYNCOSA_KEY_G,
    CYNCOSA_KEY_H,
    CYNCOSA_KEY_I,
    CYNCOSA_KEY_J,
    CYNCOSA_KEY_K,
    CYNCOSA_KEY_L,
    CYNCOSA_KEY_M,
    CYNCOSA_KEY_N,
    CYNCOSA_KEY_O,
    CYNCOSA_KEY_P,
    CYNCOSA_KEY_Q,
    CYNCOSA_KEY_R,
    CYNCOSA_KEY_S,
    CYNCOSA_KEY_T,
    CYNCOSA_KEY_U,
    CYNCOSA_KEY_V,
    CYNCOSA_KEY_W,
    CYNCOSA_KEY_X,
    CYNCOSA_KEY_Y,
    CYNCOSA_KEY_Z,
    CYNCOSA_KEY_SPACE,
    CYNCOSA_KEY_BACKSPACE,
    CYNCOSA_KEY_DELETE,
    CYNCOSA_KEY_ENTER,
    CYNCOSA_KEY_TAB,
    CYNCOSA_KEY_0,
    CYNCOSA_KEY_1,
    CYNCOSA_KEY_2,
    CYNCOSA_KEY_3,
    CYNCOSA_KEY_4,
    CYNCOSA_KEY_5,
    CYNCOSA_KEY_6,
    CYNCOSA_KEY_7,
    CYNCOSA_KEY_8,
    CYNCOSA_KEY_9,
    CYNCOSA_KEY_SQUARE,
    CYNCOSA_KEY_MINUS,
    CYNCOSA_KEY_PLUS,
    CYNCOSA_KEY_EQUAL,
    CYNCOSA_KEY_LESSTHAN,
    CYNCOSA_KEY_MORETHAN,
    CYNCOSA_KEY_STAR,
    CYNCOSA_KEY_HOME,
    CYNCOSA_KEY_INSERT,
    CYNCOSA_KEY_ESCAPE,
    CYNCOSA_KEY_END,
    CYNCOSA_KEY_PG_UP,
    CYNCOSA_KEY_PG_DOWN,
    CYNCOSA_KEY_ARROW_UP,
    CYNCOSA_KEY_ARROW_DOWN,
    CYNCOSA_KEY_ARROW_LEFT,
    CYNCOSA_KEY_ARROW_RIGHT,
    CYNCOSA_KEY_SYSHOME, /* Windows Key/Command Key*/
    
    CYNCOSA_KEY_LCTRL,
    CYNCOSA_KEY_RCTRL,
    CYNCOSA_KEY_ALT,
    CYNCOSA_KEY_LSHIFT,
    CYNCOSA_KEY_RSHIFT,
} cynCOSA_stdkeys;

typedef enum cynCOSA_funckeys {
    CYNCOSA_KEY_FUNC1,
    CYNCOSA_KEY_FUNC2,
    CYNCOSA_KEY_FUNC3,
    CYNCOSA_KEY_FUNC4,
    CYNCOSA_KEY_FUNC5,
    CYNCOSA_KEY_FUNC6,
    CYNCOSA_KEY_FUNC7,
    CYNCOSA_KEY_FUNC8,
    CYNCOSA_KEY_FUNC9,
    CYNCOSA_KEY_FUNC10,
    CYNCOSA_KEY_FUNC11,
    CYNCOSA_KEY_FUNC12,
    CYNCOSA_KEY_FUNC13,
    CYNCOSA_KEY_FUNC14,
    CYNCOSA_KEY_FUNC15,
    CYNCOSA_KEY_FUNC16,
    CYNCOSA_KEY_FUNC17,
    CYNCOSA_KEY_FUNC18,
    CYNCOSA_KEY_FUNC19,
    CYNCOSA_KEY_FUNC20,
    CYNCOSA_KEY_FUNC21,
    CYNCOSA_KEY_FUNC22
} cynCOSA_funckeys;

/*
    cynCOSA provides keypages, which are 64 bit unsigned ints where each bit represents whether a key is down or not.
    
    The keys (for example stdkey and funckey), are indexes. Adding more keypages is always possible, though it may complicate stuff.
*/
#define cynCOSA_key(keycode) (CUINT64)((CUINT64)1U << (keycode))

typedef enum cynCOSA_pxlfmt {
    cynCOSA_pxlfmt8_rgb,        /* 332 */
    cynCOSA_pxlfmt8_rgba,       /* 2321*/
    cynCOSA_pxlfmt8_rgbaMono,   /* 2222 */
    cynCOSA_pxlfmt8_monotone,   /* 8bit grayscale */
    cynCOSA_pxlfmt16_rgb,        /* 565 */  
    cynCOSA_pxlfmt16_rgba,      /* 5551 */
    cynCOSA_pxlfmt16_rgbaMono,  /* 4444 */
    cynCOSA_pxlfmt16_monotone,  /* 16bit grayscale */
    cynCOSA_pxlfmt32_rgb,       /* 11 11 10 */
    cynCOSA_pxlfmt32_rgba,      /* 10 11 10 1 */
    cynCOSA_pxlfmt32_rgbaMono,  /* 8888 */
    cynCOSA_pxlfmt32_monotone,
    cynCOSA_pxlfmt32_monofloat, /* 32F grayscale */
    cynCOSA_pxlfmt32_depthRGB,  /* 24 bit mono + pxlfmt8_rgb */
    cynCOSA_pxlfmt32_depthRGBA, /* 24 bit mono + pxlfmt8_rgba */
    cynCOSA_pxlfmt64_rgba,      /* 16 16 16 16 */
    cynCOSA_pxlfmt64_floatrgba, /* 16 bit float per channel */
    cynCOSA_pxlfmt64_depthRGBA  /* pxlfmt32_monotone + pxlfmt32_rgbaMono */
} cynCOSA_pxlfmt;

typedef CUINT64 cynCOSA_keypage;

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
/* Are the pixels inverted? */
#define CYNCOSA_WIN_PXLFMT_INV  (1U << 6U)
/* Keeps a direct keypage array */
#define CYNCOSA_WIN_KEEP_HANDLE (1U << 7U)

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
    CBOOL focus;        /* focus onstart */
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

/* Logs using the current instance's name */
/*
    Attributes: takes at least a cynstr
    Behaviour:
    * Almost exactly the same as printf
*/
CYNDEF CYNCALL CVOID cynCOSA_InstanceLog(CCONST cynstr,...); 

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
CYNDEF CYNCALL cynCOSAWindow cynCOSA_WindowCreate(cynCOSAWinInfo* winfo, cynCOSA_sflags winflags);
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
    Has the window received a close command?
    [internally checks if window is part of window list of cynstance]
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
    * Only has access to specific parts, so check whether attributes are set-able (eg. keypages are not supported for set)
*/
CYNDEF CYNCALL CVOID cynCOSA_WindowSetAttr(cynCOSAWindow window, cynCOSA_winattr winattr, CVOID* winattr_p);
/* Returns a CVOID* to the specific winattr */
/* 
    Attribute window shall be valid within the global context
    Attribute winattr should be a valid get attribute (see docs if a winattr is not supported for get)
    Attribute winattr_dest MUST point to memory with enough size for the attribute
    Behaviour:
    * Places/copies the data attribute data within the destination pointer
*/
CYNDEF CYNCALL CVOID*cynCOSA_WindowGetAttr(cynCOSAWindow window, cynCOSA_winattr winattr, CVOID*winattr_dest);
/* Returns a CVOID* to the specific winattr and keeps track of space */
/* 
    Attribute window shall be valid within the global context
    Attribute winattr should be a valid get attribute (see docs if a winattr is not supported for get)
    Attribute winattr_dest must point to the start of memory with enough size for the attribute
    Attribute winattr_destend must point to the last address allocated for the given attribute
    Behaviour:
    * Checks if enough space is present, if not: CYNCOSA_RESULT_PARTIAL.
    * Places/copies the data attribute data within the destination pointer
*/
CYNDEF CYNCALL CVOID*cynCOSA_WindowGetAttrSafe(cynCOSAWindow window, cynCOSA_winattr winattr, CVOID*winattr_dest, CVOID*winattr_destend);
/* Retrieves the first keypage of the keyatlas */
/*
    Attribute window has to be valid within curent context
    Behaviour:
    * Returns a pointer to first keypage of the keyatlas
    * This keyatlas is managed by the window, thus should not be freed!
*/
CYNDEF CYNCALL cynCOSA_keypage*cynCOSA_WindowGetKeyAtlas(cynCOSAWindow window);
/* Shows a window */
/* 
    Attribute window should be a valid window within the global context
    Attribute show_window should be a valid CBOOL (CIM boolean)
*/
CYNDEF CYNCALL CVOID cynCOSA_WindowShow(cynCOSAWindow window, CBOOL show_window);



/* These functions do not use global type */
/* Documentation coming soon for these */
/* Soon: when all cynCOSA functions are written */


CYNDEF CYNCALL CVOID cynCOSA_instance_create(cynstance* instance_p, cynCOSA_platform platform);
CYNDEF CYNCALL CVOID cynCOSA_instance_createspecific(cynstance* instance_p, cynCOSA_platform platform, cynCOSA_flags flags);
CYNDEF CYNCALL CVOID cynCOSA_instance_destroy(cynstance* instance_p);

CYNDEF CYNCALL cynCOSAWindow cynCOSA_window_create(cynstance* instance_p, cynCOSAWinInfo* winfo, cynCOSA_sflags winflags);
CYNDEF CYNCALL CVOID cynCOSA_window_update(cynstance* instance_p, cynCOSAWindow window);
CYNDEF CYNCALL CVOID cynCOSA_window_updateall(cynstance* instance_p);
CYNDEF CYNCALL CVOID cynCOSA_window_destroy(cynstance* instance_p, cynCOSAWindow window);
CYNDEF CYNCALL CVOID cynCOSA_window_destroyall(cynstance* instance_p);

CYNDEF CYNCALL CBOOL cynCOSA_window_getclosed(cynstance* instance_p, cynCOSAWindow window);
CYNDEF CYNCALL CVOID cynCOSA_window_setinfo(cynstance* instance_p, cynCOSAWindow window, cynCOSAWinInfo*);
CYNDEF CYNCALL CVOID cynCOSA_window_setattr(cynstance* instance_p, cynCOSAWindow window, cynCOSA_winattr winattr, CVOID* winattr_p);

#endif