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

		vector<ofxDatGui*> guiPanels;

		double amp;
		maxiClock clock;
		int counter = 0;
		vector<vector<int> > rhythms;
		vector<int> triggers;


		int numVoices = 4;
		vector<ofxMaxiOsc> oscillators;
		vector<ofxMaxiFilter> filters;
		vector<maxiEnv> oscEnvs;
		vector<maxiEnv> filterEnvs;

		vector<float> oscEnvAttacks;
		vector<float> oscEnvReleases;
		vector<float> filterEnvAttacks;
		vector<float> filterEnvReleases;
		vector<float> cutoffs;
		vector<float> resonances;
		vector<float> multipliers;
		vector<double> volumes;
		//gui apparently only works with floats
		vector<float> guiVolumes;
		vector<double> voices;

		int	bufferSize; // This is the audio buffersize
		int	sampleRate;
};
