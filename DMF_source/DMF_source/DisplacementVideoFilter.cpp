#include "DisplacementVideoFilter.h"

DisplacementVideoFilter::DisplacementVideoFilter()
{
}


DisplacementVideoFilter::~DisplacementVideoFilter()
{
}

void DisplacementVideoFilter::displace(const string &inputVideoFileName, const string &displacementVideoFileName)
{
	VideoCapture inputVideoCapture(inputVideoFileName);

	if (!inputVideoCapture.isOpened()) {
		cerr << "Error: Cannot open input video!" << endl;
		return;
	}

	/*int inputVideoWidth = static_cast<int>(inputVideoCapture.get(CV_CAP_PROP_FRAME_WIDTH));
	int inputVideoHeight = static_cast<int>(inputVideoCapture.get(CV_CAP_PROP_FRAME_HEIGHT));*/

	VideoCapture filterVideoCapture(displacementVideoFileName);

	if (!filterVideoCapture.isOpened()) {
		cerr << "Error: Cannot open filter video!" << endl;
		return;
	}

	/*int filterVideoWidth = filterVideoCapture.get(CV_CAP_PROP_FRAME_WIDTH);
	int filterVideoHeight = filterVideoCapture.get(CV_CAP_PROP_FRAME_HEIGHT);*/

	namedWindow("Output", CV_WINDOW_AUTOSIZE);

	while (1) {
		Mat frame;

		bool readFrameSuccess = inputVideoCapture.read(frame);

		if (!readFrameSuccess) {
			cerr << "Error: Read next frame failed!";
			break;
		}

		Mat filterFrame;

		bool readFilterFrameSuccess = filterVideoCapture.read(filterFrame);

		if (!readFilterFrameSuccess) {
			filterFrame = Mat(frame.cols, frame.rows, CV_8UC1, 127);
		}

		Mat outputFrame;

		blend(frame, filterFrame, outputFrame);

		imshow("Output", outputFrame);

		if (waitKey(30) == 27)
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}
}

void DisplacementVideoFilter::blend(Mat &inputImg, Mat &filterImg, Mat &outputImg)
{
	resize(inputImg, inputImg, Size(512, 512));

	outputImg.create(inputImg.size(), inputImg.type());

	resize(filterImg, filterImg, Size(inputImg.cols, inputImg.rows));

	for (int x = 0; x < inputImg.cols; x++) {
		for (int y = 0; y < inputImg.rows; y++) {
			int dx = (filterImg.at<uchar>(y, x) - 127);
			int dy = dx;

			//cout << "dx = " << dx << ", dy = " << dy << endl;

			int newX = x + dx;
			int newY = y + dy;

			if (newX < 0) {
				newX = 0;
			}

			if (newX >= inputImg.cols) {
				newX = inputImg.cols - 1;
			}

			if (newY < 0) {
				newY = 0;
			}

			if (newY >= inputImg.rows) {
				newY = inputImg.rows - 1;
			}

			outputImg.at<Vec3b>(y, x) = inputImg.at<Vec3b>(newY, newX);
		}
	}
}
