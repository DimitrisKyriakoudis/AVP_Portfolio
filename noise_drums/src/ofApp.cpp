#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	bufferSize = 512;
	sampleRate = 44100;
	amp = 0.2;

	clock.setTempo(60);
	clock.setTicksPerBeat(2);

	//One bar of 8ths for each voice
	rhythms = {
		{1, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 1, 0, 0, 0, 1, 0},
		{1, 1, 1, 1, 1, 1, 1, 1},
		{0, 1, 0, 1, 0, 1, 0, 1}
	};

	//TODO: change these to something better
	guiVolumes = {1.0f, 1.0f, 0.8f, 0.6f};
	oscEnvAttacks = { 50, 50, 50, 50 };
	oscEnvReleases = { 250, 250, 250, 250 };
	filterEnvAttacks = { 70, 70, 70, 70 };
	filterEnvReleases = { 250, 250, 250, 250 };
	cutoffs = { 150, 300, 600, 600 };
	resonances = { 5, 5, 5, 5 };
	multipliers = { 5, 10, 10, 20 };

	int yOffset = 200;
	for (int i = 0; i < numVoices; i++) {
		voices.push_back(0.0);
		volumes.push_back(0.0);
		triggers.push_back(0);

		oscillators.push_back(ofxMaxiOsc());
		oscEnvs.push_back(maxiEnv());
		filters.push_back(ofxMaxiFilter());
		filterEnvs.push_back(maxiEnv());

		oscEnvs[i].setAttack(oscEnvAttacks[i]);
		oscEnvs[i].setDecay(1);
		oscEnvs[i].setSustain(1);
		oscEnvs[i].setRelease(oscEnvReleases[i]);

		filterEnvs[i].setAttack(filterEnvAttacks[i]);
		filterEnvs[i].setDecay(1);
		filterEnvs[i].setSustain(1);
		filterEnvs[i].setRelease(filterEnvReleases[i]);

		guiPanels.push_back(new ofxDatGui(0, yOffset*i));
		guiPanels[i]->addSlider("Volume", 0, 1)->bind(guiVolumes[i]);
		guiPanels[i]->addSlider("Osc Attack", 0, 300)->bind(oscEnvAttacks[i]);
		guiPanels[i]->addSlider("Osc Release", 0, 300)->bind(oscEnvReleases[i]);
		guiPanels[i]->addSlider("Cutoff", 20, 2000)->bind(cutoffs[i]);
		guiPanels[i]->addSlider("Cutoff Attack", 0, 300)->bind(filterEnvAttacks[i]);
		guiPanels[i]->addSlider("Cutoff Release", 0, 300)->bind(filterEnvReleases[i]);
		guiPanels[i]->addSlider("Cutoff Multiplier", 1, 20)->bind(multipliers[i]);
		guiPanels[i]->addSlider("Resonance", 1, 50)->bind(resonances[i]);
	}
	ofxDatGuiLog::quiet();

	cout << "finished setup" << endl;

	ofSoundStreamSetup(2, 0, this, sampleRate, bufferSize, 4);
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {


	for (int i = 0; i < bufferSize; i++) {

		clock.ticker();

		if (clock.tick) {
			//Increment counter
			counter++;
			counter = counter % 8;
			//Check to see which voices should play
			for (int i = 0; i < numVoices; i++) {
				if (rhythms[i][counter] == 1)
					triggers[i] = 1;
				else triggers[i] = 0;
			}

			cout << "tick!" << endl;
		}
		else {
			for (int i = 0; i < numVoices; i++) {
				triggers[i] = 0;
			}
		}

		for (int i = 0; i < 2; i++) {
			double sig = oscillators[i].noise() * oscEnvs[i].adsr(1, triggers[i]);
			double filterEnv = filterEnvs[i].adsr(multipliers[i], triggers[i]);
			double cutoff = ofClamp(cutoffs[i] + cutoffs[i] * filterEnv, 20, 20000);
			//Using lowpass resonant filter for first 2 voices
			sig = filters[i].lores(sig, cutoff, resonances[i]);
			voices[i] = sig;
		}

		for (int i = 2; i < 4; i++) {
			double sig = oscillators[i].noise() * oscEnvs[i].adsr(1, triggers[i]);
			double filterEnv = filterEnvs[i].adsr(multipliers[i], triggers[i]);
			double cutoff = ofClamp(cutoffs[i] - cutoffs[i] * filterEnv, 20, 20000);
			//Hipass resonant filter for the rest
			sig = filters[i].hires(sig, cutoff, resonances[i]);
			voices[i] = sig;
		}

		double outputSig = 0;
		for (int i = 0; i < numVoices; i++) {
			outputSig += voices[i];
		}
		outputSig *= amp / numVoices;

		output[i*nChannels] = outputSig;
		output[i*nChannels + 1] = outputSig;
	}
}

//--------------------------------------------------------------
void ofApp::update() {
	for (int i = 0; i < numVoices; i++) {
		oscEnvs[i].setAttack(oscEnvAttacks[i]);
		oscEnvs[i].setDecay(1);
		oscEnvs[i].setSustain(1);
		oscEnvs[i].setRelease(oscEnvReleases[i]);

		filterEnvs[i].setAttack(filterEnvAttacks[i]);
		filterEnvs[i].setDecay(1);
		filterEnvs[i].setSustain(1);
		filterEnvs[i].setRelease(filterEnvReleases[i]);

		volumes[i] = (double)guiVolumes[i];
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

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
