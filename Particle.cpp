#include "Particle.h"
#include "glut.h"
#include "V_Randomizer.h"
#include<string>
#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
#include <mciapi.h>

//int counter = 0;
int randStateSpeed;
int friction = 0;
My_Particles::~My_Particles() {
}

void setRandomS(int v)
{
	randStateSpeed = v;
}


My_Particles::My_Particles(double Position_X_axis, double Position_Y_axis, double Position_Z_axis, double Velocity_X_axis, double Velocity_Y_axis, double Velocity_Z_axis, float colR, float colG, float colB, float colA) {

	partType = 1;
	size = 1;

	pos.x = Position_X_axis;
	pos.y = Position_Y_axis;
	pos.z = Position_Z_axis;
	initYPos = Position_Y_axis;

	vel.x = Velocity_X_axis;
	vel.y = Velocity_Y_axis;
	vel.z = Velocity_Z_axis;

	acc.x = 0.0;
	acc.y = -9.8;
	acc.z = 0.0;

	colour[0] = colR;
	colour[1] = colG;
	colour[2] = colB;

	alpha = colA;
	age = 0;
	partType = 1;

	bounce = false;

}
void My_Particles::setColour(float r, float g, float b) {
	colour[0] = r;
	colour[1] = g;
	colour[2] = b;
}

void My_Particles::reset()
{
	vel.y = 35;
	pos.x = 0;
	pos.z = 0;
	bounce = false;
}

double My_Particles::getX() {
	return pos.x;
}

double My_Particles::getY() {
	return pos.y;
}

double My_Particles::getZ() {
	return pos.z;
}

void My_Particles::setSize(float newSize) {
	size = newSize;
}
void My_Particles::Update(double time) {

	//RGB effects
	if (pos.x < 0 || pos.x > 255) {
		colour[0] = (int)pos.x % 3;
	}
	else {
		colour[0] = (int)pos.x;
	}
	if (pos.y < 0 || pos.y > 255) {
		colour[1] = (int)pos.y % 3;
	}
	else {
		colour[1] = (int)pos.y;
	}
	if (pos.z < 0 || pos.z > 255) {
		colour[2] = (int)pos.z % 3;
	}
	else {
		colour[2] = (int)pos.z;
	}
	
	//acc.y = randVal;
	//Myrand_generate randNumber;
	pos.x += (vel.x * time) + (0.5 * (acc.y * (time * time)));
	vel.x = vel.x + (acc.x * time);
	pos.y += (vel.y * time) + (0.5 * (acc.y * (time * time)));
	vel.y = vel.y + (acc.y * time);
	pos.z += (vel.z * time) + (0.5 * (acc.y * (time * time)));
	vel.z = vel.z + (acc.z * time);

	if (pos.y <= -25 && bounce == false) {
		vel.y = -vel.y;	
		vel.y /= 1.25;
		PlaySound(TEXT("click.wav"), NULL, SND_FILENAME | SND_ASYNC);
		//counter++;
		//Momentum Reduce 
		if (friction == 1) {
			vel.x *= 0.90;
			vel.y *= 0.90;
			vel.z *= 0.90;
		}
		//If any particle has acceleration less then -10 its velocity diminishes
		if (acc.y < -10)
		{
			vel.y -=1;
		}
		bounce = true;
	}

	//Boundaries
	else if (pos.y <= -25 && bounce == true) {
		vel.y = 35;
		pos.x = 0;
		pos.z = 0;
		bounce = false;
	}
}

void My_Particles::setMy_ParticlesType(int a) {
	partType = a;
}

void My_Particles::setFriction(int a) {
	friction = a;
}

void My_Particles::Render() {

	Myrand_generate randNumber;
	glPushMatrix();

	glColor4f(colour[0], colour[1], colour[2], alpha);
	glTranslated(pos.x, pos.y, pos.z);
	glRotated(1.0, 1.0, 1.0, 0.0);
	switch (partType) {
	case 1:
		glutSolidCube(size);
		break;
	case 2:
		glutSolidTeapot(size);
		break;
	case 3:
		glutSolidSphere(size, 15, 15);

		break;
	case 4:
		glutWireSphere(size, 15, 15);
		break;
	case 5:
		glutWireCube(size);
		break;
	case 6:
		glutSolidCone(size, size, 15, 15);
		break;
	case 7:
		glutSolidTorus(size / 2, size, 15, 15);
		break;
	case 8:
		glPointSize(size * 2);
		glBegin(GL_POINTS);
		glVertex3f(0, 0, 0);
		glEnd();
		break;
	}
	glPopMatrix();
}