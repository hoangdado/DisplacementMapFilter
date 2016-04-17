#define _USE_MATH_DEFINES

#include "VideoWaveMaker.h"
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

#include <cmath>


using namespace cv;

VideoWaveMaker::VideoWaveMaker() :
mVideoHeight(0),
mVideoWidth(0),
mFps(0),
mWaveLength(0),
mAmplitude(0),
mPeriod(0),
mDuration(0)
{
}


VideoWaveMaker::~VideoWaveMaker()
{
}

int VideoWaveMaker::getVideoWidth()
{
	return mVideoWidth;
}

void VideoWaveMaker::setVideoWidth(const int &width)
{
	mVideoWidth = width;
}

int VideoWaveMaker::getVideoHeight()
{
	return mVideoHeight;
}

void VideoWaveMaker::setVideoHeight(const int &height)
{
	mVideoHeight = height;
}

int VideoWaveMaker::getFps()
{
	return mFps;
}

void VideoWaveMaker::setFps(const int &fps)
{
	mFps = fps;
}

int VideoWaveMaker::getWaveLength()
{
	return mWaveLength;
}

void VideoWaveMaker::setWaveLength(const int &wavelength)
{
	mWaveLength = wavelength;
}

int VideoWaveMaker::getAmplitude()
{
	return mAmplitude;
}

void VideoWaveMaker::setAmplitude(const int &amplitude)
{
	mAmplitude = amplitude;
}

double VideoWaveMaker::getPeriod()
{
	return mPeriod;
}

void VideoWaveMaker::setPeriod(const double &period)
{
	mPeriod = period;
}

double VideoWaveMaker::getDuration()
{
	return mDuration;
}

void VideoWaveMaker::setDuration(const double &duration)
{
	mDuration = duration;
}

string VideoWaveMaker::getOutputFileName()
{
	return mOutputFileName;
}

void VideoWaveMaker::setOutputFileName(const string &outputFileName)
{
	mOutputFileName = outputFileName;
}

bool VideoWaveMaker::generate()
{
	if (mVideoWidth <= 0) {
		cerr << "Generate video failed! Video width must be greater than 0" << endl;
		return false;
	}

	if (mVideoHeight <= 0) {
		cerr << "Generate video failed! Video height must be greater than 0" << endl;
		return false;
	}

	if (mFps < 7) {
		cerr << "Generate video failed! Video frames per second must be grater than 6" << endl;
	}

	if (mWaveLength < 2) {
		cerr << "Generate video failed! Wavelength must be greater than 1 pixel" << endl;
		return false;
	}

	if (mAmplitude <= 0 || mAmplitude > 127) {
		cerr << "Generate video failed! Amplitude must be grater than 0 pixel and less than 128 pixels" << endl;
		return false;
	}

	if (mPeriod < 0.2) {
		cerr << "Generate video failed! Period must be greater than 0.2 seconds" << endl;
		return false;
	}

	if (mDuration < mPeriod) {
		cerr << "Generate video failed! Duration must be greater than period" << endl;
		return false;
	}

	VideoWriter videoWriter;

	videoWriter.open(mOutputFileName, -1, mFps, Size(mVideoWidth, mVideoHeight), true);

	if (!videoWriter.isOpened()) {
		cerr << "Generate video failed! Cannot open the writer";
		return false;
	}

	int maxNumberFrames = static_cast<int>(mDuration * mFps);

	bool isOddNumWidth = (mVideoWidth % 2 > 0);
	bool isOddNumHeight = (mVideoHeight % 2 > 0);

	cout << "Generating video ...";

	for (int frameCount = 0; frameCount < maxNumberFrames; frameCount++) {
		double t = frameCount * 1.0 / mFps;

		Mat outputFrame(mVideoWidth, mVideoHeight, CV_8UC1);

		// the wave equation is u(t) = A*cos[2*PI*(t/T - d/Lamda)]
		Point2d centerD((mVideoWidth - 1.0) / 2, (mVideoHeight - 1.0)/ 2);
		Point2i centerI((mVideoWidth - 1)/ 2, (mVideoHeight - 1)/ 2);

		for (int x = 0; x <= centerI.x; ++x) {
			for (int y = 0; y <= centerI.y; ++y) {
				double d = sqrt(pow(x - centerD.x, 2) + pow(y - centerD.y, 2));

				double u = mAmplitude * cos(2 * M_PI *(t/mPeriod - d/mWaveLength));

				uchar tmpValue = static_cast<uchar>(127 + u);

				outputFrame.at<uchar>(y, x) = tmpValue;
				outputFrame.at<uchar>(mVideoHeight - 1 - y, x) = tmpValue;
				outputFrame.at<uchar>(y, mVideoWidth - 1 - x) = tmpValue;
				outputFrame.at<uchar>(mVideoHeight - 1 - y, mVideoWidth - 1 - x) = tmpValue;
			}
		}

		videoWriter << outputFrame;
	}

	cout << "\nWritting finished!";
	return true;
}