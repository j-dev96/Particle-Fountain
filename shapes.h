void Draw_Box(float c[3], float my_width, float my_height, float my_depth){
	float w = my_width;
	float h = my_height;
	float d = my_depth;

	float vertic_array[8][3] = {{c[0]-w,c[1]-h,c[2]+d},   {c[0]-w,c[1]+h,c[2]+d},   {c[0]+w,c[1]+h,c[2]+d},   {c[0]+w,c[1]-h,c[2]+d},
							{c[0]-w,c[1]-h,c[2]-d},    {c[0]-w,c[1]+h,c[2]-d},   {c[0]+w,c[1]+h,c[2]-d},   {c[0]+w,c[1]-h,c[2]-d}};
	
	glBegin(GL_POLYGON);
	glVertex3fv(vertic_array[2]);
	glVertex3fv(vertic_array[6]);
	glVertex3fv(vertic_array[7]);
	glVertex3fv(vertic_array[3]);
	glVertex3fv(vertic_array[2]);

	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3fv(vertic_array[0]);
	glVertex3fv(vertic_array[1]);
	glVertex3fv(vertic_array[2]);
	glVertex3fv(vertic_array[3]);
	glVertex3fv(vertic_array[4]);

	glEnd();

	glBegin(GL_POLYGON);
	glVertex3fv(vertic_array[3]);
	glVertex3fv(vertic_array[7]);
	glVertex3fv(vertic_array[4]);
	glVertex3fv(vertic_array[0]);
	glVertex3fv(vertic_array[1]);

	glEnd();

	glBegin(GL_POLYGON);
	glVertex3fv(vertic_array[5]);
	glVertex3fv(vertic_array[1]);
	glVertex3fv(vertic_array[2]);
	glVertex3fv(vertic_array[3]);
	glVertex3fv(vertic_array[0]);

	glEnd();

	glBegin(GL_POLYGON);
	glVertex3fv(vertic_array[5]);
	glVertex3fv(vertic_array[4]);
	glVertex3fv(vertic_array[7]);
	glVertex3fv(vertic_array[6]);
	glVertex3fv(vertic_array[4]);

	glEnd();

	glBegin(GL_POLYGON);
	glVertex3fv(vertic_array[0]);
	glVertex3fv(vertic_array[4]);
	glVertex3fv(vertic_array[5]);
	glVertex3fv(vertic_array[3]);
	glVertex3fv(vertic_array[1]);

	glEnd();

	
}

void Draw_Polygon(float c[3], float my_width, float my_height, float my_depth){
	float w = my_width;
	float h = my_height;
	float d = my_depth;

	float vertic_array[8][3] = {{c[0]-w,c[1]-h,c[2]+d},   {c[0]-w,c[1]+h,c[2]+d},   {c[0]+w,c[1]+h,c[2]+d},   {c[0]+w,c[1]-h,c[2]+d},
							{c[0]-w,c[1]-h,c[2]-d},    {c[0]-w,c[1]+h,c[2]-d},   {c[0]+w,c[1]+h,c[2]-d},   {c[0]+w,c[1]-h,c[2]-d}};
	
	glNormal3f(0,0,1);
	glBegin(GL_POLYGON);
	glColor4f(1,1,0.3,1);
	glVertex3fv(vertic_array[2]);
	glVertex3fv(vertic_array[6]);
	glVertex3fv(vertic_array[7]);
	glVertex3fv(vertic_array[3]);
	glEnd();
	
	glNormal3f(0,1,0);
	glBegin(GL_POLYGON);
	glColor3f(0.3,0.9,1);
	glVertex3fv(vertic_array[0]);
	glVertex3fv(vertic_array[1]);
	glVertex3fv(vertic_array[2]);
	glVertex3fv(vertic_array[3]);
	glEnd();

	glNormal3f(-1,0,0);
	glBegin(GL_POLYGON);
	glColor3f(0.2,0.6,.9);
	glVertex3fv(vertic_array[3]);
	glVertex3fv(vertic_array[7]);
	glVertex3fv(vertic_array[4]);
	glVertex3fv(vertic_array[0]);
	glEnd();

	glNormal3f(1,0,0);
	glBegin(GL_POLYGON);
	glColor4f(0.5,0.7,1,0.1);
	glVertex3fv(vertic_array[5]);
	glVertex3fv(vertic_array[1]);
	glVertex3fv(vertic_array[2]);
	glVertex3fv(vertic_array[6]);
	glEnd();

	glNormal3f(0,0,1);
	glBegin(GL_POLYGON);
	glColor3f(0.5,0.6,.8);
	glVertex3fv(vertic_array[5]);
	glVertex3fv(vertic_array[4]);
	glVertex3fv(vertic_array[7]);
	glVertex3fv(vertic_array[6]);
	glEnd();

	glNormal3f(0,-1,0);
	glBegin(GL_POLYGON);
	glColor3f(0.5,0.5,1);
	glVertex3fv(vertic_array[0]);
	glVertex3fv(vertic_array[4]);
	glVertex3fv(vertic_array[5]);
	glVertex3fv(vertic_array[1]);
	glEnd();


	
}