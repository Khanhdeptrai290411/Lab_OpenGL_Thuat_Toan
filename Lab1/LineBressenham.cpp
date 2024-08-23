#include <GL/glut.h>

int x1 = 0, y1 = 0, x2 = 0, y2 = 0; // T?a ð? c?a ði?m A và B
bool firstClick = true; // Bi?n ðánh d?u ð? click l?n ð?u hay chýa

void initGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Màu n?n tr?ng
    glOrtho(-320, 320, -240, 240, -1, 1); // Thi?t l?p h? t?a ð?
}

void plotPoint(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void LineBres(int x1, int y1, int x2, int y2)
{
    int Dx = abs(x2 - x1);
    int Dy = abs(y2 - y1);
    int d = (Dx > Dy) ? (2 * Dy - Dx) : (2 * Dx - Dy);
    int x, y, x_unit, y_unit;

    if (x1 < x2)
        x_unit = 1;
    else
        x_unit = -1;

    if (y1 < y2)
        y_unit = 1;
    else
        y_unit = -1;

    x = x1;
    y = y1;

    plotPoint(x, y);

    if (Dx > Dy)
    {
        while (x != x2)
        {
            x += x_unit;
            if (d < 0)
                d += 2 * Dy;
            else
            {
                d += 2 * (Dy - Dx);
                y += y_unit;
            }
            plotPoint(x, y);
        }
    }
    else
    {
        while (y != y2)
        {
            y += y_unit;
            if (d < 0)
                d += 2 * Dx;
            else
            {
                d += 2 * (Dx - Dy);
                x += x_unit;
            }
            plotPoint(x, y);
        }
    }
}

void mydisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    if (!firstClick && !(x1 == x2 && y1 == y2))
    {
        // V? ðo?n th?ng t? ði?m A ð?n ði?m B
        LineBres(x1, y1, x2, y2);
    }

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (firstClick)
        {
            x1 = x - 320; // Chuy?n ð?i t?a ð? chu?t v? h? t?a ð? OpenGL
            y1 = 240 - y;
            firstClick = false;
        }
        else
        {
            x2 = x - 320;
            y2 = 240 - y;
            firstClick = true;
            glutPostRedisplay(); // Yêu c?u v? l?i màn h?nh
        }
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Bresenham Line Drawing");

    initGL();
    glutDisplayFunc(mydisplay);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}

