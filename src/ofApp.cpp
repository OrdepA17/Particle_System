#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	
	int num = 1500;
	p.assign(num, Particle());
	currentMode = PARTICLE_MODE_ATTRACT;

	currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse"; 

	resetParticles();
}

//--------------------------------------------------------------
void ofApp::resetParticles(){

	//these are the attraction points used in the fourth demo 
	attractPoints.clear();
	for(int i = 0; i < 4; i++){
		attractPoints.push_back( glm::vec3( ofMap(i, 0, 4, 100, ofGetWidth()-100) , ofRandom(100, ofGetHeight()-100) , 0) );
	}
	
	attractPointsWithMovement = attractPoints;
	
	for(unsigned int i = 0; i < p.size(); i++){
		p[i].setMode(currentMode);		
		p[i].setAttractPoints(&attractPointsWithMovement);;
		p[i].reset();
	}	
}

//--------------------------------------------------------------
void ofApp::update(){
	for(unsigned int i = 0; i < p.size(); i++){
		p[i].setMode(currentMode);
		p[i].setShapeMode(shapeMode);
		p[i].update();
	}
	
	//lets add a bit of movement to the attract points
	for(unsigned int i = 0; i < attractPointsWithMovement.size(); i++){
		attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
		attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
	}

	if(replay){
		if(loopCount%150==0){
			keyPressed(rec[index]);
			index++;
		}
	}
	if(index==rec.size()){
		loopCount=0;
		index=0;
	}	
	loopCount++;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor (0,51,102), ofColor(128,0,128));

	for(unsigned int i = 0; i < p.size(); i++){
		p[i].draw();
	}
	
	ofSetColor(190);
	if( currentMode == PARTICLE_MODE_NEAREST_POINTS ){
		for(unsigned int i = 0; i < attractPoints.size(); i++){
			ofNoFill();
			ofDrawCircle(attractPointsWithMovement[i], 10);
			ofFill();
			ofDrawCircle(attractPointsWithMovement[i], 4);
		}
	}

	if(record){
		ofDrawBitmapString("Recording", ofGetWidth() - 90, ofGetHeight() - 750);
	}
	if(replay){
		ofDrawBitmapString("Replaying", ofGetWidth() - 90, ofGetHeight() - 650);
	}

	ofSetColor(230);	
	ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-4 to change mode.\nPress A to pause, then again to unpause\nPress I or D to alter the sizes.\nPress F or S to alter the speeds.\nPress R to record.\nPress P to replay the recording.\nPress C to cancel the replay.\nKeys 5-6 changes the particle shapes.", 10, 20);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
if(key == 'c' || key == 'C'){//Cancels the replay mode
	replay = false;
}
	if(loopCount%150==0||!replay){//Acts as a counter for when to replay the next saved input
	if( key == '1'){
		currentMode = PARTICLE_MODE_ATTRACT;
		currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse"; 
		if(record) rec.push_back(key);		
	}
	if( key == '2'){
		currentMode = PARTICLE_MODE_REPEL;
		currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse"; 
		if(record) rec.push_back(key);				
	}
	if( key == '3'){
		currentMode = PARTICLE_MODE_NEAREST_POINTS;
		currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS:"; 
		if(record) rec.push_back(key);						
	}
	if( key == '4'){
		currentMode = PARTICLE_MODE_NOISE;
		currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation";
		if(record) rec.push_back(key); 						
		resetParticles();
	}

	if(key=='5')
	{
		//Changes particles to squares
		shapeModeStr = "5 - PARTICLE_SHAPE_SQUARE: particles are now squares";
		shapeMode=PARTICLE_SHAPE_SQUARE;
		if(record) rec.push_back(key);
	}	

	if(key=='6')
	{
		//changes particles back to circles
		shapeModeStr = "6 - PARTICLE_SHAPE_CIRCLE: particles are now circles";
		shapeMode=PARTICLE_SHAPE_CIRCLE;
		if(record) rec.push_back(key);
	}
		
	if( key == ' ' ){
		if(record) rec.push_back(key);
		resetParticles();
	}
	if( currentMode == PARTICLE_MODE_PAUSE ){
		key = 'a';
		if(record) rec.push_back(key);
	}
	
	if( key == 'a' || key == 'A'){
		//Pauses the program and turns the particles white
		if( currentMode != PARTICLE_MODE_PAUSE){
			previousMode = currentMode;
			currentMode = PARTICLE_MODE_PAUSE;
			if(record) rec.push_back(key);
		}
		//Unpauses the program 
		else{
			currentMode = previousMode;
			if(record) rec.push_back(key); 
		}
	}

	if ( key == 'i' || key == 'I'){
		//Increases the size of the particles
		unsigned int x = 0;
		while ( x < p.size()){
			p[x].increaseSize();
			x++;	
		}
		if(record) rec.push_back(key);
	}

	if ( key == 'd' || key == 'D'){
		//Decreases the size of the particles
		unsigned int x = 0;
		while ( x < p.size()){
			p[x].decreaseSize();
			x++;	
		}
		if(record) rec.push_back(key); 
	}
	if(key=='f'|| key=='F'){
		//Toggles a speed increase to all particles
		speedIncrease();
		if(record) rec.push_back(key);
	}

	if(key=='s'|| key=='S'){
		//Toggles a speed decrease to all particles
		speedDecrease();
		if(record) rec.push_back(key);
	}

	if(key == 'r' || key == 'R' && key != 'r'){
		//Starts to record all key inputs and stores them in the rec vector
		record = !record;
		if(record) rec.clear();
	}
	if(key=='p'||key=='P'){replay=true;}//Replays the record vector
	}
}

//--------------------------------------------------------------
void ofApp::speedIncrease(){
	for (unsigned int i=0; i<p.size(); i++){
		p[i].setMode(currentMode);
		p[i].speedIncrease(4);
	}
}
//--------------------------------------------------------------
void ofApp::speedDecrease(){
	for (unsigned int i=0; i<p.size(); i++){
		p[i].setMode(currentMode);
		p[i].speedDecrease(0.25);
	}
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
