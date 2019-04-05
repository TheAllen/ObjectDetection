#include "CannySill.h"

CannyStill::CannyStill()
{

}


CannyStill::~CannyStill()
{

}

void CannyStill::canny(const char* image)
{
	originalImage = cv::imread(image);
	if (originalImage.empty())
	{
		std::cout << "Error loading the image" << std::endl;
		return;
	}

	cv::cvtColor(originalImage, grayscaleImage, cv::COLOR_BGR2GRAY);

	/*Gaussian blur*/
	cv::GaussianBlur(grayscaleImage, blurredImage, cv::Size(5, 5), 1.5);

	/*Canny*/
	cv::Canny(blurredImage, cannyImage, 82, 164);

	cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Canny Image", cv::WINDOW_AUTOSIZE);

	cv::imshow("Original", originalImage);
	cv::imshow("Canny Image", cannyImage);


}