#include <algorithm>
#include <gl/glaux.h>
#include <gl/glut.h>
#include <math.h>
using std::min;

#define GL_PI 3.1415f
#define GL_GRAVITY 9.8f

void trackSet()
{
	glPushMatrix();
	glColor3ub(100, 100, 100);
	glTranslated(15.0f, 0, 0);
	glBegin(GL_QUADS); //add
	GLfloat angle, x, y, z = 0.0f;
	for (angle = 0.0f; angle <= 2.0f*GL_PI; angle += 0.1f){
		x = 3.0f*sin(angle);
		y = 3.0f*cos(angle);
		glVertex3f(x, y, z);
		glVertex3f(x, y, z + 40.0f);
		x = 3.0f*sin(angle + 0.1f);
		y = 3.0f*cos(angle + 0.1f);
		glVertex3f(x, y, z + 40.0f);
		glVertex3f(x, y, z);
	}
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslated(-15.0f, 0, 0);
	glBegin(GL_QUADS); //add
	for (angle = 0.0f; angle <= 2.0f*GL_PI; angle += 0.1f){
		x = 3.0f*sin(angle);
		y = 3.0f*cos(angle);
		glVertex3f(x, y, z - 0);
		glVertex3f(x, y, z + 40.0f);
		x = 3.0f*sin(angle + 0.1f);
		y = 3.0f*cos(angle + 0.1f);
		glVertex3f(x, y, z + 40.0f);
		glVertex3f(x, y, z - 0);
	}
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslated(0, 0, 7);
	glRotated(90.0f, 1, 0, 0);
	glColor3ub(186, 96, 43);
	glBegin(GL_QUADS); //add

	glVertex3f(15, 5, 0);
	glVertex3f(-15, 5, 0);
	glVertex3f(-15, -5, 0);
	glVertex3f(15, -5, 0);
	glEnd();
	glPopMatrix();
}

void track()
{
	int i;
	glPushMatrix();
	trackSet();

	for (i = 0; i < 30; i++)
	{
		glTranslated(0, 0, 30);	trackSet();
	}
	//오르막
	for (i = 0; i < 4; i++)
	{
		glTranslated(0, 0, 30);	glRotated(15, -1, 0, 0); trackSet();
	}
	for (i = 0; i < 60; i++)
	{
		glTranslated(0, 0, 30);	trackSet();
	}
	//내리막
	for (i = 0; i < 8; i++)
	{
		glTranslated(0, 0, 30);	glRotated(15, 1, 0, 0); trackSet();
	}
	for (i = 0; i < 25; i++)
	{
		glTranslated(0, 0, 30);	trackSet();
	}

	for (i = 0; i < 3; i++)
	{
		glTranslated(0, 0, 30);	glRotated(15, -1, 0, 0); trackSet();
	}
	//나선 내리막
	glTranslated(0, 0, 30);	glRotated(20, 0, 0, -1); trackSet();
	glTranslated(0, 0, 30);	glRotated(20, 0, 0, -1); trackSet();
	glTranslated(0, 0, 30);	glRotated(20, 0, 0, -1); trackSet();
	for (i = 0; i < 30; i++)
	{
		glTranslated(0, 0, 30);	glRotated(5, -1, 0, 0); glRotated(5, 0, 1, 0); trackSet();
	}
	glTranslated(0, 0, 30);	glRotated(20, 0, 0, 1); trackSet();
	glTranslated(0, 0, 30);	glRotated(20, 0, 0, 1); trackSet();
	glTranslated(0, 0, 30);	glRotated(20, 0, 0, 1); trackSet();

	//내리막
	for (i = 0; i < 8; i++)
	{
		glTranslated(0, 0, 30);	glRotated(15, 1, 0, 0); trackSet();
	}
	for (i = 0; i < 15; i++)
	{
		glTranslated(0, 0, 30);	trackSet();
	}
	//평지
	for (i = 0; i < 25; i++)
	{
		glTranslated(0, 0, 30);	glRotated(10, -1, 0, 0); trackSet();
	}
	//회전
	glTranslated(0, 0, 30);	glRotated(20, 0, 0, 1); trackSet();
	for (i = 0; i < 21; i++)
	{
		glTranslated(0, 0, 30);	glRotated(10, -1, 0, 0); trackSet();
	}
	//평지
	for (i = 0; i < 20; i++)
	{
		glTranslated(0, 0, 30);	trackSet();
	}

	//오르막
	for (i = 0; i < 2; i++)
	{
		glTranslated(0, 0, 30);	glRotated(15, -1, 0, 0); trackSet();
	}
	for (i = 0; i < 20; i++)
	{
		glTranslated(0, 0, 30);	trackSet();
	}
	//평지
	for (i = 0; i < 2; i++)
	{
		glTranslated(0, 0, 30);	glRotated(15, 1, 0, 0); trackSet();
	}
	for (i = 0; i < 20; i++)
	{
		glTranslated(0, 0, 30);	trackSet();
	}
	for (i = 0; i < 3; i++)
	{
		glTranslated(0, 0, 30);	glRotated(15, 0, -1, 0); trackSet();
	}
	for (i = 0; i < 20; i++)
	{
		glTranslated(0, 0, 30);	trackSet();
	}
	//내리막
	for (i = 0; i < 2; i++)
	{
		glTranslated(0, 0, 30);	glRotated(20, 1, 0, 0); trackSet();
	}
	glTranslated(0, 0, 30);	glRotated(-1, 1, 0, 0); trackSet();
	for (i = 0; i < 15; i++)
	{
		glTranslated(0, 0, 30);	trackSet();
	}
	//평지
	for (i = 0; i < 2; i++)
	{
		glTranslated(0, 0, 30);	glRotated(20, -1, 0, 0); trackSet();
	}
	for (i = 0; i < 40; i++)
	{
		glTranslated(0, 0, 30);	trackSet();
	}
	for (i = 0; i < 30; i++)
	{
		glTranslated(0, 0, 30);	glRotated(5, 0, -1, 0); trackSet();
	}
	for (i = 0; i < 48; i++)
	{
		glTranslated(0, 0, 30);	trackSet();
	}
	glTranslated(0, 0, 12);	trackSet();
	for (i = 0; i < 6; i++)
	{
		glTranslated(0, 0, 30);	glRotated(5, 0, -1, 0); trackSet();
	}
	glTranslated(0, 0, 30);	glRotated(5, 0, -1, 0); glRotated(4, 1, 0, 0); trackSet();
	glPopMatrix();
}

void train()
{
	glPushMatrix();
	glRotated(-90, 0, 1, 0);
	glRotated(90, -1, 0, 0);
	glPushMatrix();
	glNormal3f(0.0f, 0.0f, 1.0f);
	glColor3ub(150, 150, 150);
	glBegin(GL_QUADS);

	//안
	glColor3ub(150, 15, 15);
	glVertex3f(60, 80, 80);
	glVertex3f(60, 80, 0);
	glVertex3f(60, -80, 0);
	glVertex3f(60, -80, 80);

	//안
	glColor3ub(150, 15, 15);
	glVertex3f(-60, 80, 80);
	glVertex3f(-60, -80, 80);
	glVertex3f(-60, -80, 0);
	glVertex3f(-60, 80, 0);

	glColor3ub(255, 94, 0);
	//밑면
	glVertex3f(100, 80, 0);
	glVertex3f(-100, 80, 0);
	glVertex3f(-100, -80, 0);
	glVertex3f(100, -80, 0);

	//옆
	glVertex3f(100, 80, 80);
	glVertex3f(-100, 80, 80);
	glVertex3f(-100, 80, 0);
	glVertex3f(100, 80, 0);

	//옆
	glVertex3f(100, -80, 0);
	glVertex3f(-100, -80, 0);
	glVertex3f(-100, -80, 80);
	glVertex3f(100, -80, 80);

	//앞
	glVertex3f(100, 80, 0);
	glVertex3f(100, -80, 0);
	glVertex3f(100, -80, 80);
	glVertex3f(100, 80, 80);

	//뒤
	glVertex3f(-100, -80, 0);
	glVertex3f(-100, 80, 0);
	glVertex3f(-100, 80, 80);
	glVertex3f(-100, -80, 80);

	//위
	glColor3ub(15, 150, 15);
	glVertex3f(-100, 80, 80);
	glVertex3f(-100, -80, 80);
	glVertex3f(-60, -80, 80);
	glVertex3f(-60, 80, 80);

	//위
	glVertex3f(100, 80, 80);
	glVertex3f(60, 80, 80);
	glVertex3f(60, -80, 80);
	glVertex3f(100, -80, 80);

	//머리 밑면
	glColor3ub(15, 15, 150);
	glVertex3f(200, 80, 0);
	glVertex3f(110, 80, 0);
	glVertex3f(110, -80, 0);
	glVertex3f(200, -80, 0);

	//머리 윗면
	glVertex3f(200, 80, 0);
	glVertex3f(110, 80, 80);
	glVertex3f(110, -80, 80);
	glVertex3f(200, -80, 0);

	//머리 뒷면
	glVertex3f(110, -80, 80);
	glVertex3f(110, 80, 80);
	glVertex3f(110, 80, 0);
	glVertex3f(110, -80, 0);
	glEnd();
	glBegin(GL_TRIANGLES);
	//머리 옆
	glVertex3f(200, -80, 0);
	glVertex3f(110, -80, 0);
	glVertex3f(110, -80, 80);

	//머리 옆
	glVertex3f(200, 80, 0);
	glVertex3f(110, 80, 80);
	glVertex3f(110, 80, 0);

	glEnd();
	glPopMatrix();
	glPopMatrix();
}
void animateTrain()
{
	static int t = 0;
	int i;
	glPushMatrix();

	//30
	for (i = 0; i < min(t, 30); i++)
	{
		glTranslated(0, 0, 30);
	}
	//오르막 34
	for (i = 30; i < min(t, 34); i++)
	{
		glTranslated(0, 0, 30);	glRotated(15, -1, 0, 0);
	}
	//94
	for (i = 34; i < min(t, 94); i++)
	{
		glTranslated(0, 0, 30);
	}
	//내리막 102

	for (i = 94; i < min(t, 102); i++)
	{
		glTranslated(0, 0, 30);	glRotated(15, 1, 0, 0);
		if (i == 94) t++;
	}
	//127
	for (i = 102; i < min(t, 127); i++)
	{
		glTranslated(0, 0, 30);
		if (i == 102 || i == 120 || i == 127) t++;
	}
	//130
	for (i = 127; i < min(t, 130); i++)
	{
		glTranslated(0, 0, 30);	glRotated(15, -1, 0, 0);
	}
	//나선 내리막
	//133
	for (i = 130; i < min(t, 133); i++)
	{
		glTranslated(0, 0, 30);	glRotated(20, 0, 0, -1);
	}
	//163
	for (i = 133; i < min(t, 163); i++)
	{
		glTranslated(0, 0, 30);	glRotated(5, -1, 0, 0); glRotated(5, 0, 1, 0);
	}
	//166
	for (i = 163; i < min(t, 166); i++)
	{
		glTranslated(0, 0, 30);	glRotated(20, 0, 0, 1);
	}
	//내리막 174
	for (i = 166; i < min(t, 174); i++)
	{
		glTranslated(0, 0, 30);	glRotated(15, 1, 0, 0);
	}
	//189
	for (i = 174; i < min(t, 189); i++)
	{
		glTranslated(0, 0, 30);
	}
	//평지 214
	for (i = 189; i < min(t, 214); i++)
	{
		glTranslated(0, 0, 30);	glRotated(10, -1, 0, 0);
	}
	//회전 215
	for (i = 214; i < min(t, 215); i++)
	{
		glTranslated(0, 0, 30);	glRotated(20, 0, 0, 1);
	}
	//236
	for (i = 215; i < min(t, 236); i++)
	{
		glTranslated(0, 0, 30);	glRotated(10, -1, 0, 0);
		if (i == 215) t--;
		if (i == 220) t--;
		if (i == 230) t++;
	}
	//평지 256
	for (i = 236; i < min(t, 256); i++)
	{
		glTranslated(0, 0, 30);
	}

	//오르막 258
	for (i = 256; i < min(t, 258); i++)
	{
		glTranslated(0, 0, 30);	glRotated(15, -1, 0, 0);
		if (i == 256) t--;
	}
	//278
	for (i = 258; i < min(t, 278); i++)
	{
		glTranslated(0, 0, 30);
	}
	//평지 280
	for (i = 278; i < min(t, 280); i++)
	{
		glTranslated(0, 0, 30);	glRotated(15, 1, 0, 0);
	}
	//300
	for (i = 280; i < min(t, 300); i++)
	{
		glTranslated(0, 0, 30);
	}
	//303
	for (i = 300; i < min(t, 303); i++)
	{
		glTranslated(0, 0, 30);	glRotated(15, 0, -1, 0);
	}
	//323
	for (i = 303; i < min(t, 323); i++)
	{
		glTranslated(0, 0, 30);
	}
	//내리막 //325
	for (i = 323; i < min(t, 325); i++)
	{
		glTranslated(0, 0, 30);	glRotated(20, 1, 0, 0);
		if (i == 323) t++;
	}
	//326
	for (i = 325; i < min(t, 326); i++)
	{
		glTranslated(0, 0, 30);	glRotated(-1, 1, 0, 0);
	}
	//341
	for (i = 326; i < min(t, 341); i++)
	{
		glTranslated(0, 0, 30);
		if (i == 335) t++;
	}
	//평지 343
	for (i = 341; i < min(t, 343); i++)
	{
		glTranslated(0, 0, 30);	glRotated(20, -1, 0, 0);
	}
	//383
	for (i = 343; i < min(t, 383); i++)
	{
		glTranslated(0, 0, 30);
	}
	//413
	for (i = 383; i < min(t, 413); i++)
	{
		glTranslated(0, 0, 30);	glRotated(5, 0, -1, 0);
	}
	//461
	for (i = 413; i < min(t, 461); i++)
	{
		glTranslated(0, 0, 30);
	}
	//462
	for (i = 461; i < min(t, 462); i++)
	{
		glTranslated(0, 0, 12);
	}
	//468
	for (i = 462; i < min(t, 468); i++)
	{
		glTranslated(0, 0, 30);	glRotated(5, 0, -1, 0);
	}
	//469
	for (i = 468; i < min(t, 469); i++){
		glTranslated(0, 0, 30);	glRotated(5, 0, -1, 0); glRotated(4, 1, 0, 0);
	}
	glScaled(0.3f, 0.5f, 0.5f);
	train();
	t++;
	if (t > 469) t = 0;
	glPopMatrix();
}
void animate()
{
	glPushMatrix();
	glScaled(0.1f, 0.1f, 0.1f);
	track();
	glPushMatrix();
	animateTrain();
	glPopMatrix();
	glPopMatrix();
}