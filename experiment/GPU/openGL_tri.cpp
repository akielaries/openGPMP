/*
 * Testing openGL with drawing a simple triangle with shades
 */
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define pi 3.142857

void display() {
    // setting every pixel in frame buffer to a clear color
    glClear(GL_COLOR_BUFFER_BIT);

    // being drawing
    glBegin(GL_POLYGON);
    glColor3f(1, 0, 1);
    glVertex3f(-0.6, -0.75, 0.5);
    glColor3f(0, 1, 0);
    glVertex3f(0.6, -0.75, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0.75, 0);
    glEnd();

    // flush the draw cmd to display image immediately
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Position window at (80,80)-(480,380) and give it a title.
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(1000, 800);
    glutCreateWindow("A Shaded Triangle");

    // Tell GLUT that whenever the main window needs to be repainted
    // that it should call the function display().
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
