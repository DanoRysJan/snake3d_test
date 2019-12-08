#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <windows.h>
#include <list>
#include <iterator>
#include <time.h>
#include "Snake.h"
#include "Cola.h"
#include "Comida.h"
#include "ImageLoader.h"


using namespace std;


//Declaramos las listas e iteradores
list<Comida*> listComida;
list<Comida*>::iterator itComida;
list<Cola*> listCola;
list<Cola*>::iterator itCola;
list<Cola*> listColaFan;
list<Cola*>::iterator itColaFan;

//Inicializamos el snake en las siguientes coordenadas
Snake snake(0,0,-10);
double rotate_x=0;
double rotate_y=0;
double rotate_z=0;
//Variables de la camara para dar perspectivas diferentes
int camara1 = -1;
int camara2 = 27;
int camara3 = -12;
int camara4 = 7;
int camara5 = -203;
int camara6 = 0;
float aspect = 1.0f;
double  camaraLadoX = 0.0;
double  camaraLadoY = 0.0;

int traslacionX = 0;
int traslacionY = 0;
int traslacionZ = 0;

int xRotacion = 0;
int yRotacion = 0;
int zRotacion = 0;

bool bx=false;
bool by=false;
bool bz=false;

//Coordenadas para realizar las paredes 
int paredLadox[] = { 0 ,1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9 ,10,-1,-2,-3,-4,-5,-6,-7,-8,-9,-10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, -1, -2, -3, -4, -5, -6, -7, -8, -9,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10 };
int paredLadoY[] = { 10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10 ,10, 9, 8, 7, 6, 5,4 ,3 ,2 ,1 ,0 ,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,   1,  2,  3, 4,  5,  6,  7,  8,  9, 10, -1, -2, -3, -4, -5, -6, -7, -8, -9,-10,  0 };

//Las variables necesarias para hacer el snake para sus respectivos movimientos
bool adelante = false;
bool derecha = false;
bool izquierda = false;
bool atras = false;
bool arriba = false;
bool abajo = false;
bool bandX = false;
bool bandY = false;
bool bandZ = false;
bool bandCola = false;
bool flagDefault = false;
//auxiliares que ocuparemos para mover la cola
int auxX,auxY,auxZ;

//Variables para mover la cola
int movimientoX[6];
int movimientoY[6];
int movimientoZ[6];
//bandera para saber hacia donde se estta moviendo el snake 
bool moverDerecha = false;
bool moverArriba = false;
bool moverAbajo = false;
bool moverIzquierda = false;
bool moverAdelante = false;
bool moverAtras = false;
int contadorX = 0;
int contadorY = 0;
int contadorZ = 0;
bool flagEjeZ = false;
bool flagEjeX = false;
bool flagEjeY = false;
bool flagEjeAnteriorZ = false;
bool flagEjeAnteriorX = false;
bool flagEjeAnteriorY = false;
int co = 0;

//Texturas-----------------------------------------
GLuint text1;
GLuint text2;
GLuint text3;
GLuint text4;
GLuint text5;
GLuint text6;

GLuint loadTexture(Image* image) {
	GLuint idtextura;
	glGenTextures(1, &idtextura);
	glBindTexture(GL_TEXTURE_2D, idtextura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	return idtextura;
}


void initRendering() {
	//se cargan las texturas al escenario las imagenes son en formato bmp
	Image* lado1 = loadBMP("4.bmp");
	text1 = loadTexture(lado1);
	delete lado1;

	Image* lado2 = loadBMP("4.bmp");
	text2 = loadTexture(lado2);
	delete lado2;

	Image* lado3 = loadBMP("4.bmp");
	text3 = loadTexture(lado3);
	delete lado3;

	Image* lado4 = loadBMP("4.bmp");
	text4 = loadTexture(lado4);
	delete lado4;

	Image* lado5 = loadBMP("4.bmp");
	text5 = loadTexture(lado5);
	delete lado5;

	Image* lado6 = loadBMP("4.bmp");
	text6 = loadTexture(lado6);
	delete lado6;
}

//metodo para cargar texturas 
void cargarTextura(GLuint _textura) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textura);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

//metodo para dibujar un cubo en 3d sencillo y con textua
void dibujaCubo(){

  //LADO FRONTAL: lado multicolor
cargarTextura(text1);
  glBegin(GL_POLYGON);
	glColor3f(0.7, 0.5, 0.8);
	  glTexCoord2f(0.0f, 0.0f);  glVertex3f(  0.5, -0.5, -0.5 );      // P1 es rojo
	  glTexCoord2f(1.0f, 0.0f);  glVertex3f(  0.5,  0.5, -0.5 );      // P2 es verde
	  glTexCoord2f(1.0f, 1.0f);  glVertex3f( -0.5,  0.5, -0.5 );      // P3 es azul
	  glTexCoord2f(0.0f, 1.0f);  glVertex3f( -0.5, -0.5, -0.5 );      // P4 es morado
  glEnd();

  // LADO TRASERO: lado blanco
  cargarTextura(text2);
  glBegin(GL_POLYGON);
	  glTexCoord2f(0.0f, 0.0f);  glVertex3f(  0.5, -0.5, 0.5 );
	  glTexCoord2f(1.0f, 0.0f);  glVertex3f(  0.5,  0.5, 0.5 );
	  glTexCoord2f(1.0f, 1.0f);  glVertex3f( -0.5,  0.5, 0.5 );
	  glTexCoord2f(0.0f, 1.0f);  glVertex3f( -0.5, -0.5, 0.5 );
  glEnd();

  // LADO DERECHO: lado morado
  cargarTextura(text3);
  glBegin(GL_POLYGON);
	  glTexCoord2f(0.0f, 0.0f);  glVertex3f( 0.5, -0.5, -0.5 );
	  glTexCoord2f(1.0f, 0.0f);  glVertex3f( 0.5,  0.5, -0.5 );
	  glTexCoord2f(1.0f, 1.0f);  glVertex3f( 0.5,  0.5,  0.5 );
	  glTexCoord2f(0.0f, 1.0f);  glVertex3f( 0.5, -0.5,  0.5 );
  glEnd();

  // LADO IZQUIERDO: lado verde
  cargarTextura(text4);
  glBegin(GL_POLYGON);
	  glTexCoord2f(0.0f, 0.0f);  glVertex3f( -0.5, -0.5,  0.5 );
	  glTexCoord2f(1.0f, 0.0f);  glVertex3f( -0.5,  0.5,  0.5 );
	  glTexCoord2f(1.0f, 1.0f);  glVertex3f( -0.5,  0.5, -0.5 );
	  glTexCoord2f(0.0f, 1.0f);	 glVertex3f( -0.5, -0.5, -0.5 );
  glEnd();

  // LADO SUPERIOR: lado azul
  cargarTextura(text5);
  glBegin(GL_POLYGON);
	  glTexCoord2f(0.0f, 0.0f);  glVertex3f(  0.5,  0.5,  0.5 );
	  glTexCoord2f(1.0f, 0.0f);  glVertex3f(  0.5,  0.5, -0.5 );
	  glTexCoord2f(1.0f, 1.0f);  glVertex3f( -0.5,  0.5, -0.5 );
	  glTexCoord2f(0.0f, 1.0f);  glVertex3f( -0.5,  0.5,  0.5 );
  glEnd();

  // LADO INFERIOR: lado rojo
  cargarTextura(text6);
  glBegin(GL_POLYGON);
	  glTexCoord2f(0.0f, 0.0f);  glVertex3f(  0.5, -0.5, -0.5 );
	  glTexCoord2f(1.0f, 0.0f);  glVertex3f(  0.5, -0.5,  0.5 );
	  glTexCoord2f(1.0f, 1.0f);  glVertex3f( -0.5, -0.5,  0.5 );
	  glTexCoord2f(0.0f, 1.0f);  glVertex3f( -0.5, -0.5, -0.5 );
  glEnd();
     }



//Se duplico en el codigo del cubo para tener uno en donde solo reciba colores 
// y otro en donde sea aplicada textura este solo sera utilizado para la cabeza del snake
void dibujaCabeza(float re, float gr, float bl) {

	glBegin(GL_POLYGON);
	glColor3f(1.0,0.0,0.0);   
	glVertex3f(0.5, -0.5, -0.5); // P1 es rojo
    glVertex3f(0.5, 0.5, -0.5);      // P2 es verde
	glVertex3f(-0.5, 0.5, -0.5);      // P3 es azul
    glVertex3f(-0.5, -0.5, -0.5);      // P4 es morado

	glEnd();

	// LADO TRASERO: lado blanco
	glBegin(GL_POLYGON);
	glColor3f(0.38,0.0, 1.0);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	// LADO DERECHO: lado morado INFERIOR
	glBegin(GL_POLYGON);
	glColor3f(0.38,0.0, 1.0);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();

	// LADO IZQUIERDO: lado Amarrillo
	glBegin(GL_POLYGON);
	glColor3f(0.38, 0.0, 1.4);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	// LADO SUPERIOR: lado azul
	glBegin(GL_POLYGON);
	glColor3f(0.38, 0.0, 1.0);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	// LADO INFERIOR: lado rojo
	glBegin(GL_POLYGON);
	glColor3f(0.38, 0.0, 1.0);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();


}

void dibujaCubo(float re, float gr, float bl) {

	glBegin(GL_POLYGON);
	
	glColor3f(re, gr, bl);        
	glVertex3f(0.5, 0.5, -0.5);      // P1 es rojo
	glColor3f(0.0, 1.0, 0.0);     
	glVertex3f(-0.5, 0.5, -0.5);      // P2 es verde
	glColor3f(0.0, 0.0, 1.0);     
	glVertex3f(-0.5, -0.5, -0.5);      // P3 es azul
	glColor3f(1.0, 0.0, 0.0);     
	glVertex3f(0.5, -0.5, -0.5);      // P4 es morado
	
	glEnd();
	
	// LADO TRASERO: lado blanco
	glBegin(GL_POLYGON);
	glColor3f(re, gr, bl);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();
	
	// LADO DERECHO: lado morado
	glBegin(GL_POLYGON);
	glColor3f(re, gr, bl);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();
	
	// LADO IZQUIERDO: lado verde
	glBegin(GL_POLYGON);
	glColor3f(re, gr, bl);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();
	
	// LADO SUPERIOR: lado azul
	glBegin(GL_POLYGON);
	glColor3f(re, gr, bl);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();
	
	// LADO INFERIOR: lado rojo
	glBegin(GL_POLYGON);
	glColor3f(re, gr, bl);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();
	

}
//en este metodo se realiza el dibujo de las paredes que se genero a partir de varios cubos pequeños 
// dibujando 20 cubos por lado
void dibujoParedes(){
	//glRotatef(rotate_x,1.0,0.0,0.0);
	//glRotatef(rotate_y,0.0,1.0,0.0);
    //Se dubujan las paredes
    for (int i = 0; i < sizeof(paredLadox) / sizeof(paredLadox[0]); i++) {
		
			glPushMatrix();
			glTranslated(paredLadox[i], paredLadoY[i], 0);
			//dibujaCubo(0.3, 0.7, 0.9);
			dibujaCubo();
			glPopMatrix();
		}

     //Dibujar los cubos 
     for (int i = 0; i < 20; i++) {
			glPushMatrix();
			glTranslated(10, 10, -i);
			//dibujaCubo(0.3, 0.7, 0.9);
			dibujaCubo();
			glPopMatrix();
		}

     //Dibujar los cubos
     for (int i = 0; i < 20; i++) {
			glPushMatrix();
			glTranslated(-10, 10, -i);
			//dibujaCubo(0.3, 0.7, 0.9);
			dibujaCubo();
			glPopMatrix();
		}

		 //Dibujar los cubos
     for (int i = 0; i < 20; i++) {
			glPushMatrix();
			glTranslated(-10, -10, -i);
			//dibujaCubo(0.3, 0.7, 0.9);
			dibujaCubo();
			glPopMatrix();
		}

		 //Dibujar los cubos 
     for (int i = 0; i < 20; i++) {
			glPushMatrix();
			glTranslated(10, -10, -i);
			//dibujaCubo(0.3, 0.7, 0.9);
			dibujaCubo();
			glPopMatrix();
		}

    //DIbujo la bases 
    for (int i = 0; i < sizeof(paredLadox) / sizeof(paredLadox[0]); i++) {
			glPushMatrix();
			glTranslated(paredLadox[i], paredLadoY[i], -20);
			//dibujaCubo(0.3, 0.7, 0.9);
			dibujaCubo();
			glPopMatrix();
		}
}
//
void onSize(int sx, int sy) {
	glRotatef(rotate_x,1.0,0.0,0.0);
	glRotatef(rotate_y,0.0,1.0,0.0);
	glViewport(camaraLadoX, camaraLadoY, sx, sy);
	aspect = (float)sx / (float)sy;
}
// aqui es en donde surge lo mas importante del juego como lo es sus movimientos 
// condicionando cada uno de los lados hacia donde la serpiete puede girar 
void movimientoCola(int num){
    bool colaCabeza = false;
    int auxCo = 0;
    switch(num){
     case 1://Derecha
     //En este for se recorrera la lista de cola
     contadorZ = 0;
     contadorY = 0;
     for(itCola = listCola.begin(); itCola != listCola.end();itCola++){

         if(contadorX < listCola.size()){ //Si el contador es menor que la lista mocera la cola si no subira
                //Segun en que posicion se econtraba antes de dar vuelta se recorrera la cola

                //Si entra aqui  ----------------
                if( auxCo >= contadorX){

                    if(derecha ==  true && bandZ == false && flagEjeAnteriorZ == true){//Si iba hacia arriba
                        (*itCola)->setZCola((*itCola)->getZCola()-1);
                        auxCo++;
                    }

                    if(derecha ==  true && bandZ == true && flagEjeAnteriorZ == true){//Si iba hacia abajo
                        (*itCola)->setZCola((*itCola)->getZCola()+1);
                        auxCo++;
                    }

                        if(izquierda ==  true && bandY == false && flagEjeAnteriorY == true){//Si iba hacia atras
                            (*itCola)->setYCola((*itCola)->getYCola()-1);
                            auxCo++;
                        }

                         if(izquierda ==  true && bandY == true && flagEjeAnteriorY == true){//Si iba hacia adelante
                            (*itCola)->setYCola((*itCola)->getYCola()+1);
                            auxCo++;
                        }

                }else{
                    (*itCola)->setXCola((*itCola)->getXCola()+1);
                      auxCo++;
                    }
            }


         if((*itCola)->getXCola() == movimientoX[0] && (*itCola)->getZCola() == movimientoZ[0] && (*itCola)->getYCola() == movimientoY[0]){
                if(colaCabeza == false && contadorX < 1){
                    (*itCola)->setXCola(snake.getXSnake()-1);
                    (*itCola)->setYCola(snake.getYSnake());
                    (*itCola)->setZCola(snake.getZSnake());
                     auxX = (*itCola)->getXCola();
                     auxY = (*itCola)->getYCola();
                     auxZ = (*itCola)->getZCola();
                     colaCabeza = true;
                     contadorX++;
                }else{
                    (*itCola)->setXCola(auxX);
                    (*itCola)->setYCola(auxY);
                    (*itCola)->setZCola(auxZ);
                     auxX = (*itCola)->getXCola();
                     auxY = (*itCola)->getYCola();
                     auxZ = (*itCola)->getZCola();
                     contadorX++;
            }
         }else{
            if(contadorX >= listCola.size() || flagDefault == false){
                if(colaCabeza == false){
                        (*itCola)->setXCola(snake.getXSnake()-1);
                        (*itCola)->setYCola(snake.getYSnake());
                        (*itCola)->setZCola(snake.getZSnake());
                         auxX = (*itCola)->getXCola();
                         auxY = (*itCola)->getYCola();
                         auxZ = (*itCola)->getZCola();
                         colaCabeza = true;
                        }else{
                        (*itCola)->setXCola(auxX-1);
                        (*itCola)->setYCola(auxY);
                        (*itCola)->setZCola(auxZ);
                         auxX = (*itCola)->getXCola();
                         auxY = (*itCola)->getYCola();
                         auxZ = (*itCola)->getZCola();
                }
            }

         }

      }
     break;
     case 2://Izquierda
         contadorZ = 0;
         contadorY = 0;
         for(itCola = listCola.begin(); itCola != listCola.end();itCola++){
             if(contadorX < listCola.size()){ //Si el contador es menor que la lista mocera la cola si no subira
                    //Segun en que posicion se econtraba antes de dar vuelta se recorrera la cola

                    //Si entra aqui  ----------------
                    if( auxCo >= contadorX){

                        if(izquierda ==  true && bandZ == false && flagEjeAnteriorZ == true){//Si iba hacia arriba
                            (*itCola)->setZCola((*itCola)->getZCola()-1);
                            auxCo++;
                        }

                        if(izquierda ==  true && bandZ == true && flagEjeAnteriorZ == true){//Si iba hacia abajo
                            (*itCola)->setZCola((*itCola)->getZCola()+1);
                            auxCo++;
                        }

                        if(izquierda ==  true && bandY == false && flagEjeAnteriorY == true){//Si iba hacia atras
                            (*itCola)->setYCola((*itCola)->getYCola()-1);
                            auxCo++;
                        }

                         if(izquierda ==  true && bandY == true && flagEjeAnteriorY == true){//Si iba hacia arriba
                            (*itCola)->setYCola((*itCola)->getYCola()+1);
                            auxCo++;
                        }

                    }else{
                        (*itCola)->setXCola((*itCola)->getXCola()-1);
                          auxCo++;
                        }
                }


             if((*itCola)->getXCola() == movimientoX[1] && (*itCola)->getZCola() == movimientoZ[1] && (*itCola)->getYCola() == movimientoY[1]){
                    if(colaCabeza == false && contadorX < 1){
                        (*itCola)->setXCola(snake.getXSnake()+1);
                        (*itCola)->setYCola(snake.getYSnake());
                        (*itCola)->setZCola(snake.getZSnake());
                         auxX = (*itCola)->getXCola();
                         auxY = (*itCola)->getYCola();
                         auxZ = (*itCola)->getZCola();
                         colaCabeza = true;
                         contadorX++;
                    }else{
                        (*itCola)->setXCola(auxX);
                        (*itCola)->setYCola(auxY);
                        (*itCola)->setZCola(auxZ);
                         auxX = (*itCola)->getXCola();
                         auxY = (*itCola)->getYCola();
                         auxZ = (*itCola)->getZCola();
                         contadorX++;
                }
             }else{
                if(contadorX >= listCola.size() || flagDefault == false){
                    if(colaCabeza == false){
                            (*itCola)->setXCola(snake.getXSnake()+1);
                            (*itCola)->setYCola(snake.getYSnake());
                            (*itCola)->setZCola(snake.getZSnake());
                             auxX = (*itCola)->getXCola();
                             auxY = (*itCola)->getYCola();
                             auxZ = (*itCola)->getZCola();
                             colaCabeza = true;
                            }else{
                            (*itCola)->setXCola(auxX+1);
                            (*itCola)->setYCola(auxY);
                            (*itCola)->setZCola(auxZ);
                             auxX = (*itCola)->getXCola();
                             auxY = (*itCola)->getYCola();
                             auxZ = (*itCola)->getZCola();
                    }
                }

             }

          }
     break;
     case 3://Atras
         //En este for se recorrera la lista de cola
         contadorZ = 0;
         contadorX = 0;
         for(itCola = listCola.begin(); itCola != listCola.end();itCola++){

             if(contadorY < listCola.size()){ //Si el contador es menor que la lista mocera la cola si no subira
                    //Segun en que posicion se econtraba antes de dar vuelta se recorrera la cola

                    //Si entra aqui  ----------------
                    if( auxCo >= contadorY){

                        if(adelante ==  true && bandZ == false && flagEjeAnteriorZ == true){//Si iba hacia arriba
                            (*itCola)->setZCola((*itCola)->getZCola()-1);
                            auxCo++;
                        }

                        if(adelante ==  true && bandZ == true && flagEjeAnteriorZ == true){//Si iba hacia abajo
                            (*itCola)->setZCola((*itCola)->getZCola()+1);
                            auxCo++;
                        }

                        if(adelante == true && bandX == true && flagEjeAnteriorX == true){//Si iba hacia la derecha
                            (*itCola)->setXCola((*itCola)->getXCola()+1);
                            auxCo++;
                        }

                        if(adelante == true && bandX == false && flagEjeAnteriorX == true){//Si iba hacia la izquierda
                            (*itCola)->setXCola((*itCola)->getXCola()-1);
                            auxCo++;
                        }

                    }else{
                        (*itCola)->setYCola((*itCola)->getYCola()-1);
                          auxCo++;
                        }
                }


             if((*itCola)->getXCola() == movimientoX[3] && (*itCola)->getZCola() == movimientoZ[3] && (*itCola)->getYCola() == movimientoY[3]){
                    if(colaCabeza == false && contadorY < 1){
                        (*itCola)->setXCola(snake.getXSnake());
                        (*itCola)->setYCola(snake.getYSnake()+1);
                        (*itCola)->setZCola(snake.getZSnake());
                         auxX = (*itCola)->getXCola();
                         auxY = (*itCola)->getYCola();
                         auxZ = (*itCola)->getZCola();
                         colaCabeza = true;
                         contadorY++;
                    }else{
                        (*itCola)->setXCola(auxX);
                        (*itCola)->setYCola(auxY);
                        (*itCola)->setZCola(auxZ);
                         auxX = (*itCola)->getXCola();
                         auxY = (*itCola)->getYCola();
                         auxZ = (*itCola)->getZCola();
                         contadorY++;
                }
             }else{
                if(contadorY >= listCola.size() || flagDefault == false){
                    if(colaCabeza == false){
                            (*itCola)->setXCola(snake.getXSnake());
                            (*itCola)->setYCola(snake.getYSnake()+1);
                            (*itCola)->setZCola(snake.getZSnake());
                             auxX = (*itCola)->getXCola();
                             auxY = (*itCola)->getYCola();
                             auxZ = (*itCola)->getZCola();
                             colaCabeza = true;
                            }else{
                            (*itCola)->setXCola(auxX);
                            (*itCola)->setYCola(auxY+1);
                            (*itCola)->setZCola(auxZ);
                             auxX = (*itCola)->getXCola();
                             auxY = (*itCola)->getYCola();
                             auxZ = (*itCola)->getZCola();
                    }
                }

             }

          }

     break;
     case 4://Adelante
     //En este for se recorrera la lista de cola
     contadorZ = 0;
     contadorX = 0;
     for(itCola = listCola.begin(); itCola != listCola.end();itCola++){

         if(contadorY < listCola.size()){ //Si el contador es menor que la lista mocera la cola si no subira
                //Segun en que posicion se econtraba antes de dar vuelta se recorrera la cola

                //Si entra aqui  ----------------
                if( auxCo >= contadorY){
                    if(adelante ==  true && bandZ == false && flagEjeAnteriorZ == true){//Si iba hacia arriba
                        (*itCola)->setZCola((*itCola)->getZCola()-1);
                        auxCo++;
                    }

                    if(adelante ==  true && bandZ == true && flagEjeAnteriorZ == true){//Si iba hacia abajo
                        (*itCola)->setZCola((*itCola)->getZCola()+1);
                        auxCo++;
                    }

                    if(adelante == true && bandX == true && flagEjeAnteriorX == true){//Si iba hacia la derecha
                        (*itCola)->setXCola((*itCola)->getXCola()+1);
                        auxCo++;
                    }

                    if(adelante == true && bandX == false && flagEjeAnteriorX == true){//Si iba hacia la izquierda
                        (*itCola)->setXCola((*itCola)->getXCola()-1);
                        auxCo++;
                    }

                }else{
                    (*itCola)->setYCola((*itCola)->getYCola()+1);
                      auxCo++;
                    }
            }


         if((*itCola)->getXCola() == movimientoX[2] && (*itCola)->getZCola() == movimientoZ[2] && (*itCola)->getYCola() == movimientoY[2]){
                if(colaCabeza == false && contadorY < 1){
                    (*itCola)->setXCola(snake.getXSnake());
                    (*itCola)->setYCola(snake.getYSnake()-1);
                    (*itCola)->setZCola(snake.getZSnake());
                     auxX = (*itCola)->getXCola();
                     auxY = (*itCola)->getYCola();
                     auxZ = (*itCola)->getZCola();
                     colaCabeza = true;
                     contadorY++;
                }else{
                    (*itCola)->setXCola(auxX);
                    (*itCola)->setYCola(auxY);
                    (*itCola)->setZCola(auxZ);
                     auxX = (*itCola)->getXCola();
                     auxY = (*itCola)->getYCola();
                     auxZ = (*itCola)->getZCola();
                     contadorY++;
            }
         }else{
            if(contadorY >= listCola.size() || flagDefault == false){
                if(colaCabeza == false){
                        (*itCola)->setXCola(snake.getXSnake());
                        (*itCola)->setYCola(snake.getYSnake()-1);
                        (*itCola)->setZCola(snake.getZSnake());
                         auxX = (*itCola)->getXCola();
                         auxY = (*itCola)->getYCola();
                         auxZ = (*itCola)->getZCola();
                         colaCabeza = true;
                        }else{
                        (*itCola)->setXCola(auxX);
                        (*itCola)->setYCola(auxY-1);
                        (*itCola)->setZCola(auxZ);
                         auxX = (*itCola)->getXCola();
                         auxY = (*itCola)->getYCola();
                         auxZ = (*itCola)->getZCola();
                }
            }

         }

      }
     break;
     case 5://Arriba
         contadorY = 0;
         contadorX = 0;
         for(itCola = listCola.begin(); itCola != listCola.end();itCola++){
            if(contadorZ <= listCola.size()){ //Si el contador es menor que la lista mocera la cola si no subira
                //Segun en que posicion se econtraba antes de dar vuelta se recorrera la cola
                //Si entra aqui  ----------------
                if( auxCo >= contadorZ){
                    if(arriba == true && bandX == true && flagEjeAnteriorX == true){//SI hiba a la derecha
                        (*itCola)->setXCola((*itCola)->getXCola()+1);
                        auxCo++;
                    }

                    if(arriba == true && bandX == false && flagEjeAnteriorX == true){//SI hiba a la izquierda
                        (*itCola)->setXCola((*itCola)->getXCola()-1);
                        auxCo++;
                    }

                    if(arriba == true && bandY == false && flagEjeAnteriorY == true){//SI hiba hacia adelante
                        (*itCola)->setYCola((*itCola)->getYCola()-1);
                        auxCo++;
                    }

                    if(arriba == true && bandY == true && flagEjeAnteriorY == true){//SI hiba hacia atras
                        (*itCola)->setYCola((*itCola)->getYCola()+1);
                        auxCo++;
                    }

                }else{
                    (*itCola)->setZCola((*itCola)->getZCola()-1);
                      auxCo++;
                    }
                }
            //Se compará la cola con e punto que dio vuelta el snake
            if((*itCola)->getXCola() == movimientoX[4] && (*itCola)->getZCola() == movimientoZ[4] && (*itCola)->getYCola() == movimientoY[4]){

                if(colaCabeza == false && contadorZ < 1){
                    (*itCola)->setXCola(snake.getXSnake());
                    (*itCola)->setYCola(snake.getYSnake());
                    (*itCola)->setZCola(snake.getZSnake()+1);
                     auxX = (*itCola)->getXCola();
                     auxY = (*itCola)->getYCola();
                     auxZ = (*itCola)->getZCola();
                     colaCabeza = true;
                     contadorZ++;
                }else{
                    (*itCola)->setXCola(auxX);
                    (*itCola)->setYCola(auxY);
                    (*itCola)->setZCola(auxZ);
                     auxX = (*itCola)->getXCola();
                     auxY = (*itCola)->getYCola();
                     auxZ = (*itCola)->getZCola();
                     contadorZ++;
                    }
                }else{
                    if(contadorZ >= listCola.size() || flagDefault == false){
                        if(colaCabeza == false){
                                (*itCola)->setXCola(snake.getXSnake());
                                (*itCola)->setYCola(snake.getYSnake());
                                (*itCola)->setZCola(snake.getZSnake()+1);
                                 auxX = (*itCola)->getXCola();
                                 auxY = (*itCola)->getYCola();
                                 auxZ = (*itCola)->getZCola();
                                 colaCabeza = true;
                                }else{
                                (*itCola)->setXCola(auxX);
                                (*itCola)->setYCola(auxY);
                                (*itCola)->setZCola(auxZ+1);
                                 auxX = (*itCola)->getXCola();
                                 auxY = (*itCola)->getYCola();
                                 auxZ = (*itCola)->getZCola();
                        }
                    }

                 }

            }
     break;
     case 6://Abajo
             contadorY = 0;
             contadorX = 0;
             for(itCola = listCola.begin(); itCola != listCola.end();itCola++){
                if(contadorZ <= listCola.size()){ //Si el contador es menor que la lista mocera la cola si no subira
                    //Segun en que posicion se econtraba antes de dar vuelta se recorrera la cola
                    //Si entra aqui  ----------------
                    if( auxCo >= contadorZ){
                        if(abajo == true && bandX == true && flagEjeAnteriorX == true){//SI hiba a la derecha
                            (*itCola)->setXCola((*itCola)->getXCola()+1);
                            auxCo++;
                        }

                        if(abajo == true && bandX == false && flagEjeAnteriorX == true){//SI hiba a la izquierda
                            (*itCola)->setXCola((*itCola)->getXCola()-1);
                            auxCo++;
                        }

                        if(arriba == true && bandY == false && flagEjeAnteriorY == true){//SI hiba hacia atras

                        (*itCola)->setYCola((*itCola)->getYCola()-1);
                        auxCo++;
                        }

                        if(arriba == true && bandY == true && flagEjeAnteriorY == true){//SI hiba hacia adelante
                            (*itCola)->setYCola((*itCola)->getYCola()+1);
                            auxCo++;
                        }


                    }else{
                        (*itCola)->setZCola((*itCola)->getZCola()+1);
                          auxCo++;
                        }
                    }
                //Se compará la cola con e punto que dio vuelta el snake
                if((*itCola)->getXCola() == movimientoX[5] && (*itCola)->getZCola() == movimientoZ[5] && (*itCola)->getYCola() == movimientoY[5]){

                    if(colaCabeza == false && contadorZ < 1){
                        (*itCola)->setXCola(snake.getXSnake());
                        (*itCola)->setYCola(snake.getYSnake());
                        (*itCola)->setZCola(snake.getZSnake()-1);
                         auxX = (*itCola)->getXCola();
                         auxY = (*itCola)->getYCola();
                         auxZ = (*itCola)->getZCola();
                         colaCabeza = true;
                         contadorZ++;
                    }else{
                        (*itCola)->setXCola(auxX);
                        (*itCola)->setYCola(auxY);
                        (*itCola)->setZCola(auxZ);
                         auxX = (*itCola)->getXCola();
                         auxY = (*itCola)->getYCola();
                         auxZ = (*itCola)->getZCola();
                         contadorZ++;
                        }
                    }else{
                        if(contadorZ >= listCola.size() || flagDefault == false){
                            if(colaCabeza == false){
                                    (*itCola)->setXCola(snake.getXSnake());
                                    (*itCola)->setYCola(snake.getYSnake());
                                    (*itCola)->setZCola(snake.getZSnake()-1);
                                     auxX = (*itCola)->getXCola();
                                     auxY = (*itCola)->getYCola();
                                     auxZ = (*itCola)->getZCola();
                                     colaCabeza = true;
                                    }else{
                                    (*itCola)->setXCola(auxX);
                                    (*itCola)->setYCola(auxY);
                                    (*itCola)->setZCola(auxZ-1);
                                     auxX = (*itCola)->getXCola();
                                     auxY = (*itCola)->getYCola();
                                     auxZ = (*itCola)->getZCola();
                            }
                        }

                     }

                }
     break;
    }

  }
//metodo para colocar comiada aleatoria dentro del cubo
void ponerComida(){
    srand(time(NULL));
    int x = -10 + 12;// por el momento se colocaron delante de la serpiente para verificar si realiza la accion de comer
    int y = -10 + 10;// recibe sus respectivas coordenadas x,y,z
    int z = -20 + 10;
    listComida.push_back(new Comida(x,y,z));
}

//ahora si con este metodo se manda a llamar a cada uno de los casos que puede realizar la serpiente en base a los movimientos permitidos
void jugarSnake(){
	//Hacia adelante
    if(adelante == true && atras == true && bandY == true){
        snake.setYSnake(snake.getYSnake()+1);
        if(snake.getYSnake() > 15){
                    exit(0);
                }
            //Verificamos si hay comida
                if(listComida.back()->getXComida() == snake.getXSnake() && listComida.back()->getYComida() == snake.getYSnake() &&
                    listComida.back()->getZComida() == snake.getZSnake()){
                    if( listCola.size() < 1 ) //Aqui comprobamos que si la cola esta vacia
                            {
                                listCola.push_back(new Cola(snake.getXSnake(),snake.getYSnake()-1,snake.getZSnake()));
                                listComida.clear();
                                ponerComida();
                                contadorY++;
                    }
                    else{
                        //Insertamoc una cola al final de la lista
                        listCola.push_back(new Cola(listCola.back()->getXCola(),listCola.back()->getYCola()-1,listCola.back()->getZCola()));
                        listComida.clear();
                        ponerComida();
                        contadorY++;
                    }

                }
    }else{ //Avanzar a la izquierda
        if(izquierda == true && derecha == true && bandX == false){
            snake.setXSnake(snake.getXSnake()-1);
            if(snake.getXSnake() < -15){
                    exit(0);
                }
            //Verificamos si hay comida
                if(listComida.back()->getXComida() == snake.getXSnake() && listComida.back()->getYComida() == snake.getYSnake() &&
                    listComida.back()->getZComida() == snake.getZSnake()){
                    if( listCola.size() < 1 ) //Aqui comprobamos que si la cola esta vacia
                            {
                                listCola.push_back(new Cola(snake.getXSnake(),snake.getYSnake()+1,snake.getZSnake()));
                                listComida.clear();
                                ponerComida();
                                contadorY++;
                    }
                    else{
                        //Insertamoc una cola al final de la lista
                        listCola.push_back(new Cola(listCola.back()->getXCola(),listCola.back()->getYCola()+1,listCola.back()->getZCola()));
                        listComida.clear();
                        ponerComida();
                        contadorY++;
                    }

                }

        }else{ //Avanzar a la Derecha
            if(derecha == true && izquierda == true && bandX == true){
                snake.setXSnake(snake.getXSnake()+1);
                //Verificamos si llego Alfinal del cubo
                if(snake.getXSnake() > 15){
                    exit(0);
                }
                //Verificamos si hay comida
                if(listComida.back()->getXComida() == snake.getXSnake() && listComida.back()->getYComida() == snake.getYSnake() &&
                    listComida.back()->getZComida() == snake.getZSnake()){
                    if( listCola.size() < 1 ) //Aqui comprobamos que si la cola esta vacia
                            {
                                listCola.push_back(new Cola(snake.getXSnake()-1,snake.getYSnake(),snake.getZSnake()));
                                bandCola = true;
                                listComida.clear();
                                ponerComida();
                                contadorY++;
                    }
                    else{
                        //Insertamoc una cola al final de la lista
                        listCola.push_back(new Cola(listCola.back()->getXCola()-1,listCola.back()->getYCola(),listCola.back()->getZCola()));
                        contadorX++;
                        listComida.clear();
                        ponerComida();
                    }

                }
            }else{ //Avanza hacia atras
                if(adelante == true && atras == true && bandY == false){
                  snake.setYSnake(snake.getYSnake()-1);
                  if(snake.getYSnake() < -15){
                    exit(0);
                }
                //Verificamos si hay comida
                if(listComida.back()->getXComida() == snake.getXSnake() && listComida.back()->getYComida() == snake.getYSnake() &&
                    listComida.back()->getZComida() == snake.getZSnake()){
                    if( listCola.size() < 1 ) //Aqui comprobamos que si la cola esta vacia
                            {
                                listCola.push_back(new Cola(snake.getXSnake(),snake.getYSnake()+1,snake.getZSnake()));
                                listComida.clear();
                                ponerComida();
                                contadorY++;
                    }
                    else{
                        //Insertamoc una cola al final de la lista
                        listCola.push_back(new Cola(listCola.back()->getXCola(),listCola.back()->getYCola()+1,listCola.back()->getZCola()));
                        listComida.clear();
                        ponerComida();
                        contadorY++;
                    }

                }
                }else{//Hacia arriba
                    if(arriba == true && abajo == true && bandZ == false)
                    {
                        snake.setZSnake(snake.getZSnake()-1);
                        if(snake.getZSnake() < -25){
                            exit(0);
                        }

                        //Verificamos si hay comida
                            if(listComida.back()->getXComida() == snake.getXSnake() && listComida.back()->getYComida() == snake.getYSnake() &&
                                listComida.back()->getZComida() == snake.getZSnake()){
                                if( listCola.size() < 1 ) //Aqui comprobamos que si la cola esta vacia
                                        {
                                            listCola.push_back(new Cola(snake.getXSnake(),snake.getYSnake(),snake.getZSnake()+1));
                                            listComida.clear();
                                            ponerComida();
                                            contadorY++;
                                        }
                                    else{
                                        //Insertamoc una cola al final de la lista
                                        listCola.push_back(new Cola(listCola.back()->getXCola(),listCola.back()->getYCola(),listCola.back()->getZCola()+1));
                                        listComida.clear();
                                        ponerComida();
                                        contadorZ++;
                                    }

                                }
                    }
                    else{//Hacia abajo
                         if(arriba == true && abajo == true && bandZ == true)
                        {
                            snake.setZSnake(snake.getZSnake()+1);
                            if(snake.getZSnake() > 5){
                                exit(0);
                            }

                            //Verificamos si hay comida
                            if(listComida.back()->getXComida() == snake.getXSnake() && listComida.back()->getYComida() == snake.getYSnake() &&
                                listComida.back()->getZComida() == snake.getZSnake()){
                                if( listCola.size() < 1 ) //Aqui comprobamos que si la cola esta vacia
                                        {
                                            listCola.push_back(new Cola(snake.getXSnake(),snake.getYSnake(),snake.getZSnake()-1));
                                            bandCola = true;
                                    }
                                    else{
                                        //Insertamoc una cola al final de la lista
                                        listCola.push_back(new Cola(listCola.back()->getXCola(),listCola.back()->getYCola(),listCola.back()->getZCola()+1));
                                        listComida.clear();
                                        ponerComida();
                                        contadorZ++;
                                    }

                                }

                        }
                    }
                }
            }
        }
    }

    Sleep(200);//velocidad del snake a menor valor mayor velocidad 
}


void aumentaCola()
{
	//todo realizado para hacer que la cola aumente de tamaño si pasa por las coordenadas en donde se encuentra la comida  
    for(int i = 0;i < 3 ;i++){
        if( bandCola == false)
                            {
                                listCola.push_back(new Cola(snake.getXSnake()-1,snake.getYSnake(),snake.getZSnake()));
                                bandCola = true;
                        }
                    else{
                        listCola.push_back(new Cola(listCola.back()->getXCola()-1,listCola.back()->getYCola(),listCola.back()->getZCola()));
                    }
    }
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

//metodo para la interaccion del teclado con el juego usando teclas especiales 
void ArrowKey(int key, int x, int y) {
	//Código
	switch(key){
	            case GLUT_KEY_RIGHT://Derecha
                    if(derecha == false){
                    zRotacion -= 90;
                    derecha = true;
                    izquierda = true;
                    adelante = false;
                    atras = false;
                    arriba = false;
                    abajo = false;
                    bandX = true;
                    //Colocmoes el anterior
                    if(flagEjeZ == true){
                        flagEjeAnteriorZ = true;
                    }else{
                        flagEjeAnteriorZ = false;
                    }

                    if(flagEjeY == true){
                        flagEjeAnteriorY = true;
                    }else{
                        flagEjeAnteriorY = false;
                    }
                    flagEjeX = true;
                    flagEjeZ = false;
                    flagEjeY = false;
                    }
                    //Se usaran las banderaas para mover la cola
                    moverDerecha = true;
                    moverArriba = false;
                    moverAbajo = false;
                    moverIzquierda = false;
                    moverAdelante = false;
                    moverAtras = false;
                    //Colcamos en el arreglo los puntos donde dio vuelta
                    movimientoX[0] = snake.getXSnake();
                    movimientoY[0] = snake.getYSnake();
                    movimientoZ[0] = snake.getZSnake();
					break;
                case GLUT_KEY_LEFT://Izquierd
                    if(izquierda == false){
                    if(arriba == true){
                    yRotacion += 90;
                    zRotacion += 90;
                    abajo = false;
                    arriba = false;
                    flagDefault = true;
                    }else{
                    zRotacion += 90;
                    }
                    izquierda = true;
                    derecha = true;
                    adelante = false;
                    atras = false;
                    bandX = false;
                    if(flagEjeZ == true){
                        flagEjeAnteriorZ = true;
                    }else{
                        flagEjeAnteriorZ = false;
                    }

                    if(flagEjeY == true){
                        flagEjeAnteriorY = true;
                    }else{
                        flagEjeAnteriorY = false;
                    }
                    flagEjeX = true;
                    flagEjeZ = false;
                    flagEjeY = false;
                    }
                    //Se usaran las banderaas para mover la cola
                    moverIzquierda = true;
                    moverDerecha = false;
                    moverArriba = false;
                    moverAbajo = false;
                    moverAdelante = false;
                    moverAtras = false;
                    movimientoX[1] = snake.getXSnake();
                    movimientoY[1] = snake.getYSnake();
                    movimientoZ[1] = snake.getZSnake();
                     break;
                case GLUT_KEY_UP://Arriba
                    if(arriba == false){
                    yRotacion -= 90;
                    arriba = true;
                    izquierda = false;
                    derecha = false;
                    atras = false;
                    adelante = false;
                    abajo = true;
                    bandZ = false;
                    flagDefault = true;
                    if(flagEjeX == true){
                        flagEjeAnteriorX = true;
                    }else{
                        flagEjeAnteriorX = false;
                    }

                    if(flagEjeY == true){
                        flagEjeAnteriorY = true;
                    }else{
                        flagEjeAnteriorY = false;
                    }
                    flagEjeZ = true;
                    flagEjeX = false;
                    flagEjeY = false;
                    }
                    //Se usaran las banderaas para mover la cola
                    moverArriba = true;
                    moverDerecha = false;
                    moverAbajo = false;
                    moverIzquierda = false;
                    moverAdelante = false;
                    moverAtras = false;
                      //Colcamos en el arreglo los puntos donde dio vuelta
                    movimientoX[4] = snake.getXSnake();
                    movimientoY[4] = snake.getYSnake();
                    movimientoZ[4] = snake.getZSnake();
                     break;
                case GLUT_KEY_DOWN://Abajo
                    if(abajo == false){
                    arriba = true;
                    izquierda = false;
                    derecha = false;
                    atras = false;
                    adelante = false;
                    abajo = true;
                    bandZ = true;
                    flagDefault = true;
                    if(flagEjeX == true){
                        flagEjeAnteriorX = true;
                    }else{
                        flagEjeAnteriorX = false;
                    }

                    if(flagEjeY == true){
                        flagEjeAnteriorY = true;
                    }else{
                        flagEjeAnteriorY = false;
                    }
                    flagEjeZ = true;
                    flagEjeX = false;
                    flagEjeY = false;
                    }
                    //Se usaran las banderaas para mover la cola
                    moverAbajo = true;
                    moverDerecha = false;
                    moverArriba = false;
                    moverIzquierda = false;
                    moverAdelante = false;
                    moverAtras = false;
                    //Colcamos en el arreglo los puntos donde dio vuelta
                    movimientoX[5] = snake.getXSnake();
                    movimientoY[5] = snake.getYSnake();
                    movimientoZ[5] = snake.getZSnake();
                     break;
                case GLUT_KEY_HOME://Atras
                    if(atras == false){
                    zRotacion += 90;
                    atras = true;
                    adelante = true;
                    izquierda = false;
                    derecha = false;
                    arriba = false;
                    abajo = false;
                    bandY = false;
                    flagDefault = true;
                    if(flagEjeZ == true){
                        flagEjeAnteriorZ = true;
                    }else{
                        flagEjeAnteriorZ = false;
                    }

                    if(flagEjeX == true){
                        flagEjeAnteriorX = true;
                    }else{
                        flagEjeAnteriorX = false;
                    }
                    flagEjeX = false;
                    flagEjeY = true;
                    flagEjeZ = false;
                    }
                     //Se usaran las banderaas para mover la cola
                    moverAtras = true;
                    moverDerecha = false;
                    moverArriba = false;
                    moverAbajo = false;
                    moverIzquierda = false;
                    moverAdelante = false;
                    movimientoX[3] = snake.getXSnake();
                    movimientoY[3] = snake.getYSnake();
                    movimientoZ[3] = snake.getZSnake();
                     break;
                case GLUT_KEY_END://Adelante
                    if(adelante == false){
                    zRotacion = -90;
                    adelante = true;
                    izquierda = false;
                    derecha = false;
                    atras = true;
                    arriba = false;
                    abajo = false;
                    bandY = true;
                    flagDefault = true;
                    if(flagEjeZ == true){
                        flagEjeAnteriorZ = true;
                    }else{
                        flagEjeAnteriorZ = false;
                    }

                    if(flagEjeX == true){
                        flagEjeAnteriorX = true;
                    }else{
                        flagEjeAnteriorX = false;
                    }
                    flagEjeX = false;
                    flagEjeY = true;
                    flagEjeZ = false;
                }
                //Se usaran las banderaas para mover la cola
                moverAdelante = true;
                moverDerecha = false;
                moverArriba = false;
                moverAbajo = false;
                moverIzquierda = false;
                moverAtras = false;
                movimientoX[2] = snake.getXSnake();
                movimientoY[2] = snake.getYSnake();
                movimientoZ[2] = snake.getZSnake();
                break;
				//teclas para cambiar perspectivas de acuerdo a la tecla 
		case GLUT_KEY_F2:
		camara1 -= 1;
		break;
        case GLUT_KEY_F1:
            camara1 += 1;
            break;
        case GLUT_KEY_F3:
            camara2 -= 1;
            break;
        case GLUT_KEY_F4:
            camara2 += 1;
            break;
        case GLUT_KEY_F5:
            camara3 += 1;
            break;
        case GLUT_KEY_F6:
            camara3 -= 1;
            break;
        case GLUT_KEY_F7:
            camara4 += 1;
            break;
        case GLUT_KEY_F8:
            camara4 -= 1;
            break;
        case GLUT_KEY_F9:
            camara5 += 1;
            break;
        case GLUT_KEY_F10:
            camara5 -= 1;
            break;
				
                }

	glutPostRedisplay();
}

//uniendo toda la escena para su funcionamiento completo
void display(void) {
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//glRotatef(rotate_x,1.0,0.0,0.0);
	//glRotatef(rotate_y,0.0,1.0,0.0);
	gluLookAt(camara1 , camara2, camara3,
			  camara4, camara5, 0,
			  0, 0, -10);
	glPushMatrix();
	if(bx==true){
		rotate_x += 50;
	}
	if(by==true){
		rotate_y += 50;
	}
	if(bz==true){
		rotate_z += 50;
	}
	glRotatef(rotate_z,0.0,0.0,1.0);
    dibujoParedes();

    //Dibuja el Snake
			glPushMatrix();
			glTranslated(snake.getXSnake(), snake.getYSnake(),snake.getZSnake());
			glRotated(zRotacion,0,0,1);
			glRotated(yRotacion,0,1,0);
			glRotated(xRotacion,1,0,0);
			dibujaCabeza(1.0, 0.2, 1.0);
			glPopMatrix();

    //Dibujar la comida
            glPushMatrix();
			glTranslated(listComida.back()->getXComida(), listComida.back()->getYComida(),listComida.back()->getZComida());
			dibujaCubo(1.0, 1.0, 0.0);
			glPopMatrix();

    //Dibuja lo cola
        for(itCola = listCola.begin(); itCola != listCola.end();itCola++){
            glPushMatrix();
			glTranslated((*itCola)->getXCola(), (*itCola)->getYCola(),(*itCola)->getZCola());
            dibujaCubo(1.0, 0.0, 0.047);
			glPopMatrix();
        }


    jugarSnake();
    //cout<<"salioo\n";

	if(moverDerecha == true)
        movimientoCola(1);
        else
         if(moverArriba == true)
         movimientoCola(5);
         else
            if(moverAbajo == true)
            movimientoCola(6);
            else
                if(moverIzquierda == true)
                movimientoCola(2);
                else
                    if(moverAdelante == true)
                    movimientoCola(4);
                    else
                        if(moverAtras == true)
                        movimientoCola(3);
	glPopMatrix();
    glFlush();
	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//Inicializa la matriz de proyeccion
	gluPerspective(70.0f, aspect, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
}
//teclas para girar la escena 
void keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
    case 'w':
		rotate_x+=50.0;
         break;
    case 's':
		rotate_x-=50.0;
         break;
    case 'a':
		rotate_y-=50.0;
         break;
    case 'd':
		rotate_y+=50.0;
         break;
    case 'x':
		rotate_z+=90.0;
		//rotate_x+=2.0;
		//rotate_y-=2.0;
         break;
	case 'z':
		rotate_z-=90.0;
		
		break;
	case 27:
		exit(0);
		break;
	}
}
//mandamos a ejecutar todo
int main(int argc, char** argv)
{
    ponerComida();
    aumentaCola();
	glutInit(&argc, argv);//inicializa el motor de OGL
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);//se ursará un doble buffer y el modelo de color RGB
	glutInitWindowSize(600,500);//Damos el tamaño a la ventana
	glutInitWindowPosition(100, 100);//Damos la posición de inicio de la ventana
	glutCreateWindow("SNAKE 3D"); //Creamos la ventana
	//glEnable(GL_DEPTH_TEST);
	//init();
	initRendering();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutIdleFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(ArrowKey);
	glutMainLoop();//ciclo infinito
	return 0;
}

