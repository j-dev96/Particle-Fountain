class My_Particles {
	typedef struct _Vector {
		double x, y, z;
	} Vector;
protected:
	Vector pos, vel, acc;
	float age;
	float alpha;
	float colour[7];
	int partType;
	float size;
	bool bounce;
	int initYPos;

public:
	void setRandomS(int val);
	My_Particles();
	~My_Particles();
	void setMy_ParticlesType(int a);
	void setFriction(int a);
	void Update(double time);
	void reset();
	double getX();
	double getY();
	double getZ();
	void Render();
	void setSize(float newSize);
	void setColour(float r, float g, float b);
	My_Particles(double _posX, double _posY, double _posZ, double _velX, double _velY, double _velZ, float colR, float colG, float colB, float colA);
};

