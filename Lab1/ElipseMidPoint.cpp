#include <GL/glut.h>
#include <cmath>

int xc, yc; // T�m ellipse
double a, b; // �? d�i tr?c l?n v� tr?c nh? c?a ellipse
bool firstClick = true;

void initGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // M�u n?n tr?ng
    glOrtho(-320, 320, -240, 240, -1, 1); // Kh�ng gian nh�n
}

void draw4point(int xc, int yc, int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x + xc, y + yc);
    glVertex2i(x + xc, -y + yc);
    glVertex2i(-x + xc, -y + yc);
    glVertex2i(-x + xc, y + yc);
    glEnd();
}

void EllipsMidpoint(int xc, int yc, double a, double b)
{
    float x0 = a * a / sqrt(a * a + b * b); // �i?m d?u ti�n tr�n ellipse
    float P;

    // V? n?a d?u ellipse
    int x = 0;
    int y = b;
    P = b * b - a * a * b + a * a / 4;

    draw4point(xc, yc, x, y);
    while (x <= x0)
    {
        if (P < 0)
            P += (b * b) * (2 * x + 3);
        else
        {
            P += (b * b) * (2 * x + 3) - 2 * a * a * (y - 1);
            y--;
        }
        x++;
        draw4point(xc, yc, x, y);
    }

    // V? n?a sau ellipse
    x = a;
    y = 0;
    P = a * a - b * b * a + b * b / 4;

    draw4point(xc, yc, x, y);
    while (x > x0)
    {
        if (P < 0)
            P += (a * a) * (2 * y + 3);
        else
        {
            P += (a * a) * (2 * y + 3) - 2 * b * b * (x - 1);
            x--;
        }
        y++;
        draw4point(xc, yc, x, y);
    }
}

void mydisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0); // M�u d?

    if (!firstClick)
    {
        EllipsMidpoint(xc, yc, a, b); // V? ellipse v?i t�m (xc, yc) v� d? d�i c�c tr?c (a, b)
    }

    glViewport(0, 0, 640, 480); // Khung nh�n
    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (firstClick)
        {
            xc = x - 320; // Chuy?n t?a d? chu?t v? kh�ng gian tr?c t?a d?
            yc = 240 - y;
            firstClick = false;
        }
        else
        {
            a = abs(x - 320); // T�nh a v� b d?a tr�n kho?ng c�ch t? t�m d?n di?m click
            b = abs(240 - y);
            firstClick = true;
            glutPostRedisplay(); // C?p nh?t l?i m�n h�nh
        }
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv); // Kh?i t?o GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 0);
    glutCreateWindow("DEMO THUAT TOAN VE DUONG ELLIPSE - MIDPOINT");

    initGL();
    glutDisplayFunc(mydisplay);
    glutMouseFunc(mouse);

    glutMainLoop(); // V�ng l?p ch�nh c?a GLUT
    return 0;
}

