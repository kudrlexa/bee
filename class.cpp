#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <fstream>
#include <math.h>
#include "coordin.h"
#include <stdio.h>

//------------------------------------------------------------------------------
// Окно
//------------------------------------------------------------------------------

void Wind::Create( const char imagepath[] ) {
	texture.LoadBMP( imagepath );
	
	if ( width < height && height > 0 ) {
  		sWidth = SCALE * (float)width / (float)height;
  		sHeight = SCALE;
  	}
  	else if ( width > 0 ) {
  		sHeight = SCALE * (float)height / (float)width;
		sWidth = SCALE;
	}
	
	if ( texture.Width > texture.Height && texture.Height > 0 ) {
  		glWidth = SCALE;
  		glHeight = SCALE * (float)texture.Height / (float)texture.Width;
  	}
  	else if ( texture.Width > 0 ) {
  		glHeight = SCALE;
  		glWidth = SCALE * (float)texture.Width / (float)texture.Height;
  	}
  	
  	if ( glWidth < sWidth && glWidth > 0 ) {
  		glWidth = sWidth;
  		glHeight = glHeight * sWidth / glWidth; 
  	}
  	
  	if ( glHeight < sHeight && glHeight > 0 ) {
  		glHeight = sHeight;
  		glWidth = glWidth * sHeight / glHeight;
  	}
  	
  	glNewList( 1, GL_COMPILE );
  		texture.PutTexture();
  		glEnable(GL_TEXTURE_2D);
    	glNormal3f(0,0,1);
        glBegin (GL_QUADS);
        	glTexCoord2d(1,1);
            glVertex3f( -glWidth, glHeight, -SCALE );
            glTexCoord2d(0,1);
            glVertex3f( glWidth, glHeight, -SCALE );
            glTexCoord2d(0,0);
            glVertex3f( glWidth, -wind.glHeight, -SCALE );
            glTexCoord2d(1,0);
            glVertex3f( -glWidth, -glHeight, -SCALE );
        glEnd ();
        glDisable(GL_TEXTURE_2D);
    glEndList();
}

//------------------------------------------------------------------------------
// Текстура
//------------------------------------------------------------------------------
Texture::Texture(){error=true;}

void Texture::LoadBMP(const char imagepath[])//Создание текстуры
{ 
//Данные прочитанные из заголовка BMP-файла           
unsigned char header[54];   //Каждый BMP-файл начинается с заголовка, длинной в 54 байта 
unsigned int imageSize;     //Размер изображения = ширина*высота*3
char filename[]="Textures\\";
strcat(filename,imagepath);
strcat(filename,".bmp");
FILE * file = fopen(filename,"rb");
error=false;
if (file==false) {
  printf("Изображение не может быть открыто!n");
  error=true;
}
if ( fread(header, 1, 54, file) != 54 ) {//Если мы прочитали меньше 54 байт значит возникла проблема 
    printf("Некорректный BMP-файл!n");
    error=true;
}
if ( header[0]!='B' || header[1]!='M' ){
    printf("Некорректный BMP-файл!n");
    error=true;
}
if (error==false)
{
//Читаем необходимые данные
imageSize  = *(int*)&(header[0x22]);//Размер изображения в байтах 
Width      = *(int*)&(header[0x12]); 
Height     = *(int*)&(header[0x16]);
if (imageSize==0)    imageSize=Width*Height*3; 
data = new unsigned char [imageSize];
fread(data,1,imageSize,file);
fclose(file);
for (int i=0;i<imageSize/3;i++)
  {int Temp=data[i*3];
   data[i*3]=data[i*3+2];
   data[i*3+2]=Temp;}
}
}

Texture::~Texture()
{
   if (error==false)
     delete [] data;
}

void Texture::PutTexture(void)                  
{
     glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,Width,Height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
}
