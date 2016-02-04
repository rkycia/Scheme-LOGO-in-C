/* Simple backend for a Logo like tortoise drawer.  */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <GL/glut.h>


#include <libguile.h>

#include <pthread.h>

#define true 1
#define false 0

struct COMMAND
{
	int CMD;
	double * value;
};


void *runScheme( void *ptr );

void *print_message_function( void *ptr );

static int bexit = 0;

static double rotx = 0;
static double roty = 0;
static double rotz = 0;


static double add = 0;
static double aa = 0;

//ZMIENNE RYSOWANIA

static int bb = 0;
double newX, newY;
double length;
static double rrcolor= 1.0;
static double bbcolor=0.0;
static double ggcolor=0.0;
static double rwidth = 5;


static double x = 0;
static double y = 0;
static double direction ;
static int mpendown =1;

double vpx1, vpy1, vpx2, vpy2, vkx1, vkx2, vky1, vky2; 


//TESTOWANIE WARTOŚCI

static double testrcolor;
static double testbcolor;
static double testgcolor;

enum wartosc {CLEAR, MOVE, TURN, POLYGON, HUDGE_LINE, SMALL_LINE, V_POLYGON, TEAPOT};

enum wartosc call;

//FUNKCJE SCM

void idle()
{
	if( bexit == true )
	{
		exit(0);
	}	
	glutPostRedisplay();
}

static SCM exit_mode()
{
	bexit = true;	

	return SCM_UNSPECIFIED;
}



static SCM cclear()
{
	call = CLEAR;	

	return SCM_UNSPECIFIED;
}


static SCM mmove(SCM length1)
{
	
	length = scm_to_double (length1);
	newX =  x + length * cos (direction);
	newY =  y + length * sin (direction);
	call = MOVE;
	return SCM_UNSPECIFIED;
}

static SCM turn (SCM degrees)
{
  const double value = scm_to_double (degrees);
  direction += M_PI / 180.0 * value;
  return scm_from_double (direction * 180.0 / M_PI);
}

static SCM pendown ()
{
  SCM result = scm_from_bool (mpendown);
  mpendown = 1;
  return result;
}

static SCM penup ()
{
  SCM result = scm_from_bool (mpendown);
  mpendown = 0;
  return result;
}

static SCM ccolor(SCM rcolor, SCM gcolor, SCM bcolor)
{
	SCM result;
	testrcolor = scm_to_double (rcolor);	
	testbcolor = scm_to_double (bcolor);
	testgcolor = scm_to_double (gcolor);

	if (testrcolor <= 1 && testrcolor >= 0 && testgcolor <=1 && testgcolor >= 0 && testbcolor<=1 && testbcolor >= 0)
{
	SCM result = scm_from_bool (1);
	rrcolor = scm_to_double (rcolor);	
	bbcolor = scm_to_double (bcolor);
	ggcolor = scm_to_double (gcolor);
return scm_from_bool(1);	
}
else {
return scm_from_bool(0);
}	
}

static SCM wwidth( SCM width)
{

	rwidth = scm_to_double (width);	

	return SCM_UNSPECIFIED;
}

static SCM xy ()
{
  
  return scm_list_2 (scm_from_double (x), scm_from_double (y));
}


static SCM poly()
{

	call = POLYGON;	

	return SCM_UNSPECIFIED;
}

static SCM h_line()
{
	call = HUDGE_LINE;	

	return SCM_UNSPECIFIED;
}

static SCM s_line()
{
	call = SMALL_LINE;	

	return SCM_UNSPECIFIED;
}

static SCM v_poly(SCM vpx11, SCM vpy11, SCM vpx22, SCM vpy22, SCM vkx11, SCM vkx22, SCM vky11, SCM vky22 )
{
	vpx1 = scm_to_double (vpx11);
	vpx2 = scm_to_double (vpx22);
	vpy1 = scm_to_double (vpy11);
	vpy2 = scm_to_double (vpy22);
	vkx1 = scm_to_double (vkx11);
	vkx2 = scm_to_double (vkx22);
	vky1 = scm_to_double (vky11);
	vky2 = scm_to_double (vky22);
		

	call = V_POLYGON;	

	return SCM_UNSPECIFIED;
}

static SCM teapot()
{
	call = TEAPOT;	

	return SCM_UNSPECIFIED;
}

static SCM resetxy ()
{
  x = 0;
  y= 0;
  return scm_list_2 (scm_from_double (x), scm_from_double (y));
}


// MY DISPLAY
void mydisplay(){


if (call == MOVE)//RYSOWANIE LINII (X, Y)
{
if (newX <= 1 && newY <=1 && newX >= -1 && newY >= -1)
{
if (mpendown)
{
glLineWidth(rwidth);
glColor3f(rrcolor, ggcolor, bbcolor);
glBegin(GL_LINES);
glVertex3f(x, y, 0.0);
glVertex3f(newX, newY, 0);
glEnd();
}
	x = newX;
	y = newY;
}

}


if (call == CLEAR) //CLEAR
{
glClearColor(1, 1, 1, 1 );
glClear( GL_COLOR_BUFFER_BIT );
x = y = 0.0;
direction = 0.0;
mpendown = 1;
}


if (call == POLYGON)

{
		glBegin(GL_POLYGON);
		glColor3f(rrcolor, ggcolor, bbcolor);        
		glVertex2f(-0.25, -0.25);        
		glVertex2f(-0.25, 0.25);        
		glVertex2f(0.25, 0.25);        
		glVertex2f(0.25, -0.25);    
		glEnd();


}


if (call == HUDGE_LINE)
{
	glLineWidth(20);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.5, 0.5, 0);
	glEnd();
}

if (call == SMALL_LINE)
{
	glLineWidth(4);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(-0.5, -0.5, 0);
	glEnd();
}

if (call == V_POLYGON)

{
glBegin(GL_POLYGON);
		glColor3f(rrcolor, ggcolor, bbcolor);        
		glVertex2f(vpx1, vpy1);        
		glVertex2f(vpx2, vpy2);        
		glVertex2f(vkx1, vky1);        
		glVertex2f(vkx2, vky2);    
		glEnd();
}


if (call == TEAPOT)

{
	glLineWidth(rwidth);
	glColor3f(rrcolor, ggcolor, bbcolor);
	glutWireTeapot( 0.5 );	
}




glFlush(); 
}

static void*
register_functions (void* data)
{
	scm_c_define_gsubr ("exit_mode", 0, 0, 0, &exit_mode);
	

	scm_c_define_gsubr ("move", 1, 0, 0, &mmove);
	scm_c_define_gsubr ("clear", 0, 0, 0, &cclear);
	scm_c_define_gsubr ("turn", 1, 0, 0, &turn);
	scm_c_define_gsubr ("penup", 0, 0, 0, &penup);
	scm_c_define_gsubr ("pendown", 0, 0, 0, &pendown);
	scm_c_define_gsubr ("recolor", 3, 0, 0, &ccolor);
	scm_c_define_gsubr ("rewidth", 1, 0, 0, &wwidth);
	scm_c_define_gsubr ("xy", 0, 0, 0, &xy);
	scm_c_define_gsubr ("v_poly", 8, 0, 0, &v_poly);

	scm_c_define_gsubr ("poly", 0, 0, 0, &poly);
	scm_c_define_gsubr ("hudge_line", 0, 0, 0, &h_line);
	scm_c_define_gsubr ("small_line", 0, 0, 0, &s_line);
	scm_c_define_gsubr ("teapot", 0, 0, 0, &teapot);
	scm_c_define_gsubr ("resetxy", 0, 0, 0, &resetxy);
	return NULL;
}

int
main (int argc, char* argv[])
{
	
	pthread_t thread1, thread2;
    const char *message1 = "Thread 1";
    const char *message2 = "Thread 2";
    int  iret1, iret2;
	

     iret1 = pthread_create( &thread1, NULL, runScheme, (void*) message1);





     if(iret1)
     {
         fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
         exit(EXIT_FAILURE);
     }

	glutInit( &argc, argv ); 

	glutInitWindowSize(500, 500);


	glutCreateWindow("Rysowanie");     
	glutDisplayFunc(mydisplay); 
	glutIdleFunc(idle);  //update when no user activity - IMPORTANT 
	glutMainLoop();		





 


  return EXIT_SUCCESS;
}



void *runScheme( void *ptr )
{
	char *message;
	message = (char *) ptr;
	printf("%s \n", message);

	scm_with_guile (&register_functions, NULL);
	scm_shell (0, NULL);
}
