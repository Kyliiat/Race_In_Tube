// glutEx1.cpp : ∂®“Âøÿ÷∆Ã®”¶”√≥Ã–Úµƒ»Îø⁄µ„°£
//

#include <glut/glut.h>
#include <stdlib.h>
#include <stdio.h>



float fTranslate;
float fRotate;
float fScale = 1.0f;	// set inital scale value to 1.0f

bool bPersp = true;
bool bAnim = false;
bool bWire = false;
bool run=false;
int wHeight = 0;
int wWidth = 0;
GLint num =10;

float eye[] = { 0, 0,  0};
float center[] = { 0, 0, 25 };


void updateView(int width, int height)
{
    glViewport(0, 0, width, height);						// Reset The Current Viewport
    
    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
    glLoadIdentity();									// Reset The Projection Matrix
    
    float whRatio = (GLfloat)width / (GLfloat)height;
    if (bPersp) {
        gluPerspective(45.0f, whRatio, 0.1f, 100.0f);
        //glFrustum(-3, 3, -3, 3, 3,100);
    }
    else {
        glOrtho(-3, 3, -3, 3, -100, 100);
    }
    
    glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

void reshape(int width, int height)
{
    if (height == 0)										// Prevent A Divide By Zero By
    {
        height = 1;										// Making Height Equal One
    }
    
    wHeight = height;
    wWidth = width;
    
    updateView(wHeight, wWidth);
}

void idle()
{
    glutPostRedisplay();
}




void key(unsigned char k, int x, int y)
{
    switch (k)
    {
        case 27:
        case 'q': {exit(0); break; }
        case 'p': {bPersp = !bPersp; break; }
            
        case ' ': {bAnim = !bAnim; break; }
        case 'o': {bWire = !bWire; break; }
            
        case 'a': {
            fRotate+=3;
            break;
        }
        case 'd': {
            fRotate-=3;
            break;
        }
        case 'w': {
            eye[1] -= 0.2f;
            center[1] -= 0.2f;
            break;
        }
        case 's': {
            eye[1] += 0.2f;
            center[1] += 0.2f;
            break;
        }
        case 'z': {
            eye[2] -= 0.2f;
            center[2] -= 0.2f;
            break;
        }
        case 'c': {
            eye[2] += 0.2f;
            center[2] += 0.2f;
            break;
        }
            
            //change the color of the light0
        case 'r': {
            run=!run;
            
            break;
        }
            
            
            
    }
    
    updateView(wHeight, wWidth);
}


void redraw()
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();									// Reset The Current Modelview Matrix
    
    gluLookAt(eye[0], eye[1], eye[2],
              center[0], center[1], center[2],
              0, 1, 0);
    
    if (bWire) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    
    
    glRotatef(fRotate, 0, 0, 1.0f);
    
    glScalef(0.2, 0.2, 0.2);
    
    
    GLUquadricObj *qobj;
    GLUquadricObj *qobj2;
    qobj = gluNewQuadric();
    qobj2 = gluNewQuadric();
    
    GLfloat line[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat clear[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glPushMatrix();
    
    //gluQuadricDrawStyle(qobj, GLU_LINE); /* flat shaded */
    //gluQuadricNormals(qobj, GLU_FLAT);
    glColor3f(1,1,1);
    gluQuadricDrawStyle(qobj, GLU_FILL); // all polygons wireframe
    gluCylinder(qobj, 10, 10,10*num, 10,num);
    
    
    glPopMatrix();
    
    
    glColor3f(0,0,0);
    gluQuadricDrawStyle(qobj2, GLU_LINE);
    
    
    
    
    
    gluCylinder(qobj2, 10, 10,10*num, 10,num);
    
    if (run) {
        num=num+1;
        eye[2] += 0.1f;
        center[2] += 0.1f;
    }
    
    
    
    if (bAnim) fRotate += 0.1f;
    
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(800, 800);
    int windowHandle = glutCreateWindow("Simple GLUT App");
    
    glutDisplayFunc(redraw);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);
    
    glutIdleFunc(idle);
    
    glutMainLoop();
    return 0;
}
