#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	shader.load("shader.vert", "shader.frag");
	//ofSetupScreen();
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
void ofApp::keyPressed(int key) {
	if (key == ' ')
		shader.load("shader");

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
