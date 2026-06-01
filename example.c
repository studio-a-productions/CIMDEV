/*
	Example file that creates a window and then destroys it on keypress "escape"

	Creates an instance with OpenGL
	Creates a window within that instance
	Waits till the escape key is pressed
	Destroys resources
*/

#define CYNCOSA_SUPPORT_OPENGL /* ensure opengl is enabled */
#define CIM_COMPILE_RELEASE /* compile release */
#include "cyncosa.h" 

int main() {
	cynstance myinst; /* handle of cynstance */


	cynCOSA_InstanceCreateS(&myinst, CYNCOSA_PLATFORM_WIN32, CYNCOSA_CYNST_GAPI_OPENGL);
	if (myinst.result != CYNCOSA_RESULT_COMPLETED)
		return 1;
	const cynCOSAWinInfo myinfo = {
		.title = "Hello World",
		.x = 500U,
		.y = 300U
	};

	cynCOSAWindow mywin = cynCOSA_WindowCreate(&myinfo, 0U);
	if (!mywin /* or myinst.result == CYNCOSA_RESULT_FAILED */) { cynCOSA_InstanceDestroy(); return 1; }
	
	CUINT64* mykeyatlas = cynCOSA_WindowGetKeyAtlas(mywin);
	CUINT8 keyatlas_size; 
	/* For safety, one could do here after a null check or result check, though that is optional */
	cynCOSA_WindowGetAttr(mywin, CYNCOSA_WINATTR_KEYATLAS_SIZE, &keyatlas_size);
	
	CBOOL myrunningvar = CTRUE;
	while (!cynCOSA_WindowGetClosed(mywin) && myrunningvar) {
		cynCOSA_WindowUpdate(mywin); /* Update events*/

		if (*mykeyatlas & cynCOSA_key(CYNCOSA_KEY_ESCAPE)) myrunningvar = CFALSE;
	}
	
	cynCOSA_WindowDestroy(mywin);
	cynCOSA_InstanceDestroy();
	return 0;
}