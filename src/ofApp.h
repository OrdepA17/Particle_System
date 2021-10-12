#pragma once

#include "ofMain.h"
#include "Particle.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void resetParticles();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void speedIncrease();
		void speedDecrease();

		particleMode currentMode;
		ShapeMode shapeMode;
		string currentModeStr;
		string shapeModeStr; 
		particleMode previousMode;
		bool record = false;
		bool replay=false;
		unsigned index=0;
		int loopCount=0;

		vector <Particle> p;
		vector <glm::vec3> attractPoints;
		vector <glm::vec3> attractPointsWithMovement;
		vector <char> rec;
		ofTrueTypeFont Size;
};
