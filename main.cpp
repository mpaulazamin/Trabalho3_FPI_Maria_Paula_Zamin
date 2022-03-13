#include "opencv2/opencv.hpp"
#include < iostream>
using namespace cv;
using namespace std;

int g_slider;
int g_slider_max;
int g_slider_max_contrast;

void on_trackbar(int, void*)
{
	//printf("%d\n", g_slider);
}

void gaussian_blur(Mat& frame, Mat& gaussianBlur, int num, VideoWriter& video)
{
	//Kernel needs to the odd
	int count = num % 2;
	if (count == 0)
		num = num + 1;

	//Applying Gaussian Blur
	GaussianBlur(frame, gaussianBlur, Size(num, num), 0);
	imshow("Gaussian Blur", gaussianBlur);

	video.write(gaussianBlur);
}

void canny_detector(Mat& frame, Mat& cannyDetector, Mat& blurBeforeCanny, int num, VideoWriter& video)
{
	int lowThreshold = num;
	int lowThresholdRatio = num * 3;

	//Applying Gaussian Blur to filter noise
	GaussianBlur(frame, blurBeforeCanny, Size(11, 11), 0);

	//Applying Canny Detector
	Canny(blurBeforeCanny, cannyDetector, lowThreshold, lowThresholdRatio, 3);
	imshow("Canny", cannyDetector);

	video.write(cannyDetector);
}

void sobel_filter(Mat& frame, Mat& sobelFilter, int num, VideoWriter& video)
{

}

void change_bright(Mat& frame, Mat& changedBright, int num, VideoWriter& video)
{
	int alpha = 1;
	int beta = num;
	frame.convertTo(changedBright, -1, alpha, beta);
	imshow("Brightness", changedBright);

	video.write(changedBright);
}

void change_contrast(Mat& frame, Mat& changedContrast, int num, VideoWriter& video)
{
	int alpha = num;
	int beta = 0;
	frame.convertTo(changedContrast, -1, alpha, beta);
	imshow("Contrast", changedContrast);

	video.write(changedContrast);
}

void change_negative(Mat& frame, Mat& changedNegative, VideoWriter& video)
{
	int alpha = -1;
	int beta = 255;
	frame.convertTo(changedNegative, -1, alpha, beta);
	imshow("Negative frame", changedNegative);

	video.write(changedNegative);
}

void grayscale(Mat& frame, Mat& changedGrayscale, VideoWriter& video)
{
	cvtColor(frame, changedGrayscale, COLOR_BGR2GRAY);
	imshow("Grayscale frame", changedGrayscale);

	video.write(changedGrayscale);
}

void rotate_frame(Mat& frame, Mat& rotatedFrame, int direction)
{
	if (direction == +90)
	{
		cv::rotate(frame, rotatedFrame, cv::ROTATE_90_CLOCKWISE);
		imshow("Rotated frame", rotatedFrame);
	}

	if (direction == -90)
	{
		cv::rotate(frame, rotatedFrame, cv::ROTATE_90_COUNTERCLOCKWISE);
		imshow("Rotated frame", rotatedFrame);
	}

	if (direction == +180)
	{
		cv::rotate(frame, rotatedFrame, cv::ROTATE_180);
		imshow("Rotated frame", rotatedFrame);
	}
}

void flip_frame(Mat& frame, Mat& flippedFrame, int flipping, VideoWriter& video)
{
	// flipping = 0 does a flipping over x-axis
	// flipping = 0 does a flipping over y-axis
	flip(frame, flippedFrame, flipping);
	imshow("Flipped frame", flippedFrame);

	video.write(flippedFrame);
}

void resize_frame(Mat& frame, Mat& resizedFrame, int newWidth, int newHeight)
{
	resize(frame, resizedFrame, Size(newWidth, newHeight));
	imshow("Resized frame", resizedFrame);
}

int main()
{
	Mat gaussianBlur;
	Mat cannyDetector;
	Mat blurBeforeCanny;
	Mat sobelFilter;
	Mat changedBright;
	Mat changedContrast;
	Mat changedNegative;
	Mat changedGrayscale;
	Mat rotatedFrame;
	Mat flippedFrame;
	Mat redimensionalized;
	Mat resizedFrame;

	VideoCapture cap = VideoCapture(1);
	if (!cap.isOpened()) return -1;

	int frame_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
	int frame_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

	VideoWriter video("C://Users//Maria Paula//teste.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height));

	g_slider = 0;
	g_slider_max = 255;
	g_slider_max_contrast = 10;
	//g_slider_bright = -255;

	//namedWindow("Gaussian Blur", 1);
	//namedWindow("Canny", 1);
	//namedWindow("Sobel", 1);
	namedWindow("Brightness", 1);
	//namedWindow("Contrast", 1);
	//namedWindow("Negative frame", 1);
	//namedWindow("Grayscale frame", 1);
	//namedWindow("Rotated frame", 1);
	//namedWindow("Flipped frame", 1);
	//namedWindow("Resized frame", 1);

	//Makes trackbar
	//createTrackbar("TrackbarGB", "Gaussian Blur", &g_slider, g_slider_max, on_trackbar);
	//createTrackbar("TrackbarCanny", "Canny", &g_slider, g_slider_max, on_trackbar);
	//createTrackbar("TrackbarSobel", "Sobel", &g_slider, g_slider_max, on_trackbar);
	createTrackbar("TrackbarBright", "Brightness", &g_slider, g_slider_max, on_trackbar);
	//createTrackbar("TrackbarContrast", "Contrast", &g_slider, g_slider_max_contrast, on_trackbar);

	for (;;)
	{
		Mat frame;
		cap >> frame;

		namedWindow("Original frame", 1);
		imshow("Original frame", frame);

		int num = g_slider;
		int direction = +90;
		int flipping = 0;
		int width = frame.size().width;
		int height = frame.size().height;
		int newWidth = round(width / 2);
		int newHeight = round(height / 2);

		//gaussian_blur(frame, gaussianBlur, num, video);
		//canny_detector(frame, cannyDetector, blurBeforeCanny, num, video);
		//sobel_filter(frame, sobelFilter, num, video);
		change_bright(frame, changedBright, num, video);
		//change_contrast(frame, changedContrast, num, video);
		//change_negative(frame, changedNegative, video);
		//grayscale(frame, changedGrayscale, video);
		//rotate_frame(frame, rotatedFrame, direction);
		//flip_frame(frame, flippedFrame, flipping, video);
		//resize_frame(frame, resizedFrame, newWidth, newHeight);

		if (waitKey(1) == 27) break;
		//if (waitKey(30) >= 0)
		//	break;
	}
	cap.release();
	video.release();

	destroyAllWindows();
	return 0;
}