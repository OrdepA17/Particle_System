#pragma once
#include "ofMain.h"

enum particleMode{
	PARTICLE_MODE_ATTRACT = 0,
	PARTICLE_MODE_REPEL,
	PARTICLE_MODE_NEAREST_POINTS,
	PARTICLE_MODE_NOISE,
	PARTICLE_MODE_PAUSE
};

enum ShapeMode{
	PARTICLE_SHAPE_CIRCLE=0,
	PARTICLE_SHAPE_SQUARE
};

class Particle{

	public:
		Particle();
		
		void setMode(particleMode newMode);	
		void setShapeMode(ShapeMode newShape);
		void setAttractPoints( vector <glm::vec3> * attract );
		void attractToPoint(int, int);
		void repelFromPoint(int, int);
		void reset();
		void update();
		void draw();		
		void increaseSize();
		void decreaseSize();
		void speedIncrease(float);
		void speedDecrease(float);



		glm::vec3 pos;
		glm::vec3 vel;
		glm::vec3 frc;
		
		float drag; 
		float uniqueVal;
		float scale;
		float defaultSpeed=1;

		particleMode mode;
		ShapeMode currentShapeMode;
		
		vector <glm::vec3> * attractPoints; 
};
