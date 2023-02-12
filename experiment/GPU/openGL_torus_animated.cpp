/*
 * Testing openGL with drawing an animate torus
 */
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define pi 3.142857

static bool      spinning = true;
static const int FPS      = 20;

// keep track of current orentation
static GLfloat current_rot = 0.0;

/*
 * handles window reshaping/resizing
 */
void reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    GLfloat aspect = (GLfloat)w / (GLfloat)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h) {
        // width is smaller, go from -50 .. 50 in width
        glOrtho(-50.0, 50.0, -50.0 / aspect, 50.0 / aspect, -1.0, 1.0);
    }

    else {
        // height is smaller, go from -50 .. 50 in height
        // glOrtho(-50.0*aspect, 50.0*aspect, -50.0, 50.0, -1.0, 1.0);

        glOrtho(-10.0 * aspect, 10.0 * aspect, -10.0, 10.0, -1.0, 1.0);
    }
}

void display() {
    // setting every pixel in frame buffer to a clear color
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1.0, 1.0, 1.0);
    glRotatef(current_rot, 0.0, 0.0, 1.0);
    glutWireTorus(0.5, 3, 15, 30);

    // being drawing

    glBegin(GL_POLYGON);
    glRotatef(current_rot, 1.0, 0.0, 1.0);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(10, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 10, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 10);
    glEnd();

    glRotatef(current_rot, 1.0, 0.0, 1.0);

    // flush the draw cmd to display image immediately
    glFlush();
    glutSwapBuffers();
}

/*
 * timer that increments the torus orientations for animation
 */
void timer(int v) {
    if (spinning) {
        current_rot += 1.0;

        if (current_rot > 360.0) {
            current_rot -= 360.0;
        }
        glutPostRedisplay();
    }

    glutTimerFunc(1000 / FPS, timer, v);
}

/*
 * mouse events, left click generates new animations, right clock
 * removes idle-time callback
 */
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        spinning = true;
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        spinning = false;
    }
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 4.0 / 3.0, 1, 40);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(4, 6, 5, 0, 0, 0, 0, 1, 0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Position window at (80,80)-(480,380) and give it a title.
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(1000, 800);
    glutCreateWindow("A Torus on a Plane");

    glutReshapeFunc(reshape);

    // Tell GLUT that whenever the main window needs to be repainted
    // that it should call the function display().
    glutDisplayFunc(display);
    glutTimerFunc(100, timer, 0);
    glutMouseFunc(mouse);

    init();

    glutMainLoop();
}
