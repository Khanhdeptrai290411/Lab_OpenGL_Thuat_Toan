#include <GL/glut.h>
#include <math.h>

// Bi?n to�n c?c �? l�u tham s? cho c�c ��?ng cong
int clickCount = 0;
float x1 = 0.0f, y1_value = 0.0f, x2 = 0.0f, y2 = 0.0f;

// H�m v? parabol
void drawParabola(float x0, float y0, float a) {
    glBegin(GL_POINTS);
    for (float x = -10.0; x <= 10.0; x += 0.01) {
        float y = a * x * x;
        glVertex2f(x0 + x, y0 + y);
    }
    glEnd();
}

// H�m v? hyperbol
void drawHyperbola(float x0, float y0, float a, float b) {
    glBegin(GL_POINTS);
    for (float x = -10.0; x <= 10.0; x += 0.01) {
        float y1 = sqrt(x * x / a / a - 1) * b;
        float y2 = -sqrt(x * x / a / a - 1) * b;
        glVertex2f(x0 + x, y0 + y1);
        glVertex2f(x0 + x, y0 + y2);
    }
    glEnd();
}

// H�m v? sin(x)
void drawSin(float x0, float y0) {
    glBegin(GL_LINE_STRIP);
    for (float x = -10.0; x <= 10.0; x += 0.01) {
        float y = sin(x);
        glVertex2f(x0 + x, y0 + y);
    }
    glEnd();
}

// H�m v? cos(x)
void drawCos(float x0, float y0) {
    glBegin(GL_LINE_STRIP);
    for (float x = -10.0; x <= 10.0; x += 0.01) {
        float y = cos(x);
        glVertex2f(x0 + x, y0 + y);
    }
    glEnd();
}

// H�m x? l? s? ki?n click chu?t
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (clickCount == 0) {
            x1 = (x - 250) / 25.0; // Chuy?n �?i t?a �? pixel sang t?a �? h? t?a �? OpenGL
            y1_value = (250 - y) / 25.0;
            clickCount++;
        } else if (clickCount == 1) {
            x2 = (x - 250) / 25.0;
            y2 = (250 - y) / 25.0;
            clickCount = 0;
            glutPostRedisplay();
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0); // M�u �?

    // V? parabol
    drawParabola(0.0, 0.0, 0.1);

//    // V? hyperbol
//    drawHyperbola(0.0, 0.0, 1.0, 1.0);
//
//    // V? sin(x)
//    glColor3f(0.0, 1.0, 0.0); // M�u xanh l�
//    drawSin(0.0, 0.0);
//
//    // V? cos(x)
//    glColor3f(0.0, 0.0, 1.0); // M�u xanh d��ng
//    drawCos(0.0, 0.0);

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // M�u n?n tr?ng
    glColor3f(0.0, 0.0, 0.0); // M�u ��?ng k? �en
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10.0, 10.0, -10.0, 10.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Curve Drawing Example");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}

