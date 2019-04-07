#include "CannyVideo.h"

CannyVideo::CannyVideo()
{
}

CannyVideo::~CannyVideo()
{

}

void CannyVideo::cannyVid()
{

	video.open(0);
	while (video.read(originalFrames))
	{
		cv::cvtColor(originalFrames, grayFrames, cv::COLOR_BGR2GRAY);

		/*Gaussian blurr*/
		cv::GaussianBlur(grayFrames, blurredFrames, cv::Size(5, 5), 1.8);

		/*Canny*/
		cv::Canny(blurredFrames, cannyFrames, 50, 100);

		cv::namedWindow("Original Feed", cv::WINDOW_NORMAL);
		cv::namedWindow("Canny Feed", cv::WINDOW_NORMAL);

		cv::imshow("Original Feed", originalFrames);
		cv::imshow("Canny Feed", cannyFrames);

		if (cv::waitKey(25) >= 0)
			break;
	}
}