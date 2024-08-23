#include <GL/glut.h>
#include <math.h>

// Bi?n toàn c?c ð? lýu các giá tr? bi?n ð?i
float tx = 0.0f, ty = 0.0f;
float sx = 1.0f, sy = 1.0f;
float angle = 0.0f;
float reflect_a = 1.0f, reflect_b = 0.0f;

void MaTran(float mat[3][3], float vec[3], float result[3]) {
    for (int i = 0; i < 3; i++) {
        result[i] = 0;
        for (int j = 0; j < 3; j++) {
            result[i] += mat[i][j] * vec[j];
        }
    }
}

void MaTranTinhTien(float tx, float ty, float mat[3][3]) {
    mat[0][0] = 1; mat[0][1] = 0; mat[0][2] = tx;
    mat[1][0] = 0; mat[1][1] = 1; mat[1][2] = ty;
    mat[2][0] = 0; mat[2][1] = 0; mat[2][2] = 1;
}

void MaTranChuyenDoi(float sx, float sy, float mat[3][3]) {
    mat[0][0] = sx; mat[0][1] = 0;  mat[0][2] = 0;
    mat[1][0] = 0;  mat[1][1] = sy; mat[1][2] = 0;
    mat[2][0] = 0;  mat[2][1] = 0;  mat[2][2] = 1;
}

void MaTranXoay(float angle, float mat[3][3]) {
    float rad = angle * M_PI / 180.0;
    mat[0][0] = cos(rad); mat[0][1] = -sin(rad); mat[0][2] = 0;
    mat[1][0] = sin(rad); mat[1][1] = cos(rad);  mat[1][2] = 0;
    mat[2][0] = 0;        mat[2][1] = 0;         mat[2][2] = 1;
}

void MaTranDoiXung(float a, float b, float mat[3][3]) {
    float angle = atan(a);
    float rad = angle;
    float reflectMat[3][3] = {
        {-1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    float rotateMat[3][3];
    float rotateBackMat[3][3];

    MaTranXoay(-angle * 180 / M_PI, rotateMat);
    MaTranXoay(angle * 180 / M_PI, rotateBackMat);

    float tempMat1[3][3] = {0};
    float tempMat2[3][3] = {0};

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            for (int k = 0; k < 3; ++k)
                tempMat1[i][j] += rotateMat[i][k] * reflectMat[k][j];

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            for (int k = 0; k < 3; ++k)
                tempMat2[i][j] += tempMat1[i][k] * rotateBackMat[k][j];

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            mat[i][j] = tempMat2[i][j];
}

void applyTransformation(float mat[3][3], float vertices[4][2]) {
    for (int i = 0; i < 4; i++) {
        float vec[3] = {vertices[i][0], vertices[i][1], 1};
        float result[3];
        MaTran(mat, vec, result);
        vertices[i][0] = result[0];
        vertices[i][1] = result[1];
    }
}

void drawTransformedSquare(float r, float g, float b) {
    float vertices[4][2] = {
        {-0.5, -0.5},
        {0.5, -0.5},
        {0.5, 0.5},
        {-0.5, 0.5}
    };

    float transformationMat[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    float tempMat[3][3];

    MaTranTinhTien(tx, ty, tempMat);
    applyTransformation(tempMat, vertices);

    MaTranChuyenDoi(sx, sy, tempMat);
    applyTransformation(tempMat, vertices);

    MaTranXoay(angle, tempMat);
    applyTransformation(tempMat, vertices);

    MaTranDoiXung(reflect_a, reflect_b, tempMat);
    applyTransformation(tempMat, vertices);

    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    for (int i = 0; i < 4; i++) {
        glVertex2f(vertices[i][0], vertices[i][1]);
    }
    glEnd();
}

void drawAxes() {
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-5.0, 0.0);
    glVertex2f(5.0, 0.0);
    glVertex2f(0.0, -5.0);
    glVertex2f(0.0, 5.0);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();

    drawTransformedSquare(1.0, 0.0, 0.0);

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 't':
            tx += 0.1f;
            break;
        case 'T':
            tx -= 0.1f;
            break;
        case 'y':
            ty += 0.1f;
            break;
        case 'Y':
            ty -= 0.1f;
            break;
        case 's':
            sx += 0.1f;
            sy += 0.1f;
            break;
        case 'S':
            sx -= 0.1f;
            sy -= 0.1f;
            break;
        case 'r':
            angle += 5.0f;
            break;
        case 'R':
            angle -= 5.0f;
            break;
        case 'f':
            reflect_a = -reflect_a;
            break;
        case 'F':
            reflect_a = -reflect_a;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D Transformations Example");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-5.0, 5.0, -5.0, 5.0);
    glMatrixMode(GL_MODELVIEW);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

