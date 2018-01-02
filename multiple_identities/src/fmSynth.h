#pragma once

#include "vector"
#include "ofMain.h"
#include "ofxMaxim.h"
//#include "math.h"

using namespace std;

class fmSynth{
public:
	fmSynth();

	double play();

	void setAmp(double);
	void setCarFreq(double);
	void setModRatio(double);

	void setTrigger(int);

	void setAmpAttack(double);
	void setAmpRelease(double);
	void setAmpExp(double);

	void setIndexAttack(double);
	void setIndexRelease(double);
	void setIndexExp(double);
	void setMaxIndex(double);

private:
	ofxMaxiOsc	car;
	ofxMaxiOsc	mod;

	double amp;
	int trigger;

	double ampAttack;
	double ampRelease;
	double ampExp;
	maxiEnv ampEnv;

	double indxAttack;
	double indxRelease;
	double indxExp;
	double maxIndex;
	maxiEnv modIndexEnv;

	double carFreq;
	double modRatio;

	double output;
};

