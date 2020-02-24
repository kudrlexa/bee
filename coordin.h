#ifndef COORDIN_H_
#define COORDIN_H_

void Create( void );

class Texture
{
    unsigned char *data;
    bool error;
public:
	int Width,Height;
    Texture();   
   ~Texture();
    void LoadBMP(const char imagepath[]);
    void PutTexture(void);       
};

class Wind 
{
	Texture texture;
	float glWidth, glHeight;
public:
	float sWidth, sHeight;
	void Create( const char imagepath[] );
};

const int SCALE = 2;

extern int width, height;
extern Wind wind;

#endif
