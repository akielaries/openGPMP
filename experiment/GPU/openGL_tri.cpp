/*
 * Testing openGL with drawing a simple triangle with shades
 */
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>

#define pi 3.142857
  
void display() {
    // setting every pixel in frame buffer to a clear color
    glClear(GL_COLOR_BUFFER_BIT);

    // being drawing
    glBegin(GL_POLYGON);
        glColor3f(1, 0, 0); glVertex3f(-0.6, -0.75, 0.5);
        glColor3f(0, 1, 0); glVertex3f(0.6, -0.75, 0);
        glColor3f(0, 0, 1); glVertex3f(0, 0.75, 0);
    glEnd();

    // flush the draw cmd to display image immediately
    glFlush();

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutMainLoop();

    return 0;
}

