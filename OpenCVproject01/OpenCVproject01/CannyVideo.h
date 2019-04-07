#pragma once;

#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class CannyVideo
{
public:
	CannyVideo();
	~CannyVideo();

	void cannyVid();

private:

	cv::Mat originalFrames;
	cv::Mat grayFrames;
	cv::Mat blurredFrames;
	cv::Mat cannyFrames;

	cv::VideoCapture video;
};