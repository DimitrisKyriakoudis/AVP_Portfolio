#include "fmSynth.h"

//--------------------------------------------------------------
fmSynth::fmSynth() {
	trigger = 0;
	amp = 0.3;

	carFreq = 100;
	modRatio = 1;

	ampAttack = 100;
	ampRelease = 200;
	ampExp = 2;

	modAttack = 20;
	modRelease = 200;
	modExp = 2;
	maxIndex = 100;

	ampEnv.setAttack(ampAttack);
	ampEnv.setDecay(1);
	ampEnv.setSustain(1);
	ampEnv.setRelease(ampRelease);

	modEnv.setAttack(modAttack);
	modEnv.setDecay(1);
	modEnv.setSustain(1);
	modEnv.setRelease(modRelease);
}

//--------------------------------------------------------------
double fmSynth::play() {
	double modOut = mod.sinewave(100) * pow(modEnv.adsr(1, trigger), modExp)  * maxIndex;
	output = car.sinewave(100 + modOut) * pow(ampEnv.adsr(1, trigger), ampExp) * amp;

	return output;
}

//--------------------------------------------------------------
void fmSynth::setCarFreq(double f) {
	carFreq = f;
}

void fmSynth::setModRatio(double r) {
	modRatio = r;
}

void fmSynth::setAmp(double v) {
	amp = v;
}

//--------------------------------------------------------------
void fmSynth::setModAttack(double v) {
	modAttack = v;
	modEnv.setAttack(modAttack);
}
void fmSynth::setModRelease(double v) {
	modRelease = v;
	modEnv.setRelease(modRelease);
}
void fmSynth::setModExp(double v) {
	modExp = v;
}
void fmSynth::setMaxIndex(double v) {
	maxIndex = v;
}

//--------------------------------------------------------------
void fmSynth::setAmpAttack(double v) {
	ampAttack = v;
	ampEnv.setAttack(ampAttack);
}
void fmSynth::setAmpRelease(double v) {
	ampRelease = v;
	ampEnv.setRelease(ampRelease);
}
void fmSynth::setAmpExp(double v) {
	ampExp = v;
}

//--------------------------------------------------------------
void fmSynth::setTrigger(int t) {
	trigger = t;
}