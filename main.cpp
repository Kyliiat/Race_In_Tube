// glutEx1.cpp : ∂®“Âøÿ÷∆Ã®”¶”√≥Ã–Úµƒ»Îø⁄µ„°£
//

#include <glut/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


float fTranslate;
float fRotate=-16;
float fScale = 1.0f;	// set inital scale value to 1.0f

bool bPersp = true;
bool bAnim = false;
bool bWire = false;
bool run=false;
int wHeight = 0;
int wWidth = 0;
GLint num =10;

float eye[] = { 0, 4, -6};
float center[] = { 0, 0, 8 };
float move_x, move_y, move_z;
GLint number[10000];
bool Open = false;
int stage = 0;

void drawGrid(int num, int offset)
{
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(20, 0, 0);
    
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 20, 0);
    
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 20);
    glEnd();
    
    glPushMatrix();
    // decide where the grid is
    if (Open == true)       // open the tube
    {
        if (num == 9)
        {
            if (stage < 1000)
            {
                stage++;
                glRotatef(36*num, 0, 0, 1);         // 绕中轴转
                glTranslatef(1, -3.078, offset*5);
                glRotatef(0.036*stage, 0, 0, 1);    // 绕自己轴转
                glTranslatef(-1, 0, 0);
            }
            else
            {
                glTranslatef(-2, -3.078, offset*5);
            }
            
        }
        else if (num == 8)
        {
            if (stage < 1000)
            {
                stage++;
            }
            else
            {
                glTranslatef(-4, -3.078, offset*5);
            }
        }
        else if (num == 1)
        {
            if (stage < 1000)
            {
                stage++;
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(-1, -3.078, offset*5);
                glRotatef(-0.036*stage, 0, 0, 1);
                glTranslatef(1, 0, 0);
            }
            else
            {
                glTranslatef(2, -3.078, offset*5);
            }
        }
        else
        {
            glRotatef(36*num, 0, 0, 1);
            glTranslatef(0, -3.078, offset*5);
        }
        
    }
    else
    {
        glRotatef(36*num, 0, 0, 1);
        glTranslatef(0, -3.078, offset*5);
    }
    
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glVertex3f(-1, 0, 0);
    glVertex3f(1, 0, 0);
    glVertex3f(1, 0, 5);
    glVertex3f(-1, 0, 5);
    glEnd();
    
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex3f(-1, 0, 0);
    glVertex3f(1, 0, 0);
    glVertex3f(1, 0, 0);
    glVertex3f(1, 0, 5);
    glVertex3f(1, 0, 5);
    glVertex3f(-1, 0, 5);
    glVertex3f(-1, 0, 5);
    glVertex3f(-1, 0, 0);
    glEnd();
    
    glPopMatrix();
}

void Draw_barrier(int i)
{
    glColor3f(1, 0, 1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    
    glPushMatrix();
    
    glRotatef(36*number[i], 0, 0, 1);       // rotate to a random angle
    glTranslatef(3, -8, 25);
    glTranslatef(move_x, move_y, move_z);
    glRotatef(0, 1, 0, 0);
    glRotatef(10, 0, 0, 1);
    glRotatef(-20, 0, 1, 0);
    

    glBegin(GL_TRIANGLES);
    
    glVertex3f(0, 2.5, 0);
    glVertex3f(-1.5, 0, 1.5);
    glVertex3f(1.5, 0, 1.5);
    
    glVertex3f(0, 2.5, 0);
    glVertex3f(-1.5, 0, 1.5);
    glVertex3f(-1.5, 0, -1.5);
    
    glVertex3f(0, 2.5, 0);
    glVertex3f(-1.5, 0, -1.5);
    glVertex3f(1.5, 0, -1.5);
    
    glVertex3f(0, 2.5, 0);
    glVertex3f(1.5, 0, -1.5);
    glVertex3f(1.5, 0, 1.5);
    
    glVertex3f(0, -2.5, 0);
    glVertex3f(-1.5, 0, 1.5);
    glVertex3f(1.5, 0, 1.5);
    
    glVertex3f(0, -2.5, 0);
    glVertex3f(-1.5, 0, 1.5);
    glVertex3f(-1.5, 0, -1.5);
    
    glVertex3f(0, -2.5, 0);
    glVertex3f(-1.5, 0, -1.5);
    glVertex3f(1.5, 0, -1.5);
    
    glVertex3f(0, -2.5, 0);
    glVertex3f(1.5, 0, -1.5);
    glVertex3f(1.5, 0, 1.5);
    glEnd();
    
    glPopMatrix();
}

void updateView(int width, int height)
{
    glViewport(0, 0, width, height);
    // Reset The Current Viewport
    
    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
    glLoadIdentity();									// Reset The Projection Matrix
    
    float whRatio = (GLfloat)width / (GLfloat)height;
    if (bPersp) {
        gluPerspective(90.0f, whRatio, 0.1f, 100.0f);
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
            fRotate-=36;
            break;
        }
        case 'd': {
            fRotate+=36;
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
        
        case 'm': {
            Open = !Open;
            break;
        }
            
            
    }
    
    updateView(wHeight, wWidth);
}


void redraw()
{
    int i;
    
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

//    glScalef(0.2, 0.2, 0.2);
    
    for (int q=0;q<num;q++)         // number of cylinders
    {
        for (i=0;i<10;i++)
        {
            drawGrid(i, q);
        }
    }
    
    
//    GLUquadricObj *qobj;
//    GLUquadricObj *qobj2;
//    qobj = gluNewQuadric();
//    qobj2 = gluNewQuadric();
//    
//    GLfloat line[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
//    GLfloat clear[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
//    glPushMatrix();
//    
//    //gluQuadricDrawStyle(qobj, GLU_LINE); /* flat shaded */
//    //gluQuadricNormals(qobj, GLU_FLAT);
//    glColor3f(1,1,1);
//    gluQuadricDrawStyle(qobj, GLU_FILL); // all polygons wireframe
//    gluCylinder(qobj, 10, 10, 10*num, 10,num);
//    
//    glPopMatrix();
//    
//    
//    glColor3f(0,0,0);
//    gluQuadricDrawStyle(qobj2, GLU_LINE);
//    
//    
//    gluCylinder(qobj2, 10, 10,10*num, 10,num);
//
//    // barriers
//    for (int i=0;i<num/2;i++)
//    {
//        if (number[0] == 0)         // set random positions
//        {
//            srand((int)time(0));
//            for (int j=0;j<num/2;j++) number[j] = rand() % 10 + 1;
//        }
//        move_x = 0;
//        move_y = 0;
//        move_z = i*10;      // position in z axis
//        Draw_barrier(i);
//    }
//    
    if (run) {
        num=num+1;
        eye[2] += 0.1f;
        center[2] += 0.1f;
        if (number[num/2] == 0)
        {
            number[num/2] = rand() % 10 + 1;
        }
    }
//
    
    
    if (bAnim) fRotate += 0.1f;
    
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(1700, 800);
    int windowHandle = glutCreateWindow("Tube");
    
    glutDisplayFunc(redraw);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);
    
    glutIdleFunc(idle);
    
    glutMainLoop();
    return 0;
}
