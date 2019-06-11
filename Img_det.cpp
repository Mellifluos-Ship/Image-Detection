#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui.hpp"
#include <stdio.h>
#include <stdint.h>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat	frame = imread("clock1.png", IMREAD_COLOR);
	imshow("Object", frame);

	Mat  frame_gray;
	Mat edge_det;
	Mat draw;

	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	Canny(frame_gray, edge_det, 20, 300, 3);
	edge_det.convertTo(draw, CV_8U);
	namedWindow("Output", WINDOW_AUTOSIZE);
	imshow("Output", draw);
	waitKey(0);





}