//Semestre 2017 - 1
//************************************************************//
//************************************************************//
//************** Alumno (s): *********************************//
//*************		Augusto Meza Peña    			    ******//
//*************		Rosa María Yolotzin Muñoz Álvarez	******//
//*************		Mauro Caballero						******//
//*************		David Cruz							******//
//************************************************************//
//************************************************************//

#include "texture.h"
#include "figuras.h"
#include <iostream>
#include <irrKlang.h>
#include "Camera.h"
#include "cmodel/CModel.h"

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll
irrklang::ISoundEngine* engine;
irrklang::ISound* music;
//Solo para Visual Studio 2015
#if (_MSC_VER == 1900)
#   pragma comment( lib, "legacy_stdio_definitions.lib" )
#endif

CCamera objCamera; 
GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font=(int)GLUT_BITMAP_HELVETICA_18;

GLfloat Diffuse[]= { 0.7f, 0.7f, 0.7f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 10.0f, -10.0f, 0.0f };			// Light Position
GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = {0.7, 0.7, 0.7, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = {18};

CTexture t_cielo,whitebrick,whitewall,greyroof,piso,pool,grass,road,blue,water,tile,tree,window,wood1;
CFiguras mi;
bool hatemusic = true,backwards=false;
float movX = 0, movZ = 0,x=0;
			
void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel (GL_SMOOTH);
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glLightfv(GL_LIGHT1, GL_AMBIENT, m_amb1);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT0);

	glEnable ( GL_COLOR_MATERIAL );

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	/* setup blending */
	//glEnable(GL_BLEND);			// Turn Blending On
    
	t_cielo.LoadBMP("textures/sky2.bmp");
	t_cielo.BuildGLTexture();
	t_cielo.ReleaseImage();

	whitebrick.LoadBMP("textures/white.bmp");
	whitebrick.BuildGLTexture();
	whitebrick.ReleaseImage();

	whitewall.LoadBMP("textures/whitewall.bmp");
	whitewall.BuildGLTexture();
	whitewall.ReleaseImage();

	greyroof.LoadBMP("textures/greyroof.bmp");
	greyroof.BuildGLTexture();
	greyroof.ReleaseImage();

	piso.LoadBMP("textures/floor.bmp");
	piso.BuildGLTexture();
	piso.ReleaseImage();

	tile.LoadBMP("textures/tile.bmp");
	tile.BuildGLTexture();
	tile.ReleaseImage();

	road.LoadBMP("textures/road.bmp");
	road.BuildGLTexture();
	road.ReleaseImage();

	blue.LoadBMP("textures/blue.bmp");
	blue.BuildGLTexture();
	blue.ReleaseImage();

	window.LoadTGA("textures/window.tga");
	window.BuildGLTexture();
	window.ReleaseImage();

	tree.LoadTGA("textures/tree.tga");
	tree.BuildGLTexture();
	tree.ReleaseImage();

	water.LoadBMP("textures/water.bmp");
	water.BuildGLTexture();
	water.ReleaseImage();

	grass.LoadBMP("textures/grass.bmp");
	grass.BuildGLTexture();
	grass.ReleaseImage();

	pool.LoadBMP("textures/pool.bmp");
	pool.BuildGLTexture();
	pool.ReleaseImage();

	wood1.LoadBMP("textures/wood1.bmp");
	wood1.BuildGLTexture();
	wood1.ReleaseImage();


>>>>>>> 42ce3efebc6dd301320e46b23f5d9a343c8e19fe
	/* Setup Sound*/
	engine = irrklang::createIrrKlangDevice();
	if (!engine) printf("No se pudo crear sonido");
	if(!hatemusic) music = engine->play3D("sounds/lostinthought.flac",
		irrklang::vec3df(10, 1.7, 10), true, false, true);
	if (music) {
		music->setMinDistance(3.0f);
		music->setIsPaused(false); // unpause the sound
	}
	engine->setListenerPosition(irrklang::vec3df(10, 1.7, 10),irrklang::vec3df(10.5, 1.7, 10));
	/*Camera initial position*/
	objCamera.Position_Camera(10,1.70,10, 10.5,1.70,10, 0, 1, 0);

}

void pintaTexto(float x, float y, float z, void *font,char *string)
{
  
  char *c;     //Almacena los caracteres a escribir
  glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
  //glWindowPos2i(150,100);
  for (c=string; *c != '\0'; c++) //Condicion de fin de cadena
  {
    glutBitmapCharacter(font, *c); //imprime
  }
}

void chair() {
	glTranslatef(2.265, .55, 2.4825 + 4);
	mi.techo(.055, 1, .055, 5, 5, 1, wood1.GLindex);

	glTranslatef(-.35, 0, 0);
	mi.techo(.055, 1, .055, 5, 5, 1, wood1.GLindex);


	glTranslatef(.15 + .025, 0.30, 0);
	mi.techo(0.3, .15, .055, 5, 5, 1, wood1.GLindex);

	glTranslatef(0, -0.225, 0);
	mi.techo(0.3, .15, .055, 5, 5, 1, wood1.GLindex);

	glTranslatef(0, 0.40 + 0.025, 0);
	mi.techo(0.405 + 0.025, .0275, .055, 5, 5, 1, wood1.GLindex);

	glTranslatef(0, -0.525 - .1, 0.1125 + 0.05625);
	mi.techo(.40, .11, .30, 5, 5, 1, wood1.GLindex);


}

void uno() {
	glPushMatrix();
		glTranslatef(9.85-0.26,1.45,0.009375);
		mi.pared(0.52, 2.9, 0.15, 0.2, 0.1, 2, whitebrick.GLindex);
		glTranslatef(-0.26+0.075,0,0.285+0.075);
		mi.pared(0.15, 2.9, 0.57, 0.1, 0.2, 2, whitebrick.GLindex);
		glTranslatef(0, 0, 0.665+0.285);
		mi.pared(0.15, 2.9, 1.33, 0.1, 2, 2, whitewall.GLindex);
		glTranslatef(0.26,0,0.665-0.075);
		mi.pared(0.37, 2.9, 0.15, 0.2, 0.1, 2, whitewall.GLindex);
		glTranslatef(0.11+0.075, 0, -0.95);
		mi.pared(0.01, 2.9, 2.05, 0.1, 1.3, 2, whitebrick.GLindex);
		glTranslatef(-2.395+0.87, 0, -0.26-0.0375+0.025);
		mi.pared(2.01, 2.9, 0.075, 2.5, 0.1, 2, 0,whitewall.GLindex,whitewall.GLindex,whitebrick.GLindex);
		glTranslatef(1.875 - 1.11 - 0.075-0.87, 0, -0.26-0.137);
		mi.pared(0.15, 2.9, 0.57+0.15, 0.1, 0.2, 2, whitebrick.GLindex);
		glTranslatef(-0.60-0.25,0,0);
		mi.pared(0.15, 2.9, 0.57 + 0.15, 0.1, 0.2, 2, whitebrick.GLindex, whitewall.GLindex, whitewall.GLindex, whitebrick.GLindex);
		glTranslatef(-0.07 - 0.845, 0, -0.4+0.075);
		mi.pared(1.69, 2.9, 0.075, 2, 0.2, 2, whitebrick.GLindex, whitewall.GLindex, whitewall.GLindex, whitebrick.GLindex);
		glTranslatef(0.0375+0.01, 0, 0.7225);
		mi.pared(1.69+0.075+0.02, 2.9, 0.075, 2.5, 0.2, 2, whitebrick.GLindex, whitewall.GLindex, whitewall.GLindex, whitewall.GLindex);
		glTranslatef(-0.8925+0.0375, 0, -0.0375-0.0375);
		mi.pared(0.075, 2.9, 0.075, 0.2, 0.1, 2, whitewall.GLindex);//Marco de la puerta
		glTranslatef(0,1.2,-0.36125+0.0375);
		mi.pared(0.075, 0.50, 0.7225-0.15,0.1,0.5,0.1, whitewall.GLindex);
		glTranslatef(-0.075, -1.2, -0.36125+0.0375);
		mi.pared(0.075, 2.9, 0.075, 0.2, 0.1, 2, 0, 0, whitewall.GLindex, whitebrick.GLindex);//Marco de la puerta
		glTranslatef(-0.3125-.0375, 1.2, 0);
		mi.pared(0.625, 0.50, 0.075 , 0.5, 0.5,0.4, 0, 0, whitewall.GLindex, whitebrick.GLindex);
		glTranslatef(-0.3125 -.075, -1.2, 0);
		mi.pared(0.15, 2.9, 0.075, 0.2, 0.1, 2, 0, 0, whitewall.GLindex, whitebrick.GLindex);//Marco de la puerta
	glPopMatrix();
	glPushMatrix();
	glTranslatef(7.265-0.24, 2.9+0.15, 2.575-0.075);
	mi.techo(5.65, 0.3, 5.17,5,5,1, greyroof.GLindex);
	glTranslatef(0.24, -2.9 - 0.15 - 0.0375, 0);
	mi.techo(5.17, 0.075, 5.17, 5, 5, 1, piso.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7.305, .95, 2.575 - 0.075);
	mi.techo(5.65, 0.3, 5.17, 5, 5, 1, wood1.GLindex);

	glPopMatrix();
}
void dos() {
	glPushMatrix();
		glTranslatef(9.85-2.825, 1.45,-6.0-.16+0.009375);
			mi.pared(5.65, 2.9,0.15, 4, 0.1, 2, whitebrick.GLindex);//pared exterior
		glTranslatef(0,1.45+0.15,3);
			mi.techo(5.65, 0.30, 6.15, 5, 5, 1, greyroof.GLindex);//techo
		glTranslatef(-2.175+0.075, -2.9-0.15-0.0375,0);
			mi.techo(9.85, 0.075, 6.15, 5, 5, 1, piso.GLindex);
	glPopMatrix();
}
void tres(){}
void cuatro(){}
void cinco(){}
void seis(){}
void siete(){}
void ocho(){}

//void pared(float largo, float altura, float profundidad, float frontback (hacia la casa), float rightleft, float vertical, GLuint right, GLuint left=0, GLuint front=0, GLuint back=0);//Funcíon creacion prisma
//void techo(float largo, float altura, float profundidad, GLuint text);//Funcion creacion prisma

void nuevediez() {
	glPushMatrix();
	glTranslatef(0, 0, 0.37);
	glPushMatrix();
	glTranslatef(0.075, 2.90 / 2, 1.90 + 2.95 + (9.93 / 2) - 0.075);
	mi.pared(0.15, 2.90, 9.93 + 0.15, 0, 4, 2, whitewall.GLindex, whitebrick.GLindex, 0, 0);
	glPopMatrix();

	/*glPushMatrix();
	glTranslatef(4.53/2, 2.90 / 2, 1.90 + 2.95 + 9.93-0.075);
	mi.pared(4.53, 2.90, 0.15, 0, 4, 2, whitewall.GLindex, whitebrick.GLindex, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.815, 2.90 / 2, 1.90 + 2.95 + 9.93-0.075);
	mi.pared(3.63, 2.90, 0.15, 0, 4, 2, whitewall.GLindex, whitebrick.GLindex, 0, 0);

	glTranslatef(1.815,1.45-.25, 0);
	mi.pared(0.90, .5, 0.15, 0, 4, 2, whitewall.GLindex, whitebrick.GLindex, 0, 0);

	glPopMatrix();*/

	glPushMatrix();
	glTranslatef(2.715, 2.90 + .15, 9.815 - 0.15);
	mi.techo(5.43, 0.30, 9.93 + 0.30, 5, 5, 1, greyroof.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0.009375);
	glTranslatef(0, 0, -0.15 - 0.15);
	glTranslatef(5.925 - 0.009375, 2.90 + .30 + .40, 4.85 + .075);
	mi.techo(9.85 + 2, .80, 0.15, 5, 5, 1, greyroof.GLindex);

	glTranslatef(-3.96, 0, 5.715);
	mi.techo(0.15, .80, 11.43 + 0.075, 5, 5, 1, greyroof.GLindex);

	glTranslatef(1.25, 0, 0);
	mi.techo(0.15, .80, 11.43 + 0.075, 5, 5, 1, greyroof.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0.009375);
	glTranslatef(7.975 - (0.0375 / 4), 2.90 + .30 + .40, 14.855 - 0.15);
	mi.techo(11.8 - (0.0375 / 2), .80, .15, 5, 5, 1, greyroof.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.715, -.0375, 9.815 - 0.075);
	mi.techo(5.43, 0.075, 9.93 + 0.15, 5, 5, 1, piso.GLindex);
	glPopMatrix();


	//mesa

	glPushMatrix();
	glTranslatef(2.265, .75, 2.4825 + 5.225);
	mi.techo(2.5, .125, 1.5, 5, 5, 1, wood1.GLindex);
	glPopMatrix();
	chair();

	glPopMatrix();




}

void once(){
	glPushMatrix();//Alberca
		glTranslatef(11.85+4, -0.0375-2, 7.5375 + 0.009375);
		mi.techo(4, 0.075, 15.225, 2, 10, 1, pool.GLindex);
		glTranslatef(2 - 0.0375, 1, 0);
		mi.pared(0.075,2-0.075, 15.225-0.15,2,10,1,pool.GLindex);
		glTranslatef(0, 1, 0);
		mi.pared(0.075, 0.075, 15.225 - 0.15, 10, 30, 0.1, tile.GLindex);
		glTranslatef(-4+0.075, -1, 0);
		mi.pared(0.075, 2 - 0.075, 15.225 - 0.15, 2, 10, 1, pool.GLindex);
		glTranslatef(0, 1, 0);
		mi.pared(0.075, 0.075, 15.225 - 0.15, 10, 30, 0.1, tile.GLindex);
		glTranslatef(2-0.0375,-1, 7.6125-0.0375);
		mi.pared(4, 2 - 0.075,0.075, 5, 2, 1, pool.GLindex);
		glTranslatef(0, 1, 0);
		mi.pared(4, 0.075, 0.075, 1, 0.1, 10, tile.GLindex);
		glTranslatef(0, -1, -15.225+0.075);
		mi.pared(4, 2 - 0.075, 0.075, 5, 2, 1, pool.GLindex);
		glTranslatef(0, 1, 0);
		mi.pared(4, 0.075, 0.075, 1, 0.1, 10, tile.GLindex);
	glPopMatrix();
	glPushMatrix();//Central grande
		glTranslatef(9.85 + 4, -0.0375, -3.15);
		mi.techo(8, 0.075, 6.15, 3, 3, 2, grass.GLindex);
		glTranslatef(0, 0, 24.4875+0.009375+0.0375);
		mi.techo(8, 0.075, 12.45, 3, 3, 2, grass.GLindex);
		glTranslatef(4+6.075,0,-10.6875);
		mi.techo(12.15, 0.075, 33.825, 3, 3, 2, grass.GLindex);
	glPopMatrix();
	glPushMatrix();//Laterales
		glTranslatef(15, -0.0375, -6.225-1.19375-.15-.0375);
		mi.techo(30, 0.075, 2.3875+.3+.075, 3, 3, 2, grass.GLindex);
		glTranslatef(0, 0, 30+5+2-0.15+0.0375);
		mi.techo(30, 0.075, 2.3875 + .3 + .15+0.5, 3, 3, 2, grass.GLindex);
	glPopMatrix();
	glPushMatrix();//Road
		glTranslatef(-5,0,11);
		mi.techo(10, 0.075, 40, 1, 2, 0.1, road.GLindex);
	glPopMatrix();
}
void doce(){
	
	

	glPushMatrix();
		glTranslatef(7.64, -0.0375, 9.225-.075-0.0375);//pasto12
		mi.techo(4.27+.15, 0.075, 8+0.075, 3, 3, 2, grass.GLindex);

		glTranslatef(0, 0, 5+0.0375);//piso pasillo de 12
		mi.techo(4.27 + .15, .075, 2, 5, 5, 1, piso.GLindex);

		glTranslatef(0, 2.9 + 0.15+.0375, 0);
		mi.techo(4.27 + .15, 0.30, 2, 5, 5, 1, greyroof.GLindex);




	glPopMatrix();
}

void trece(){
	glPushMatrix();
		glTranslatef(2.34, 1.45, 0);
		mi.pared(4.68, 2.9, 0.15, 3, 0.1, 2, whitebrick.GLindex);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.075, 1.45, 2.5+0.075);
		mi.pared(0.15, 2.9, 5, 0.1, 3, 2, whitebrick.GLindex);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(2.34, -0.0375, 2.5);
		mi.techo(4.68, 0.075, 5.15, 3, 3, 2, grass.GLindex);
	glPopMatrix();
}
void catorce(){}
void quince(){
	glPushMatrix();
	glTranslatef(11.85, 2.9 + 0.15, 7.5375+0.009375);
	mi.techo(4, 0.30, 15.225, 5, 5, 1, greyroof.GLindex);
	glTranslatef(0, -2.9-0.15-.0375, 0);
	mi.techo(4, 0.075, 15.225, 5, 5, 1, piso.GLindex);
	glTranslatef(0, +2.9 + 0.15 + .0375 + 0.15 + 0.4, 1.1625);
	mi.techo(0.15, .80, 12.9, 5, 5, 1, greyroof.GLindex);
	glPopMatrix();

}
void uno_ventanas(){}
void dos_ventanas(){}
void tres_ventanas(){}
void cuatro_ventanas(){}
void cinco_ventanas(){}
void seis_ventanas(){}
void siete_ventanas(){}
void ocho_ventanas(){}
void nuevediez_ventanas(){}
void once_ventanas(){
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);     // Turn Blending On
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_COLOR);
		glPushMatrix();//Alberca
			glTranslatef(11.85 + 4, -0.15-1+0.075, 7.5375 + 0.009375);
			mi.techomueve(4-0.15, 2, 15.225-0.15, 4,movX, 15,movZ, 1, water.GLindex);
		glPopMatrix();

	glDisable(GL_BLEND);        // Turn Blending Off
	glEnable(GL_LIGHTING);
}
void doce_ventanas(){}
void trece_ventanas(){
	/*glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);     // Turn Blending On
	glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
	glTranslatef(2.34 + 0.075, 1.45, 5 + 0.075);
	glRotatef(90, 0, 1, 0);
	mi.pared(0.001, 2.9, 4.53, 0, 5, 1, window.GLindex, window.GLindex, 0, 0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.15+4.53, 1.45, 2.5 + 0.075);
		mi.pared(0.001, 2.9, 5, 0, 4, 1, window.GLindex, window.GLindex,0,0);
	glPopMatrix();
	glDisable(GL_BLEND);        // Turn Blending Off
	glEnable(GL_LIGHTING);*/

}
void catorce_ventanas(){}
void quince_ventanas(){}


void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	
	glPushMatrix();

		glRotatef(g_lookupdown,1.0f,0,0);

		gluLookAt(	objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
					objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
					objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);
	

		glPushMatrix();		
			glPushMatrix(); //Creamos cielo
				glDisable(GL_LIGHTING);
				glTranslatef(10,30-0.075-2,11);
				mi.skybox(40.0, 60.0, 40.0,t_cielo.GLindex,blue.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();
		glPopMatrix();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3d(0,0,0);
		glVertex3d(100, 0, 0);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(1, 1, 1);
		glVertex3d(0, 0, 0);
		glVertex3d(0, 100, 0);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0.4, 0.4, 0.4);
		glVertex3d(0, 0, 0);
		glVertex3d(0, 0, 100);
		glEnd();
		
		glPushMatrix();
			uno();
			dos();
			tres();
			cuatro();
			cinco();
			seis();
			siete();
			ocho();
			nuevediez();
			once();
			doce();
			trece();
			catorce();
			quince();
			uno_ventanas();
			dos_ventanas();
			tres_ventanas();
			cuatro_ventanas();
			cinco_ventanas();
			seis_ventanas();
			siete_ventanas();
			ocho_ventanas();
			nuevediez_ventanas();
			once_ventanas();
			doce_ventanas();
			trece_ventanas();
			catorce_ventanas();
			quince_ventanas();
		glPopMatrix();

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
		glColor3f(1.0,0.0,0.0);
		pintaTexto(-12,12.0,-14.0,(void *)font,"Proyecto Final");
		glColor3f(1.0,1.0,1.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glutSwapBuffers ( );

}

void animacion()
{
	if (x > 1000) x = 0;
	x += 0.005;
	movX = sin(x*2);
	movZ = sin(x*2);
	
	//printf("%.2f %.2f\n", movX, movZ);
	glutPostRedisplay();
}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 170.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) {
		case 'f':   //Movimientos de camara
		case 'F':
			g_lookupdown = 3;
			objCamera.Position_Camera(-6.39, 1.70, -4.8, -5.97, 1.7, -4.54, 0, 1, 0);
			break;
		case 'c':   //Movimientos de camara
		case 'C':
			g_lookupdown = 2;
			objCamera.Position_Camera(1.5, 1.70, 11.89, 1.76, 1.7, 11.46, 0, 1, 0);
			break;
		case 'o':   //Movimientos de camara
		case 'O':
			g_lookupdown = 6;
			objCamera.Position_Camera(13.74, 1.70, 17.27, 13.83, 1.7, 16.78, 0, 1, 0);
			break;
		case 'i':   //Movimientos de camara
		case 'I':
			g_lookupdown = 29;
			objCamera.Position_Camera(20.55, 10.10, 18.83, 20.20, 10.10, 18.48, 0, 1, 0);
			break;
		case 'w':   //Movimientos de camara
		case 'W':
			objCamera.Move_Camera( CAMERASPEED+0.2 );
			break;

		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED+0.2));
			break;

		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED+0.4));
			break;

		case 'd':
		case 'D':
			objCamera.Strafe_Camera( CAMERASPEED+0.4 );
			break;

		case 'p':
		case 'P':
			printf("Pos x:%.2f\tPos y:%.2f\tPos z:%.2f\tView x:%.2f\tView y:%.2f\tView z:%.2f\tLookupdown:%.2f\n",
				objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z, objCamera.mView.x, objCamera.mView.y, objCamera.mView.z, g_lookupdown);
			break;

		case ' ':		//Poner algo en movimiento
					//Activamos/desactivamos la animacíon
			break;

		case 27:        // Cuando Esc es presionado...
			if(!hatemusic) music->drop(); // release music stream.
			engine->drop(); // delete engine
			exit ( 0 );   // Salimos del programa
			break;        
		default:        // Cualquier otra
			break;
  }
  if(!hatemusic)
  engine->setListenerPosition(irrklang::vec3df(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z), irrklang::vec3df(objCamera.mView.x, objCamera.mView.y, objCamera.mView.z));
  glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
	case GLUT_KEY_PAGE_UP:
		
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View( CAMERASPEED);
		break;

    default:
		break;
  }
  glutPostRedisplay();
}


int main ( int argc, char** argv )   // Main Function
{
  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (1600, 900);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Proyecto Final"); // Nombre de la Ventana
  //glutFullScreen     ( );         // Full Screen
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutIdleFunc		  ( animacion );
  glutMainLoop        ( );          // 

  return 0;
}
