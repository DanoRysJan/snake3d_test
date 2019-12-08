#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <windows.h>
#include <list>
#include <iterator>
#include <time.h>

using namespace std;


double rotate_x=0;
double rotate_y=0;
double rotate_z=0;
//Variables de la camara Y necesarias
int camara1 = -1;
int camara2 = 27;
int camara3 = -12;
int camara4 = 7;
int camara5 = -203;
int camara6 = 0;
float aspect = 1.0f;
double  camara_x = 0.0;
double  camara_y = 0.0;

int xTraslate = 0;
int yTraslate = 0;
int zTraslate = 0;

int xRotacion = 0;
int yRotacion = 0;
int zRotacion = 0;

bool bx=false;
bool by=false;
bool bz=false;

//Coordenadas
int paredx[] = { 0 ,1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9 ,10,-1,-2,-3,-4,-5,-6,-7,-8,-9,-10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, -1, -2, -3, -4, -5, -6, -7, -8, -9,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10 };
int paredY[] = { 10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10 ,10, 9, 8, 7, 6, 5,4 ,3 ,2 ,1 ,0 ,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,   1,  2,  3, 4,  5,  6,  7,  8,  9, 10, -1, -2, -3, -4, -5, -6, -7, -8, -9,-10,  0 };

int contadorX = 0;
int contadorY = 0;
int contadorZ = 0;

int co = 0;

	
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
	
	void dubujarParedes(){
		
		//Se dubujan las paredes
		//glRotatef(rotate_x,1.0,0.0,0.0);
		//glRotatef(rotate_y,0.0,1.0,0.0);
		for (int i = 0; i < sizeof(paredx) / sizeof(paredx[0]); i++) {
			//glRotatef(rotate_x,1.0,0.0,0.0);
			//glRotatef(rotate_y,0.0,1.0,0.0);
			glPushMatrix();
			glTranslated(paredx[i], paredY[i], 0);
			dibujaCubo(0.3, 0.7, 0.9);
			//dibujaCubo();
			glPopMatrix();
		}
		
		//Dibujar los cubos en el eje z
		for (int i = 0; i < 20; i++) {
			//glRotatef(rotate_x,1.0,0.0,0.0);
			//glRotatef(rotate_y,0.0,1.0,0.0);
			glPushMatrix();
			glTranslated(10, 10, -i);
			dibujaCubo(0.3, 0.7, 0.9);
			//dibujaCubo();
			glPopMatrix();
		}
		
		//Dibujar los cubos en el eje z
		for (int i = 0; i < 20; i++) {
			//glRotatef(rotate_x,1.0,0.0,0.0);
			//glRotatef(rotate_y,0.0,1.0,0.0);
			glPushMatrix();
			glTranslated(-10, 10, -i);
			dibujaCubo(0.3, 0.7, 0.9);
			//dibujaCubo();
			glPopMatrix();
		}
		
		//Dibujar los cubos en el eje z
		for (int i = 0; i < 20; i++) {
			//glRotatef(rotate_x,1.0,0.0,0.0);
			//glRotatef(rotate_y,0.0,1.0,0.0);
			glPushMatrix();
			glTranslated(-10, -10, -i);
			dibujaCubo(0.3, 0.7, 0.9);
			//dibujaCubo();
			glPopMatrix();
		}
		
		//Dibujar los cubos en el eje z
		for (int i = 0; i < 20; i++) {
			//glRotatef(rotate_x,1.0,0.0,0.0);
			//glRotatef(rotate_y,0.0,1.0,0.0);
			glPushMatrix();
			glTranslated(10, -10, -i);
			dibujaCubo(0.3, 0.7, 0.9);
			//dibujaCubo();
			glPopMatrix();
		}
		
		//DIbujo la bases pero con el eje z
		for (int i = 0; i < sizeof(paredx) / sizeof(paredx[0]); i++) {
			//glRotatef(rotate_x,1.0,0.0,0.0);
			//glRotatef(rotate_y,0.0,1.0,0.0);
			glPushMatrix();
			glTranslated(paredx[i], paredY[i], -20);
			dibujaCubo(0.3, 0.7, 0.9);
			//dibujaCubo();
			glPopMatrix();
		}
	}
		
		void onSize(int sx, int sy) {
			
			glViewport(camara_x, camara_y, sx, sy);
			aspect = (float)sx / (float)sy;
		}
		
					void init(void) {
		
						glClearColor(0.0, 0.0, 0.0, 0.0);
					}
					
					void ArrowKey(int key, int x, int y) {
						//Código
						switch(key){
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
					
					
					void display(void) {
						glMatrixMode(GL_MODELVIEW);
						glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
						glLoadIdentity();
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
						//glRotatef(rotate_x,1.0,0.0,0.0);
						//glRotatef(rotate_y,0.0,1.0,0.0);
						glRotatef(rotate_z,0.0,0.0,1.0);
						
						
						dubujarParedes();
						
						glPopMatrix();
						glFlush();
					    glutSwapBuffers();
						
					}
					
					void reshape(int w, int h) {
						glViewport(0, 0, (GLsizei)w, (GLsizei)h);
						glMatrixMode(GL_PROJECTION);
						glLoadIdentity();//Inicializa la matriz de proyeccion
						gluPerspective(70.0f, aspect, 0.1f, 1000.0f);
						//glOrtho(-40.0, 40.0, -20.0, 20.0, 40.0, 1.0);
						glMatrixMode(GL_MODELVIEW);
					}
					
					void keyboard(unsigned char key, int x, int y) {
						switch (key)
						{
						case 'w':
							//glRotatef(0.0,1.0,0.0,0.0);
							rotate_x+=50.0;
							break;
						case 's':
							rotate_x-=50.0;
							break;
						case 'a':
							rotate_y-=100.0;
							break;
						case 'd':
							rotate_y+=50.0;
							break;
						case 'x':
							rotate_z+=50.0;
							//rotate_x+=2.0;
							//rotate_y-=2.0;
							break;
						case 'z':
							rotate_z-=50.0;
							
							break;
						case 27:
							exit(0);
							break;
						}
						glutPostRedisplay();
					}
					
					int main(int argc, char** argv)
					{
					
						glutInit(&argc, argv);//inicializa el motor de OGL
						glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);//se ursará un doble buffer y el modelo de color RGB
						glutInitWindowSize(600,500);//Damos el tamaño a la ventana
						glutInitWindowPosition(100, 100);//Damos la posición de inicio de la ventana
						glutCreateWindow("SNAKE 3D"); //Creamos la ventana
						//glEnable(GL_DEPTH_TEST);
						init();
						glutDisplayFunc(display);
						glutReshapeFunc(reshape);
						
						glutIdleFunc(display);
						glutKeyboardFunc(keyboard);
						glutSpecialFunc(ArrowKey);
						glutMainLoop();//ciclo infinito
						return 0;
					}
					
					
