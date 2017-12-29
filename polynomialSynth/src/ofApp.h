#pragma once

//#define MAXIMILIAN_RT_AUDIO
//#define MAXIMILIAN_PORTAUDIO

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxOsc.h"
#include "ofxGui.h"


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
		double wavetable(double frequency);
		void plotTable(double* table, int s);


		double outputs[2];
		ofSoundStream soundStream;

		int	bufferSize; // This is the audio buffersize
		int	sampleRate; // This is the audio sample rate

		maxiOsc myOsc;
};
