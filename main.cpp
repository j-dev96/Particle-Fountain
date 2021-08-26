#include <cstdlib>
#include <stdlib.h>
#include "glut.h"
#include "Particle.h"
#include "V_Randomizer.h"
#include "shapes.h"
#include <Windows.h>
#include <mmsystem.h>
#include <mciapi.h>
#define STB_IMAGE_IMPLEMENTATION
#include <xiosbase>
#include <time.h>
#include <iostream>

#pragma comment(lib, "Winmm.lib")

Myrand_generate myobj_rand;
//unsigned int loadTexture(char const* path);
// 
/////// Number of Particles ///////
int num_My_Particles = 15;
My_Particles** My_Particles_obj;
My_Particles** trailSize;
float light_array[4] = { .1, .1, .1, 1.0 };
float diffuse_array[4] = { 0.5, 0.4,0.6, 1.0 };
float spec_array[4] = { 1, 1, 1, 1.0 };
float light_position[4] = { 5, 5, 5, 1 };
float position_array[3] = { 0,-21,0 };

boolean flag = false;

int setRandSpeed = 0;
int f = 0;
unsigned int texID;
int counter = 0;
int eyeMode = 0;

float r;

float Y_axis_angle = 0;
float rotating_speed = 0.0;
float speed_updating = 0.08;
int fireMode = 1;
int fireM2 = 0;
int fireM3 = 0;
int randM3 = 0;
int reset = 0;




void update(int value);

//
void Light_Function() {
	float Light_position2[4] = { 5,20,0,1 };
	float Light_direction[3] = { 0,0,0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_array);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_array);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec_array);
}

void Display_Function(void) {

	//if reset flag is 0 then the stream will continue to flow 
	if (reset == 0) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		Light_Function();
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		randM3 = (0) + static_cast <int> (rand()) / (static_cast <int> (RAND_MAX / (num_My_Particles - (0))));
		if (eyeMode == 1) {
			if (fireMode == 3) gluLookAt(My_Particles_obj[randM3]->getX(), My_Particles_obj[randM3]->getY(), My_Particles_obj[randM3]->getZ(), 0, 0, 0, 0, 1, 0);
			else gluLookAt(My_Particles_obj[2]->getX(), My_Particles_obj[2]->getY(), My_Particles_obj[2]->getZ(), 0, 0, 0, 0, 1, 0);
		}
		else gluLookAt(20, 20, -45, 0, 1, 0, 0, 1, 0);
		glRotatef(Y_axis_angle, 0, 1, 0);
		glPushMatrix();
		Draw_Polygon(position_array, 30, 2, 30);
		glPopMatrix();


		glPushMatrix();
		//glBindTexture(GL_TEXTURE_2D, texID);
		//glEnable(GL_TEXTURE_2D);
		/*glBegin(GL_QUADS);
		glColor3f(1, 0, 0);*/
		//glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
		//glEnable(GL_TEXTURE_GEN_T);


		/*glTexCoord2f(0.0, 0.0);
		glVertex3f(-50.0, -30.0, -50.0);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(50.0, -30.0, -50.0);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(50.0, -30.0, 50.0);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-50.0, -30.0, 50.0);
		glEnd();*/

		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		//glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
		//glDisable(GL_TEXTURE_GEN_T);
		glPopMatrix();

		srand((unsigned)time(0));

		if (fireMode == 1 || fireMode == 2) {
			for (int i = 0; i < num_My_Particles; i++) {
				glPushMatrix();
				glRotatef(Y_axis_angle, 0, 1, 0);
				My_Particles_obj[i]->Render();
				glPopMatrix();
			}
			/*for (int i = 0; i < 10; i++) {
				glPushMatrix();
				glRotatef(Y_axis_angle, 0, 1, 0);
				trailSize[i]->Render();
				glPopMatrix();
			}*/
			glFlush();
		}
		else if (fireMode == 3)
		{
			glPushMatrix();
			glRotatef(Y_axis_angle, 0, 1, 0);
			My_Particles_obj[randM3]->Render();
			glPopMatrix();

			glFlush();
		}
		glutSwapBuffers();
	}
	// reset is 1 then every changes user made are reset 
	else if (reset == 1)
	{
		for (int i = 0; i < num_My_Particles; i++) {
			My_Particles_obj[i] = new My_Particles(0, -10.0, myobj_rand.box_muller(-0.5, 0.5),//Position
				myobj_rand.box_muller(-1, 1), myobj_rand.box_muller(30, 34), myobj_rand.box_muller(-1, 1),//Velocity
				myobj_rand.box_muller(0.3, 1), myobj_rand.box_muller(.30, 1), myobj_rand.box_muller(0.3, 1),  //Colour
				1); // Alpha
		}
		reset = 0;
		eyeMode = 0;
		fireMode = 1;
		rotating_speed = 0.0;
		speed_updating = 0.08;
		setRandSpeed = 0;
	}
}

double random() {
	return sqrt((double)rand() / RAND_MAX);
}

void Insert_keys_check(unsigned char key, int x, int y) {
	switch (key) {

		// Change update speed
	case 'q':
		speed_updating -= 0.005;
		if (speed_updating < 0)speed_updating = 0;
		glutPostRedisplay();
		break;
	case 'w':
		speed_updating += 0.005;
		glutPostRedisplay();
		break;
	case 's':
		if (setRandSpeed == 0)
		{
			setRandSpeed = 1;
		}
		else if (setRandSpeed == 1)
		{
			setRandSpeed = 0;
			counter = 0;
		}

		//speed_updating += 0.005;
		glutPostRedisplay();
		break;

		// Change speed of camera rotation
	case 'i':
		rotating_speed += 0.1;
		glutPostRedisplay();
		break;
	case 'o':
		rotating_speed -= 0.1;
		glutPostRedisplay();
		break;
	case 'r':
		reset = 1;
		glutPostRedisplay();
		break;
	case 'f':
		if (fireMode == 2)
		{
			if (GLUT_KEY_DOWN)
			{
				fireM2 = 1;
				update(1);
			}
			if (GLUT_KEY_UP)
			{
				fireM2 = 0;
				update(1);
			}
		}
		if (fireMode == 3)
		{
			if (GLUT_KEY_DOWN)
			{
				fireM3 = 1;
				update(1);
			}
			if (GLUT_KEY_UP)
			{
				fireM3 = 0;
				update(1);
			}
		}
		break;
	case 'm':
		if (f == 0) {
			f = 1;
			for (int i = 0; i < num_My_Particles; i++) {
				My_Particles_obj[i]->setFriction(f);
			}
		}
		else if (f == 1) {
			f = 0;
			for (int i = 0; i < num_My_Particles; i++) {
				My_Particles_obj[i]->setFriction(f);
			}
		}
		break;
	case 'e':
		if (eyeMode == 0) eyeMode = 1;
		else if (eyeMode == 1) eyeMode = 0;
		break;
	case 'p':
		mciSendString("close mp3", NULL, 0, NULL);
		break;
	}
}
void menu_My_Particles(int value) {
	switch (value) {
	case 1:
		for (int i = 0; i < num_My_Particles; i++) {
			My_Particles_obj[i]->setMy_ParticlesType(1);
			glPopMatrix();
		}
		break;
	case 3:
		for (int i = 0; i < num_My_Particles; i++) {
			My_Particles_obj[i]->setMy_ParticlesType(3);
			glPopMatrix();
		}
		break;

	case 4:
		for (int i = 0; i < num_My_Particles; i++) {
			My_Particles_obj[i]->setMy_ParticlesType(4);
			glPopMatrix();
		}
		break;

	case 8:
		for (int i = 0; i < num_My_Particles; i++) {
			My_Particles_obj[i]->setMy_ParticlesType(8);
			glPopMatrix();
		}
		break;

	}
}

void menuMain(int value) {
	if (value == 5) {
		if (f == 0) {
			f = 1;
			for (int i = 0; i < num_My_Particles; i++) {
				My_Particles_obj[i]->setFriction(f);
			}
		}
		else if (f == 1) {
			f = 0;
			for (int i = 0; i < num_My_Particles; i++) {
				My_Particles_obj[i]->setFriction(f);
			}
		}
	}
	if (value == 6)
		exit(0);
}
void menuColour(int value) {
	switch (value) {
	case 1:
		for (int i = 0; i < num_My_Particles; i++) {
			My_Particles_obj[i]->setColour(1.6, 0.5, 0);
		}
		break;
	case 2:
		for (int i = 0; i < num_My_Particles; i++) {
			My_Particles_obj[i]->setColour(0, 1, 0);
		}
		break;
	case 3:
		for (int i = 0; i < num_My_Particles; i++) {
			My_Particles_obj[i]->setColour(0, 0, 1);
		}
		break;
	case 4:
		for (int i = 0; i < num_My_Particles; i++) {
			My_Particles_obj[i]->setColour(1, 1, 0);
		}
		break;
	case 5:
		for (int i = 0; i < num_My_Particles; i++) {
			My_Particles_obj[i]->setColour(0, 1, 1);
		}
		break;
	case 6:
		for (int i = 0; i < num_My_Particles; i++) {
			My_Particles_obj[i]->setColour(1, 0, 1);
		}
		break;
	case 7:
		for (int i = 0; i < num_My_Particles; i++) {
			My_Particles_obj[i]->setColour(0.1, 0.1, 0.1);
		}
		break;
	case 8:
		for (int i = 0; i < num_My_Particles; i++) {
			My_Particles_obj[i]->setColour(myobj_rand.box_muller(0, 1), myobj_rand.box_muller(0, 1), myobj_rand.box_muller(0, 1));
		}
		break;
	}
}
void FireModes(int value)
{
	switch (value) {
	case 1:
		fireMode = 1;
		break;
	case 2:
		fireMode = 2;
		break;
	case 3:
		fireMode = 3;
		break;
	}

}
void Size_of_Menu(int value) {
	switch (value) {
	case 1:
		for (int i = 0; i < num_My_Particles; i++) {
			My_Particles_obj[i]->setSize(1);
		}
		break;
	case 2:
		for (int i = 0; i < num_My_Particles; i++) {
			My_Particles_obj[i]->setSize(2);
		}
		break;
	case 3:
		for (int i = 0; i < num_My_Particles; i++) {
			My_Particles_obj[i]->setSize(3);
		}
		break;
	case 4:
		for (int i = 0; i < num_My_Particles; i++) {
			My_Particles_obj[i]->setSize(4);
		}
		break;
	case 5:
		for (int i = 0; i < num_My_Particles; i++) {
			My_Particles_obj[i]->setSize(5);
		}
		break;
	case 6:
		for (int i = 0; i < num_My_Particles; i++) {
			My_Particles_obj[i]->setSize(6);
		}
		break;
	case 7:
		for (int i = 0; i < num_My_Particles; i++) {
			My_Particles_obj[i]->setSize(7);
		}
		break;
	}
}
void initMenus() {

	glutCreateMenu(menu_My_Particles);
	glutAddMenuEntry("Cube", 1);
	glutAddMenuEntry("Sphere", 3);
	glutAddMenuEntry("Wire Sphere", 4);
	glutAddMenuEntry("Dot", 8);


	glutCreateMenu(menuColour);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Yellow", 4);
	glutAddMenuEntry("Teal", 5);
	glutAddMenuEntry("Purple", 6);
	glutAddMenuEntry("Black", 7);

	glutAddMenuEntry("Random", 8);

	glutCreateMenu(Size_of_Menu);
	glutAddMenuEntry("1", 1);
	glutAddMenuEntry("2", 2);
	glutAddMenuEntry("3", 3);
	glutAddMenuEntry("4", 4);
	glutAddMenuEntry("5", 5);
	glutAddMenuEntry("6", 6);
	glutAddMenuEntry("7", 7);

	glutCreateMenu(FireModes);
	glutAddMenuEntry("Default Mode", 1);
	glutAddMenuEntry("Fire Mode 2 (Hold F to Fire Stream)", 2);
	glutAddMenuEntry("Fire Mode 3 (Hold F to Fire 1 Particle)", 3);

	glutCreateMenu(menuMain);
	glutAddSubMenu("Shape", 1);
	glutAddSubMenu("Colour", 2);
	glutAddSubMenu("Size", 3);
	glutAddSubMenu("Fire Modes", 4);
	glutAddMenuEntry("Toggle Friction Mode, or press m", 5);
	glutAddMenuEntry("Quit", 6);
	

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void update(int value) {
	srand(unsigned(time(NULL)));
	if (fireMode == 1) {
		Y_axis_angle += rotating_speed;
		for (int i = 0; i < num_My_Particles; i++) {
			boolean flag = true;
			//r = (-10.0) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0 - (-10.0))));
			if (setRandSpeed == 1) {
				if (counter == 0) r = 0.001 + (0.1 - 0.001) * random();
				My_Particles_obj[i]->Update(r);
				/*for (int i = 0; i < 10; i++) {
					trailSize[i]->Update(speed_updating - 0.001, r);
				}*/
			}
			else {
				My_Particles_obj[i]->Update(speed_updating);
				/*for (int i = 0; i < 10; i++) {
					trailSize[i]->Update(speed_updating - 0.001, r);
				}*/
			}
		}
		if (flag) counter++;
	}
	if (fireMode == 2)
	{
		if (fireM2 == 1) {
			Y_axis_angle += rotating_speed;
			for (int i = 0; i < num_My_Particles; i++) {
				boolean flag = true;
				//r = (-10.0) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0 - (-10.0))));
				if (setRandSpeed == 1) {
					if (counter == 0) r = 0.001 + (0.1 - 0.001) * random();
					My_Particles_obj[i]->Update(r);
					/*for (int i = 0; i < 10; i++) {
						trailSize[i]->Update(speed_updating - 0.001, r);
					}*/
				}
				else {
					My_Particles_obj[i]->Update(speed_updating);
					/*for (int i = 0; i < 10; i++) {
						trailSize[i]->Update(speed_updating - 0.001, r);
					}*/
				}
			}
		}
		if (flag) counter++;
	}
	if (fireMode == 3)
	{
		if (fireM3 == 1) {
			Y_axis_angle += rotating_speed;
			if (setRandSpeed == 1) {
				boolean flag = true;
				if (counter == 0) r = 0.001 + (0.1 - 0.001) * random();
				My_Particles_obj[randM3]->Update(r);
			}
			else {
				My_Particles_obj[randM3]->Update(speed_updating);
			}
		}
		if (flag) counter++;
	}
	glutPostRedisplay();
	glutTimerFunc(10, update, 0);
}
void init(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glClearColor(1, 1, 1, 1);

	glFrontFace(GL_CW);
	//	glEnable(GL_CULL_FACE);
	//	glCullFace(GL_FRONT);
	gluPerspective(100, 1, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	initMenus();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}
int main(int argc, char** argv)
{
	//texID = loadTexture("Bricks.jpg");
	printf("Hello! Please right click the display to see all available options");
	printf("\nPress s to toggle random speed mode");
	printf("\nPress o to rotate clockwise");
	printf("\nPress i to rotate counterclockwise");
	printf("\nPress w to increase fountain speed");
	printf("\nPress q to reduce fountain speed");
	printf("\nPress m to toggle friction mode"); 
	printf("\nPress e to toggle eye mode");
	printf("\nPlease note you can use single fire mode with eye mode on!");
	printf("\nPress p if you want to stop the music");
	mciSendString("open \"breakout.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
	mciSendString("play mp3", NULL, 0, NULL);
	My_Particles_obj = new My_Particles * [num_My_Particles];
	//trailSize = new My_Particles * [10];

	for (int i = 0; i < num_My_Particles; i++) {
		My_Particles_obj[i] = new My_Particles(0, -10.0, myobj_rand.box_muller(-2, 2),//Position
			myobj_rand.box_muller(-2, 2), myobj_rand.box_muller(5, 15), myobj_rand.box_muller(-2, 2),//Velocity
			myobj_rand.box_muller(0.3, 1), myobj_rand.box_muller(.30, 1), myobj_rand.box_muller(0.3, 1),  //Colour
			1); // Alpha
	}
	//for (int i = 0; i < 10; i++) {
	//	trailSize[i] = new My_Particles(0, -10.0, myobj_rand.box_muller(-0.5, 0.5),//Position
	//		myobj_rand.box_muller(-1, 1), myobj_rand.box_muller(30, 34), myobj_rand.box_muller(-1, 1),//Velocity
	//		myobj_rand.box_muller(0.3, 1), myobj_rand.box_muller(.30, 1), myobj_rand.box_muller(0.3, 1),  //Colour
	//		0.5); // Alpha
	//}

	glutInit(&argc, argv);		//starts up GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutCreateWindow("My_Particles Fountain");	//creates the window
	glutDisplayFunc(Display_Function);
	glutKeyboardFunc(Insert_keys_check);
	init();

	glutTimerFunc(25, update, 0);

	glutMainLoop();				//starts the event loop

	return(0);					//return may not be necessary on all compilers
}


//unsigned int loadTexture(char const* path)
//{
//	unsigned int texture1;
//	// texture 1
//	// ---------
//	glGenTextures(1, &texture1);
//	glBindTexture(GL_TEXTURE_2D, texture1);
//	// set the texture wrapping parameters
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // note that we set the container wrapping method to GL_CLAMP_TO_EDGE
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	// set texture filtering parameters
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // set texture filtering to nearest neighbor to clearly see the texels/pixels
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	// load image, create texture and generate mipmaps
//	int width, height, nrChannels;
//	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
//	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
//	unsigned char* data = stbi_load("Bricks.jpg", &width, &height, &nrChannels, 0);
//	if (data)
//	{
//
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else
//	{
//		std::cout << "Failed to load texture" << std::endl;
//	}
//	stbi_image_free(data);
//
//	return texture1;
//}