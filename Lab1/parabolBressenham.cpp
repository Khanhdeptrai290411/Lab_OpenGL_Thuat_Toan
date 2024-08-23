#include <GL/glut.h>
#include <cmath>

int xc = 0, yc = 0;  // Ði?m ð?nh c?a parabol
int x_b = 0, y_b = 0;  // Ði?m bên c?a parabol
bool firstClick = true;  // Bi?n ki?m tra l?n click ð?u tiên

void initGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // Màu n?n tr?ng
    glOrtho(-320, 320, -240, 240, -1, 1);  // Thi?t l?p không gian nh?n
}

void drawPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void ParabolBresenham(int xc, int yc, int x_b, int y_b)
{
    int dx = abs(x_b - xc);
    int dy = abs(y_b - yc);
    int p = 2 * dy - dx;
    int x = xc;
    int y = yc;

    drawPixel(x, y);

    int incrE = 2 * dy;
    int incrNE = 2 * (dy - dx);

    int stepX = (x_b > xc) ? 1 : -1;
    int stepY = (y_b > yc) ? 1 : -1;

    while (x != x_b)
    {
        x += stepX;
        if (p < 0)
        {
            p += incrE;
        }
        else
        {
            y += stepY;
            p += incrNE;
        }
        drawPixel(x, y);
    }
}

void mydisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);  // Màu ð?

    if (!firstClick)
    {
        ParabolBresenham(xc, yc, x_b, y_b);  // V? parabol t? ði?m ð?nh ð?n ði?m bên
    }

    glViewport(0, 0, 640, 480);
    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (firstClick)
        {
            xc = x - 320;  // Chuy?n t?a ð? chu?t v? không gian to? ð? c?a OpenGL
            yc = 240 - y;
            firstClick = false;
        }
        else
        {
            x_b = x - 320;  // Chuy?n t?a ð? chu?t v? không gian to? ð? c?a OpenGL
            y_b = 240 - y;
            firstClick = true;
            glutPostRedisplay();  // Yêu c?u c?p nh?t l?i c?a s?
        }
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);  // Kh?i t?o GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 0);
    glutCreateWindow("V? Parabol - Bresenham");

    initGL();
    glutDisplayFunc(mydisplay);
    glutMouseFunc(mouse);

    glutMainLoop();  // V?ng l?p chính c?a GLUT
    return 0;
}

