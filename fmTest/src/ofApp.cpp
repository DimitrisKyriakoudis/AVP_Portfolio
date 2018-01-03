#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	bufferSize = 512;
	sampleRate = 44100;



	clock.setTempo(80);
	clock.setTicksPerBeat(2);

	ampEnv.setAttack(20);
	ampEnv.setDecay(1);
	ampEnv.setSustain(1);
	ampEnv.setRelease(250);

	modEnv.setAttack(20);
	modEnv.setDecay(1);
	modEnv.setSustain(1);
	modEnv.setRelease(250);
	maxMod = 100;

	ampExp = 2;
	modExp = 2;


	ofSoundStreamSetup(2, 0, this, sampleRate, bufferSize, 4);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
	for (int i = 0; i < bufferSize; i++) {
		clock.ticker();

		if (clock.tick) {
			trigger = 1;

			ampEnv.setAttack(ofRandom(8, 50));
			ampEnv.setRelease(ofRandom(100, 350));

			modEnv.setAttack(ofRandom(5, 20));
			modEnv.setRelease(ofRandom(250, 350));
			maxMod = ofRandom(50, 1000);

			cout << "Trigger!" << endl;
		}
		else {
			trigger = 0;
		}

		double modOut = mod.sinewave(100) * pow(modEnv.adsr(1, trigger), modExp)  * maxMod;
		double outputSig = car.sinewave(100 + modOut) * pow(ampEnv.adsr(1, trigger), ampExp);
		
		output[i*nChannels] = outputSig * 0.2;
		output[i*nChannels + 1] = outputSig * 0.2;

	}
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
