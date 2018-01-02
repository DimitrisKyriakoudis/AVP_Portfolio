#include "fmSynth.h"

//--------------------------------------------------------------
fmSynth::fmSynth() {
	trigger = 0;
	amp = 0.3;

	carFreq = 100;
	modRatio = 1;

	ampAttack = 20;
	ampRelease = 200;
	ampExp = 2;

	indxAttack = 20;
	indxRelease = 200;
	indxExp = 2;
	maxIndex = 100;

	ampEnv.setAttack(ampAttack);
	ampEnv.setDecay(1);
	ampEnv.setSustain(1);
	ampEnv.setRelease(ampRelease);

	modIndexEnv.setAttack(indxAttack);
	modIndexEnv.setDecay(1);
	modIndexEnv.setSustain(1);
	modIndexEnv.setRelease(indxRelease);

	cout << "amp attack: " << ampEnv.attack << endl;
	cout << "mod attack: " << modIndexEnv.attack << endl;
	
}

//--------------------------------------------------------------
double fmSynth::play() {
	//double ampEnvOut = ampEnv.adsr(1, trigger);// , ampExp);
	//double modIndexEnvOut = maxIndex * pow(modIndexEnv.adsr(1, trigger), indxExp);

	/*double modOut = mod.sinewave(carFreq * modRatio) * modIndexEnvOut;
	output = car.sinewave(carFreq + modOut) * ampEnvOut;
	*/

	/*double modOut = mod.sinewave(100) * maxIndex * pow(modIndexEnv.adsr(1, trigger), indxExp);
	double outputSig = car.sinewave(100 + modOut) * pow(ampEnv.adsr(1, trigger), ampExp);
*/

	double outputSig = car.sinewave(440 + 500.0*mod.sinewave(480));

	return outputSig * amp;
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
void fmSynth::setIndexAttack(double v) {
	indxAttack = v;
	modIndexEnv.setAttack(indxAttack);
}
void fmSynth::setIndexRelease(double v) {
	indxRelease = v;
	modIndexEnv.setRelease(indxRelease);
}
void fmSynth::setIndexExp(double v) {
	indxExp = v;
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