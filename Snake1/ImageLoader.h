#ifndef IMAGE_LOADER_H_INCLUDED
#define IMAGE_LOADER_H_INCLUDED
class Image {
	//Manejo de textura dentro del juego para añadir un nuevo aspecto al juego
public:
	Image(char* ps, int w, int h);
	~Image();
	char* pixels;
	int width;
	int height;
};
Image* loadBMP(const char* filename);
#endif
