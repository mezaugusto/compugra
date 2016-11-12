//#include <windows.h>  //Solo para Windows
//#include <GL/gl.h>     // The GL Header File
//#include <stdio.h>

//#include <math.h>
#include "Main.h"


class CFiguras
{
	public:

	float text_der;
	float text_izq;

	void esfera(GLfloat radio, int meridianos, int paralelos, GLuint text); //Funcíon creacion esfera
	void cilindro(float radio, float altura, int resolucion, GLuint text);	//Funcíon creacion cilindro
	void cono(float altura, float radio, int resolucion, GLuint text);		//Funcíon creacion cono
	void prisma_anun (GLuint text, GLuint text2);							//Funcíon creacion movimiento
	void prisma (float altura, float largo, float profundidad, GLuint text);//Funcíon creacion prisma
	void arbol(float altura,float radio,GLuint arbol);
	void pared(float largo, float altura, float profundidad, float frontback, float rightleft, float vertical, GLuint right, GLuint left=0, GLuint front=0, GLuint back=0);//Funcíon creacion prisma
	void techo(float largo, float altura, float profundidad, float vertical, float horizontal,float side, GLuint top, GLuint bottom = 0, GLuint sides = 0);//Funcíon creacion prisma
	void techomueve(float largo, float altura, float profundidad, float vertical,float verticalMoving, float horizontal, float horizontalMoving, float side, GLuint top, GLuint bottom = 0, GLuint sides = 0);//Funcíon creacion prisma
	void agua(float largo, float altura, float profundidad, float vertical, float horizontal, float verticalMoving, float side, GLuint top);
	void prisma2 (GLuint text, GLuint text2);
	void skybox(float altura, float largo, float profundidad, GLuint text,GLuint text2);	//Funcion creacion cielo
	void ventana_solid(float altura, float largo, float profundidad, GLuint frame);
	void ventana_blend(float altura, float largo, float profundidad, GLuint window);
	void ventana_solid_repeat(float longitud,float ventanas,float altura, float profundidad, GLuint frame);
	void ventana_blend_repeat(float longitud, float ventanas, float altura, float profundidad, GLuint window);
	void chair(GLuint material,GLuint sillon);
	void table(GLuint patas, GLuint mesa);
	void sofa(GLuint sides, GLuint material, GLuint cojines=0);
	void tv(GLuint material, GLuint tv,float distortion=0);
	//void torus(GLfloat radioM, GLfloat radiom, int meridianos, int paralelos, GLuint text );
	void torus(GLfloat radioM, GLfloat radiom, int meridianos, int paralelos);
	void alacena(GLuint material, GLuint sillon, float rotalacena);

};
