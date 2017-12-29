#pragma once

#include "ofMain.h"
#include <vector>
#include "ofxDatGui.h"
#include "ofxMaxim.h"

using namespace std;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
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
		
		void audioOut(float * output, int bufferSize, int nChannels);

		double outputs[2];
		ofSoundStream soundStream;

		ofxDatGui* gui;
		float attack, release, attack2, release2, resonance;
		float mult;

		int trigger;
		double amp;
		maxiClock clock;

		vector<ofxMaxiOsc> oscillators;
		vector<ofxMaxiFilter> filters;
		vector<double> filterOutputs;
		vector<maxiEnv> oscEnvs;
		vector<maxiEnv> filterEnvs;
		vector<double> oscFreqs;
		vector<double> filterEnvDecays;

		int	bufferSize; // This is the audio buffersize
		int	sampleRate;
};
