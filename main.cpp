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
#include "Camera.h"
#include "cmodel/CModel.h"

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
GLfloat m_amb1[] = {0.2, 0.2, 0.2, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = {18};

CTexture t_cielo,whitebrick,whitewall,greyroof,piso;
CFiguras mi;


			
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
    
	t_cielo.LoadBMP("textures/sky.bmp");
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


	objCamera.Position_Camera(0,1.70,0, 0.5,1.70,0, 0, 1, 0);

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

void uno() {
	glPushMatrix();
		glTranslatef(0.15+4.53+0.9+1.69+0.6+1.11+0.26,1.45+.04,0);
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
		mi.pared(1.69, 2.9, 0.075, 0.1, 0.2, 2, whitebrick.GLindex, whitewall.GLindex, whitewall.GLindex, whitebrick.GLindex);
		glTranslatef(0.0375+0.01, 0, 0.7225);
		mi.pared(1.69+0.075+0.02, 2.9, 0.075, 0.1, 0.2, 2, whitebrick.GLindex, whitewall.GLindex, whitewall.GLindex, whitewall.GLindex);
		glTranslatef(-0.8925+0.0375, 0, -0.0375-0.0375);
		mi.pared(0.075, 2.9, 0.075, 0.2, 0.1, 2, whitewall.GLindex);
		glTranslatef(0,0,0);
	glPopMatrix();
}
void dos() {
	glPushMatrix();
		glTranslatef(0.15+4.53+2.825, 1.45,-6.0-.16);
			mi.pared(5.65, 2.9,0.15, 4, 0.1, 2, whitebrick.GLindex);//pared exterior
		glTranslatef(0,1.45+0.15,3);
			mi.techo(5.65, 0.30, 6.15, greyroof.GLindex);//techo
		glTranslatef(0, -3.2+0.15,0);
			mi.techo(5.65, 0.075, 6.15, piso.GLindex);
	glPopMatrix();
}
void tres(){}
void cuatro(){}
void cinco(){}
void seis(){}
void siete(){}
void ocho(){}
void nuevediez(){}
void once(){}
void doce(){}
void trece(){}
void catorce(){}
void quince(){}
void uno_ventanas(){}
void dos_ventanas(){}
void tres_ventanas(){}
void cuatro_ventanas(){}
void cinco_ventanas(){}
void seis_ventanas(){}
void siete_ventanas(){}
void ocho_ventanas(){}
void nuevediez_ventanas(){}
void once_ventanas(){}
void doce_ventanas(){}
void trece_ventanas(){}
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
				glTranslatef(0,60,0);
				mi.skybox(130.0, 130.0, 130.0,t_cielo.GLindex);
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

		case ' ':		//Poner algo en movimiento
					//Activamos/desactivamos la animacíon
			break;

		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
			break;        
		default:        // Cualquier otra
			break;
  }

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
