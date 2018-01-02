#include "ofApp.h"

bool isLogging = true;
//--------------------------------------------------------------
void ofApp::setup() {
	bufferSize = 512;
	sampleRate = 44100;

	shader.load("shader.vert", "shader.frag");
	//ofSetupScreen();


	clock.setTempo(80);
	clock.setTicksPerBeat(1);

	synths.push_back(fmSynth());
	synths[0].setAmpAttack(20);
	synths[0].setAmpRelease(200);
	synths[0].setAmpExp(1);

	synths[0].setIndexAttack(20);
	synths[0].setIndexRelease(200);
	synths[0].setIndexExp(1);
	synths[0].setMaxIndex(100);


	ofSoundStreamSetup(2, 0, this, sampleRate, bufferSize, 4);
}

//--------------------------------------------------------------
void ofApp::update() {


}

//--------------------------------------------------------------
void ofApp::draw() {

	shader.begin();
	//Sending basic shader uniforms
	//Time elapsed since the start of the piece
	shader.setUniform1f("time", ofGetElapsedTimeMillis()*0.001);
	shader.setUniform2f("mouse", (float)ofGetMouseX() / ofGetWidth(), (float)ofGetMouseY() / ofGetHeight());
	shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());

	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
	shader.end();
}


//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
	for (int i = 0; i < bufferSize; i++) {
		clock.ticker();

		if (clock.tick) {
			synths[0].setTrigger(1);
			cout << "Trigger!" << endl;
		}
		else {
			synths[0].setTrigger(0);
		}

		double outputSig = synths[0].play();
		//if (isLogging)
			//cout << outputSig << endl;
		output[i*nChannels] = outputSig;
		output[i*nChannels + 1] = outputSig;

	}
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == ' ')
		shader.load("shader");

	if (key == '1')
		isLogging = !isLogging;

	if (key == 'f')
		ofToggleFullscreen();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
