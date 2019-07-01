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
	Mat	frame = imread("clock1.png");
	//imshow("Object", frame);
	Mat blurred;
	GaussianBlur(frame, blurred, Size(7, 7), 1.1);
	//imshow("Blurred", blurred);

	Mat  frame_gray;
	Mat edge_det;
	Mat draw;
	cvtColor(blurred, frame_gray, COLOR_BGR2GRAY);
	//imshow("Gray", frame_gray);
	Canny(frame_gray, edge_det, 60, 340, 3);
	edge_det.convertTo(draw, CV_8U);
	namedWindow("Output", WINDOW_AUTOSIZE);
	imshow("Output", draw);
	
	vector<Vec3f> circles;
	HoughCircles(draw, circles, HOUGH_GRADIENT, 1,
		draw.rows / 1,  // change this value to detect circles with different distances to each other
		100, 30, 100, 125 // change the last two parameters
   // (min_radius & max_radius) to detect larger circles
	);
	for (size_t i = 0; i < circles.size(); i++)
	{
		Vec3i c = circles[i];
		Point center = Point(c[0], c[1]);
		cout << "center  " << center;
		// circle center
		
		Mat frame1;
		frame.copyTo(frame1);
		circle(frame1, center, 1, Scalar(0, 100, 100), 3, LINE_AA);
		// circle outline
		int radius = c[2];
		cout << "radius " << radius;
		circle(frame1, center, radius, Scalar(255, 0, 255), 1, LINE_AA);
		
		Point cen = center;
			int rad = radius;

		//get the Rect containing the circle:
		Rect r(cen.x - rad, cen.y - rad, rad * 2, rad * 2);

		// obtain the image ROI:
		Mat roi(frame, r);

		// make a black mask, same size:
		Mat mask(roi.size(), roi.type(), Scalar::all(0));
		// with a white, filled circle in it:
		circle(mask, Point(radius, radius), radius, Scalar::all(255), -1);

		// combine roi & mask:
		Mat cropped = roi & mask;
		imshow("Cropped", cropped);
		imwrite("cropped.png", cropped);

		imshow("detected circles", frame1);
		waitKey();
	}

}
