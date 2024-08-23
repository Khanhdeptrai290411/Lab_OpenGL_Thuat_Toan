#include <GL/glut.h>
#include <cmath>

int xc = 0, yc = 0; // T�m ��?ng tr?n
int x_b = 0, y_b = 0; // �i?m n?m tr�n ��?ng tr?n
bool firstClick = true; // Bi?n ki?m tra l?n click �?u ti�n

void initGL()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // M�u n?n tr?ng
	glOrtho(-320, 320, -240, 240, -1, 1); // Thi?t l?p kh�ng gian nh?n
}

void draw8point(int xc, int yc, int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(xc + x, yc + y);
	glVertex2i(xc + y, yc + x);
	glVertex2i(xc + y, yc - x);
	glVertex2i(xc + x, yc - y);
	glVertex2i(xc - x, yc - y);
	glVertex2i(xc - y, yc - x);
	glVertex2i(xc - y, yc + x);
	glVertex2i(xc - x, yc + y);
	glEnd();
}

void CircleMidpoint(int xc, int yc, int R)
{
	float P = 5.0 / 4.0 - R;
	int y = R;
	int x = 0;
	draw8point(xc, yc, x, y);
	while (x <= y)
	{
		if (P < 0)
		{
			P += 2 * x + 3;
		}
		else
		{
			P += 2 * (x - y) + 5;
			y--;
		}
		x++;
		draw8point(xc, yc, x, y);
	}
}

void mydisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0); // M�u �?

	if (!firstClick)
	{
		int R = sqrt((x_b - xc) * (x_b - xc) + (y_b - yc) * (y_b - yc)); // T�nh b�n k�nh t? t�m �?n �i?m n?m tr�n ��?ng tr?n
		CircleMidpoint(xc, yc, R); // V? ��?ng tr?n
	}

	glViewport(0, 0, 640, 480); // Khung nh?n
	glFlush();
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (firstClick)
		{
			xc = x - 320; // Chuy?n t?a �? chu?t v? kh�ng gian tr?c t?a �?
			yc = 240 - y;
			firstClick = false;
		}
		else
		{
			x_b = x - 320; // Chuy?n t?a �? chu?t v? kh�ng gian tr?c t?a �?
			y_b = 240 - y;
			firstClick = true;
			glutPostRedisplay();
		}
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // Kh?i t?o GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 0);
	glutCreateWindow("DEMO THUAT TOAN VE DUONG TRON - MIDPOINT");

	initGL();
	glutDisplayFunc(mydisplay);
	glutMouseFunc(mouse);

	glutMainLoop(); // V?ng l?p ch�nh c?a GLUT
	return 0;
}

