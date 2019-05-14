#include <GL/glut.h>
#include <GL/gl.h>
#define WIDTH 800
#define HEIGHT 600

static void drawFace(GLfloat v[4][3], GLfloat RGB[3]){
		glColor3f(RGB[0], RGB[1], RGB[2]);
		glBegin(GL_QUADS);
			for(int j = 0; j < 4; j++){
				glVertex3d(v[j][0], v[j][1], v[j][2]);
			}
		glEnd();
}

class cube{
public:
	GLfloat x, y, z, xRotate, yRotate, revolution, vertexes[6][4][3], RGB[6][3], zTrans;
	GLfloat xRo = 0, yRo = 0, rRe = 0;
	cube(GLfloat x, GLfloat y, GLfloat z, GLfloat xRotate, GLfloat yRotate, GLfloat revolution, GLfloat zTrans){
		this->x = x;
		this->y = y;
		this->z = z;
		this->xRotate = xRotate;
		this->yRotate = yRotate;
		this->revolution = revolution;
		this->zTrans = zTrans;

		GLfloat lvertexes[6][4][3] = {
			{{x, y, z}, {x, -y, z}, {-x, -y, z}, {-x, y, z}},
			{{x, y, -z}, {x, -y, -z}, {-x, -y, -z}, {-x, y, -z}},
			{{x, y, z}, {-x, y, z}, {-x, y, -z}, {x, y, -z}},
			{{x, -y, z}, {-x, -y, z}, {-x, -y, -z}, {x, -y, -z}},
			{{x, y, z}, {x, -y, z}, {x, -y, -z}, {x, y, -z}},
			{{-x, y, z}, {-x, -y, z}, {-x, -y, -z}, {-x, y, -z}}
		};
		GLfloat lRGB[6][3] = {
			{0, 0, 0}, {0.1f, 0.5f, 0.3f}, {0.4f, 0.3f, 0.5f}, {0.5f, 0.3f, 0.2f}, {0.2f, 0.2f, 0.2f}, {1.f, 1.f, 1.f}
		};
		for(int i = 0; i < 6; i++){
			for(int j = 0; j < 4; j++){
				for(int k = 0; k < 3; k++){
					vertexes[i][j][k] = lvertexes[i][j][k];
					RGB[i][k] = lRGB[i][k];
				}
			}
		}
	}
	void update(){
		glPushMatrix();
			glRotatef(rRe += this->revolution, 0.0f, 1.0f, 0.0f);
			glTranslatef(0, 0, this->zTrans);
			glRotatef(xRo += this->xRotate, 1.0f, 0.0f, 0.0f);
			glRotatef(yRo += this->yRotate, 0.0f, 1.0f, 0.0f);
			for(int i = 0; i < 6; i++){
				drawFace(this->vertexes[i], this->RGB[i]);
			}
		glPopMatrix();
	}
};

cube sol = cube(1.5f, 1.5f, 1.5f, 0, 3, 0, 0);
cube terra = cube(1.f, 1.f, 1.f, 1, 0, -1, 15);

void display(){
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	sol.update();
	terra.update();

	glFlush();
	glutSwapBuffers();
}

int main(int argc, char **argv){
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("OpenGL Cube");

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, (GLsizei)WIDTH, (GLsizei)HEIGHT);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 100.0);
	glTranslatef(0, -8.0, -30.0f); // "ALTERA" VISÃO DA "CAMERA"

	glMatrixMode(GL_MODELVIEW);
	glutDisplayFunc(display);
	glutIdleFunc(display);

	glutMainLoop();

	return 0;
}
