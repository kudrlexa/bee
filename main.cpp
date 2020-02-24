/**************************
 * Includes
 *
 **************************/

#include <windows.h>
#include <gl/gl.h>
#include "coordin.h"

/**************************
 * Function Declarations
 *
 **************************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);
HDC hDC;

/**************************
 * WinMain
 *
 **************************/

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
    WNDCLASS wc;        
    MSG msg;
    BOOL bQuit = FALSE;
    HWND hWnd;
	HGLRC hRC;
	DEVMODE dm;
	RECT rect = {0};

    /* register window class */
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "Bee";
    RegisterClass (&wc);

	EnumDisplaySettings(NULL,ENUM_CURRENT_SETTINGS,&dm);
    /* create main window */
    hWnd = CreateWindow (
      "Bee", "Bee", 
      WS_POPUP | WS_MAXIMIZE | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
      0, 0, dm.dmPelsWidth, dm.dmPelsHeight,
      NULL, NULL, hInstance, NULL);
      GetWindowRect(hWnd, &rect);
      width = rect.right - rect.left;
      height = rect.bottom - rect.top;
      
      EnableOpenGL (hWnd, &hDC, &hRC);
      Create();

    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL (hWnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow (hWnd);

    return msg.wParam;
}


/********************
 * Window Procedure
 *
 ********************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_PAINT:
		tagPAINTSTRUCT *ps;
	
		glMatrixMode(GL_PROJECTION);
  		glLoadIdentity();
  		glOrtho( -wind.sWidth, wind.sWidth, -wind.sHeight, wind.sHeight, -5*SCALE, 5*SCALE );
  		
  		glViewport(0,0,width,height);
  		BeginPaint(hWnd,ps);
			glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
    		glClear (GL_COLOR_BUFFER_BIT);
    		glCallList( 1 );
			glFlush();
    		SwapBuffers (hDC);   
    	EndPaint(hWnd,ps);
		return 0;	
    
    case WM_CLOSE:
        PostQuitMessage (0);
        return 0;
        
    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            return 0;
        }
        return 0;

    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}


/*******************
 * Enable OpenGL
 *
 *******************/

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC (hWnd);

    /* set the pixel format for the DC */
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );

}


/******************
 * Disable OpenGL
 *
 ******************/

void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}
