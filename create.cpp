#include <windows.h>
#include <gl/gl.h>
#include "coordin.h"

int width, height;
Wind wind;

using namespace std;
void Create( void ) {
	wind.Create( "Fon" );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}
