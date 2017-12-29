#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	bufferSize = 512;
	sampleRate = 44100;
	amp = 0.2;

	clock.setTempo(40);
	clock.setTicksPerBeat(4);

	oscillators.push_back(ofxMaxiOsc());
	oscEnvs.push_back(maxiEnv());
	filterEnvs.push_back(maxiEnv());
	filters.push_back(ofxMaxiFilter());


	gui = new ofxDatGui(0, 0);
	ofxDatGuiLog::quiet();
	gui->addSlider("Attack", 0, 300)->bind(attack);
	gui->addSlider("Release", 0, 300)->bind(release);
	gui->addSlider("Attack", 0, 300)->bind(attack2);
	gui->addSlider("Release", 0, 300)->bind(release2);
	gui->addSlider("Resonance", 1, 20)->bind(resonance);
	gui->addSlider("Mult", 1, 5)->bind(mult);



	ofSoundStreamSetup(2, 0, this, sampleRate, bufferSize, 4);
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
	
	trigger = 0;

	for (int i = 0; i < bufferSize; i++) {

		clock.ticker();

		if (clock.tick) {
			trigger = 1;
			cout << "tick!" << endl;
		}
		else trigger = 0;

		double sig = oscillators[0].noise() * oscEnvs[0].adsr(1, trigger);
		double filterEnv = filterEnvs[0].adsr(mult, trigger);
		sig = filters[0].lores(sig, 150 + 150 * filterEnv, resonance);

		output[i*nChannels] = sig*amp;
		output[i*nChannels + 1] = sig*amp;

	}
}

//--------------------------------------------------------------
void ofApp::update(){
	oscEnvs[0].setAttack(attack);
	oscEnvs[0].setDecay(1);
	oscEnvs[0].setSustain(1);
	oscEnvs[0].setRelease(release);

	filterEnvs[0].setAttack(attack2);
	filterEnvs[0].setDecay(1);
	filterEnvs[0].setSustain(1);
	filterEnvs[0].setRelease(release2);
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
