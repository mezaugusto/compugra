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
GLfloat Diffuse2[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 30.0f, 30.0f, 0.0f };			// Light Position
GLfloat Position2[]= { 7.0f, 1.0f, -2.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = {0.7, 0.7, 0.7, 1.0 };				// Ambiental Light Values
GLfloat m_amb2[] = { 1.0, 1.0, 1.0, 1.0 };				// Ambiental Light Values

CTexture t_cielo,whitebrick,whitewall,greyroof,piso,pool,grass,road,blue,water,tile,tree,window,wood2,wood1,metal,leather,tree2,tree3;
CTexture sofa, puff, carpet, tv1, tv2,tv3,tv4,tv5,black,puerta,puerta2;
CFiguras mi;
CModel toilet;
GLuint currenttv;
GLuint currentsky;
#define COLOR_DEFAULT 0.35
bool hatemusic = true,backwards=false,ejes=false,valak=false;
float movX = 0,x=0,x2=0,defaultcolor = COLOR_DEFAULT, distortion=0;


#define MAX_FRAMES 13 //cantidad de cuadros clave que se pueden guardar
int i_max_steps = 60;//cuadro intermedios
int i_curr_steps = 0;//CONTADOR

float tras_sillas = 0.0;
float up_sillas = 0.0;
float rot_sillas = 0.0;
float door = 0.0;

typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float tras_sillas;
	float tras_sillas_inc;
	float up_sillas;
	float up_sillas_inc;
	float rot_sillas;
	float rot_sillas_inc;
	float door;
	float door_inc;

}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;
			
void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);
	//Para construir la figura comentar esto
	glLightfv(GL_LIGHT0, GL_POSITION, Position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, m_amb1);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Position2);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);

	glEnable(GL_COLOR_MATERIAL);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glPolygonMode(GL_BACK, GL_LINE);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	//NEW Iniciar variables de KeyFrames
	for (int i = 0; i<MAX_FRAMES; i++)
	{
		KeyFrame[i].tras_sillas = 0;
		KeyFrame[i].up_sillas = 0;
		KeyFrame[i].rot_sillas = 0;
		KeyFrame[i].door = 0;
	}
	//Cuadro 1
		FrameIndex++;	
	//Cuadro 2
		KeyFrame[FrameIndex].tras_sillas = 1;
		FrameIndex++;
	//Cuadro 3
		KeyFrame[FrameIndex].tras_sillas = 1;
		KeyFrame[FrameIndex].up_sillas = 1.4;
		KeyFrame[FrameIndex].rot_sillas = (float)(rand()%20);
		FrameIndex++;
	//Cuadro 4
		KeyFrame[FrameIndex].tras_sillas = 1;
		KeyFrame[FrameIndex].up_sillas = 1.5;
		KeyFrame[FrameIndex].door = 0.99;
		KeyFrame[FrameIndex].rot_sillas = -1 * (float)(rand() % 20);
		FrameIndex++;
	//Cuadro 5
		KeyFrame[FrameIndex].tras_sillas = 1;
		KeyFrame[FrameIndex].up_sillas = 1.7;
		KeyFrame[FrameIndex].rot_sillas = -1 * (float)(rand() % 20);
		FrameIndex++;
	//Cuadro 6
		KeyFrame[FrameIndex].tras_sillas = 1;
		KeyFrame[FrameIndex].up_sillas = 0;
		KeyFrame[FrameIndex].door = 0;
		KeyFrame[FrameIndex].rot_sillas = 0;
		FrameIndex++;
	//Cuadro 7
		KeyFrame[FrameIndex].tras_sillas = 0;
		FrameIndex++;
		FrameIndex++;
		FrameIndex++;

	//Modelos 3ds
	toilet._3dsLoad("models/toilet.3ds");

	t_cielo.LoadBMP("textures/sky2.bmp");
	t_cielo.BuildGLTexture();
	t_cielo.ReleaseImage();
	currentsky = t_cielo.GLindex;

	black.LoadBMP("textures/skyblack.bmp");
	black.BuildGLTexture();
	black.ReleaseImage();

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

	carpet.LoadBMP("textures/carpet.bmp");
	carpet.BuildGLTexture();
	carpet.ReleaseImage();

	puff.LoadBMP("textures/puff.bmp");
	puff.BuildGLTexture();
	puff.ReleaseImage();


	blue.LoadBMP("textures/blue.bmp");
	blue.BuildGLTexture();
	blue.ReleaseImage();

	window.LoadTGA("textures/window.tga");
	window.BuildGLTexture();
	window.ReleaseImage();

	puerta.LoadTGA("textures/door.tga");
	puerta.BuildGLTexture();
	puerta.ReleaseImage();

	puerta2.LoadTGA("textures/door2.tga");
	puerta2.BuildGLTexture();
	puerta2.ReleaseImage();

	tv1.LoadTGA("textures/tv1.tga");
	tv1.BuildGLTexture();
	tv1.ReleaseImage();
	currenttv = tv1.GLindex;

	tv2.LoadTGA("textures/tv2.tga");
	tv2.BuildGLTexture();
	tv2.ReleaseImage();

	tv3.LoadTGA("textures/tv3.tga");
	tv3.BuildGLTexture();
	tv3.ReleaseImage();

	tv4.LoadTGA("textures/tv4.tga");
	tv4.BuildGLTexture();
	tv4.ReleaseImage();

	tv5.LoadTGA("textures/tv5.tga");
	tv5.BuildGLTexture();
	tv5.ReleaseImage();

	tree.LoadTGA("textures/tree.tga");
	tree.BuildGLTexture();
	tree.ReleaseImage();

	tree2.LoadTGA("textures/tree2.tga");
	tree2.BuildGLTexture();
	tree2.ReleaseImage();

	tree3.LoadTGA("textures/tree3.tga");
	tree3.BuildGLTexture();
	tree3.ReleaseImage();

	water.LoadTGA("textures/water.tga");
	water.BuildGLTexture();
	water.ReleaseImage();

	grass.LoadBMP("textures/grass.bmp");
	grass.BuildGLTexture();
	grass.ReleaseImage();

	pool.LoadBMP("textures/pool.bmp");
	pool.BuildGLTexture();
	pool.ReleaseImage();

	sofa.LoadBMP("textures/sofa.bmp");
	sofa.BuildGLTexture();
	sofa.ReleaseImage();

	leather.LoadBMP("textures/leather.bmp");
	leather.BuildGLTexture();
	leather.ReleaseImage();

	metal.LoadBMP("textures/metal.bmp");
	metal.BuildGLTexture();
	metal.ReleaseImage();

	wood1.LoadBMP("textures/wood1.bmp");
	wood1.BuildGLTexture();
	wood1.ReleaseImage();

	wood2.LoadBMP("textures/wood2.bmp");
	wood2.BuildGLTexture();
	wood2.ReleaseImage();

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

void resetElements(void)//lo que tenia en el cuadro cero se empieza a reproducir lo hace l
{
	tras_sillas = KeyFrame[0].tras_sillas;
	up_sillas = KeyFrame[0].up_sillas;
	rot_sillas = KeyFrame[0].rot_sillas;
	door = KeyFrame[0].door;
}

void interpolation(void)// playIndex me lleva al cuadro clave  y sus propiedades, se le resta el valor
{
	KeyFrame[playIndex].tras_sillas_inc = (KeyFrame[playIndex + 1].tras_sillas - KeyFrame[playIndex].tras_sillas) / i_max_steps;
	KeyFrame[playIndex].up_sillas_inc = (KeyFrame[playIndex + 1].up_sillas - KeyFrame[playIndex].up_sillas) / i_max_steps;
	KeyFrame[playIndex].rot_sillas_inc = (KeyFrame[playIndex + 1].rot_sillas - KeyFrame[playIndex].rot_sillas) / i_max_steps;
	KeyFrame[playIndex].door_inc = (KeyFrame[playIndex + 1].door - KeyFrame[playIndex].door) / i_max_steps;
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

void chairkitch() {

	mi.cilindro(.2, .025, 24, greyroof.GLindex);
	glTranslatef(0,.0125-0.00625,0);
	mi.cilindro(.025, .7, 16, greyroof.GLindex);
	glTranslatef(0, .7+.025, 0);
	mi.prisma(.3,0.075, .4, metal.GLindex);
	glTranslatef(0, .0375, 0);
	mi.prisma(.3, .0375, .4, puff.GLindex);
	glTranslatef(0, .075+ .0375, .2-.005 - .005 - .005 - .005 - .005);
	mi.prisma(.3, .2-.005, .05, metal.GLindex);
}


void uno() {
	glPushMatrix();
		glTranslatef(9.59, 1.45, 0.009375);
		mi.pared(0.52, 2.9, 0.15, 0.2, 0.1, 2, whitebrick.GLindex);
		glTranslatef(-.185, 0, 0.36);
		mi.pared(0.15, 2.9, 0.57, 0.1, 0.2, 2, whitebrick.GLindex);
		glTranslatef(0, 0, 0.95);
		mi.pared(0.15, 2.9, 1.33, 0.1, 2, 2, whitewall.GLindex);
		glTranslatef(0.26, 0, 0.59);
		mi.pared(0.37, 2.9, 0.15, 0.2, 0.1, 2, whitewall.GLindex);
		glTranslatef(0.185, 0, -0.95);
		mi.pared(0.01, 2.9, 2.05, 0.1, 1.3, 2, whitebrick.GLindex);
		glTranslatef(-1.525, 0, -0.2725);
		mi.pared(2.01, 2.9, 0.075, 2.5, 0.1, 2, 0, whitewall.GLindex, whitewall.GLindex, whitebrick.GLindex);
		glTranslatef(-.18, 0, -0.397);
		mi.pared(0.15, 2.9, 0.72, 0.1, 0.2, 2, whitebrick.GLindex);
		glTranslatef(-0.85, 0, 0);
		mi.pared(0.15, 2.9, 0.72, 0.1, 0.2, 2, whitebrick.GLindex, whitewall.GLindex, whitewall.GLindex, whitebrick.GLindex);
		glTranslatef(-0.915, 0, -0.325);
		mi.pared(1.69, 2.9, 0.075, 2, 0.2, 2, whitebrick.GLindex, whitewall.GLindex, whitewall.GLindex, whitebrick.GLindex);
		glTranslatef(0.0475, 0, 0.7225);
		mi.pared(1.785, 2.9, 0.075, 2.5, 0.2, 2, whitebrick.GLindex, whitewall.GLindex, whitewall.GLindex, whitewall.GLindex);
		glTranslatef(-0.855, 0, -.32375);
		mi.door(0.075, 2.9, 0.6475, x2, whitewall.GLindex,whitewall.GLindex, puerta.GLindex,puerta2.GLindex);
		glTranslatef(-0.35, -1.2, -0.32375);
		glPushMatrix();
			glRotatef(90,0,1,0);
			mi.door(0.075, 2.9, .7, -x2, whitewall.GLindex,whitebrick.GLindex, puerta.GLindex, puerta2.GLindex);
		glPopMatrix();
		glTranslatef(-.467, 0, 0);
		mi.pared(0.15, 2.9, 0.075, 0.2, 0.1, 2, 0, 0, whitewall.GLindex, whitebrick.GLindex);//Marco de la puerta*/
	glPopMatrix();
	glPushMatrix();
	glTranslatef(7.265-0.24, 2.9+0.15, 2.575-0.075);
	mi.techo(5.65, 0.3, 5.17,5,5,1, greyroof.GLindex);
	glTranslatef(0.24, -2.9 - 0.15 - 0.0375, 0);
	mi.techo(5.17, 0.075, 5.17, 5, 5, 1, piso.GLindex);
	glPopMatrix();
	//alacena
	glPushMatrix();

		glTranslatef(5.43 + 0.57 + .075 + .0375, 0.475, 0.80 - .075 + .025);
		glPushMatrix();
			mi.alacena(wood1.GLindex, greyroof.GLindex, movX*100*play);

			glTranslatef(1.8, 0,0);
			mi.alacena(wood1.GLindex, greyroof.GLindex, movX * 100 * play);

			glTranslatef(0, 2.2, 0);
			mi.alacena(wood1.GLindex, greyroof.GLindex, movX * 100 * play);

			glTranslatef(-1.8, 0, 0);
			mi.alacena(wood1.GLindex, greyroof.GLindex, movX * 100 * play);
			glPopMatrix();
			
		glTranslatef(0.57+0.33, 0, 0);
		mi.techo(0.66, 0.9, 0.05, 5, 5, 1, wood1.GLindex);

		glTranslatef(0, 0, 0.575);
		mi.techo(0.66, 0.9, 0.05, 5, 5, 1, wood1.GLindex);

		glTranslatef(0, 2.2, 0);
		mi.techo(0.66, 0.9, 0.05, 5, 5, 1, wood1.GLindex);

		glTranslatef(0, -.45-0.025, -0.2875);
		mi.techo(0.66, .05, .60 + 0.0125 + 0.0125, 5, 5, 1, greyroof.GLindex);

		glTranslatef(0, -1.25,0.2875-0.071875);
		mi.techo(0.66, .05,0.14375+0.05, 5, 5, 1, greyroof.GLindex);

		glTranslatef(0, -.1, -0.2875);
		glPushMatrix();
			mi.techo(0.66, .05, 0.38125, 5, 5, 1, metal.GLindex);

			glTranslatef(-0.33-.2,+.05+0.0125+.002, 0);
			mi.techo(.4+.002, .1+.025, 0.38125, 5, 5, 1, metal.GLindex);

			glTranslatef(+0.33+.5+.05, 0, 0);
			mi.techo(.05, .1 + 0.025+0.002, 0.38125, 5, 5, 1, metal.GLindex);
		glPopMatrix();
		  
		glTranslatef(-0.226+0.05, 0.05+0.025, -0.190625-0.025);
		mi.techo(1.112, .1, 0.05+0.002+0.002, 5, 5, 1, metal.GLindex);

		glTranslatef(+0.226 - 0.05,+0.052,0);
		mi.techo(0.45, 0.095, 0.05, 5, 5, 1, metal.GLindex);

		glTranslatef(-0.1125, +0.026, 0);
		mi.cilindro(.025, 0.085, 12, metal.GLindex);

		glTranslatef(0.225, 0, 0);
		mi.cilindro(.025, 0.085, 12, metal.GLindex);

		glTranslatef(-0.1125, .2, 0);
		mi.prisma(.04, .4, .04, metal.GLindex);

		glTranslatef(0, .2, .1-.0125+.002+.002);
		mi.prisma(.04, .05, .2+.025, metal.GLindex);

		glTranslatef(0, -.025, .0915);
		mi.prisma(.04, .03, .04, metal.GLindex);
		//refri
		glTranslatef(0.33+1.14+.4+0.025, -1, 0.075); //parte baja
		mi.prisma(.885-0.025-0.0125, 1.2, .65, metal.GLindex);//ancho
		
		glTranslatef(0, +1.2+.05, 0);//parte alta
		mi.prisma(.885 - 0.025 - 0.0125, 1.2, .65, metal.GLindex);//ancho


		glTranslatef(0, -.6 + .025, 0);//mitad
		mi.prisma(.885 - 0.025 - 0.0125, .05, .65, greyroof.GLindex);//ancho

		glTranslatef(0, -0.05, 0);//mitad
		mi.prisma(.885 - 0.025 - 0.0125, .05, .65, greyroof.GLindex);//ancho

		glTranslatef(-.4+.0125, -0.4, .375+.002);//agarraderas
		mi.prisma(.035, .55, .025, greyroof.GLindex);//ancho

		glTranslatef(0, .95, 0);//agarradera
		mi.prisma(.035, .65, .025, greyroof.GLindex);//ancho
		glTranslatef(-1 - .625, -1.25 + .2, 1.6);
		mi.alacena(wood1.GLindex, greyroof.GLindex, 0);

		glTranslatef(0.57 + .5 - .15, 0, 0.575 - 0.14375 + 0.025);
		mi.techo(1 - .3, .90, 0.14375 * 2, 5, 5, 1, wood1.GLindex);//ancho alto profunididad

		glTranslatef(.5 + .285, 0, -0.45625);
		mi.alacena(wood1.GLindex, greyroof.GLindex, 0);

		glTranslatef(-.5 - .285 - .05 - .025 + .00625, +.05, +.45625 - .2875 - .025);
		mi.techo(.5, .55, 0.14375 * 2 + .05 + .025, 5, 5, 1, metal.GLindex);

		glTranslatef(0, 0, 0);
		mi.techo(.6 - .025, .85, 0.14375 * 2 + .05 + .002, 5, 5, 1, greyroof.GLindex);

		glTranslatef(0, -0.425 - .05 - .025, 0);
		mi.techo(.6 - .025, .1 + .05, 0.14375 * 2 + .05 + .002, 5, 5, 1, metal.GLindex);

		glTranslatef(0, +0.90, 0);
		mi.techo(.6 - .025, .09, 0.14375 * 2 + .05 + .002 + .002, 5, 5, 1, metal.GLindex);

		glTranslatef(0, +0.005, 0);
		mi.techo(.6 - .025, .01, 0.14375 * 2 + .05 + .002 + .002, 5, 5, 1, metal.GLindex);

		glTranslatef(0, 0.025 - .002 - .002, +.14375 * 2 + .025);
		mi.techo(.6 - .025, .05, 0.14375 * 2, 5, 5, 1, greyroof.GLindex);

		glTranslatef(0, -1 + .05, 0);
		mi.techo(.6 - .025, .05, 0.14375 * 2, 5, 5, 1, greyroof.GLindex);

		glTranslatef(0, +1 - 0.05 + .05 + .3 + 1.05 + .10, -(+.14375 * 2 + .025));
		mi.prisma(.3, 1.2 - .05 - .1 - .1, .3, greyroof.GLindex);//ancho

		glTranslatef(0, -.475, 0);
		mi.prisma(.75, .05, .4, greyroof.GLindex);//ancho

		glTranslatef(-.9, -2, .7);
		chairkitch();
		glTranslatef(1,-.5-.25-.125, -.2);
		chairkitch();
		glTranslatef(1, -.5 - .25 - .125, -.2);
		chairkitch();
												  
	glPopMatrix();

	glPushMatrix();
		glTranslatef(4.53+1.85,0.5,0.4);
		glRotatef(90, 0, 1, 0);
		glScalef(0.0005, 0.0011, 0.0008);
		toilet.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(9.85-0.0375,1.45,2.125+1.475-.075+ 0.009375);
		mi.ventana_solid_repeat(2.95+.15, 4, 2.9, 0.075, metal.GLindex);
		glTranslatef(-2.135-0.0375, 0, 1.475+0.0375);
		glRotatef(90, 0, 1, 0);
		mi.ventana_solid_repeat(4.27+0.15, 6, 2.9, 0.075, metal.GLindex);
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
		glTranslatef(0,0.8,-1.5);
	glPopMatrix();
}
void tres(){
	glPushMatrix();
		glTranslatef(0.15 + 4.53 + .90 + 4.27 - 0.075 , 2.90 / 2, 1.90 + .15 + 2.95 + .075 + 10 + 0.075);
		
		glPushMatrix();
			glTranslatef(0, 0, 1.0875);
			mi.pared(0.15, 2.90, 2.175, 0, 4, 2, whitebrick.GLindex, whitewall.GLindex, whitewall.GLindex, whitewall.GLindex);
			glPushMatrix();
				glTranslatef(-.075-4-.075, 0, 0);
				mi.pared(0.15, 2.90, 2.175, 0, 4, 2, whitewall.GLindex, 0, 0, 0);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-.075-2, 2.90 / 2 + .15, 0.075 + 1.5);
			mi.techo(4.3, 0.30, 3.15, 5, 5, 1, greyroof.GLindex);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-.075-2, 0, 0.075 + 3 + 0.075/2);
			mi.pared(4.0, 2.90, 0.075, 0, 4, 2, whitewall.GLindex, 0, 0, 0);
		glPopMatrix();

	glPopMatrix();
}
void cuatro(){
	glPushMatrix();
		glTranslatef(0.15 + 4.53 + .90 + 4.27 - 0.075, 2.90 / 2, 1.90 + .15 + 2.95 + .075 + 10 + 0.075 + 0.075 + 3);

		glPushMatrix();
			glTranslatef(0,0, 0.3375);
			mi.pared(0.15, 2.90, 0.675, 0, 4, 2, whitebrick.GLindex, whitewall.GLindex, whitewall.GLindex, whitewall.GLindex);
			glPushMatrix();
				glTranslatef(-.075 - 4 - .075, 0, 0);
				mi.pared(0.15, 2.90, 0.675, 0, 4, 2, whitewall.GLindex, 0, 0, 0);
			glPopMatrix();
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(-.075 - 2, 2.90 / 2 + .15, 0.075 + 0.825);
			mi.techo(4.3, 0.30, 1.65, 5, 5, 1, greyroof.GLindex);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-2.075, 0, 0.075 + 1.5 + .075);
			mi.pared(4.3, 2.90, 0.15, 0, 4, 2, whitebrick.GLindex, whitewall.GLindex, whitewall.GLindex, whitewall.GLindex);
		glPopMatrix();
	glPopMatrix();
}
void cinco(){

	glPushMatrix();
	glTranslatef(0.15 + 4.53 + .90 + 4.27 - 0.075, 2.90 / 2, 1.90 + .15 + 2.95 + .075 + 10 + 0.075 + 0.075 + 3 + .075 + 1.5);
		glPushMatrix();
			glTranslatef(-.075-2, 2.90 / 2 + .15, .15 + 1.925);
			mi.techo(4.3, 0.30, 3.85, 5, 5, 1, greyroof.GLindex);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-.075 -3 - .15 - .5, 2.90 / 2 + .15, .15 + 3.7+.15 + 1.025);
			mi.techo(1.0, 0.30, 2.05, 5, 5, 1, greyroof.GLindex);
		glPopMatrix();
	glPopMatrix();

}
void seis(){
	glPushMatrix();
		glTranslatef(0.15 + 4.53 + .90 + 4.27 - 0.075, 2.90 / 2, 1.90 + .15 + 2.95 + .075 + 10 + 0.075 + 0.075 + 3 + .075 + 1.5 +.15 +3.7);
	
		glPushMatrix();
			glTranslatef(0, 0, 0.375);
			mi.pared(0.15, 2.90, .75, 0, 4, 2, whitebrick.GLindex, whitewall.GLindex, whitewall.GLindex, whitewall.GLindex);
			glPushMatrix();
				glTranslatef(-.075-3-.075, 0, 0);
				mi.pared(0.15, 2.90, .75, 0, 4, 2, whitewall.GLindex, 0, 0, 0);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-.075 - 1.5, 2.90 / 2 + .15, .15 + 1.025);
			mi.techo(3.3, 0.30, 2.05, 5, 5, 1, greyroof.GLindex);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-.075-1.5, 0, .075);
			mi.pared(3, 2.90, 0.15, 0, 4, 2, whitewall.GLindex, 0, 0, 0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-.075-1.5, 0, .15+1.9+.075);
			mi.pared(3.3, 2.90, 0.15, 0, 4, 2, whitebrick.GLindex, whitewall.GLindex, whitewall.GLindex, whitewall.GLindex);
		glPopMatrix();
	glPopMatrix();
}
void siete() {
	glPushMatrix();
		glTranslatef(0.15 + 4.53 + .90 + 4.27 - 0.075, 2.90 / 2, 1.90 + .15 + 2.95 + .075 + 10 + 0.075 + 0.075 + 3 + .075 + 1.5 + .15 + 3.7 + .15 + 1.9);
		glPushMatrix();
			glTranslatef(-.075 - 2, 2.90 / 2 + .15, .15 + 0.875);
			mi.techo(4.3, 0.30, 1.775, 5, 5, 1, greyroof.GLindex);
		glPopMatrix();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(7.64, -0.0375, 15.225 + ((24.78) / 4) - 0.0750 + 0.04);	//Piso 5,6,7
		mi.techo(4.27 + .15, 0.075, 12.3 + 0.170, 3, 3, 2, piso.GLindex);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(7.64, 2.90 / 2, 15.225 + 0.105 + 6.36 + ((5.75 / 2) + 0.05) * 2);
		mi.pared(4.27 + .15, 2.90, 0.15, 3, 3, 2, whitebrick.GLindex, whitewall.GLindex, whitebrick.GLindex, whitewall.GLindex);
	glPopMatrix();
}
void ocho() {

	glPushMatrix();
	glTranslatef(4.53 + 0.45, -0.0375, 15.225 + (5.75 / 2) + 0.05);
	mi.techo(0.9, 0.075, 6, 3, 3, 2, piso.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.53 + 0.45, -0.0375, 15.225 + (5.75 / 2) + 0.05 + 6 + 0.25);
	mi.techo(0.9, 0.075, 6.5, 3, 3, 2, grass.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.53 + 0.45, 2.90 / 2, 15.225 + 0.105 + ((5.75 / 2) + 0.05) * 2);
	mi.pared(0.9, 2.90, 0.075, 3, 3, 2, whitewall.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.53 + 0.45, 2.90 / 2, 15.225 + 0.105 + 6.36 + ((5.75 / 2) + 0.05) * 2);
	mi.pared(0.9, 2.90, 0.15, 3, 3, 2, whitewall.GLindex, whitebrick.GLindex, whitebrick.GLindex);
	glPopMatrix();
}

//void pared(float largo, float altura, float profundidad, float frontback (hacia la casa), float rightleft, float vertical, GLuint right, GLuint left=0, GLuint front=0, GLuint back=0);//Funcíon creacion prisma
//void techo(float largo, float altura, float profundidad, GLuint text);//Funcion creacion prisma

void nuevediez() {
	glPushMatrix();
			glTranslatef(0, 0, 0.37);
			glPushMatrix();
				glTranslatef(0.075, 2.90 / 2, 1.90 + 2.95 + (9.93 / 2) - 0.075);
				mi.pared(0.15, 2.90, 9.93 + 0.15, 0, 4, 2, whitewall.GLindex, whitebrick.GLindex, 0, 0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(3.63/2, 2.90 / 2, 1.90 + 2.95 + 9.93-0.075);
				mi.pared(3.63, 2.90, 0.15, 0, 4, 2, whitewall.GLindex, whitebrick.GLindex, 0, 0);
		

		
				glTranslatef(1.815+.45-0.025,1+0.225,0);
				mi.pared(.90, .45, 0.15, 0, 4, 2, whitewall.GLindex, whitebrick.GLindex, 0, 0);
		
		
				glTranslatef(0.45-0.075,-1.225, 0);
				mi.pared(0.15+.05, 2.90, 0.15, 0, 4, 2, whitewall.GLindex, whitebrick.GLindex, 0, 0);

			glPopMatrix();
		


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
			glTranslatef(1,0, 6.5);
			glPushMatrix();
				glScalef(1.2, 1, 1);
				mi.table(wood2.GLindex,wood2.GLindex);
			glPopMatrix();
			glTranslatef(0.625,0+up_sillas,-0.6 - tras_sillas);
			glRotatef(-90, 0, 1, 0);
			glRotatef(rot_sillas , 0, 0, 1);
			mi.chair(wood2.GLindex, leather.GLindex);
			glTranslatef(0, 0, -0.5);
			mi.chair(wood2.GLindex, leather.GLindex);
			glTranslatef(0, 0, -0.5);
			mi.chair(wood2.GLindex, leather.GLindex);
			glTranslatef(0, 0, -0.5);
			mi.chair(wood2.GLindex, leather.GLindex);
			glTranslatef(1.2 + 2*tras_sillas, 0, 0.4);
			glRotatef(-180, 0, 1, 0);
			glRotatef(2*rot_sillas, 0, 0, 1);
			mi.chair(wood2.GLindex, leather.GLindex);
			glTranslatef(0, 0, -0.5);
			mi.chair(wood2.GLindex, leather.GLindex);
			glTranslatef(0, 0, -0.5);
			mi.chair(wood2.GLindex, leather.GLindex);
			glTranslatef(0, 0, -0.5);
			mi.chair(wood2.GLindex, leather.GLindex);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(3,0,8.5);
			glRotatef(-90, 0, 1, 0);
			mi.sofa(sofa.GLindex,sofa.GLindex, puff.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(2.3, 0.001, 10);
			mi.techo(1.5, 0, 1.5, 3, 4, 1, carpet.GLindex);
			glTranslatef(0, 0.001, 0);
			mi.techo(1.1, 0, 0.5, 3, 4, 1, leather.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(3.6, 0, 10.25);
			glRotatef(-180, 0, 1, 0);
			glScalef(0.8, 1, 0.333);
			mi.sofa(sofa.GLindex, sofa.GLindex, 0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(5.415,1.45,6.715);
			mi.ventana_solid_repeat(4, 4, 2.9, 0.0375, metal.GLindex);
			glTranslatef(-0.04, 0, 1.5);
			glPushMatrix();
				glTranslatef(0,0,door);
				mi.ventana_solid_repeat(1, 1, 2.9, 0.0375, metal.GLindex);
			glPopMatrix();
			glTranslatef(0.0378,0,4.5325);
			mi.ventana_solid_repeat(4.065, 5, 2.9, 0.0375, metal.GLindex);
			glTranslatef(-0.04, 0, -1.53225);
			glPushMatrix();
				glTranslatef(0, 0, -door);
				mi.ventana_solid_repeat(1, 1, 2.9, 0.0375, metal.GLindex);
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.15, 1.5, 10);
			glDisable(GL_LIGHTING);
			glColor3f(0.7, 0.7, 0.7);
			mi.tv(metal.GLindex, currenttv, distortion);
			glColor3f(defaultcolor, defaultcolor, defaultcolor);
			glEnable(GL_LIGHTING);
		glPopMatrix();
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
	glPushMatrix();
	glTranslatef(2, -0.1, 3);
		mi.arbol(8,2,tree2.GLindex);
	glPopMatrix();
	glPushMatrix(); //aqui empieza una ventana
		glTranslatef(2.34 + 0.075, 1.45, 5 + 0.075); //se posicionan en el centro, como cualquier figura
		glRotatef(90, 0, 1, 0); //rote los ejes, las repeticiones estan sobre z
		mi.ventana_solid_repeat(4.53,5,2.9,0.075,metal.GLindex); // longitud del cuarto, # de ventanas, altura, profundidad, textura del marco
	glPopMatrix();
	glPushMatrix();
		glTranslatef(4.53 + 0.15+0.0375, 1.45, 2.5 + 0.075-0.01875);
		mi.ventana_solid_repeat(5.15-0.0375, 6, 2.9, 0.075, metal.GLindex);
	glPopMatrix();
}
void catorce() {

	glPushMatrix();
	glTranslatef(4.53 / 2, -0.0375, 15.225 + ((24.78) / 4) - 0.0750);
	mi.techo(4.53, 0.075, ((24.78 + 0.3) / 2), 3, 3, 2, grass.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.075, 1.45, 15.225 + 1.675);
	mi.pared(0.15, 2.9, 3.5, 1, 4, 2, whitebrick.GLindex, whitebrick.GLindex, whitebrick.GLindex, whitebrick.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.53 / 2, 2.90 + .15, 15.225 + 1.16);
	mi.techo(4.53, 0.30, 2.5, 5, 5, 1, greyroof.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.075, 2.90 + .15, 15.225 + 2.91);
	mi.techo(0.15, 0.30, 1.025, 5, 5, 1, greyroof.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.455, 1.45, 15.225 + ((24.78) / 4) - 0.038);
	mi.pared(0.15, 2.9, ((24.78 + 0.3) / 2) - 0.075, 0.1, 4, 2, whitewall.GLindex, whitebrick.GLindex, whitebrick.GLindex, 0);
	glPopMatrix();
}
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
void uno_ventanas(){
	glPushMatrix();
		glTranslatef(9.85 - 0.0375, 1.45, 2.125 + 1.475 - .075 + 0.009375);
		mi.ventana_blend_repeat(2.95 + .15, 4, 2.9, 0.075, window.GLindex);
		glTranslatef(-2.135 - 0.0375, 0, 1.475 + 0.0375);
		glRotatef(90, 0, 1, 0);
		mi.ventana_blend_repeat(4.27 + 0.15, 6, 2.9, 0.075, window.GLindex);
	glPopMatrix();

	glPushMatrix();
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);     // Turn Blending On
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glPushMatrix();//llave cocina
		glTranslatef(5.43 + 0.57 + .075 + .0375 + .9, 0.475+1-.35, 0.80 - .075 + .025+ .1 - .0125 + .002 + .002+ .1 - .0125 + .002 + .002);
		mi.agua(.02,.6 , .02,0.5,0.1,x,1,water.GLindex);
		glPopMatrix();
		glDisable(GL_BLEND);        // Turn Blending Off
		glEnable(GL_LIGHTING);
	glPopMatrix();
}
void dos_ventanas(){}
void tres_ventanas(){}
void cuatro_ventanas(){}
void cinco_ventanas(){}
void seis_ventanas(){}
void siete_ventanas(){}
void ocho_ventanas(){}
void nuevediez_ventanas(){
	glPushMatrix();
		glTranslatef(0, 0, 0.37);
		glTranslatef(5.415, 1.45, 6.715);
		mi.ventana_blend_repeat(4, 4, 2.9, 0.0375, window.GLindex);
		glTranslatef(-0.04, 0, 1.5);
		glPushMatrix();
		glTranslatef(0, 0, door);
		mi.ventana_blend_repeat(1, 1, 2.9, 0.0375, window.GLindex);
		glPopMatrix();
		glTranslatef(0.04, 0, 4.5325);
		mi.ventana_blend_repeat(4.065, 5, 2.9, 0.0375, window.GLindex);
		glTranslatef(-0.04, 0, -1.53225);
		glPushMatrix();
		glTranslatef(0, 0, -door);
		mi.ventana_blend_repeat(1, 1, 2.9, 0.0375, window.GLindex);
		glPopMatrix();
	glPopMatrix();
}
void once_ventanas(){
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);     // Turn Blending On
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glPushMatrix();//Alberca
			glTranslatef(11.85 + 4, -0.15-1+0.075, 7.5375 + 0.009375);
			mi.techomueve(4-0.15-.005, 2, 15.225-0.15-.01, 4-.005,movX, 15,0, 1, water.GLindex);
		glPopMatrix();
	glDisable(GL_BLEND);        // Turn Blending Off
	glEnable(GL_LIGHTING);
}
void doce_ventanas(){}
void trece_ventanas(){
	glPushMatrix();
		glTranslatef(2.34 + 0.075, 1.45, 5 + 0.075); //nos movemos al mismo punto CTLR-C +CLTR+V
		glRotatef(90, 0, 1, 0); //misma rotacion
		mi.ventana_blend_repeat(4.53, 5, 2.9, 0.075, window.GLindex); //Solo cambiamos el nombre de la funcion por blend y la textura
	glPopMatrix();
	glPushMatrix();
		glTranslatef(4.53 + 0.15 + 0.0375, 1.45, 2.5 + 0.075 - 0.01875);
		mi.ventana_blend_repeat(5.15 - 0.0375, 6, 2.9, 0.075, window.GLindex);
	glPopMatrix();
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
	
		glPushMatrix(); //Creamos cielo
			glDisable(GL_LIGHTING);
			glTranslatef(10,30-0.075-2,11);
			glColor3f(1, 1, 1);
			mi.skybox(40.0, 60.0, 40.0,currentsky,blue.GLindex);
			glColor3f(defaultcolor, defaultcolor, defaultcolor);
			glEnable(GL_LIGHTING);
		glPopMatrix();
		glColor3f(defaultcolor, defaultcolor, defaultcolor);
		if(ejes){
			glBegin(GL_LINES);
			glVertex3d(0, 0, 0);
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
		}
		
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
		if (valak) {
			glPushMatrix();
				float alejamiento = 1.0;
				float dx = objCamera.mView.x - objCamera.mPos.x;
				float dy = objCamera.mView.y - objCamera.mPos.y;
				float dz = objCamera.mView.z - objCamera.mPos.z;
				glTranslatef(objCamera.mPos.x + alejamiento*dx, objCamera.mPos.y + alejamiento*dy, objCamera.mPos.z + alejamiento*dz);
				float dz2 = dz > 0 ? dz : -dz;
				float dx2 = dx > 0 ? dx : -dx;
				if ((dx*dz) > 0) {
					dx *= -1;
				}
				else {
					dz = dz > 0 ? dz : -dz;
					dx = dx > 0 ? dx : -dx;
				}
				float angulo = atan(dz / dx) * 180 / 3.1415;
				glRotatef(angulo + 90, 0, 1, 0);
				glDisable(GL_LIGHTING);
				glEnable(GL_ALPHA_TEST);     // Turn Blending On
				glAlphaFunc(GL_GREATER, 0.1);
				glColor3d(1.0, 1.0, 1.0);
				mi.prisma(1, 1.5, 0, tv5.GLindex);
				glColor3f(defaultcolor, defaultcolor,defaultcolor);
				glDisable(GL_ALPHA_TEST);        // Turn Blending Off
				glEnable(GL_LIGHTING);
			glPopMatrix();
		}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
		glColor3f(1.0, 0.0, 0.0);
		pintaTexto(-12, 12.0, -14.0, (void *)font, "Proyecto Final");
		glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glutSwapBuffers ( );

}

void animacion()
{
	if (x > 3.1415*2) x = 0;
	x += 0.01;
	movX = cos((x-3.1415)*.5)+1;
	if (objCamera.mPos.x > 1 && objCamera.mPos.x<7 && objCamera.mPos.z>-4 && objCamera.mPos.z < 5) {
		x2 += x2>3.14?0 : 0.2;
	}
	else {
		x2 -= x2>0? 0.2 : 0;
	}
	//Animacion Keyframes
	if (play)
	{
		if(!hatemusic)music->setIsPaused();
		defaultcolor = 0.2;
		distortion = 0;
		currenttv = tv4.GLindex;
		if(playIndex==0 && i_curr_steps==1)engine->play2D("sounds/doll.flac");
		currentsky = black.GLindex;
		if (i_curr_steps >= i_max_steps) //end of animation between frames? si realiza los cuadros intermedios
		{
			playIndex++;
			if (playIndex>FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				currenttv = tv1.GLindex;
				currentsky = t_cielo.GLindex;
				if (!hatemusic)music->setIsPaused(false);
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			tras_sillas += KeyFrame[playIndex].tras_sillas_inc;
			up_sillas += KeyFrame[playIndex].up_sillas_inc;
			rot_sillas += KeyFrame[playIndex].rot_sillas_inc;
			door += KeyFrame[playIndex].door_inc;
			if (i_curr_steps > 30 && i_curr_steps < 46 && playIndex==2) {
				if (i_curr_steps>36) {
					currentsky = whitewall.GLindex;
					defaultcolor = 1.0;
					currenttv = black.GLindex;
					valak = true;
				}
				else {
					defaultcolor = 0.2;
					currenttv = tv4.GLindex;
					currentsky = black.GLindex;
				}
				if (i_curr_steps == 31) {
					engine->play2D("sounds/thunder.wav");
				}
			}
			else {
				valak = false;
				defaultcolor = 0.2;
			}
			i_curr_steps++;
		}

	}
	else {
		defaultcolor = COLOR_DEFAULT;
		if (x > 5) {
			distortion = 0;
			currenttv = tv1.GLindex;
		}
		else if (x > 4) {
			distortion += x;
			currenttv = tv3.GLindex;
		}
		else if (x > 2) {
			distortion = 0;
			currenttv = tv2.GLindex;
		}
		else if (x > 1)
		{
			distortion += x;
			currenttv = tv3.GLindex;
		}
	}
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
			objCamera.Position_Camera(1.51, 1.70, 12.70, 1.58, 1.70, 12.21, 0, 1, 0);
			break;
		case 'o':   //Movimientos de camara
		case 'O':
			g_lookupdown = 6;
			objCamera.Position_Camera(13.74, 1.70, 16.48, 13.83, 1.7, 15.99, 0, 1, 0);
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
		case 'l':
			if (play == false && (FrameIndex>1)){
				resetElements();
				interpolation();
				play = true;
				playIndex = 0;
				i_curr_steps = 0;
			}
			else
				play = false;
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
