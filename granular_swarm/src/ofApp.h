#pragma once

#include "ofMain.h"

/*
A swarm of DFO agents that control grain players. Each grain playre
is responsible for creating grains of certain duration, position, and rate
at a certain frequency (depending on the frequency the grains will overlap
or not). The swarm is controlled by setting the "ideal" parameters and then
choosing how how much the disturbance from each parameter will be.
*/

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
		
};
