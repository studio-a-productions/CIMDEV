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
#ifdef CYNCOSA_IMPLEMENT
#define CYNDEF
#else
#define CYNDEF CIMEXTR
#endif
#endif

#define CYNCOSA_FLAGS_NONE 0U

#ifdef CYNCOSA_BACKEND
typedef struct cynCOSAHandle {
    cynCOSA_platform platform;
    cynCOSACallback* fns;
    CIZE fncount;
    CVOID* context; /* implementation defined */
} cynCOSAHandle;

CIM_ADV_BUF_GEN(cynCOSAHandleBuffer, cynCOSAHandle*);

typedef struct cynCOSAGlobalState {
    cynCOSAHandleBuffer handles;
    cynstance* ginst;
    CIZE cynsts;
    CIZE gMxWindow;
    cynCOSA_result gresult;
} cynCOSAGlobalState; 

CYNDEF cynCOSAGlobalState cynCOSAState;

#endif


/* currently empty, but defined for future use when filled in */
#define CYNCALL


#define CYNCOSA_VERSION_MAJ 0
#define CYNCOSA_VERSION_MIN 1
#define CYNCOSA_VERSION_PATCH 3

/*
    cynCOSA uses "instances", which contain their own platform information.
    cynstance = cynCOSA instance.
    A "cynstance" contains only a result and a CVOID* to the actual body content.

    cynCOSA does not keep track of instances, it is up to the user to define safe methods to store the CVOID* until the program is finished.

    Ifn't be known, CYNCALL is used for further compiler optimisation when needed, so it may be optimised. It is not the same as "CIMCALL", as CIMCALL is the clib-style call.

    If you don't want to use global state, you may use the lowercase variants (see documentation)

*/

typedef enum cynCOSA_result {
    CYNCOSA_RESULT_NONE = -1,
    CYNCOSA_RESULT_COMPLETED = 0,
    CYNCOSA_RESULT_FAILED,
    CYNCOSA_RESULT_PARTIAL
} cynCOSA_result;

typedef struct cynstance {
    CVOID* context;
    cynCOSA_result result;
} cynstance;

/* Can have any signature */
typedef CVOID (*cynCOSACallback)();

typedef CUINT64  cynCOSA_lflags;
typedef CUINT32  cynCOSA_flags;
typedef CUINT16  cynCOSA_hflags;
typedef CUINT8   cynCOSA_sflags;

typedef enum cynCOSA_platform { /* platform = windowing platform/system */
    CYNCOSA_PLATFORM_WIN32 = 0,
    CYNCOSA_PLATFORM_MACOS
    /* More CYNCOSA_PLATFORM_* flags */
} cynCOSA_platform;

#ifndef CIM_COMPILE_RELEASE
/* Debug enabled for this instance */
#define CYNCOSA_CYNST_DEBUG         (1U << 0U)
#else
#define CYNCOSA_CYNST_DEBUG         0U
#endif
/* Ensure there is padding (at least 1 byte) between elements */
#define CYNCOSA_CYNST_PADDING       (1U << 1U)
#ifndef CIM_COMPILE_DEBUG
/* Use error checking/context */
#define CYNCOSA_CYNST_ERCONTX       (1U << 2U)
#else 
/* Error checking disabled */
#define CYNCOSA_CYNST_ERCONTX       0U
#endif
/* Does not allocate any resources for windows (if attempted fails) */
#define CYNCOSA_CYNST_BACKGROUND    (1U << 3U)
/* Don't ask why there are background tasks in cynCOSA... */

/* bits 8 to 16 are reserved for GAPIs */
#if defined(CYNCOSA_SUPPORT_OPENGL) && defined(CYNCOSA_SUPPORT_VULKAN)
#define CYNCOSA_CYNST_GAPI_OPENGL   (1U << 8U)
#define CYNCOSA_CYNST_GAPI_VULKAN   (1U << 9U)
#elif defined(CYNCOSA_SUPPORT_OPENGL)
#define CYNCOSA_CYNST_GAPI_OPENGL   (1U << 8U)
#define CYNCOSA_CYNST_GAPI_VULKAN   0U
#elif defined(CYNCOSA_SUPPORT_VULKAN)
#define CYNCOSA_CYNST_GAPI_OPENGL   0U
#define CYNCOSA_CYNST_GAPI_VULKAN   (1U << 9U)

#else 
#define CYNCOSA_CYNST_GAPI_OPENGL   0U
#define CYNCOSA_CYNST_GAPI_VULKAN   0U
#endif


typedef enum cynCOSAPixelFormat {
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
} cynCOSAPixelFormat;

/* Window stuff */

/* Center makes pos an offset from screen center */
#define CYNCOSA_WIN_POS_CENTER  (cynCOSA_sflags)(1U << 0U)
/* Create a window without a border/titlebar */
#define CYNCOSA_WIN_BORDER_NONE (cynCOSA_sflags)(1U << 1U)
/* Hide the window on creation */
#define CYNCOSA_WIN_HIDE        (cynCOSA_sflags)(1U << 2U)
/* If window is fullscreen size and position are IGNORED */
#define CYNCOSA_WIN_FULLSCREEN  (cynCOSA_sflags)(1U << 3U)
/* Sets the window's background to black on redraw without content, otherwise undefined */
#define CYNCOSA_WIN_BACK        (cynCOSA_sflags)(1U << 4U)
/* Allocates a 256x256x256 RGBA sprite buffer for the window, undefined behaviour if no pxlfmt is set */
#define CYNCOSA_WIN_SPRITE      (cynCOSA_sflags)(1U << 5U)
/* Are the pixels inverted? */
#define CYNCOSA_WIN_PXLFMT_INV  (cynCOSA_sflags)(1U << 6U)
/* Keeps a direct keypage array */
#define CYNCOSA_WIN_KEEP_HANDLE (cynCOSA_sflags)(1U << 7U)

typedef CCHAR* cynstr;
typedef CVOID* cynCOSAWindow;

typedef struct cynCOSAWinInfo {
    cynstr title;
    cynCOSAPixelFormat pxlf;
    CUINT32 x;
    CUINT32 y;
    CUINT16 width;
    CUINT16 height;
    CUINT16 width_min;  /* cyncosa min req width is 120px, if lower, defaults to 120px */
    CUINT16 width_max;  /* if set to 0, will set no max width */
    CUINT16 height_min; /* cyncosa min req height is 1px, if lower, defaults to 1px */
    CUINT16 height_max; /* if set to 0, will set no max height */
} cynCOSAWinInfo;

typedef enum cynCOSAWinEvent {
    CYNCOSA_WINEVENT_POSITION,
    CYNCOSA_WINEVENT_RESIZE,
    CYNCOSA_WINEVENT_FOCUS,
    CYNCOSA_WINEVENT_CLOSE,
    CYNCOSA_WINEVENT_MINIMIZE,
    CYNCOSA_WINEVENT_MAXIMIZE
} cynCOSAWinEvent;

typedef enum cynCOSAWinAttr {
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
} cynCOSAWinAttr;

/*
    cynCOSA provides keypages, which are 64 bit unsigned ints where each bit represents whether a key is down or not.
    
    The keys (for example stdkey and funckey), are indexes. Adding more keypages is always possible, though it may complicate stuff.
*/

typedef CUINT64 cynCOSAKeypage;
#define cynCOSA_key(keycode) ((cynCOSAKeypage)1 << (keycode))
#define cynCOSAKeyPressed(keypage, keycode) (keypage) & cynCOSA_key(keycode)

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

typedef enum cynCOSA_npadkeys {
    CYNCOSA_KEY_NPAD_0,
    CYNCOSA_KEY_NPAD_1,
    CYNCOSA_KEY_NPAD_2,
    CYNCOSA_KEY_NPAD_3,
    CYNCOSA_KEY_NPAD_4,
    CYNCOSA_KEY_NPAD_5,
    CYNCOSA_KEY_NPAD_6,
    CYNCOSA_KEY_NPAD_7,
    CYNCOSA_KEY_NPAD_8,
    CYNCOSA_KEY_NPAD_9,
    CYNCOSA_KEY_NPAD_DELETE,
    CYNCOSA_KEY_NPAD_RETURN,
    CYNCOSA_KEY_NPAD_HOME,
    CYNCOSA_KEY_NPAD_END,
    CYNCOSA_KEY_NPAD_PAGEUP,
    CYNCOSA_KEY_NPAD_PAGEDOWN,
    CYNCOSA_KEY_NPAD_EQUAL,
    CYNCOSA_KEY_NPAD_PLUS,
    CYNCOSA_KEY_NPAD_MINUS
} cynCOSA_npadkeys;


/* Making a cynstance also sets it if no Cur is set */
/* It is not recommended to manually poke into cynstances as their internal structure remains unknown (platform specific) */
/* It is possible to create instances with different platform flags */

/* Creates a cynstance (cyn instance): */
/* 
    Creates a default-style instance.

    Behaviour:
    - Upon creation, checks if there's a current global and if not sets itself as the global cynstance
    - If failed, check the result member of the cynstance (if cynstance is not zero)
    - If no platform is specified, the function takes this as a critical error
*/
CYNDEF CYNCALL CVOID cynCOSA_InstanceCreate(
    cynstance* instance_p,      /* Address reserved for the cynstance */
    cynCOSA_platform platform   /* Target platform/system */
);
/* Creates a cynstance (cyn instance) with extra flags */
/* 
    Create Specific variant of InstanceCreate.

    Behaviour:
    - Upon creation, checks if there's a current global and if not sets itself as the global cynstance
    - If failed, check the result member of the cynstance (if cynstance is not zero)
    - If no platform is specified, the function takes this as a critical error 
*/
CYNDEF CYNCALL CVOID cynCOSA_InstanceCreateS(
    cynstance* instance_p,      /* Address reserved for the cynstance */
    cynCOSA_platform platform,           /* Target platform/system */
    cynCOSA_flags flags         /* Additional flags (bitmask), such as GAPI, all under CYNCOSA_CYNST_* */
);
/* Sets the current global instance */
/*
    Unsets the current instance, but does not destroy it. Windows of the previous instance should NOT be updated

    Behaviour:
    - Switches the global context, any call after this will use this instance's context
*/
CYNDEF CYNCALL CVOID cynCOSA_InstanceCurSet(
    cynstance* instance_p       /* Pointer to the cynstance to be set */
);
/* Returns the current instance, CNULL if none */
CYNDEF CYNCALL cynstance* cynCOSA_InstanceCurGet();
/* Cleans up all tracked cynstance resources of the current global context */
/* 
    This function does not clean up user allocated resources.
    
    Calls WindowDestroyAll(), thus will create callbacks

    Behaviour:
    - Any tracked resources get destroyed, and thus calls functions like WindowDestroyAll()
    - It'll set the cynstance* to CNULL, which you can check with InstanceCurGet, this doesn't account for the input cynstance* from its creation.
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
    Window flags should be added together using the OR opperation ( | ), which means it technically is one integer.
    
    Behaviour:
    - Creates a window using the global context's platform definition
    - Allocates resources within the global instance and adds itself into it's winlist
    - On failure, cynCOSAWindow will be zero/NULL and adds error to the global context's result
*/
CYNDEF CYNCALL cynCOSAWindow cynCOSA_WindowCreate(
    cynCOSAWinInfo* winfo,      /* Pointer to window info struct */
    cynCOSA_sflags winflags     /* Window flags */
);
/* Updates a window to fetch events */
/* 
    This function will fetch all events and keyinputs (as provided by the system)

    Behaviour:
    - Allows update of keyatlas
    - Allows for window callbacks
*/
CYNDEF CYNCALL CVOID cynCOSA_WindowUpdate(
    cynCOSAWindow window        /* Valid window pointer within context */
);
/* Updates all windows from the global instance */
/* 
    This is not recommended as it takes a long time to execute!
*/
CYNDEF CYNCALL CVOID cynCOSA_WindowUpdateAll();
/* Destroys a window and its resources */
/*     
    BEWARE: this function does not create an event.

    Behaviour:
    - Destroys (closes) a window and its resources (not including a instance's global GAPI context)
*/
CYNDEF CYNCALL CVOID cynCOSA_WindowDestroy(
    cynCOSAWindow window        /* Valid window pointer within context */
);
/* Destroys all windows of the global instance */
/*
    This function is also called within cynCOSA_InstanceDestroy, though it remains best practice to destroy individual windows when they are no longer needed.

    BEWARE: unlike WindowDestroy(window), this function does create the window close event!
*/
CYNDEF CYNCALL CVOID cynCOSA_WindowDestroyAll();

/* Retruns if the window closed/destroyed */
/* 
    Sees if the window is recently closed by looking if it's part of the instance's list, if it is not set to CNULL.
*/
CYNDEF CYNCALL CBOOL cynCOSA_WindowGetClosed(
    cynCOSAWindow window        /* Valid window pointer within context */
);
/* Sets a window's specific attribute */
/*     
    Behaviour:
    - Calls internal functions for these attributes, which translate to the specific platform's functions
    - Only has access to specific parts, so check whether attributes are set-able (eg. keypages are not supported for set)
*/
CYNDEF CYNCALL CVOID cynCOSA_WindowSetAttr(
    cynCOSAWindow window,       /* Valid window pointer within context */
    cynCOSAWinAttr winattr,    /* Window attribute to be set */
    CVOID* winattr_p            /* Pointer to space allocated for the winattr */
);
/* Retrieves a window attribute  */
/* 
    Places/copies the data attribute data within the destination pointer
*/
CYNDEF CYNCALL CVOID cynCOSA_WindowGetAttr(
    cynCOSAWindow window,       /* Valid window pointer within context */
    cynCOSAWinAttr winattr,    /* Window attribute to be received*/
    CVOID*winattr_dest          /* Pointer to space allocated for the winattr */
);
/*  Retrieves a window attribute safely */
/* 
    Makes sure that data does not escape boundries.

    Behaviour:
    - Checks if enough space is present, if not: CYNCOSA_RESULT_PARTIAL.
    - Places/copies the data attribute data within the destination pointer
*/
CYNDEF CYNCALL CVOID*cynCOSA_WindowGetAttrSafe(
    cynCOSAWindow window,       /* Valid window pointer within context */
    cynCOSAWinAttr winattr,    /* Window attribute to be retrieved */
    CVOID*winattr_dest,         /* Pointer to the beginning of the allocated space for the window attribute */
    CVOID*winattr_destend       /* Pointer to the end of the allocated space for the winow attribute */
);
/* Retrieves the first keypage of the keyatlas */
/*
    Attribute window has to be valid within curent context
    
    Behaviour:
    - Returns a pointer to first keypage of the keyatlas
    - This keyatlas is managed by the window, thus should not be freed!
*/
CYNDEF CYNCALL cynCOSAKeypage*cynCOSA_WindowGetKeyAtlas(
    cynCOSAWindow window    /* Valid window pointer within context */
);


/* Shows a window */
/* 
    Hides/unhides the window, more or less a minimise operation.
    This operation does not create an event!
*/
CYNDEF CYNCALL CVOID cynCOSA_WindowShow(
    cynCOSAWindow window,   /* Valid window pointer within context */
    CBOOL show_window       /* Value indicating if window should be shown */
);
/* Sets a callback for cynCOSA window events */
/* 
    callback should be filled in so (cynCOSACallback)function ; this converts/typecasts it to a callback (aka a opaque function pointer)

    Normally, these would be used in a queue, but due to cynCOSA's design (aka me being lazy) you'll need to provide your own callbacks.
    BEWARE: callbacks provided here (window callback) shall assume global context and thus shall not receive instance information (unless explicit)
    BEWARE: function signatures are required to match the documentation's.
*/
CYNDEF CYNCALL CVOID cynCOSA_WindowCallback(
    cynCOSAWindow window,       /* Valid window pointer within context */
    cynCOSAWinEvent winevent,   /* Type of window event the callback is for */
    cynCOSACallback callback    /* The function the window will call on the event */
);



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
CYNDEF CYNCALL CVOID cynCOSA_window_getattr(cynstance* instance_p, cynCOSAWindow window, cynCOSAWinAttr winattr, CVOID* winattr_p);
CYNDEF CYNCALL CVOID cynCOSA_window_setattr(cynstance* instance_p, cynCOSAWindow window, cynCOSAWinAttr winattr, CVOID* winattr_p);

#endif