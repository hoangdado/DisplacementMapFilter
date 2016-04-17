#pragma once

#include <iostream>
#include <cstdio>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;

using namespace std;

class DisplacementVideoFilter
{
public:
	DisplacementVideoFilter();
	~DisplacementVideoFilter();

	void displace(const string &inputVideoFileName, const string &displacementVideoFileName);
	void blend(Mat &inputImg, Mat &filterImg, Mat &outputImg);
};

