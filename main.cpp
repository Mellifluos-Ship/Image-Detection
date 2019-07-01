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
	Mat raw = imread("cropped.png");
	//GaussianBlur(raw, raw, Size(5, 5), 0.0);
	//imshow("Raw Blurred", raw);
	Mat rawGray;
	cvtColor(raw, rawGray, COLOR_BGR2GRAY);
	imshow("GrayRaw", rawGray);


	Mat rawBlur;
	bilateralFilter(rawGray, rawBlur, 10, 50, 100);
	//imshow("Raw Blurred", rawBlur);



	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	Mat grad;

	
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;

	
	
	Sobel(rawGray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);

	
	Sobel(rawGray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);

	
	addWeighted(abs_grad_x, 0.4, abs_grad_y, 0.4, 0, grad);
	imshow("Gradient", grad);
	Mat rawEdge;
	Canny(grad, rawEdge, 70, 500, 3);
	imshow("Raw Canny", rawEdge);

	if (0) {
		vector<Vec2f> lines;
		HoughLines(rawEdge, lines, 1, CV_PI / 180, 50, 0, 0);

		for (size_t i = 0; i < lines.size(); i++)
		{
			float rho = lines[i][0], theta = lines[i][1];
			Point pt1, pt2;
			double a = cos(theta), b = sin(theta);
			double x0 = a * rho, y0 = b * rho;
			pt1.x = cvRound(x0 + 1000 * (-b));
			pt1.y = cvRound(y0 + 1000 * (a));
			pt2.x = cvRound(x0 - 1000 * (-b));
			pt2.y = cvRound(y0 - 1000 * (a));
			line(raw, pt1, pt2, Scalar(255, 0, 255), 1, LINE_AA);

		}
	}
	else {
		vector<Vec4i> lines;
		HoughLinesP(rawEdge, lines, 1, CV_PI / 180, 78, 78, 10);
		for (size_t i = 0; i < lines.size(); i++)
		{
			Vec4i l = lines[i];
			line(raw, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 1, LINE_AA);
		}
	}
	


	imshow("detected lines", raw);
	waitKey();
}
