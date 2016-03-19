/* Guohua Jiang */
/*
    q - Quit the program
    c - Clear the screen
*/
#include "C:\Program Files (x86)\CodeBlocks\MinGW\include\GL\glut.h"
#include <C:\Program Files (x86)\CodeBlocks\MinGW\include\GL\gl.h>
#include <C:\Program Files (x86)\CodeBlocks\MinGW\include\GL\glext.h>
#include <C:\Program Files (x86)\CodeBlocks\MinGW\include\GL\glu.h>

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#define MAX_SHAPE 20   /* fixed maximum number of bezier curve */

static int width = GetSystemMetrics(SM_CXSCREEN), height = GetSystemMetrics(SM_CYSCREEN);   /* window width and height */

int option = 0;

// bezier curve
struct bezierCurve{
    int colorSeleted = 0;
    GLfloat cpts[4][3];
    float color[3];
};

struct bezierCurve BC[MAX_SHAPE];
int ncpts = 0;

static int numberOfBezierCurve = 0;

// rectangle
struct rectangle{
    int colorSeleted = 0;
    int isFilled = 0;
    GLfloat cpts[2][3];
    float color[3];
};

struct rectangle RE[MAX_SHAPE];
int ncpts_r = 0;
static int numberOfRectangle = 0;

// line
struct line{
    int colorSeleted = 0;
    GLfloat cpts[2][3];
    float color[3];
};
struct line L[MAX_SHAPE];
int ncpts_l = 0;
static int numberOfLine = 0;

// ellipse
struct ellipse{
    int colorSeleted = 0;
    int isFilled = 0;
    GLfloat cpts [2][3];
    float color[3];
};

struct ellipse EL[MAX_SHAPE];
int ncpts_e = 0;
static int numberOfEllipse = 0;

// menu
static int window;
static int menu_id;
static int submenu1, submenu2, submenu3, submenu4, submenu5, submenu6, submenu7, submenu8;
static int value = 0;

void keyboard(unsigned char key, int x, int y);
void menu(int num);
void drawCurves();
void createMenu(void);
void display(void);
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void reshape(int w, int h);

void menu(int num){
  if(num == 0){
    glutDestroyWindow(window);
    exit(0);
  }else{
    value = num;
  }
  glutPostRedisplay();
}

void drawCurves()
{
    int i;
    for(i=0; i<numberOfBezierCurve; i++)
    {
        /* draw the curve using OpenGL evaluators */
        glColor3f(BC[i].color[0], BC[i].color[1], BC[i].color[2]);
        glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, BC[i].cpts[0]);
        glMapGrid1f(30, 0.0, 1.0);
        glEvalMesh1(GL_LINE, 0, 30);
    }
    glFlush();
}

void drawRectangle()
{
    int i;

    for(i=0; i<numberOfRectangle; i++)
    {
        /* draw the curve using OpenGL evaluators */
        glColor3f(RE[i].color[0], RE[i].color[1], RE[i].color[2]);
        if(RE[i].isFilled == 0){
            glBegin(GL_LINE_LOOP);
        }else{
            glBegin(GL_QUADS);
        }
        glVertex3f( RE[i].cpts[0][0], RE[i].cpts[0][1], 0.0 );
        glVertex3f( RE[i].cpts[1][0], RE[i].cpts[0][1], 0.0 );
        glVertex3f( RE[i].cpts[1][0], RE[i].cpts[1][1], 0.0 );
        glVertex3f( RE[i].cpts[0][0], RE[i].cpts[1][1], 0.0 );
        glEnd();
        glFlush();
    }

}

void drawLine()
{
    int i;

    for(i=0; i<numberOfLine; i++)
    {
        /* draw the curve using OpenGL evaluators */
        glColor3f(L[i].color[0], L[i].color[1], L[i].color[2]);

        glBegin(GL_LINES);

        glVertex3f( L[i].cpts[0][0], L[i].cpts[0][1], 0.0 );

        glVertex3f( L[i].cpts[1][0], L[i].cpts[1][1], 0.0 );
        glEnd();
        glFlush();
    }

}

void drawEllipse(){
    int i;
    float theta, major_axis, minor_axis ;
    float center_x, center_y;
    for(i = 0; i< numberOfEllipse; i++){
        glColor3f(EL[i].color[0], EL[i].color[1], EL[i].color[2]);
        major_axis = fabs(EL[i].cpts[1][0] - EL[i].cpts[0][0]);
        minor_axis = fabs(EL[i].cpts[1][1] - EL[i].cpts[0][1]);
        center_x = (EL[i].cpts[1][0] + EL[i].cpts[0][0])/2;
        center_y = (EL[i].cpts[1][1] + EL[i].cpts[0][1])/2;

        if(EL[i].isFilled == 0){
            glBegin(GL_LINE_LOOP);;
        }else{
            glBegin(GL_POLYGON);
        }
        for(theta = 0; theta < 2 * M_PI; theta += M_PI /36){
            glVertex3f (center_x + cos(theta) * major_axis / 2, center_y + sin(theta) * minor_axis / 2, 0.0f);
        }
        glEnd();
        glFlush ();
    }
}

void createMenu(void){
    submenu1 = glutCreateMenu(menu);
    glutAddMenuEntry("red", 1);
    glutAddMenuEntry("green", 2);
    glutAddMenuEntry("blue", 3);
    glutAddMenuEntry("yellow", 4);
    glutAddMenuEntry("purple", 5);
    glutAddMenuEntry("orange", 6);
    glutAddMenuEntry("white", 7);
    glutAddMenuEntry("black", 8);

    submenu2 = glutCreateMenu(menu);
    glutAddMenuEntry("red", 9);
    glutAddMenuEntry("green", 10);
    glutAddMenuEntry("blue", 11);
    glutAddMenuEntry("yellow", 12);
    glutAddMenuEntry("purple", 13);
    glutAddMenuEntry("orange", 14);
    glutAddMenuEntry("white", 15);
    glutAddMenuEntry("black", 16);

    submenu3 = glutCreateMenu(menu);
    glutAddMenuEntry("red", 17);
    glutAddMenuEntry("green", 18);
    glutAddMenuEntry("blue", 19);
    glutAddMenuEntry("yellow", 20);
    glutAddMenuEntry("purple", 21);
    glutAddMenuEntry("orange", 22);
    glutAddMenuEntry("white", 23);
    glutAddMenuEntry("black", 24);

    submenu4 = glutCreateMenu(menu);
    glutAddMenuEntry("red", 25);
    glutAddMenuEntry("green", 26);
    glutAddMenuEntry("blue", 27);
    glutAddMenuEntry("yellow", 28);
    glutAddMenuEntry("purple", 29);
    glutAddMenuEntry("orange", 30);
    glutAddMenuEntry("white", 31);
    glutAddMenuEntry("black", 32);

    submenu5 = glutCreateMenu(menu);
    glutAddMenuEntry("red", 33);
    glutAddMenuEntry("green", 34);
    glutAddMenuEntry("blue", 35);
    glutAddMenuEntry("yellow", 36);
    glutAddMenuEntry("purple", 37);
    glutAddMenuEntry("orange", 38);
    glutAddMenuEntry("white", 39);
    glutAddMenuEntry("black", 40);

    submenu6 = glutCreateMenu(menu);
    glutAddMenuEntry("red", 41);
    glutAddMenuEntry("green", 42);
    glutAddMenuEntry("blue", 43);
    glutAddMenuEntry("yellow", 44);
    glutAddMenuEntry("purple", 45);
    glutAddMenuEntry("orange", 46);
    glutAddMenuEntry("white", 47);
    glutAddMenuEntry("black", 48);

    submenu7 = glutCreateMenu(menu);
    glutAddSubMenu("filled", submenu1);
    glutAddSubMenu("outline", submenu2);

    submenu8 = glutCreateMenu(menu);
    glutAddSubMenu("filled", submenu3);
    glutAddSubMenu("outline", submenu4);
    menu_id = glutCreateMenu(menu);

    glutAddSubMenu("add rectangle", submenu7);
    glutAddSubMenu("add ellipse", submenu8);
    glutAddSubMenu("add line", submenu5);
    glutAddSubMenu("add bezier curve", submenu6);
    glutAttachMenu(GLUT_LEFT_BUTTON);
}

void display(void){

    int i;
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);
    for (i = 0; i < ncpts; i++)
        glVertex3fv(BC[numberOfBezierCurve].cpts[i]);

    for (i = 0; i < ncpts_r; i++)
        glVertex3fv(RE[numberOfRectangle].cpts[i]);

    for (i = 0; i < ncpts_e; i++)
        glVertex3fv(EL[numberOfEllipse].cpts[i]);

    for (i = 0; i < ncpts_l; i++)
        glVertex3fv(L[numberOfLine].cpts[i]);
    glEnd();

    glFlush();


  if(value == 1){
    option = 2;
    RE[numberOfRectangle].colorSeleted = 1;
    RE[numberOfRectangle].isFilled = 1;
    RE[numberOfRectangle].color[0] = 1.0;
    RE[numberOfRectangle].color[1] = 0.0;
    RE[numberOfRectangle].color[2] = 0.0;
  }else if(value == 2){
    option = 2;
    RE[numberOfRectangle].colorSeleted = 1;
    RE[numberOfRectangle].isFilled = 1;
    RE[numberOfRectangle].color[0] = 0.0;
    RE[numberOfRectangle].color[1] = 1.0;
    RE[numberOfRectangle].color[2] = 0.0;
  }else if(value == 3){
    option = 2;
    RE[numberOfRectangle].colorSeleted = 1;
    RE[numberOfRectangle].isFilled = 1;
    RE[numberOfRectangle].color[0] = 0.0;
    RE[numberOfRectangle].color[1] = 0.0;
    RE[numberOfRectangle].color[2] = 1.0;
  }else if(value == 4){
    option = 2;
    RE[numberOfRectangle].colorSeleted = 1;
    RE[numberOfRectangle].isFilled = 1;
    RE[numberOfRectangle].color[0] = 1.0;
    RE[numberOfRectangle].color[1] = 1.0;
    RE[numberOfRectangle].color[2] = 0.0;
  }else if(value == 5){
    option = 2;
    RE[numberOfRectangle].colorSeleted = 1;
    RE[numberOfRectangle].isFilled = 1;
    RE[numberOfRectangle].color[0] = 1.0;
    RE[numberOfRectangle].color[1] = 0.0;
    RE[numberOfRectangle].color[2] = 1.0;
  }else if(value == 6){
    option = 2;
    RE[numberOfRectangle].colorSeleted = 1;
    RE[numberOfRectangle].isFilled = 1;
    RE[numberOfRectangle].color[0] = 1.0;
    RE[numberOfRectangle].color[1] = 0.5;
    RE[numberOfRectangle].color[2] = 0.0;
  }else if(value == 7){
    option = 2;
    RE[numberOfRectangle].colorSeleted = 1;
    RE[numberOfRectangle].isFilled = 1;
    RE[numberOfRectangle].color[0] = 1.0;
    RE[numberOfRectangle].color[1] = 1.0;
    RE[numberOfRectangle].color[2] = 1.0;
  }else if(value == 8){
    option = 2;
    RE[numberOfRectangle].colorSeleted = 1;
    RE[numberOfRectangle].isFilled = 1;
    RE[numberOfRectangle].color[0] = 0.0;
    RE[numberOfRectangle].color[1] = 0.0;
    RE[numberOfRectangle].color[2] = 0.0;
  }else if(value == 9){
    option = 2;
    RE[numberOfRectangle].colorSeleted = 1;
    RE[numberOfRectangle].color[0] = 1.0;
    RE[numberOfRectangle].color[1] = 0.0;
    RE[numberOfRectangle].color[2] = 0.0;
  }else if(value == 10){
    option = 2;
    RE[numberOfRectangle].colorSeleted = 1;
    RE[numberOfRectangle].color[0] = 0.0;
    RE[numberOfRectangle].color[1] = 1.0;
    RE[numberOfRectangle].color[2] = 0.0;
  }else if(value == 11){
    option = 2;
    RE[numberOfRectangle].colorSeleted = 1;
    RE[numberOfRectangle].color[0] = 0.0;
    RE[numberOfRectangle].color[1] = 0.0;
    RE[numberOfRectangle].color[2] = 1.0;
  }else if(value == 12){
    option = 2;
    RE[numberOfRectangle].colorSeleted = 1;
    RE[numberOfRectangle].color[0] = 1.0;
    RE[numberOfRectangle].color[1] = 1.0;
    RE[numberOfRectangle].color[2] = 0.0;
  }else if(value == 13){
    option = 2;
    RE[numberOfRectangle].colorSeleted = 1;
    RE[numberOfRectangle].color[0] = 1.0;
    RE[numberOfRectangle].color[1] = 0.0;
    RE[numberOfRectangle].color[2] = 1.0;
  }else if(value == 14){
    option = 2;
    RE[numberOfRectangle].colorSeleted = 1;
    RE[numberOfRectangle].color[0] = 1.0;
    RE[numberOfRectangle].color[1] = 0.5;
    RE[numberOfRectangle].color[2] = 0.0;
  }else if(value == 15){
    option = 2;
    RE[numberOfRectangle].colorSeleted = 1;
    RE[numberOfRectangle].color[0] = 1.0;
    RE[numberOfRectangle].color[1] = 1.0;
    RE[numberOfRectangle].color[2] = 1.0;
  }else if(value == 16){
    option = 2;
    RE[numberOfRectangle].colorSeleted = 1;
    RE[numberOfRectangle].color[0] = 0.0;
    RE[numberOfRectangle].color[1] = 0.0;
    RE[numberOfRectangle].color[2] = 0.0;
  }else if(value == 17){
    option = 4;
    EL[numberOfEllipse].colorSeleted = 1;
    EL[numberOfEllipse].isFilled = 1;
    EL[numberOfEllipse].color[0] = 1.0;
    EL[numberOfEllipse].color[1] = 0.0;
    EL[numberOfEllipse].color[2] = 0.0;
  }else if(value == 18){
    option = 4;
    EL[numberOfEllipse].colorSeleted = 1;
    EL[numberOfEllipse].isFilled = 1;
    EL[numberOfEllipse].color[0] = 0.0;
    EL[numberOfEllipse].color[1] = 1.0;
    EL[numberOfEllipse].color[2] = 0.0;
  }else if(value == 19){
    option = 4;
    EL[numberOfEllipse].colorSeleted = 1;
    EL[numberOfEllipse].isFilled = 1;
    EL[numberOfEllipse].color[0] = 0.0;
    EL[numberOfEllipse].color[1] = 0.0;
    EL[numberOfEllipse].color[2] = 1.0;
  }else if(value == 20){
    option = 4;
    EL[numberOfEllipse].colorSeleted = 1;
    EL[numberOfEllipse].isFilled = 1;
    EL[numberOfEllipse].color[0] = 1.0;
    EL[numberOfEllipse].color[1] = 1.0;
    EL[numberOfEllipse].color[2] = 0.0;
  }else if(value == 21){
    option = 4;
    EL[numberOfEllipse].colorSeleted = 1;
    EL[numberOfEllipse].isFilled = 1;
    EL[numberOfEllipse].color[0] = 1.0;
    EL[numberOfEllipse].color[1] = 0.0;
    EL[numberOfEllipse].color[2] = 1.0;
  }else if(value == 22){
    option = 4;
    EL[numberOfEllipse].colorSeleted = 1;
    EL[numberOfEllipse].isFilled = 1;
    EL[numberOfEllipse].color[0] = 1.0;
    EL[numberOfEllipse].color[1] = 0.5;
    EL[numberOfEllipse].color[2] = 0.0;
  }else if(value == 23){
    option = 4;
    EL[numberOfEllipse].colorSeleted = 1;
    EL[numberOfEllipse].isFilled = 1;
    EL[numberOfEllipse].color[0] = 1.0;
    EL[numberOfEllipse].color[1] = 1.0;
    EL[numberOfEllipse].color[2] = 1.0;
  }else if(value == 24){
    option = 4;
    EL[numberOfEllipse].colorSeleted = 1;
    EL[numberOfEllipse].isFilled = 1;
    EL[numberOfEllipse].color[0] = 0.0;
    EL[numberOfEllipse].color[1] = 0.0;
    EL[numberOfEllipse].color[2] = 0.0;
  }else if(value == 25){
    option = 4;
    EL[numberOfEllipse].colorSeleted = 1;
    EL[numberOfEllipse].color[0] = 1.0;
    EL[numberOfEllipse].color[1] = 0.0;
    EL[numberOfEllipse].color[2] = 0.0;
  }else if(value == 26){
    option = 4;
    EL[numberOfEllipse].colorSeleted = 1;
    EL[numberOfEllipse].color[0] = 0.0;
    EL[numberOfEllipse].color[1] = 1.0;
    EL[numberOfEllipse].color[2] = 0.0;
  }else if(value == 27){
    option = 4;
    EL[numberOfEllipse].colorSeleted = 1;
    EL[numberOfEllipse].color[0] = 0.0;
    EL[numberOfEllipse].color[1] = 0.0;
    EL[numberOfEllipse].color[2] = 1.0;
  }else if(value == 28){
    option = 4;
    EL[numberOfEllipse].colorSeleted = 1;
    EL[numberOfEllipse].color[0] = 1.0;
    EL[numberOfEllipse].color[1] = 1.0;
    EL[numberOfEllipse].color[2] = 0.0;
  }else if(value == 29){
    option = 4;
    EL[numberOfEllipse].colorSeleted = 1;
    EL[numberOfEllipse].color[0] = 1.0;
    EL[numberOfEllipse].color[1] = 0.0;
    EL[numberOfEllipse].color[2] = 1.0;
  }else if(value == 30){
    option = 4;
    EL[numberOfEllipse].colorSeleted = 1;
    EL[numberOfEllipse].color[0] = 1.0;
    EL[numberOfEllipse].color[1] = 0.5;
    EL[numberOfEllipse].color[2] = 0.0;
  }else if(value == 31){
    option = 4;
    EL[numberOfEllipse].colorSeleted = 1;
    EL[numberOfEllipse].color[0] = 1.0;
    EL[numberOfEllipse].color[1] = 1.0;
    EL[numberOfEllipse].color[2] = 1.0;
  }else if(value == 32){
    option = 4;
    EL[numberOfEllipse].colorSeleted = 1;
    EL[numberOfEllipse].color[0] = 0.0;
    EL[numberOfEllipse].color[1] = 0.0;
    EL[numberOfEllipse].color[2] = 0.0;
  }else if(value == 33){
      option = 3;
      L[numberOfLine].colorSeleted = 1;
      L[numberOfLine].color[0] = 1.0;
      L[numberOfLine].color[1] = 0.0;
      L[numberOfLine].color[2] = 0.0;
  }else if(value == 34){
      option = 3;
      L[numberOfLine].colorSeleted = 1;
      L[numberOfLine].color[0] = 0.0;
      L[numberOfLine].color[1] = 1.0;
      L[numberOfLine].color[2] = 0.0;
  }else if(value == 35){
      option = 3;
      L[numberOfLine].colorSeleted = 1;
      L[numberOfLine].color[0] = 0.0;
      L[numberOfLine].color[1] = 0.0;
      L[numberOfLine].color[2] = 1.0;
  }else if(value == 36){
      option = 3;
      L[numberOfLine].colorSeleted = 1;
      L[numberOfLine].color[0] = 1.0;
      L[numberOfLine].color[1] = 1.0;
      L[numberOfLine].color[2] = 0.0;
  }else if(value == 37){
      option = 3;
      L[numberOfLine].colorSeleted = 1;
      L[numberOfLine].color[0] = 1.0;
      L[numberOfLine].color[1] = 0.0;
      L[numberOfLine].color[2] = 1.0;
  }else if(value == 38){
      option = 3;
      L[numberOfLine].colorSeleted = 1;
      L[numberOfLine].color[0] = 1.0;
      L[numberOfLine].color[1] = 0.5;
      L[numberOfLine].color[2] = 0.0;
  }else if(value == 39){
      option = 3;
      L[numberOfLine].colorSeleted = 1;
      L[numberOfLine].color[0] = 1.0;
      L[numberOfLine].color[1] = 1.0;
      L[numberOfLine].color[2] = 1.0;

  }else if(value == 40){
      option = 3;
      L[numberOfLine].colorSeleted = 1;
      L[numberOfLine].color[0] = 0.0;
      L[numberOfLine].color[1] = 0.0;
      L[numberOfLine].color[2] = 0.0;
  }else if(value == 41){
	  option = 1;
	  BC[numberOfBezierCurve].colorSeleted = 1;
	  ncpts =0;
      BC[numberOfBezierCurve].color[0] = 1.0;
      BC[numberOfBezierCurve].color[1] = 0.0;
      BC[numberOfBezierCurve].color[2] = 0.0;
  }else if(value == 42){
      option = 1;
      BC[numberOfBezierCurve].colorSeleted = 1;
	  ncpts =0;
      BC[numberOfBezierCurve].color[0] = 0.0;
      BC[numberOfBezierCurve].color[1] = 1.0;
      BC[numberOfBezierCurve].color[2] = 0.0;
  }else if(value == 43){
	  option = 1;
	  BC[numberOfBezierCurve].colorSeleted = 1;
	  ncpts =0;
      BC[numberOfBezierCurve].color[0] = 0.0;
      BC[numberOfBezierCurve].color[1] = 0.0;
      BC[numberOfBezierCurve].color[2] = 1.0;
  }else if(value == 44){
	  option = 1;
	  BC[numberOfBezierCurve].colorSeleted = 1;
	  ncpts =0;
      BC[numberOfBezierCurve].color[0] = 1.0;
      BC[numberOfBezierCurve].color[1] = 1.0;
      BC[numberOfBezierCurve].color[2] = 0.0;
  }else if(value == 45){
	  option = 1;
	  BC[numberOfBezierCurve].colorSeleted = 1;
	  ncpts =0;
      BC[numberOfBezierCurve].color[0] = 1.0;
      BC[numberOfBezierCurve].color[1] = 0.0;
      BC[numberOfBezierCurve].color[2] = 1.0;
  }else if(value == 46){
	  option = 1;
	  BC[numberOfBezierCurve].colorSeleted = 1;
	  ncpts =0;
      BC[numberOfBezierCurve].color[0] = 1.0;
      BC[numberOfBezierCurve].color[1] = 0.5;
      BC[numberOfBezierCurve].color[2] = 0.0;
  }else if(value == 47){
	  option = 1;
	  BC[numberOfBezierCurve].colorSeleted = 1;
	  ncpts =0;
      BC[numberOfBezierCurve].color[0] = 1.0;
      BC[numberOfBezierCurve].color[1] = 1.0;
      BC[numberOfBezierCurve].color[2] = 1.0;
  }else if(value == 48){
	  option = 1;
	  BC[numberOfBezierCurve].colorSeleted = 1;
	  ncpts =0;
      BC[numberOfBezierCurve].color[0] = 0.0;
      BC[numberOfBezierCurve].color[1] = 0.0;
      BC[numberOfBezierCurve].color[2] = 0.0;
  }
  glFlush();
  value = 0;
  drawCurves();
  drawRectangle();
  drawLine();
  drawEllipse();
}

void mouse(int button, int state, int x, int y)
{
    float wx, wy;
    //int i;
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && option == 1)
    {

       /* translate back to our coordinate system */
       wx = (2.0 * x) / (float)(width - 1) - 1.0;
       wy = (2.0 * (height - 1 - y)) / (float)(height - 1) - 1.0;


       /* see if we have room for any more bezier curve */
       if (numberOfBezierCurve == MAX_SHAPE){
           option = 0;
           return;
       }

       /* save the point */
       BC[numberOfBezierCurve].cpts[ncpts][0] = wx;
       BC[numberOfBezierCurve].cpts[ncpts][1] = wy;
       BC[numberOfBezierCurve].cpts[ncpts][2] = 0.0;
       ncpts++;

       /* draw the point */
       glColor3f(0.0, 0.0, 0.0);
       glPointSize(5.0);
       glBegin(GL_POINTS);
       glVertex3f(wx, wy, 0.0);
       glEnd();
       glFlush();

       if(ncpts == 4){
        ncpts =0;
        if(BC[numberOfBezierCurve].colorSeleted == 0){
            BC[numberOfBezierCurve].color[0] = BC[numberOfBezierCurve-1].color[0];
            BC[numberOfBezierCurve].color[1] = BC[numberOfBezierCurve-1].color[1];
            BC[numberOfBezierCurve].color[2] = BC[numberOfBezierCurve-1].color[2];
        }
        numberOfBezierCurve++;
     }
    }else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && option == 2){

       /* translate back to our coordinate system */
       wx = (2.0 * x) / (float)(width - 1) - 1.0;
       wy = (2.0 * (height - 1 - y)) / (float)(height - 1) - 1.0;


       /* see if we have room for any more bezier curve */
       if (numberOfRectangle == MAX_SHAPE){
           option = 0;
           return;
       }

       /* save the point */
       RE[numberOfRectangle].cpts[ncpts_r][0] = wx;
       RE[numberOfRectangle].cpts[ncpts_r][1] = wy;
       RE[numberOfRectangle].cpts[ncpts_r][2] = 0.0;
       ncpts_r++;

       /* draw the point */
       glColor3f(0.0, 0.0, 0.0);
       glPointSize(5.0);
       glBegin(GL_POINTS);
       glVertex3f(wx, wy, 0.0);
       glEnd();
       glFlush();

	   if(ncpts_r == 2){
        ncpts_r =0;
        if(RE[numberOfRectangle].colorSeleted == 0){
            RE[numberOfRectangle].isFilled = RE[numberOfRectangle-1].isFilled;
            RE[numberOfRectangle].color[0] = RE[numberOfRectangle-1].color[0];
            RE[numberOfRectangle].color[1] = RE[numberOfRectangle-1].color[1];
            RE[numberOfRectangle].color[2] = RE[numberOfRectangle-1].color[2];
        }
        numberOfRectangle++;
     }
    }else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && option == 3){

       /* translate back to our coordinate system */
       wx = (2.0 * x) / (float)(width - 1) - 1.0;
       wy = (2.0 * (height - 1 - y)) / (float)(height - 1) - 1.0;


       /* see if we have room for any more bezier curve */
       if (numberOfLine == MAX_SHAPE){
           option = 0;
           return;
       }

       /* save the point */
       L[numberOfLine].cpts[ncpts_l][0] = wx;
       L[numberOfLine].cpts[ncpts_l][1] = wy;
       L[numberOfLine].cpts[ncpts_l][2] = 0.0;
       ncpts_l++;

       /* draw the point */
       glColor3f(0.0, 0.0, 0.0);
       glPointSize(5.0);
       glBegin(GL_POINTS);
       glVertex3f(wx, wy, 0.0);
       glEnd();
       glFlush();

	   if(ncpts_l == 2){
        ncpts_l =0;
        if(L[numberOfLine].colorSeleted == 0){
            L[numberOfLine].color[0] = L[numberOfLine-1].color[0];
            L[numberOfLine].color[1] = L[numberOfLine-1].color[1];
            L[numberOfLine].color[2] = L[numberOfLine-1].color[2];
        }
        numberOfLine++;
     }
    }else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && option == 4){

       /* translate back to our coordinate system */
       wx = (2.0 * x) / (float)(width - 1) - 1.0;
       wy = (2.0 * (height - 1 - y)) / (float)(height - 1) - 1.0;


       /* see if we have room for any more bezier curve */
       if (numberOfEllipse == MAX_SHAPE){
           option = 0;
           return;
       }

       /* save the point */
       EL[numberOfEllipse].cpts[ncpts_e][0] = wx;
       EL[numberOfEllipse].cpts[ncpts_e][1] = wy;
       EL[numberOfEllipse].cpts[ncpts_e][2] = 0.0;
       ncpts_e++;

       /* draw the point */
       glColor3f(0.0, 0.0, 0.0);
       glPointSize(5.0);
       glBegin(GL_POINTS);
       glVertex3f(wx, wy, 0.0);
       glEnd();
       glFlush();

	   if(ncpts_e == 2){
        ncpts_e =0;
        if(EL[numberOfEllipse].colorSeleted == 0){
            EL[numberOfEllipse].isFilled = EL[numberOfEllipse-1].isFilled;
            EL[numberOfEllipse].color[0] = EL[numberOfEllipse-1].color[0];
            EL[numberOfEllipse].color[1] = EL[numberOfEllipse-1].color[1];
            EL[numberOfEllipse].color[2] = EL[numberOfEllipse-1].color[2];
        }
        numberOfEllipse++;
     }
    }

}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'q': case 'Q':
            exit(0);
            break;
        case 'c': case 'C':
            numberOfBezierCurve = 0;
            numberOfEllipse = 0;
            numberOfLine = 0;
            numberOfRectangle =0;
            ncpts = 0;
            ncpts_e = 0;
            ncpts_l = 0;
            ncpts_r = 0;
            value = 0;
            option = 0;
            glutAttachMenu(GLUT_LEFT_BUTTON);
            glutPostRedisplay();
            break;
    }
}

void reshape(int w, int h)
{
    width = w;
    height = h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-width)/2,
                       (glutGet(GLUT_SCREEN_HEIGHT)-height)/2);

    glutCreateWindow("Simple Paint And Draw Program");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    createMenu();
    glClearColor(0.85f, 0.85f, 0.85f, 0.0f);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(5.0);
    glEnable(GL_MAP1_VERTEX_3);
    glutMainLoop();
}
