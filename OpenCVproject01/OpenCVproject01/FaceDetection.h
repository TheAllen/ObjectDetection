#pragma once

#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class FaceDetection
{
public:
	FaceDetection();
	~FaceDetection();

	void detectFace(cv::Mat frame);

	cv::CascadeClassifier face_cascade;
	cv::CascadeClassifier eyes_cascade;

	std::string face_cascade_name = "haarcascade_frontalface_alt.xml";
	std::string eyes_cascade_name = "haarcascade_frontalface_alt_tree.xml";
	const char* window_title = "Cascade Face Detection";
};