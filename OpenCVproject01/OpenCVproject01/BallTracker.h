#pragma once

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

class BallTracker
{
public:
	BallTracker();
	~BallTracker();

	void detectBall();

private:
	cv::VideoCapture webCam;

	cv::Mat originalFrame;
	cv::Mat HSV;
	cv::Mat threshLow;
	cv::Mat threshHigh;
	cv::Mat imageThresh;

	std::vector<cv::Vec3f> v3fCircle;
};