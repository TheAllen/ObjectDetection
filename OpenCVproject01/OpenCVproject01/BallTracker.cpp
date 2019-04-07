#include "BallTracker.h"

BallTracker::BallTracker()
{

}

BallTracker::~BallTracker()
{

}

void BallTracker::detectBall()
{
	webCam = cv::VideoCapture(0);
	if (!webCam.isOpened())
	{
		std::cout << "Error: web cam 1 not accessed" << std::endl;
		return;
	}

	while (webCam.read(originalFrame) && webCam.isOpened())
	{
		/*Convert to HSV*/
		cvtColor(originalFrame, HSV, cv::COLOR_BGR2HSV);

		/*Check high and low thresh*/
		cv::inRange(HSV, cv::Scalar(0, 155, 155), cv::Scalar(18, 255, 255), threshLow);
		cv::inRange(HSV, cv::Scalar(165, 155, 155), cv::Scalar(179, 255, 255), threshHigh);

		/*Add*/
		cv::add(threshLow, threshHigh, imageThresh);

		/*Gaussian Blur*/
		cv::GaussianBlur(imageThresh, imageThresh, cv::Size(3, 3), 0);

		cv::Mat structElement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));

		cv::dilate(imageThresh, imageThresh, structElement);
		cv::erode(imageThresh, imageThresh, structElement);

		//Fill circles vector with all circles in processed image
		cv::HoughCircles(imageThresh, v3fCircle, cv::HOUGH_GRADIENT, 2, imageThresh.rows / 4, 100, 50, 10, 400);

		for (int i = 0; i < v3fCircle.size(); i++)
		{
			// draw small green circle at center of detected object
			cv::circle(originalFrame, cv::Point((int)v3fCircle[i][0], (int)v3fCircle[i][1]), 3, cv::Scalar(0, 255, 0), cv::FILLED);
			// draw red circle around the detected object
			cv::circle(originalFrame, cv::Point((int)v3fCircle[i][0], (int)v3fCircle[i][1]), (int)v3fCircle[i][2], cv::Scalar(0, 0, 255), 3);
		}

		cv::namedWindow("imgOriginal", cv::WINDOW_AUTOSIZE);
		cv::namedWindow("imgThresh", cv::WINDOW_AUTOSIZE);

		cv::imshow("imgOriginal", originalFrame);
		cv::imshow("imgThresh", imageThresh);

		if (cv::waitKey(25) >= 0)
			break;
	}
}