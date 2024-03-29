// C++ implementation for mandelbrot set fractals
#include <GL/glut.h>
#include <graphics.h>
#include <stdio.h>

// #define MAXCOUNT 30
#define MAXCOUNT 100

// Function to draw mandelbrot set
void fractal(float left, float top, float xside, float yside) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);

    float xscale, yscale, zx, zy, cx, tempx, cy;
    int x, y, i, j;
    int maxx, maxy, count;

    // getting maximum value of x-axis of screen
    maxx = getmaxx();

    // getting maximum value of y-axis of screen
    maxy = getmaxy();

    // setting up the xscale and yscale
    xscale = xside / maxx;
    yscale = yside / maxy;

    // calling rectangle function
    // where required image will be seen
    rectangle(0, 0, maxx, maxy);

    // scanning every point in that rectangular area.
    // Each point represents a Complex number (x + yi).
    // Iterate that complex number
    for (y = 1; y <= maxy - 1; y++) {
        for (x = 1; x <= maxx - 1; x++) {
            // c_real
            cx = x * xscale + left;

            // c_imaginary
            cy = y * yscale + top;

            // z_real
            zx = 0;

            // z_imaginary
            zy = 0;
            count = 0;

            // Calculate whether c(c_real + c_imaginary) belongs
            // to the Mandelbrot set or not and draw a pixel
            // at coordinates (x, y) accordingly
            // If you reach the Maximum number of iterations
            // and If the distance from the origin is
            // greater than 2 exit the loop
            while ((zx * zx + zy * zy < 4) && (count < MAXCOUNT)) {
                // Calculate Mandelbrot function
                // z = z*z + c where z is a complex number

                // tempx = z_real*_real - z_imaginary*z_imaginary +
                // c_real
                tempx = zx * zx - zy * zy + cx;

                // 2*z_real*z_imaginary + c_imaginary
                zy = 2 * zx * zy + cy;

                // Updating z_real = tempx
                zx = tempx;

                // Increment count
                count = count + 1;
            }

            // To display the created fractal
            putpixel(x, y, count);
        }
    }
    glEnd();
    glFlush();
}

void display() {
    float left, top, xside, yside;

    left = -1.74;
    top = -0.25;
    xside = 0.25;
    yside = 0.45;

    fractal(left, top, xside, yside);
}

// Driver code
int main(int argc, char **argv) {
    // gm is Graphics mode which is
    // a computer display mode that
    // generates image using pixels.
    // DETECT is a macro defined in
    // "graphics.h" header file
    int gd = DETECT, gm, errorcode;

    float left, top, xside, yside;

    // setting the left, top, xside and yside
    // for the screen and image to be displayed

    /*
    left = -1;
    top = 0;
    xside = 0;
    yside = 0.2;
    */
    left = -1.74;
    top = -0.25;
    xside = 0.25;
    yside = 0.45;

    char driver[] = "";

    // initgraph initializes the
    // graphics system by loading a
    // graphics driver from disk
    initgraph(&gd, &gm, driver);
    // glutInit(&gd, driver);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1366, 768);
    glutInitWindowPosition(0, 0);

    // Function calling
    // fractal(left, top, xside, yside);

    // getch();

    // closegraph function closes the
    // graphics mode and deallocates
    // all memory allocated by
    // graphics system
    // closegraph();
    glutCreateWindow("Mandelbrot Fractals with openGL");
    glutDisplayFunc(display);
    glutMainLoop();

    getch();

    return 0;
}
