#include <windows.h>
#include <gl/gl.h>
#include "coordin.h"

void PaintMain( const HWND hWnd, const HDC hDC ) {
	tagPAINTSTRUCT *ps;
	HWND hW = hWnd;
	
	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();
  	glOrtho( -wind.sWidth, wind.sWidth, -wind.sHeight, wind.sHeight, -5*SCALE, 5*SCALE );
  		
  	glViewport(0,0,width,height);
  	BeginPaint(hW,ps);
		glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
    	glClear (GL_COLOR_BUFFER_BIT);
    	glCallList( 1 );
		glFlush();
    	SwapBuffers (hDC);   
    EndPaint(hW,ps);
}

