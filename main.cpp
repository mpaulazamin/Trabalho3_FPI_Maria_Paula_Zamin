#include "opencv2/opencv.hpp"
#include < iostream>
using namespace cv;
using namespace std;

int g_slider; //slider pos value
int g_slider_max; //slider max value

void on_trackbar(int, void*)
{
	//printf("%d\n", g_slider);
}

void gaussian_blur(Mat& frame, Mat& gaussianBlur, int num)
{
	//Kernel needs to the odd
	int count = num % 2;
	if (count == 0)
		num = num + 1;

	GaussianBlur(frame, gaussianBlur, Size(num, num), 0);
	imshow("Gaussian Blur", gaussianBlur);
}

void canny_detector(Mat& frame, Mat& cannyDetector, int num)
{
	//Should I filter the noise with a gaussian blur before?
	int lowThreshold = num;
	int lowThresholdRatio = num * 3;
	Canny(frame, cannyDetector, lowThreshold, lowThresholdRatio, 3);
	imshow("Canny", cannyDetector);
}

int main()
{
	Mat gaussianBlur;
	Mat cannyDetector;
	VideoCapture cap = VideoCapture(1);

	if (!cap.isOpened()) return -1;
	
	g_slider = 0;
	g_slider_max = 255;

	namedWindow("Gaussian Blur", 1);
	namedWindow("Canny", 1);

	//Makes trackbar
	createTrackbar("TrackbarName", "Gaussian Blur", &g_slider, g_slider_max, on_trackbar);
	createTrackbar("TrackbarName", "Canny", &g_slider, g_slider_max, on_trackbar);

	for (;;)
	{
		Mat frame;
		cap >> frame; // get a new frame from camera
		//cvtColor(frame, edges, COLOR_BGR2GRAY);
		//Canny(edges, edges, num, 30, 3);

		namedWindow("Original frame", 1);
		imshow("Original frame", frame);

		int num = g_slider;
		gaussian_blur(frame, gaussianBlur, num);
		canny_detector(frame, cannyDetector, num);

		if (waitKey(1) == 27) break;
		//if (waitKey(30) >= 0)
		//	break;
	}
	cap.release();
	return 0;
}