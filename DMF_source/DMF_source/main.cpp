#include <iostream>
#include "VideoWaveMaker.h"

using namespace std;

int main() {
	VideoWaveMaker videoWaveMaker;
	videoWaveMaker.setVideoWidth(512);
	videoWaveMaker.setVideoHeight(512);
	videoWaveMaker.setFps(25);
	videoWaveMaker.setDuration(20.0);
	videoWaveMaker.setPeriod(1.0);
	videoWaveMaker.setWaveLength(100);
	videoWaveMaker.setAmplitude(50);
	videoWaveMaker.setOutputFileName("C:/Users/Public/Videos/Sample Videos/water_wave.avi");
	videoWaveMaker.generate();

	system("pause");
	return 0;
}