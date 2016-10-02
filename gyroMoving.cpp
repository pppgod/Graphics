#include <gl/glaux.h>
#include <gl/glut.h>
#include <math.h>

#define GL_PI 3.1415f
#define GL_GRAVITY 9.8f

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

AUX_RGBImageRec * texRec;
GLuint texID;

GLfloat window_width;
GLfloat window_height;
GLfloat point = 1.0f;

extern void animate();

void circle(GLfloat rad)
{
	glPushMatrix();
	glBegin(GL_POLYGON);   //relocated (vertex drawing)
	GLfloat angle, x, y, z = 0.0f;
	for (angle = 0.0f; angle <= (2.0f*GL_PI); angle += 0.1f){
		x = rad*sin(angle);
		y = rad*cos(angle);
		glVertex3f(x, y, z);
	}
	glEnd();                      //relocated
	glPopMatrix();
}

void SetupRC()
{
	GLfloat ambientLight[] = { 0.9f, 0.9f, 0.9f, 0.9f }; //ambient light

	glEnable(GL_LIGHTING);   // Enable lighting	

	// Set light model to use ambient light specified by ambientLight
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	glEnable(GL_COLOR_MATERIAL);// Enable Material color tracking

	// Front material ambient and diffuse colors track glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glShadeModel(GL_FLAT); // add
	glFrontFace(GL_CW);    // add 
}

/*
x1:왼쪽 x2:오른쪽
아래 y1:위쪽 y2:아래쪽 /위 x3: 왼쪽 x4:오른쪽
fZ:아랫면 bZ:윗면
*/
void glColumn2(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2, GLfloat y3, GLfloat y4, GLfloat fZ, GLfloat bZ)
{
	glPushMatrix();
	glBegin(GL_QUADS);
	////////////////////////////////////////// 밑면
	glVertex3f(x1, y1, fZ);	//v1  
	glVertex3f(x2, y1, fZ);	//v4
	glVertex3f(x2, y2, fZ);	//v3
	glVertex3f(x1, y2, fZ);		//v2
	///////////////////////////////////////////앞면
	glVertex3f(x1, y4, bZ);//v6
	glVertex3f(x1, y2, fZ);//v2
	glVertex3f(x2, y2, fZ);//v3
	glVertex3f(x2, y4, bZ);//v7
	///////////////////////////////////////////좌측면
	glVertex3f(x1, y3, bZ);	//v5  
	glVertex3f(x1, y1, fZ);	//v1
	glVertex3f(x1, y2, fZ);		//v2
	glVertex3f(x1, y4, bZ);	//v6
	///////////////////////////////////////////우측면
	glVertex3f(x2, y4, bZ);	//v7
	glVertex3f(x2, y2, fZ);	//v3
	glVertex3f(x2, y1, fZ);	//v4
	glVertex3f(x2, y3, bZ);	//v8
	///////////////////////////////////////////뒷면
	glVertex3f(x2, y3, bZ);//v8
	glVertex3f(x2, y1, fZ);//v4
	glVertex3f(x1, y1, fZ);//v1
	glVertex3f(x1, y3, bZ);//v5
	///////////////////////////////////////////윗면
	glVertex3f(x1, y3, bZ);	//v5
	glVertex3f(x1, y4, bZ);	//v6
	glVertex3f(x2, y4, bZ);	//v7
	glVertex3f(x2, y3, bZ);	//v8
	////////////////////////////////////////////
	glEnd();
	glPopMatrix();
}

/*
x1 : 가까운 면 가로/2, y1 : 가까운 면 세로/2
x2 : 먼 면 가로/2, y2 : 먼 면 세로/2
z : 높이
*/
void glColumn(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat z)
{
	glPushMatrix();
	glBegin(GL_QUADS);
	///////////////////////////////가까운면
	glVertex3f(-x1, y1, 0.0f); //v1
	glVertex3f(-x1, -y1, 0.0f); //v3
	glVertex3f(x1, -y1, 0.0f); //v4
	glVertex3f(x1, y1, 0.0f); //v2
	///////////////////////////////먼면
	glVertex3f(-x2, y2, z); //v5
	glVertex3f(x2, y2, z); //v6
	glVertex3f(x2, -y2, z); //v8
	glVertex3f(-x2, -y2, z); //v7
	///////////////////////////////좌측면
	glVertex3f(-x1, y1, 0.0f); //v1
	glVertex3f(-x2, y2, z); //v5
	glVertex3f(-x2, -y2, z); //v7
	glVertex3f(-x1, -y1, 0.0f); //v3
	///////////////////////////////우측면
	glVertex3f(x2, y2, z); //v6
	glVertex3f(x1, y1, 0.0f); //v2
	glVertex3f(x1, -y1, 0.0f); //v4
	glVertex3f(x2, -y2, z); //v8
	///////////////////////////////윗면
	glVertex3f(-x2, y2, z); //v5
	glVertex3f(-x1, y1, 0.0f); //v1
	glVertex3f(-x2, -y2, z); //v7
	glVertex3f(x2, y2, z); //v6
	///////////////////////////////밑면
	glVertex3f(x1, -y1, 0.0f); //v4
	glVertex3f(-x1, -y1, 0.0f); //v3
	glVertex3f(x1, y1, 0.0f); //v2
	glVertex3f(x2, -y2, z); //v8
	glEnd();
	glPopMatrix();
}

//원기둥
void cylinder()
{
	glPushMatrix();
	glBegin(GL_QUADS); //add
	GLfloat angle, x, y, z = 0.0f;
	for (angle = 0.0f; angle <= 2.0f*GL_PI; angle += 0.1f){
		x = 30.0f*sin(angle);
		y = 30.0f*cos(angle);
		glVertex3f(x, y, z - 20.0f);
		glVertex3f(x, y, z + 20.0f);
		x = 30.0f*sin(angle + 0.1f);
		y = 30.0f*cos(angle + 0.1f);
		glVertex3f(x, y, z + 20.0f);
		glVertex3f(x, y, z - 20.0f);
	}
	glEnd();
	glPopMatrix();
}
//움직이는 원
void gyroCircle()
{
	static GLfloat rotate = 0.0f;
	glPushMatrix();
	glRotated(rotate, 0.0f, 0.0f, 1.0f);
	glColor3ub(255, 94, 0);
	glutSolidTorus(5.0f, 50.0f, 30, 15);
	glBegin(GL_LINES); //add
	GLfloat angle, x, y, z = 0.0f;
	z = 0.0f;
	for (angle = 0.0f; angle < GL_PI; angle += (GL_PI / 20.0f))	// add - 20개의 line drawing
	{
		x = 50.0f*sin(angle);
		y = 50.0f*cos(angle);
		glVertex3f(x, y, z);
		x = 50.0f*sin(angle + GL_PI);
		y = 50.0f*cos(angle + GL_PI);
		glVertex3f(x, y, z);
	}
	glEnd();
	glBegin(GL_POLYGON);   //relocated (vertex drawing)
	for (angle = 0.0f; angle <= (2.0f*GL_PI)*3.0f; angle += 0.1f){
		x = 10.0f*sin(angle);
		y = 10.0f*cos(angle);
		glVertex3f(x, y, z);
	}
	glEnd();                      //relocated
	rotate += 2.0f;
	glPopMatrix();
}

void gyroPivot()
{
	static GLfloat rotate = 0.0f, rotStep = 7.5f, acc = 0.3f;
	glPushMatrix();
	glRotated(rotate, 1.0f, 0, 0);
	glPushMatrix();
	glRotated(90.0f, 1.0f, 0, 0);

	glPushMatrix();
	glColor3ub(75, 75, 75);
	glRotated(90, 0, 1.0f, 0);
	cylinder();
	glPopMatrix();
	glColor3ub(255, 30, 30);
	glTranslated(0, 0, 25);
	glColumn(20.0f, 20.0f, 5.0f, 5.0f, 200.0f);
	glPopMatrix();
	glTranslated(0, -25, 0);
	if (rotate > 0.0f && acc > 0.0f)
		acc = -acc;
	else if (rotate < 0.0f && acc < 0.0f)
		acc = -acc;
	rotStep += acc;
	rotate += rotStep;
	glPushMatrix();
	glTranslated(0, -200.0f, 0);
	glRotated(90.0f, 1.0f, 0, 0);
	gyroCircle();
	glPopMatrix();
	glPopMatrix();
}

//자이로스윙
void gyroswing()
{
	glPushMatrix();
	glColor3ub(150, 30, 30);
	glTranslated(80, 0, -5);
	glRotated(90, 0, 1, 0);
	circle(40.0f);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(150, 30, 30);
	glTranslated(-80, 0, -5);
	glRotated(-90, 0, 1, 0);
	circle(40.0f);
	glPopMatrix();
	glPushMatrix();
	gyroPivot();
	glPushMatrix();
	glTranslated(-40, 0, -45);
	glColumn(20, 30, 20, 30, 85);
	glPopMatrix();
	glPushMatrix();
	glTranslated(40, 0, -45);
	glColumn(20, 30, 20, 30, 85);
	glPopMatrix();
	glPushMatrix();
	glColor3ub(237, 210, 0);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glTranslated(0, 0, -20.0f);
	glColumn2(-75.0f, -60.0f, 15.0f, 0.0f, -150.0f, -135.0f, 70.0f, -250.0f); //좌측기둥
	glColumn2(-75.0f, -60.0f, 15.0f, 0.0f, 165.0f, 150.0f, 70.0f, -250.0f); //좌측기둥
	glColumn2(55.0f, 70.0f, 15.0f, 0.0f, -150.0f, -135.0f, 70.0f, -250.0f); //우측기둥
	glColumn2(55.0f, 70.0f, 15.0f, 0.0f, 165.0f, 150.0f, 70.0f, -250.0f); //우측기둥
	glPopMatrix();
	glPopMatrix();
}

//바닥 그리기
void floor()
{
	glPushMatrix();
	glRotated(-90, 1, 0, 0);
	texRec = auxDIBImageLoad("grass.bmp");
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texRec->sizeX, texRec->sizeY, 0, GL_RGB,
		GL_UNSIGNED_BYTE, texRec->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glEnable(GL_TEXTURE_2D); 	//glColor3f(0.4f, 1.0f, 0.4f);
	glBegin(GL_POLYGON);   //relocated (vertex drawing)
	GLfloat angle, x, y, z = 0.0f;
	for (angle = 0.0f; angle <= (2.0f*GL_PI); angle += 0.1f){
		x = 200.0f*sin(angle);
		y = 200.0f*cos(angle);
		glVertex3f(x, y, z);
	}
	glEnd();                      //relocated
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void RenderScene()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	
	glPushMatrix();
	glRotated(20, 1, 0, 0);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	
	glNormal3f(0.0f, 0.0f, -1.0f);
	floor();
	glScaled(0.4f, 0.4f, 0.4f);
	glColor3ub(150, 150, 150);
	animate();
	glTranslated(200, -150, 30);
	glScaled(0.5f, 0.5f, 0.5f);
	glTranslated(0, 550, 0);
	gyroswing();
	glPopMatrix();
	glutSwapBuffers();
}

void KeyControl(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;

	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if (key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if (key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	glutPostRedisplay();

}

void ChangeSize(int w, int h)
{

	GLfloat fAspect;

	glViewport(0, 0, w, h);

	fAspect = (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, fAspect, 1.0f, 500.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -150.0f); //
}

void TimerFunction(int value) //콜백함수로 호출
{
	glutPostRedisplay(); // 다시 그리기
	glutTimerFunc(33, TimerFunction, 1);
}

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |
		GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 800);
	glutCreateWindow("제 2 롯데월드");

	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(KeyControl);
	glutDisplayFunc(RenderScene);
	glutTimerFunc(2000, TimerFunction, 1);
	SetupRC();
	glutMainLoop();

}









