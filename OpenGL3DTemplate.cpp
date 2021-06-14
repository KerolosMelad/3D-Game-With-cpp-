#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <gl/glut.h>
#include <string>
#include<time.h>
#include <iostream>
#include<windows.h>

//----------------------------------------
double r;
double g;
double b;
int t = 0;

double Goalx;
double Goaly;
double scaleUmbrella = 0;
double scaleFlower = 0;
double scaleTree = 0;
double scaleGrass = 0;
double scalepoolx = 0;
double scalewall = 0;


bool flowertick = false;
bool walltick = false;
bool grasstick = false;
bool umbrellatick = false;
bool treetick = false;
bool pooltick = false;
bool win = false;
double playerx = 0;
double playery = 0.6;
//--------
#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)


class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f& v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f& v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};
void setupLights() {
	GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
	GLfloat shininess[] = { 50 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
	GLfloat lightPosition[] = { -7.0f, 6.0f, 3.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}

// done

class Camera {
public:
	Vector3f eye, center, up;

	Camera(float eyeX = 0.0f, float eyeY = 1.0f, float eyeZ = 0.9f, float centerX = 0.0f, float centerY = 0.0f, float centerZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
	}

	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
	}

	void moveY(float d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
	}

	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	void rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	void look() {
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}
};

Camera camera;

void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 640 / 480, 0.001, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}
void drawground() {

	// done with one primotive
	glPushMatrix();
	glColor3f(0.1, 0.7, 0.3);
	glTranslated(0, 0, 0);
	glScaled(1.3, 0.07, 1.3);
	glutSolidCube(1.0);
	glPopMatrix();

}
void drawflower1() {
	glColor3f(0.1, 0.9, 0.9);
	glTranslated(0.2, 0.05, 0.2);
	glScaled(0.009, 0.1, 0.009);
	glutSolidCube(1.0);



	glColor3f(1, 0.5, 0.3);
	glTranslated(0.1, 0.4, 0.1);
	glScaled(1, 0.08, 1);
	glutSolidSphere(2, 22, 22);

	glColor3f(1, 0, 0);

	glTranslated(2, 0.4, 1);
	glScaled(1, 0.08, 1);
	glutSolidSphere(1, 22, 22);



	glTranslated(0, 0.4, -2);
	glScaled(1, 0.08, 1);
	glutSolidSphere(1, 22, 22);



	glTranslated(-2, 0.4, 3.7);
	glScaled(1, 0.08, 1);
	glutSolidSphere(1, 22, 22);

	glTranslated(-1, 0.4, -1.4);
	glScaled(1, 0.08, 1);
	glutSolidSphere(1, 22, 22);

	glTranslated(-0.7, 0.4, -1.6);
	glScaled(1, 0.08, 1);
	glutSolidSphere(1, 22, 22);

}
void drawflower2() {
	glColor3f(0.1, 0.9, 0.9);
	glTranslated(0.5, 0.05, 0.1);
	glScaled(0.009, 0.1, 0.009);
	glutSolidCube(1.0);
	glColor3f(1, 0.5, 0.3);
	glTranslated(0.1, 0.4, 0.1);
	glScaled(1, 0.08, 1);
	glutSolidSphere(2, 22, 22);

	glColor3f(1, 0, 0);

	glTranslated(2, 0.4, 1);
	glScaled(1, 0.08, 1);
	glutSolidSphere(1, 22, 22);



	glTranslated(0, 0.4, -2);
	glScaled(1, 0.08, 1);
	glutSolidSphere(1, 22, 22);



	glTranslated(-2, 0.4, 3.7);
	glScaled(1, 0.08, 1);
	glutSolidSphere(1, 22, 22);

	glTranslated(-1, 0.4, -1.4);
	glScaled(1, 0.08, 1);
	glutSolidSphere(1, 22, 22);

	glTranslated(-0.7, 0.4, -1.6);
	glScaled(1, 0.08, 1);
	glutSolidSphere(1, 22, 22);



}

void drawFence1() {


	glTranslated(0, 0.09, -0.6);
	glScaled(1.3, 0.05, 0.02);
	glutSolidCube(1.0);



}

void drawFence1p() {
	glColor3f(r, g, b);
	glTranslated(0, 0.2, -0.6);
	glScaled(1.3, 0.05, 0.02);
	glutSolidCube(1.0);
}

void drawFence11() {
	glColor3f(r, g, b);
	glTranslated(0, 0.13, -0.6);
	glScaled(0.04, 0.3, 0.02);
	glutSolidCube(1.0);




}

void drawFence12() {
	glColor3f(r, g, b);
	glTranslated(-0.6, 0.13, -0.6);
	glScaled(0.04, 0.3, 0.02);
	glutSolidCube(1.0);




}


void drawFence13() {
	glColor3f(r, g, b);
	glTranslated(0.6, 0.13, -0.6);
	glScaled(0.04, 0.3, 0.02);
	glutSolidCube(1.0);




}


void drawFence14() {
	glColor3f(r, g, b);
	glTranslated(0.3, 0.13, -0.6);
	glScaled(0.04, 0.3, 0.02);
	glutSolidCube(1.0);




}

void drawGoal() {
	glColor3f(1, 1, 0);
	glutWireSphere(1, 20, 20);
}
void drawFence15() {
	glColor3f(r, g, b);
	glTranslated(-0.3, 0.13, -0.6);
	glScaled(0.04, 0.3, 0.02);
	glutSolidCube(1.0);




}






void drawFence2() {

	glColor3f(r, g, b);
	glTranslated(-0.6, 0.09, 0);
	glScaled(0.02, 0.05, 1.3);
	glutSolidCube(1.0);



}

void drawFence2p() {
	glColor3f(r, g, b);
	glTranslated(-0.6, 0.2, 0);
	glScaled(0.02, 0.05, 1.3);
	glutSolidCube(1.0);
}

void drawFence21() {
	glColor3f(r, g, b);
	glTranslated(-0.6, 0.13, 0);
	glScaled(0.02, 0.3, 0.04);
	glutSolidCube(1.0);




}

void drawFence22() {
	glColor3f(r, g, b);
	glTranslated(-0.6, 0.13, -0.6);
	glScaled(0.02, 0.3, 0.04);
	glutSolidCube(1.0);




}


void drawFence23() {
	glColor3f(r, g, b);
	glTranslated(-0.6, 0.13, 0.6);
	glScaled(0.02, 0.3, 0.04);
	glutSolidCube(1.0);




}


void drawFence24() {
	glColor3f(r, g, b);
	glTranslated(-0.6, 0.13, 0.3);
	glScaled(0.02, 0.3, 0.04);
	glutSolidCube(1.0);




}


void drawFence25() {
	glColor3f(r, g, b);
	glTranslated(-0.6, 0.13, -0.3);
	glScaled(0.02, 0.3, 0.04);
	glutSolidCube(1.0);




}



void drawFence3() {

	glColor3f(r, g, b);
	glTranslated(0.6, 0.2, 0);
	glScaled(0.02, 0.05, 1.3);
	glutSolidCube(1.0);



}

void drawFence3p() {
	glColor3f(r, g, b);
	glTranslated(0.6, 0.13, 0);
	glScaled(0.02, 0.05, 1.3);
	glutSolidCube(1.0);
}

void drawFence31() {
	glColor3f(r, g, b);
	glTranslated(0.6, 0.13, 0);
	glScaled(0.02, 0.3, 0.04);
	glutSolidCube(1.0);




}

void drawFence32() {
	glColor3f(r, g, b);
	glTranslated(0.6, 0.13, -0.6);
	glScaled(0.02, 0.3, 0.04);
	glutSolidCube(1.0);




}


void drawFence33() {
	glColor3f(r, g, b);
	glTranslated(0.6, 0.13, 0.6);
	glScaled(0.02, 0.3, 0.04);
	glutSolidCube(1.0);




}


void drawFence34() {
	glColor3f(r, g, b);
	glTranslated(0.6, 0.13, 0.3);
	glScaled(0.02, 0.3, 0.04);
	glutSolidCube(1.0);




}


void Drawpool() {
	glColor3f(0.3, 0.6, 1);
	glutSolidCube(1);
}
void Drawpool1() {
	glColor3f(1, 1, 1);
	glutWireCube(1);
}

void drawpool2() {
	glColor3f(0.4, 0.5, 1);
	glutSolidCube(1);
}
void drawpool3() {
	glColor3f(1, 1, 1);
	glutWireCube(1);
}

void drawFence35() {
	glColor3f(r, g, b);
	glTranslated(0.6, 0.13, -0.3);
	glScaled(0.02, 0.3, 0.04);
	glutSolidCube(1.0);




}

void drawGrass2(int x, int y) {

	glColor3f(0.3, 0.6, 0.2);
	glTranslated(x, 0.04, y);
	glScaled(0.01, 0.08, 0.01);
	glutSolidCube(1);




	glTranslated(0, 0.5, 0);
	glRotated(90, 0, 0.6, 0);
	glScaled(0.5, 0.2, 0.5);
	glutSolidCone(2, 2, 20, 15);



	glTranslated(0, 0.5, 0);
	glRotated(-90, 0, 0.6, 0);
	glScaled(0.5, 0.2, 0.5);
	glutSolidCone(2, 2, 20, 15);




}

void DrawUmbrella1() {
	glColor3f(0.5, 0.3, 0.1);
	glutSolidCube(1);
}
void DrawUmbrella2() {
	glColor3f(0.9, 0.8, 0.1);
	glutSolidCone(1, 1, 20, 20);
}

void DrawUmbrella3() {
	glColor3f(0, 0, 0);
	glutWireCone(1, 1, 20, 20);
}
void DrawUmbrella4() {
	glColor3f(0, 0, 0);
	glutWireCube(1);
}


void DrawTree() {
	glScaled(0.02, 0.3, 0.02);
	glColor3f(0.5, 0.3, 0);
	glutSolidCube(1);





}



void DrawTree2() {


	glScaled(0.04, 0.03, 0.04);
	glColor3f(0.4, 0.6, 0);
	glutSolidSphere(1, 20, 20);


}


void Drawplayer() {


	glPushMatrix();
	glScaled(0.05, 0.05, 0.05);
	glColor3f(0.9, 1, 1);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0, 0.05, 0);
	glScaled(0.03, 0.03, 0.03);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.05, 0.05, 0.05);
	glColor3f(0, 0, 0);
	glutWireSphere(1, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0, 0.05, 0);
	glScaled(0.03, 0.03, 0.03);
	glutWireCube(1);
	glPopMatrix();

		
}
void Display() {	

	
	if (t > 50 || win) {
		LPCWSTR sound = L"end.wav";
		PlaySound(sound, NULL, SND_ASYNC | SND_FILENAME);
	}
	else{
	setupCamera();
	setupLights();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	drawground();
	glPopMatrix();

	glPushMatrix();
	glScaled(1, 1+scaleFlower, 1);
	drawflower1();
	glPopMatrix();
	glPushMatrix();
	glScaled(1, 1 + scaleFlower, 1);
	drawflower2();
	glPopMatrix();
	//______________________________
	glPushMatrix();
	glColor3f(r, g, b);
	glScaled(1, 1 + scalewall, 1);

	drawFence1();

	glPopMatrix();


	glPushMatrix();
	glScaled(1, 1 + scalewall, 1);

	drawFence1p();

	glPopMatrix();


	glPushMatrix();	glScaled(1, 1 + scalewall, 1);

	drawFence11();

	glPopMatrix();

	glPushMatrix();	glScaled(1, 1 + scalewall, 1);


	drawFence13();

	glPopMatrix();
	glPushMatrix();
	glScaled(1, 1 + scalewall, 1);

	drawFence12();

	glPopMatrix();


	glPushMatrix();
	glScaled(1, 1 + scalewall, 1);

	drawFence14();

	glPopMatrix();

	glPushMatrix();
	glScaled(1, 1 + scalewall, 1);

	drawFence15();

	glPopMatrix();



	//------------------------- done with first side 









	//______________________________
	glPushMatrix();
	glScaled(1, 1 + scalewall, 1);

	drawFence2();

	glPopMatrix();


	glPushMatrix();
	glScaled(1, 1 + scalewall, 1);

	drawFence2p();

	glPopMatrix();


	glPushMatrix();	glScaled(1, 1 + scalewall, 1);

	drawFence21();

	glPopMatrix();

	glPushMatrix();
	glScaled(1, 1 + scalewall, 1);

	drawFence23();

	glPopMatrix();
	glPushMatrix();
	glScaled(1, 1 + scalewall, 1);

	drawFence22();

	glPopMatrix();


	glPushMatrix();
	glScaled(1, 1 + scalewall, 1);

	drawFence24();

	glPopMatrix();

	glPushMatrix();
	glScaled(1, 1 + scalewall, 1);

	drawFence25();

	glPopMatrix();
	//________________________________________




	glPushMatrix();
	glScaled(1, 1 + scalewall, 1);

	drawFence3();

	glPopMatrix();


	glPushMatrix();
	glScaled(1, 1 + scalewall, 1);

	drawFence3p();

	glPopMatrix();


	glPushMatrix();
	glScaled(1, 1 + scalewall, 1);

	drawFence31();

	glPopMatrix();

	glPushMatrix();
	glScaled(1, 1 + scalewall, 1);

	drawFence33();

	glPopMatrix();
	glPushMatrix();
	glScaled(1, 1 + scalewall, 1);

	drawFence32();

	glPopMatrix();


	glPushMatrix();
	glScaled(1, 1 + scalewall, 1);

	drawFence34();

	glPopMatrix();

	glPushMatrix();
	glScaled(1, 1 + scalewall, 1);

	drawFence35();

	glPopMatrix();


	//---------------------------------------------------------------



	glPushMatrix();
	glScaled(0.5, 1+scaleGrass, 0.5);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.1, 0, 0);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.2, 0, 0);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.3, 0, 0);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.4, 0, 0);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.5, 0, 0);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.6, 0, 0);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.7, 0, 0);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.8, 0, 0);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1, 0.5);
	glTranslated(0.9, 0, 0);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(1, 0, 0);
	drawGrass2(0, 0);
	glPopMatrix();




	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.1, 0, 0);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1+scaleGrass, 0.5);
	glTranslated(-0.2, 0, 0);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.3, 0, 0);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.4, 0, 0);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.5, 0, 0);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1+scaleGrass, 0.5);
	glTranslated(-0.6, 0, 0);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.7, 0, 0);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.8, 0, 0);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.9, 0, 0);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-1, 0, 0);
	drawGrass2(0, 0);
	glPopMatrix();
	//-------------

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);

	glTranslated(0, 0, 0.2);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.1, 0, 0.2);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.2, 0, 0.2);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.3, 0, 0.2);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.4, 0, 0.2);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.5, 0, 0.2);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1+scaleGrass, 0.5);
	glTranslated(0.6, 0, 0.2);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.7, 0, 0.2);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.8, 0, 0.2);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.9, 0, 0.2);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(1, 0, 0.2);
	drawGrass2(0, 0);
	glPopMatrix();




	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.1, 0, 0.2);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.2, 0, 0.2);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.3, 0, 0.2);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.4, 0, 0.2);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.5, 0, 0.2);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.6, 0, 0.2);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1, 0.5);
	glTranslated(-0.7, 0, 0.2);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.8, 0, 0.2);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.9, 0, 0.2);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-1, 0, 0.2);
	drawGrass2(0, 0);
	glPopMatrix();

	//___-


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0, 0, 0.4);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.1, 0, 0.4);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.2, 0, 0.4);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.3, 0, 0.4);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.4, 0, 0.4);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.5, 0, 0.4);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.6, 0, 0.4);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.7, 0, 0.4);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.8, 0, 0.4);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.9, 0, 0.4);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(1, 0, 0.4);
	drawGrass2(0, 0);
	glPopMatrix();




	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.1, 0, 0.4);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.2, 0, 0.4);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.3, 0, 0.4);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.4, 0, 0.4);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.5, 0, 0.4);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.6, 0, 0.4);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.7, 0, 0.4);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.8, 0, 0.4);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.9, 0, 0.4);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-1, 0, 0.4);
	drawGrass2(0, 0);
	glPopMatrix();
	//-------


	double  i = 0.6;



	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.1, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.2, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.3, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.4, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.5, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.6, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.7, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.8, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.9, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(1, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();




	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.1, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.2, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.3, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.4, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.5, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.6, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.7, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.8, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.9, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-1, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	i = 0.8;

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.1, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.2, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.3, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.4, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.5, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.6, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.7, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.8, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.9, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(1, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();




	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.1, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.2, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1, 0.5);
	glTranslated(-0.3, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.4, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1, 0.5);
	glTranslated(-0.5, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.6, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.7, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.8, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.9, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-1, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();
	glPushMatrix();
	glScaled(0.5, 1, 0.5);
	glTranslated(0, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.1, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.2, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.3, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1, 0.5);
	glTranslated(0.4, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.5, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.6, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.7, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.8, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.9, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(1, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();




	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.1, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.2, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.3, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.4, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.5, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.6, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.7, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.8, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.9, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-1, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	i = 1;

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.1, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.2, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.3, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.4, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.5, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.6, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.7, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.8, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.9, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(1, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();




	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.1, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.2, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.3, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.4, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.5, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.6, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.7, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.8, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.9, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-1, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	i = -0.2;
	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.1, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.2, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.3, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.4, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.5, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.6, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.7, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.8, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.9, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(1, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();




	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.1, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.2, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.3, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.4, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.5, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.6, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.7, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.8, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.9, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-1, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	i = -0.4;

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.1, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.2, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.3, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.4, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.5, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.6, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.7, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.8, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.9, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(1, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();




	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.1, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.2, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();






	i = -0.6;

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.1, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.2, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.3, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.4, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.5, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.6, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.7, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.8, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.9, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(1, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();




	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.1, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.2, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();







	i = -0.8;
	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.1, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.2, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.3, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.4, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.5, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.6, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.7, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.8, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(0.9, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();


	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(1, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();




	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.1, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.5, 1 + scaleGrass, 0.5);
	glTranslated(-0.2, 0, i);
	drawGrass2(0, 0);
	glPopMatrix();






	//-----------------------------------------------------------done with grass!!!



	glPushMatrix();
	glScaled(0.39, 0.1, 0.4);
	glTranslated(-1, -0.1, -1);
	glScaled(1 + scalepoolx, 1, 1 + scalepoolx);

	Drawpool();
	glPopMatrix();

	glPushMatrix();
	glScaled(0.39, 0.1, 0.4);
	glTranslated(-1, -0.1, -1);
	glScaled(1 + scalepoolx, 1, 1 + scalepoolx);

	Drawpool1();
	glPopMatrix();


	glPushMatrix();
	glScaled(0.07, 0.2, 0.4);
	glTranslated(-3, -0.1, -1);
	glScaled(1 + scalepoolx, 1, 1 + scalepoolx);

	drawpool2();
	glPopMatrix();


	glPushMatrix();
	glScaled(0.07, 0.2, 0.4);
	glTranslated(-3, -0.1, -1);
	glScaled(1 + scalepoolx, 1, 1 + scalepoolx);

	drawpool3();
	glPopMatrix();

	//----------------------------done with        pool
	glPushMatrix();
	glScaled(0.01 , 0.35, 0.01 );
	glTranslated(-8, 0.3, -0.9);
	glScaled(1+scaleUmbrella  ,1, 1+ scaleUmbrella);

	DrawUmbrella1();

	glPopMatrix();


	glPushMatrix();
	glScaled(0.08 , 0.08 , 0.08);
	glRotatef(90, -0.8, 0, 0);
	glTranslated(-0.9, 0.05, 2.63);
	glScaled(1 + scaleUmbrella, 1, 1 + scaleUmbrella);



	DrawUmbrella2();

	glPopMatrix();


	glPushMatrix();
	glScaled(0.08 , 0.08 , 0.08 );
	glRotatef(90, -0.8, 0, 0);
	glTranslated(-0.9, 0.05, 2.63);
	glScaled(1 + scaleUmbrella, 1, 1 + scaleUmbrella);

	DrawUmbrella3();

	glPopMatrix();


	glPushMatrix();
	
	glTranslated(-8, 0.3, -0.9);
	glScaled(0.01, 0.35 , 0.01 );
	glScaled(1 + scaleUmbrella, 1, 1 + scaleUmbrella);

	DrawUmbrella4();

	glPopMatrix();
	//---------------------  done with umbrelllllllaaaaaaaaaaaaaaaaa
	glPushMatrix();
	
	glTranslated(-0.2, 0.07, 0.3);
	glScaled(1+ scaleTree, 1 , 1+ scaleTree);
	DrawTree();
	glPopMatrix();




	glPushMatrix();
	

	glTranslated(-0.2, 0.2, 0.3);
	glScaled(1.5, 1.5+scaleTree, 1.5);

	DrawTree2();
	glPopMatrix();

	glPushMatrix();

	glTranslated(-0.15, 0.2, 0.3);
	glScaled(1, 1 + scaleTree, 1);

	DrawTree2();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.25, 0.2, 0.3);
	glScaled(1, 1 + scaleTree, 1);

	DrawTree2();
	glPopMatrix();


	glPushMatrix();

	glTranslated(-0.2, 0.2, 0.35);
	glScaled(1, 1 + scaleTree, 1);

	DrawTree2();
	glPopMatrix();


	glPushMatrix();

	glTranslated(-0.2, 0.2, 0.25);
	glScaled(1, 1 + scaleTree, 1);

	DrawTree2();
	glPopMatrix();







	glPushMatrix();
	

	glTranslated(0.2, 0.07, -0.3);
	glScaled(1+scaleTree, 1 , 1+scaleTree);
	DrawTree();
	glPopMatrix();




	glPushMatrix();

	glTranslated(0.2, 0.2, -0.3);
	glScaled(1.5, 1.5+scaleTree, 1.5);

	DrawTree2();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.15, 0.2, -0.3);
	glScaled(1, 1 + scaleTree, 1);

	DrawTree2();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.25, 0.2, -0.3);
	glScaled(1, 1 + scaleTree, 1);

	DrawTree2();
	glPopMatrix();


	glPushMatrix();
	glTranslated(0.2, 0.2, -0.35);
	glScaled(1, 1 + scaleTree, 1);

	DrawTree2();
	glPopMatrix();


	glPushMatrix();
	glTranslated(0.2, 0.2, -0.25);
	glScaled(1, 1 + scaleTree, 1);

	DrawTree2();
	glPopMatrix();

	glPushMatrix();
	glTranslated(playerx, 0.1, playery);


	Drawplayer();
	glPopMatrix();


	glPushMatrix();
	glTranslated(Goalx, 0.13, Goaly);
	glScaled(0.1, 0.1, 0.02);

	drawGoal();
	glPopMatrix();

	}
	
	glFlush();

}


void anim() {

}
void animgrass() {
	if (grasstick)
		scaleGrass += 0.0000001;
}
void animflowers() {
	if(flowertick)
	scaleFlower += 0.0000001;
}
void animtress() {
	if (treetick)
		scaleTree += 0.0000001;
}
void animwalls() {
	if (walltick) {
		scalewall += 0.0000001;
	}
}
void animpool() {
	if (pooltick) {
		scalepoolx += 0.0000001;
	}

}
void animumbrella() {
	if (umbrellatick) {
		scaleUmbrella +=0.0000001;
	}

}

void Keyboard(unsigned char key, int x, int y) {
	float d = 0.01;
	double speed = 0.1;
	printf("%f", Goaly);
	printf("\n");
	printf("%f", playery);
	printf("\n");
	printf("%f", Goalx);
	printf("\n");
	printf("%f", playerx);
	printf("\n");
	if ((float)playerx == (float)Goalx && (float)playery == (float)Goaly) { // winnnnnnnnnnnnnnnnnnn!
		win = true;
		printf("heree");
	}
	

	switch (key) {
	case 'w':
		if (playery != -0.5)
			playery -= speed;
		else {
			LPCWSTR sound = L"down.wav";
			PlaySound(sound, NULL, SND_ASYNC | SND_FILENAME);
		}
		break;
	case 's':
		if (playery != 0.6)
			playery += speed;
		else {
			LPCWSTR sound = L"down.wav";
			PlaySound(sound, NULL, SND_ASYNC | SND_FILENAME);
		}
		break;
	case 'a':
		if (playerx != -0.5)
			playerx -= speed;
		else {
			LPCWSTR sound = L"down.wav";
			PlaySound(sound, NULL, SND_ASYNC | SND_FILENAME);
		}
		break;
	case 'd':
		if (playerx != 0.5)
			playerx += speed;
		else {
			LPCWSTR sound = L"down.wav";
			PlaySound(sound, NULL, SND_ASYNC | SND_FILENAME);
		}
		break;
	case'g':
		// animate grass
		grasstick = !grasstick;
		glutIdleFunc(animgrass);
		break;

	case'f': // animate flowers
		flowertick = !flowertick;
		
		glutIdleFunc(animflowers);break;

	case'p': // animate pool
		pooltick = !pooltick;glutIdleFunc(animpool);break;

	case't': // animate tree


		treetick = !treetick;glutIdleFunc(animtress);break;

	case'1': // animate wall

		walltick = !walltick;glutIdleFunc(animwalls);break;
	case'u': // animate umbrella	
		umbrellatick = !umbrellatick;glutIdleFunc(animumbrella);break;
	case GLUT_KEY_ESCAPE:
		exit(EXIT_SUCCESS);
	}

	

	glutPostRedisplay();
}
void Special(int key, int x, int y) {
	float a = 1.0;
	switch (key) {
	case GLUT_KEY_UP:  // front
		camera.eye.x = -0.000349;
		camera.eye.y = 0.160596;
		camera.eye.z = 1.734329;
		camera.center.x = -0.000349;
		camera.center.y = 0.17197;
		camera.center.z = 0.734394;
		camera.up.x = 0.000000;
		camera.up.y = 0.999935;
		camera.up.z = 0.011379;

		break;
	case GLUT_KEY_DOWN:
		camera.eye.x = -0.000000;
		camera.eye.y = 1.362348;
		camera.eye.z = 0.137897;
		camera.center.x = 0.000000;
		camera.center.y = 0.367254;
		camera.center.z = 0.038958;
		camera.up.x = 0.000000;
		camera.up.y = 0.098938;
		camera.up.z = -0.995094;

		break;
	case GLUT_KEY_LEFT:
		camera.eye.x = 1.777608;
		camera.eye.y = 0.379771;
		camera.eye.z = 0.064238;
		camera.center.x = 0.789698;
		camera.center.y = 0.228225;
		camera.center.z = 0.031553;
		camera.up.x = -0.151884;
		camera.up.y = 0.988365;
		camera.up.z = 0.008130;
		break;
	case GLUT_KEY_RIGHT:
		camera.eye.x = 0.0;
		camera.eye.y = 1.0;
		camera.eye.z = 0.9;
		camera.center.x = 0.0;
		camera.center.y = 0.0;
		camera.center.z = 0.0;
		camera.up.x = 0.0;
		camera.up.y = 1.0;
		camera.up.z = 0.0;
		break;
	}

	glutPostRedisplay();
}


void timee(int timer)
{


	r = double(rand() % 10) / 10;
	g = double(rand() % 10) / 10;
	b = double(rand() % 10) / 10;


	t++;
	glutPostRedisplay();
	glutTimerFunc(1 * 1000, timee, 0);
}





void main(int argc, char** argv) {
	glutInit(&argc, argv);
	srand(time(0));
	Goaly = double(rand() % 6) / 10;
	Goalx = double(rand() % 6) / 10;
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Assignment 2");
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glutIdleFunc(animflowers);
	glShadeModel(GL_SMOOTH);
	glutIdleFunc(anim);
	glutTimerFunc(0, timee, 0);
	glutPostRedisplay();
	glutMainLoop();
}

