#include <GL/glut.h>

// T?a d? c�c d?nh c?a h�nh vu�ng
GLfloat toadodinh[3][2] = {
    {100.0, 100.0},
    {200.0, 100.0},
    {200.0, 200.0},
   // {100.0, 200.0}
};

// V�c to t?nh ti?n ban d?u
GLfloat tx = 20.0;
GLfloat ty = 20.0;

// V�c to t?nh ti?n hi?n t?i
GLfloat currentTx = 0.0;
GLfloat currentTy = 0.0;

void khoitao() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 800.0, 0.0, 600.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // V? h�nh ban d?u
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        for (int i = 0; i < 4; ++i) {
            glVertex2f(toadodinh[i][0], toadodinh[i][1]);
        }
    glEnd();

    // T�nh to�n v� v? h�nh sau khi t?nh ti?n
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
        for (int i = 0; i < 4; ++i) {
            glVertex2f(toadodinh[i][0] + currentTx, toadodinh[i][1] + currentTy);
        }
    glEnd();

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': // T?nh ti?n l�n
            currentTy += ty;
            break;
        case 's': // T?nh ti?n xu?ng
            currentTy -= ty;
            break;
        case 'a': // T?nh ti?n tr�i
            currentTx -= tx;
            break;
        case 'd': // T?nh ti?n ph?i
            currentTx += tx;
            break;
        case 'r': // Reset
            currentTx = 0.0;
            currentTy = 0.0;
            break;
    }
    glutPostRedisplay(); // G?i l?i h�m display d? v? l?i h�nh
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ph�p bien doi 2D - Tinh Tien");

    khoitao();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); // �ang k� h�m x? l� b�n ph�m
    glutMainLoop();

    return 0;
}

