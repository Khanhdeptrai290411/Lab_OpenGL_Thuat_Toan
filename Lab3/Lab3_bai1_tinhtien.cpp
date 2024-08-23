#include <GL/glut.h>

// T?a d? các d?nh c?a hình vuông
GLfloat toadodinh[3][2] = {
    {100.0, 100.0},
    {200.0, 100.0},
    {200.0, 200.0},
   // {100.0, 200.0}
};

// Véc to t?nh ti?n ban d?u
GLfloat tx = 20.0;
GLfloat ty = 20.0;

// Véc to t?nh ti?n hi?n t?i
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

    // V? hình ban d?u
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        for (int i = 0; i < 4; ++i) {
            glVertex2f(toadodinh[i][0], toadodinh[i][1]);
        }
    glEnd();

    // Tính toán và v? hình sau khi t?nh ti?n
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
        case 'w': // T?nh ti?n lên
            currentTy += ty;
            break;
        case 's': // T?nh ti?n xu?ng
            currentTy -= ty;
            break;
        case 'a': // T?nh ti?n trái
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
    glutPostRedisplay(); // G?i l?i hàm display d? v? l?i hình
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Phép bien doi 2D - Tinh Tien");

    khoitao();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); // Ðang ký hàm x? lý bàn phím
    glutMainLoop();

    return 0;
}

