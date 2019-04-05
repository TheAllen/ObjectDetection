#pragma once;

#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


class CannyStill
{
public:
	CannyStill();
	~CannyStill();


	cv::Mat originalImage;
	cv::Mat grayscaleImage;
	cv::Mat blurredImage;
	cv::Mat cannyImage;

	void canny(const char* image);

};