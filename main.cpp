#include "opencv2/opencv.hpp"
#include < iostream>
using namespace cv;
using namespace std;

//Defines global variables for the trackbars
int g_slider;
int g_slider_max;

//For the contrast, creates a separated variable for the maximum value
int g_slider_max_contrast;

//Function to get the value of the trackbar defined by the user
void on_trackbar(int, void*)
{
	//printf("%d\n", g_slider);
}

void gaussian_blur(Mat& frame, Mat& gaussianBlur, int num, VideoWriter& video_gaussian)
{
	//Ckecks if kernel is even or odd
	//If kernel in even, rounds to the closest odd number
	int count = num % 2;
	if (count == 0)
		num = num + 1;

	//Applying Gaussian Blur
	GaussianBlur(frame, gaussianBlur, Size(num, num), 0);
	imshow("Gaussian Blur", gaussianBlur);

	//Records video
	video_gaussian.write(gaussianBlur);
}

void canny_detector(Mat& frame, Mat& cannyDetector, Mat& preprocessedCanny, int num, VideoWriter& video_canny)
{
	//Getting trackbar number defined by the user
	int lowThreshold = num;

	//Ratio of lower:upper threshold is 3:1
	int lowThresholdRatio = num * 3;

	//Kernel size of Canny detector
	int kernelSize = 3;

	//Convert original frame to grayscale
	cvtColor(frame, preprocessedCanny, COLOR_BGR2GRAY);

	//Applying Gaussian Blur to filter noise
	GaussianBlur(preprocessedCanny, preprocessedCanny, Size(3, 3), 0);

	//Applying Canny Detector
	Canny(preprocessedCanny, cannyDetector, lowThreshold, lowThresholdRatio, kernelSize);
	imshow("Canny", cannyDetector);

	//Records video
	video_canny.write(cannyDetector);
}

void sobel_filter(Mat& frame, Mat& sobelFilter, Mat& preprocessedSobel, int dx, int dy, VideoWriter& video_sobel)
{	
	//Applying Gaussian Blur to reduce noise
	GaussianBlur(frame, preprocessedSobel, Size(3, 3), 0);

	//Converts frame to graycsale
	Mat frameGray;
	cvtColor(preprocessedSobel, preprocessedSobel, COLOR_BGR2GRAY);

	//Kernel size for Sobel filter
	int kernelSize = 5;

	//Depth of output frame
	int ddepth = CV_16S;

	//If dx=1 and dy=0, computes the 1st derivative Sobel image in the x-direction
	//If dx=0 and dy=1, computes the 1st derivative Sobel image in the y-direction
	//If both dx = 1 and dy = 1, computes the 1st derivative Sobel image in both directions
	Sobel(preprocessedSobel, sobelFilter, ddepth, dx, dy, kernelSize);
	imshow("Sobel", sobelFilter);

	//Records video
	video_sobel.write(sobelFilter);
}

void change_bright(Mat& frame, Mat& changedBright, int num, VideoWriter& video_bright)
{
	//Defines alpha to 1, and beta to the number defined by the user on trackbar
	int alpha = 1;
	int beta = num;

	//Changes the brightness
	frame.convertTo(changedBright, -1, alpha, beta);
	imshow("Brightness", changedBright);

	//Records video
	video_bright.write(changedBright);
}

void change_contrast(Mat& frame, Mat& changedContrast, int num, VideoWriter& video_contrast)
{
	//Defines alpha to the number defined by the user of trackbar, and beta to zero
	int alpha = num;
	int beta = 0;

	//Changes the contrast
	frame.convertTo(changedContrast, -1, alpha, beta);
	imshow("Contrast", changedContrast);

	//Records video
	video_contrast.write(changedContrast);
}

void change_negative(Mat& frame, Mat& changedNegative, VideoWriter& video_negative)
{
	//Defines alpha to -1 and beta do 255
	int alpha = -1;
	int beta = 255;

	//Converts original frame to its negative
	frame.convertTo(changedNegative, -1, alpha, beta);
	imshow("Negative frame", changedNegative);

	//Records video
	video_negative.write(changedNegative);
}

void grayscale(Mat& frame, Mat& changedGrayscale, VideoWriter& video_gray)
{
	//Converts original frame to grayscale
	cvtColor(frame, changedGrayscale, COLOR_BGR2GRAY);
	imshow("Grayscale frame", changedGrayscale);

	//Records video
	video_gray.write(changedGrayscale);
}

void rotate_frame(Mat& frame, Mat& rotatedFrame, int direction)
{
	//Rotates by 90 degrees on clockwise direction
	if (direction == +90)
	{
		cv::rotate(frame, rotatedFrame, cv::ROTATE_90_CLOCKWISE);
		imshow("Rotated frame", rotatedFrame);
	}

	//Rotates by 90 degrees on counterclockwise direction
	if (direction == -90)
	{
		cv::rotate(frame, rotatedFrame, cv::ROTATE_90_COUNTERCLOCKWISE);
		imshow("Rotated frame", rotatedFrame);
	}

	//Rotates by 180 degrees
	if (direction == +180)
	{
		cv::rotate(frame, rotatedFrame, cv::ROTATE_180);
		imshow("Rotated frame", rotatedFrame);
	}
}

void flip_frame(Mat& frame, Mat& flippedFrame, int flipping, VideoWriter& video_flipped)
{
	//Flips original frame according to flipping value
	flip(frame, flippedFrame, flipping);
	imshow("Flipped frame", flippedFrame);

	//Records video
	video_flipped.write(flippedFrame);
}

void resize_frame(Mat& frame, Mat& resizedFrame, int newWidth, int newHeight)
{
	//Resizes original frame to half of size
	resize(frame, resizedFrame, Size(newWidth, newHeight));
	imshow("Resized frame", resizedFrame);
}

int main()
{
	//Creates Mat images to store the results
	Mat gaussianBlur;
	Mat cannyDetector;
	Mat preprocessedCanny;
	Mat sobelFilter;
	Mat preprocessedSobel;
	Mat changedBright;
	Mat changedContrast;
	Mat changedNegative;
	Mat changedGrayscale;
	Mat rotatedFrame;
	Mat flippedFrame;
	Mat redimensionalized;
	Mat resizedFrame;

	//Opens the camera
	VideoCapture cap = VideoCapture(1);
	if (!cap.isOpened()) return -1;

	//Getting width and height of the capture
	int frame_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
	int frame_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

	//Creates VideoWriter objects to records the results
	//Please, comment the functions you are not going to use
	//Change the address to save the videos on your own computer
	VideoWriter video_gaussian("C://Users//Maria Paula//video_gaussian.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(frame_width, frame_height));
	VideoWriter video_canny("C://Users//Maria Paula//video_canny.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(frame_width, frame_height));
	VideoWriter video_sobel("C://Users//Maria Paula//video_sobel.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(frame_width, frame_height));
	VideoWriter video_bright("C://Users//Maria Paula//video_bright.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(frame_width, frame_height));
	VideoWriter video_contrast("C://Users//Maria Paula//video_contrast.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(frame_width, frame_height));
	VideoWriter video_negative("C://Users//Maria Paula//video_negative.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(frame_width, frame_height));
	VideoWriter video_gray("C://Users//Maria Paula//video_gray.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(frame_width, frame_height));
	VideoWriter video_flipped_x("C://Users//Maria Paula//video_flipped_x.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(frame_width, frame_height));
	VideoWriter video_flipped_y("C://Users//Maria Paula//video_flipped_y.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(frame_width, frame_height));

	//Setting values for the values of the trackbars
	g_slider = 0;
	g_slider_max = 255;
	g_slider_max_contrast = 10;

	//Creates windows to show the frames
	//Please, comment the functions you are not going to use
	namedWindow("Gaussian Blur", 1);
	namedWindow("Canny", 1);
	namedWindow("Sobel", 1);
	namedWindow("Brightness", 1);
	namedWindow("Contrast", 1);
	namedWindow("Negative frame", 1);
	namedWindow("Grayscale frame", 1);
	namedWindow("Rotated frame", 1);
	namedWindow("Flipped frame", 1);
	namedWindow("Resized frame", 1);

	//Creates trackbars
	//Please, comment the functions you are not going to use
	createTrackbar("TrackbarGB", "Gaussian Blur", &g_slider, g_slider_max, on_trackbar);
	createTrackbar("TrackbarCanny", "Canny", &g_slider, g_slider_max, on_trackbar);
	createTrackbar("TrackbarBright", "Brightness", &g_slider, g_slider_max, on_trackbar);
	createTrackbar("TrackbarContrast", "Contrast", &g_slider, g_slider_max_contrast, on_trackbar);

	for (;;)
	{
		//Captures the frames
		Mat frame;
		cap >> frame;

		//Displays original frames
		namedWindow("Original frame", 1);
		imshow("Original frame", frame);

		//Number of trackbar defined by the user
		int num = g_slider;

		//Derivates for horizontal and vertical changes in Sobel filter
		//If dx = 1 and dy = 0, computes the first derivative Sobel in the x-direction
		//If dx = 0 and dy = 1, computes the first derivative Sobel in the y-direction
		//If dx = 1 and dy = 1, computes the first derivative in both directions
		int dx = 1;
		int dy = 1;

		//Direction for rotating the image
		//If direction = +90, rotates the frame by 90 degrees in clockwise direction
		//If direction = -90, rotates the frame by 90 degrees in counterclockwise
		//If direction = +180, rotates the frame by 180 degrees
		int direction = +90;

		//Type of flipping
		//If flipping = 0,flips the frame over the x-axis
		//If flipping = 1, flips the frame over the y-axis
		int flipping = 1;

		//Gets the width and height of the frame
		int width = frame.size().width;
		int height = frame.size().height;

		//Defines new width and height to resize the frame by hald
		int newWidth = round(width / 2);
		int newHeight = round(height / 2);

		//Functions to perform operations on the frames and show the results
		//Please, comment the functions you are not going to use
		gaussian_blur(frame, gaussianBlur, num, video_gaussian);
		canny_detector(frame, cannyDetector, preprocessedCanny, num, video_canny);
		sobel_filter(frame, sobelFilter, preprocessedSobel, dx, dy, video_sobel);
		change_bright(frame, changedBright, num, video_bright);
		change_contrast(frame, changedContrast, num, video_contrast);
		change_negative(frame, changedNegative, video_negative);
		grayscale(frame, changedGrayscale, video_gray);
		rotate_frame(frame, rotatedFrame, direction);
		flip_frame(frame, flippedFrame, flipping, video_flipped_x);
		flip_frame(frame, flippedFrame, flipping, video_flipped_y);
		resize_frame(frame, resizedFrame, newWidth, newHeight);

		//Stops executing
		if (waitKey(1) == 27) break;
	}

	//Releases captures and videos
	//Please, comment the functions you are not going to use
	cap.release();
	video_gaussian.release();
	video_canny.release();
	video_sobel.release();
	video_bright.release();
	video_contrast.release();
	video_negative.release();
	video_gray.release();
	video_flipped_x.release();
	video_flipped_y.release();

	//Destroy the windows created
	destroyAllWindows();
	return 0;
}