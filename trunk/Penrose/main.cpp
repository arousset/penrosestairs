/* Penrose Stairs								*/
/*                                              */
/* Autors:	Rousset Alban                       */
/*			Kawczak Clément						*/
/*								                */
/* Informatique graphique                       */

#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

/* Variables et constantes globales             */
/* pour les angles et les couleurs utilises     */

static float rx = 0.0F;
static float ry = 0.0F;
static float rz = 0.0F;
static const float blanc[]       = { 1.0F,1.0F,1.0F,1.0F };
static const float jaune[]       = { 1.0F,1.0F,0.0F,1.0F };
static const float cyan[]        = { 0.0F,1.0F,1.0F,1.0F };
static const float magenta[]     = { 1.0F,0.0F,1.0F,1.0F };
static const float rouge[]       = { 1.0F,0.0F,0.0F,1.0F };
static const float vert[]        = { 0.0F,1.0F,0.0F,1.0F };
static const float bleu[]        = { 0.0F,0.0F,1.0F,1.0F };
static const float noir[]        = { 0.0F,0.0F,0.0F,1.0F };
static const float grisMoyen[]   = { 0.5F,0.5F,0.5F,1.0F };
static const float jauneMoyen[]  = { 0.5F,0.5F,0.0F,1.0F };
static const float defaultDiff[] = { 0.8F,0.8F,0.8F,1.0F };
static const float defaultSpec[] = { 0.0F,0.0F,0.0F,1.0F };
static const float defaultAmbi[] = { 0.2F,0.2F,0.2F,1.0F };

static int scn = 0;
static int n = 18;
static int aff = 1;

static float posx = -1.0;
static float posy = 0.8;
static float posz = 0.0;

float angle = 0.0;

/* Fonction d'initialisation des parametres     */
/* OpenGL ne changeant pas au cours de la vie   */
/* du programme                                 */

void init(void) {
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_AUTO_NORMAL);
}

/* Scene dessinee                               */

void face(int x)
{
	int y = 2;
	for(int i = 0;i < x;i++)
	{
		glPushMatrix();
		for(int j = 0;j < 1;j++)
		{
			glutSolidCube(1.0);
			glTranslatef(0.0, 1.0, 0.0);
		}
		glPopMatrix();
		glTranslatef(1.0, 0.2, 0.0);
	}
}

void scene(void) {
	/*glPushMatrix();
	glutSolidTorus(1.0,9.0F,n,n*8);
	glRotatef(90.0F,1.0F,0.0F,0.0F);
	glutSolidTorus(1.0,9.0F,n,n*8);
	glRotatef(90.0F,0.0F,1.0F,0.0F);
	glutSolidTorus(1.0,9.0F,n,n*8);
	glPopMatrix();*/
	glPushMatrix();
	face(3);
	glRotatef(90, 0.0, 1.0, 0.0);
	face(6);
	glRotatef(90, 0.0, 1.0, 0.0);
	face(6);
	glRotatef(90, 0.0, 1.0, 0.0);
	face(3);

	glTranslatef(posx, posy, posz);
	glRotatef(90, 0.0, 1.0, 0.0);
	
	glutSolidSphere(0.5,36,36);

	glPopMatrix();
}

void configurationLumieresEtMateriaux(void) {
	glEnable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	switch (scn) {
	case 0 :
	case 1 :
	case 2 :
		glMaterialfv(GL_FRONT,GL_AMBIENT,noir);
		glMaterialfv(GL_FRONT,GL_SPECULAR,noir);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,defaultDiff);
		break;
	case 3 :
		glMaterialfv(GL_FRONT,GL_AMBIENT,noir);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,defaultDiff);
		glMaterialfv(GL_FRONT,GL_SPECULAR,blanc);
		{ const GLfloat shininess[] = { 64.0 };
		glMaterialfv(GL_FRONT,GL_SHININESS,shininess); }
		break;
	case 4 :
		glMaterialfv(GL_FRONT,GL_AMBIENT,defaultAmbi);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,noir);
		glMaterialfv(GL_FRONT,GL_SPECULAR,noir);
		break; }
	const GLfloat light0_position[] = {   0.0, 0.0, 0.0, 1.0 };
	const GLfloat light1_position[] = {   1.0, 0.0, 0.0, 0.0 };
	const GLfloat light2_position[] = { -20.0,20.0,20.0, 1.0 };
	const GLfloat light2_dir[] = { 1.0,-1.0,-1.0 };
	switch (scn) {
	case 0 :
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,jaune);
		glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
		break;
	case 1 :
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,jaune);
		glLightfv(GL_LIGHT1,GL_DIFFUSE,cyan);
		glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
		glLightfv(GL_LIGHT1,GL_POSITION,light1_position);
		break;
	case 2 :
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,jaune);
		glLightfv(GL_LIGHT1,GL_DIFFUSE,cyan);
		glLightfv(GL_LIGHT2,GL_DIFFUSE,magenta);
		glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
		glLightfv(GL_LIGHT1,GL_POSITION,light1_position);
		glLightfv(GL_LIGHT2,GL_POSITION,light2_position);
		glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION,light2_dir);
		glLightf(GL_LIGHT2,GL_SPOT_CUTOFF,10.0F);
		break;
	case 3 :
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,jaune);
		glLightfv(GL_LIGHT1,GL_DIFFUSE,cyan);
		glLightfv(GL_LIGHT2,GL_DIFFUSE,magenta);
		glLightfv(GL_LIGHT0,GL_SPECULAR,blanc);
		glLightfv(GL_LIGHT1,GL_SPECULAR,blanc);
		glLightfv(GL_LIGHT2,GL_SPECULAR,blanc);
		glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
		glLightfv(GL_LIGHT1,GL_POSITION,light1_position);
		glLightfv(GL_LIGHT2,GL_POSITION,light2_position);
		glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION,light2_dir);
		glLightf(GL_LIGHT2,GL_SPOT_CUTOFF,10.0F);
		break;
	case 4 :
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,noir);
		glLightfv(GL_LIGHT0,GL_SPECULAR,noir);
		glLightfv(GL_LIGHT0,GL_AMBIENT,jauneMoyen);
		break; }
}

/* Fonction executee lors d'un changement       */
/* de la taille de la fenetre OpenGL            */

void reshape(int w,int h) {
	glViewport(0,0,w,h); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(8.0F,(float) w/h,80.0,120.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,0.0,100.0,0.0,0.0,0.0,0.0,1.0,0.0);
}

/* Fonction executee lors d'un rafraichissement */
/* de la fenetre de dessin                      */

void display(void) {
	glClearColor(0.5F,0.5F,0.5F,1.0F);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	configurationLumieresEtMateriaux();
	glPolygonMode(GL_FRONT_AND_BACK,(aff) ? GL_FILL : GL_LINE);
	glPushMatrix();
	glRotatef(rx,1.0F,0.0F,0.0F);
	glRotatef(ry,0.0F,1.0F,0.0F);
	glRotatef(rz,0.0F,0.0F,1.0F);
	scene();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

/* Fonction executee lorsqu'aucun evenement     */
/* n'est en file d'attente                      */

float speed = 0.01;
float tmp = 0.0;
float tmp2 = 0.0;
int cptface = 0;

void idle(void) {
	if(cptface == 0)
		posx -= speed;
	if(cptface == 1)
		posz -= speed;
	if(cptface == 2)
		posx += speed;
	if(cptface == 3)
		posz += speed;
	//posx -= speed;
	tmp -= speed;
	tmp2 -= speed;
	if(tmp <= -1)
	{
		tmp = 0.0;
		posy -= 0.2;
	}
	if(cptface == 0 && tmp2 <= -2.0)
	{
		angle = 90;
		tmp2 = 0.0;
		cptface++;
	}
	if(cptface == 1 && tmp2 <= -6.0)
	{
		angle = 180;
		tmp2 = 0.0;
		cptface++;
	}
	if(cptface == 2 && tmp2 <= -6.0)
	{
		angle = 270;
		tmp2 = 0.0;
		cptface++;
	}
	if(cptface == 3 && tmp2 <= -2.0)
	{
		tmp2 = 0.0;
		tmp2 = 0;
		cptface = 0;
		posx = -1.0;
		posy = 0.8;
		posz = 0.0;
	}

	glutPostRedisplay();
}

/* Fonction executee lors de la frappe          */
/* d'une touche special du clavier:             */
/* - touches de curseur                         */
/* - touches de fonction                        */
/* - ...                                        */

void special(int code,int x,int y) {
	switch ( code ) {
	case GLUT_KEY_UP :
		rx += 1.0F;
		glutPostRedisplay(); 
		break;
	case GLUT_KEY_DOWN :
		rx -= 1.0F;
		glutPostRedisplay(); 
		break;
	case GLUT_KEY_RIGHT :
		ry += 1.0F;
		glutPostRedisplay(); 
		break;
	case GLUT_KEY_LEFT :
		ry -= 1.0F;
		glutPostRedisplay(); 
		break;
	case GLUT_KEY_PAGE_UP :
		rz += 1.0F;
		glutPostRedisplay(); 
		break;
	case GLUT_KEY_PAGE_DOWN :
		rz -= 1.0F;
		glutPostRedisplay(); 
		break; }
}

/* Fonction executee lors de l'appui            */
/* d'une touche alphanumerique du clavier       */

void keyboard(unsigned char key,int x,int y) {
	switch (key) {
	case 'r' :
		rx = 35.0F;
		ry = 10.0F;
		rz = 40.0F;
		glutPostRedisplay();
		break;
	case 43 :
		n++;
		glutPostRedisplay();
		break;
	case 45 :
		n--;
		if ( n == 2 )
			n = 3;
		glutPostRedisplay();
		break;
	case 0x20 :
		scn = (scn+1)%5;
		glutPostRedisplay();
		break;
	case 'm' :
		aff = !aff;
		glutPostRedisplay();
		break;
	case 0x0D :
		{ static int anim = 0;
		anim = !anim;
		glutIdleFunc(( anim ) ? idle : NULL); }
		break;
	case 0x1B :
		exit(0);
		break; }
}

void mousemove(int x, int y)
{
	rx = y/2;
	ry = x/2;
	glutPostRedisplay(); 
}

/* Fonction principale                          */

int main(int argc,char **argv) {
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(900,750); 
	glutInitWindowPosition(50,50); 
	glutCreateWindow("Lumieres et matériaux"); 
	init();
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMotionFunc(mousemove);
	glutIdleFunc(idle);
	glutMainLoop();
	return(0);
}