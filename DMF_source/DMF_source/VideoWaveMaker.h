#pragma once

#include <iostream>
#include <cstdint>
#include <string>

using namespace std;

class VideoWaveMaker
{
public:
	VideoWaveMaker();
	~VideoWaveMaker();

	int getVideoWidth();
	void setVideoWidth(const int &width);

	int getVideoHeight();
	void setVideoHeight(const int &height);

	int getFps();
	void setFps(const int &fps);

	int getWaveLength();
	void setWaveLength(const int &wavelength);

	int getAmplitude();
	void setAmplitude(const int &amplitude);

	double getPeriod();
	void setPeriod(const double &period);

	double getDuration();
	void setDuration(const double &duration);

	string getOutputFileName();
	void setOutputFileName(const string &outputFileName);

	bool generate();

private:
	int mVideoWidth;
	int mVideoHeight;
	int mFps;
	int mWaveLength;	// in number of pixels
	int mAmplitude;		// in pixels [0-128]
	double mPeriod;		// in seconds
	double mDuration;	// total video time in seconds
	string mOutputFileName;
};

