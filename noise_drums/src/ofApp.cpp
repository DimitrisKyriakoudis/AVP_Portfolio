#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	bufferSize = 512;
	sampleRate = 44100;
	amp = 0.2;

	//Initialise clock
	clock.setTempo(110);
	clock.setTicksPerBeat(2);

	//One bar of 8ths for each voice
	rhythms = {
		{1, 0, 0, 0, 1, 0, 0, 0}, //kick
		{0, 0, 1, 0, 0, 0, 1, 0}, //snare
		{1, 1, 1, 1, 1, 1, 1, 1}, //hihat
		{0, 1, 0, 0, 0, 1, 0, 1}  //misc perc
	};

	//Initialise parameters to starting values
	volumes =			{1.0f, 1.0f, 0.8f, 0.6f};
	oscEnvAttacks =		{ 7, 17, 12, 220};
	oscEnvReleases =	{ 80, 100, 65, 350};
	cutoffs =			{ 60, 990, 3000, 330 };
	filterEnvAttacks =	{ 5, 5, 10, 10 };
	filterEnvReleases = { 60, 30, 20, 20 };
	exponents =			{ 9, 2, 10, 6 };
	multipliers =		{ 10, 17, 2, 15 };
	resonances =		{ 13, 4, 3.5, 13 };

	//Initialise GUI panels, one for each voice
	int yOffset = 300;
	int xOffset = 350;
	guiPanels.push_back(new ofxDatGui(0, 0));
	guiPanels.push_back(new ofxDatGui(0, yOffset));
	guiPanels.push_back(new ofxDatGui(xOffset, 0));
	guiPanels.push_back(new ofxDatGui(xOffset, yOffset));


	for (int i = 0; i < numVoices; i++) {
		//Initialise the vectors
		voices.push_back(0.0);
		//volumes.push_back(0.0);
		triggers.push_back(0);

		//Initialise oscillators, filters and envelopes
		oscillators.push_back(ofxMaxiOsc());
		oscEnvs.push_back(maxiEnv());
		filters.push_back(ofxMaxiFilter());
		filterEnvs.push_back(maxiEnv());

		//Set the envelope parameters to the initial values
		oscEnvs[i].setAttack(oscEnvAttacks[i]);
		oscEnvs[i].setDecay(1);
		oscEnvs[i].setSustain(1);
		oscEnvs[i].setRelease(oscEnvReleases[i]);

		filterEnvs[i].setAttack(filterEnvAttacks[i]);
		filterEnvs[i].setDecay(1);
		filterEnvs[i].setSustain(1);
		filterEnvs[i].setRelease(filterEnvReleases[i]);

		//Add sliders to each panel and bind them
		//to their corresponding parameter
		guiPanels[i]->addSlider("Volume", 0, 1)->bind(volumes[i]);
		guiPanels[i]->addSlider("Osc Attack", 0, 350)->bind(oscEnvAttacks[i]);
		guiPanels[i]->addSlider("Osc Release", 0, 350)->bind(oscEnvReleases[i]);
		guiPanels[i]->addSlider("Cutoff", 20, 3000)->bind(cutoffs[i]);
		guiPanels[i]->addSlider("Cutoff Attack", 0, 350)->bind(filterEnvAttacks[i]);
		guiPanels[i]->addSlider("Cutoff Release", 0, 350)->bind(filterEnvReleases[i]);
		guiPanels[i]->addSlider("Env Exponent", 0.5, 10)->bind(exponents[i]);
		guiPanels[i]->addSlider("Cutoff Mult", 1, 20)->bind(multipliers[i]);
		guiPanels[i]->addSlider("Resonance", 1, 50)->bind(resonances[i]);
	}
	//Avoid annoying warnings about callbacks
	ofxDatGuiLog::quiet();

	//Initialise the DAC
	ofSoundStreamSetup(2, 0, this, sampleRate, bufferSize, 4);
}

//--------------------------------------------------------------
void ofApp::update() {
	//Update the parameters of the envelopes according to the values
	//changed in the GUI
	for (int i = 0; i < numVoices; i++) {
		oscEnvs[i].setAttack(oscEnvAttacks[i]);
		oscEnvs[i].setDecay(1);
		oscEnvs[i].setSustain(1);
		oscEnvs[i].setRelease(oscEnvReleases[i]);

		filterEnvs[i].setAttack(filterEnvAttacks[i]);
		filterEnvs[i].setDecay(1);
		filterEnvs[i].setSustain(1);
		filterEnvs[i].setRelease(filterEnvReleases[i]);

		//Gui appears to only work with floats so casting it to a double here
		//volumes[i] = (double)guiVolumes[i];
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
	for (int i = 0; i < bufferSize; i++) {
		//Increment clock ticker
		clock.ticker();
		//If we're on a beat
		if (clock.tick) {
			//Increment beat counter (going from 0 to 7)
			counter++;
			counter = counter % 8;
			//Check to see which voices should play
			for (int i = 0; i < numVoices; i++) {
				if (rhythms[i][counter] == 1)
					triggers[i] = 1;
				else triggers[i] = 0;
			}
		} //If we're not on a beat, set all triggers to 0
		//so that the envelopes start their release phase
		else {
			for (int i = 0; i < numVoices; i++) {
				triggers[i] = 0;
			}
		}


		//Use a lowpass filter for the first 2 voices and a highpass for the rest
		for (int i = 0; i < 2; i++) {
			double sig = oscillators[i].noise() * oscEnvs[i].adsr(1, triggers[i]);
			//The exponent of the filter envelope determines its curve (numbers higher than 1
			//make it snappier whereas numbers less than 1 make it curve down more towards its end)
			double filterEnv = multipliers[i] * pow(filterEnvs[i].adsr(1, triggers[i]), 2.0);
			//The filter envelope gets used to modulate the cutoff, it goes from the
			//multiplier value (e.g. 5 or 7) to 0 and so it's used here to produce
			//an overall downward sweep from a multiple of the cutoff (multiplier+1)
			//to the base cutoff itself
			double cutoff = ofClamp(cutoffs[i] + cutoffs[i]*filterEnv, 20, 20000);
			//Using lowpass resonant filter for first 2 voices
			sig = filters[i].lores(sig, cutoff, resonances[i]);
			voices[i] = sig * volumes[i];
		}

		for (int i = 2; i < 4; i++) {
			double sig = oscillators[i].noise() * oscEnvs[i].adsr(1, triggers[i]);
			double filterEnv = multipliers[i] * pow(filterEnvs[i].adsr(1, triggers[i]), exponents[i]);
			//Here the filter Env is used to sweep the cutoff up by subtracting it from the 
			//base cutoff
			double cutoff = ofClamp(cutoffs[i] - cutoffs[i] * filterEnv, 20, 20000);
			//Hipass resonant filter for the last 2 voices
			sig = filters[i].hires(sig, cutoff, resonances[i]);
			voices[i] = sig * volumes[i];
		}

		//Accumulate all the voices into the final output...
		double outputSig = 0;
		for (int i = 0; i < numVoices; i++) {
			outputSig += voices[i];
		}
		//... and scale it according to the global amp and the number of 
		//total voices to avoid clipping
		outputSig *= amp / numVoices;

		output[i*nChannels] = outputSig;
		output[i*nChannels + 1] = outputSig;
	}
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
