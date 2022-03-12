#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    int camera = 1;
    VideoCapture cap;
    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    if (!cap.open(camera))
        return 0;

    for (;;)
    {
        Mat frame;
        cap >> frame;
        if (frame.empty()) break; // end of video stream

        namedWindow("Original frame", WINDOW_AUTOSIZE);
        namedWindow("Processed frame", WINDOW_AUTOSIZE);

        imshow("Original frame", frame);
        imshow("Processed frame", frame);

        if (waitKey(1) == 27) break; // stop capturing by pressing ESC
    }
    cap.release();  // release the VideoCapture object
    return 0;
}