#include "ofApp.h"
const int steps = 514;
double wt[steps];
double phase;

double ofApp::wavetable(double frequency) {
	double remainder;
	phase += 512. / (44100 / frequency);
	if (phase >= 511) phase -= 512;
	remainder = phase - floor(phase);
	double output = (double)((1 - remainder) * wt[1 + (long)phase] + remainder * wt[2 + (long)phase]);
	return(output);
}

void ofApp::plotTable(double* table, int s) {
	/*ofPolyline p;
	ofPoint* verts = new ofPoint[size];
	int drawSize = 300;
	for (int i = 0; i < size; i++) {
		verts[i] = ofPoint(drawSize*i / (float)size, drawSize*table[i]);
	}
	p.addVertices(verts, size);
	p.draw();*/


	ofPoint* verts = new ofPoint[5];
	// make a pentagon
	float size = 80.f;
	float X1 = 0.125*sqrt(10 + 2 * sqrt(5)) * size;
	float X2 = 0.125*sqrt(10 - 2 * sqrt(5)) * size;
	float Y1 = 0.125*(sqrt(5) - 1) * size;
	float Y2 = 0.125*(sqrt(5) + 1) * size;
	verts[0] = ofPoint(0, -0.5 * size);
	verts[1] = ofPoint(-X1, -Y1);
	verts[2] = ofPoint(-X2, Y2);
	verts[3] = ofPoint(X2, Y2);
	verts[4] = ofPoint(X1, -Y1);
	ofPolyline p;
	p.addVertices(verts, 5);
	
	p.draw();
}

//--------------------------------------------------------------
void ofApp::setup(){
	bufferSize = 512;
	sampleRate = 44100;
	ofBackground(51);
	ofSoundStreamSetup(2, 0, this, sampleRate, bufferSize, 4);
	
	for (int i = 0; i < steps; i++) {
		wt[i] = (2*i / (float)steps)-1;
		//std::cout << wt[i] << std::endl;
	}

	ofSetColor(255, 0, 0);

	ofFill();
	ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, 100);
	//plotTable(wt, steps);
}

//--------------------------------------------------------------
void ofApp::update(){

}

void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
	for (int i = 0; i < bufferSize; i++) {

		double sig = 0;// wavetable(200)*0.1;
		//std::cout << sig << std::endl;

		output[i*nChannels] = sig;
		output[i*nChannels + 1] = sig;

	}
}
//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
