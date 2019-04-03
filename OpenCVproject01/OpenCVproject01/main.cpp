#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <stdint.h>
#include <iostream>
#include <stdio.h>

#include "FaceDetection.h"


using namespace cv;

using namespace std;

#define log(x) std::cout << x << std::endl;

void takeDFT(Mat& source, Mat& destination)
{
	cv::Mat originalComplex[2] = { source, Mat::zeros(source.size(), CV_32F) };

	Mat dftReady;
	merge(originalComplex, 2, dftReady);

	Mat dftOfOriginal;
	dft(dftReady, dftOfOriginal, DFT_COMPLEX_OUTPUT);
	destination = dftOfOriginal;
}

void showDFT(Mat& source)
{
	Mat splitArray[2] = { Mat::zeros(source.size(), CV_32F), Mat::zeros(source.size(), CV_32F) };

	cv::split(source, splitArray);

	/*Magnitude*/
	Mat dftMagnitude;
	magnitude(splitArray[0], splitArray[1], dftMagnitude);

	dftMagnitude += Scalar::all(1);

	log(dftMagnitude, dftMagnitude);

	normalize(dftMagnitude, dftMagnitude, 0, 1, NORM_MINMAX);

	imshow("DFT", dftMagnitude);
	waitKey();
}

void detectAndDisplay(Mat frame);

/*Global variables*/
String face_cascade_name = "";
String eyes_cascade_name = "";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
String title = "Capture - Face detection";
RNG rng(12345);

void videoFeed()
{
	cv::VideoCapture vid(0);
	Mat frames;

	if (!vid.isOpened())
	{
		return;
	}

	while (vid.read(frames))
	{
		imshow("Video Feed", frames);
		if (waitKey(1) >= 0)
		{
			break;
		}
	}

	vid.release();
	destroyAllWindows();
}

void faceDetection()
{

}



int main()
{
	FaceDetection fd;
	
	//videoFeed();
	cv::VideoCapture capture;
	cv::Mat frame;



	capture.open(0);
	if (!capture.isOpened()) 
	{
		printf("Error opening video capture");
		return -1;
	}

	while (capture.read(frame))
	{
		if (frame.empty())
		{
			printf("No captured frame");
			break;
		}

		fd.detectFace(frame);

		if (waitKey(10) >= 0)
			break;

	}

	capture.release();
	destroyAllWindows();

	
	/*cv::Mat image = cv::imread("lena.jpg", cv::IMREAD_UNCHANGED);
	cv::Mat modified = cv::imread("lena.jpg", cv::IMREAD_GRAYSCALE);

	for (int r = 0; r < image.rows; r++) {
		for (int c = 0; c < image.cols; c++) {
			image.at<cv::Vec3b>(r, c)[0] = image.at<cv::Vec3b>(r, c)[0] * 1.25f;
			image.at<cv::Vec3b>(r, c)[1] = image.at<cv::Vec3b>(r, c)[1] * 1.0f;
			image.at<cv::Vec3b>(r, c)[2] = image.at<cv::Vec3b>(r, c)[2] * 1.0f;
		}
	}

	imshow("image", image);
	cv::waitKey();
	cv::destroyAllWindows();*/

	////Get rid of the green property
	//cv::Mat splitScreens[3];

	//cv::split(image, splitScreens);

	//cv::imshow("B", splitScreens[0]);
	//cv::imshow("G", splitScreens[1]);
	//cv::imshow("R", splitScreens[2]);

	//cv::Mat output;

	//splitScreens[2] = cv::Mat::zeros(splitScreens[2].size(), CV_8UC1);

	//cv::merge(splitScreens, 3, output);

	//cv::imshow("Rid of green", output);

	/*cv::namedWindow("Image", cv::WINDOW_FREERATIO);
	cv::resizeWindow("Image", image.cols, image.rows);
	cv::moveWindow("Image", 500, 250);*/

	//cv::imshow("Image", image);
	/*cv::imshow("GrayScale", modified);

	cv::waitKey();
	cv::destroyAllWindows();*/

	//Save Image
	//cv::imwrite("LenaGray.jpg", image);

	/*Web cam*/
	//cv::VideoCapture video(0);
	//if(!video.isOpened())
	//{
	//	return -1;
	//}

	///*Output file*/

	////for saving frame
	//cv::Mat frame;
	//Mat grayFrame;
	//Mat sobelx;
	//double minVal, maxVal;
	//Mat draw;

	//while (video.read(frame))
	//{
	//	cv::imshow("Video feed", frame);
	//	cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
	//	imshow("Gray feed", grayFrame);
	//	Sobel(grayFrame, sobelx, CV_32F, 1, 0);	
	//	minMaxLoc(sobelx, &minVal, &maxVal);
	//	sobelx.convertTo(draw, CV_8U, 255.0 / ( - minVal), -minVal * 255.0 / (maxVal - minVal));

	//	imshow("Sobel Detection", draw);


	//	//End the video early
	//	if (cv::waitKey(25) >= 0)
	//		break;
	//}
	//
	//video.release();
	//destroyAllWindows();

	/*Mat image = imread("lena.jpg", cv::IMREAD_COLOR);
	
	line(image, Point(0, 0), Point(150, 150), cv::Scalar(0, 0, 255), 15);
	cv::rectangle(image, Point(3, 3), Point(500,260), cv::Scalar(0, 255, 255), 5);
	cv::circle(image, Point(250, 130), 65, cv::Scalar(255, 0, 255), 0.1);

	cv::putText(image, "Lena", Point(250, 250), FONT_HERSHEY_SIMPLEX, 1, Scalar(200, 255, 255), 2, LINE_AA);

	cv::namedWindow("Image", WINDOW_AUTOSIZE);
	cv::imshow("Image", image);
	cv::waitKey(0);
	cv::destroyAllWindows();*/

	//Mat img = imread("manhattan.jpg");
	//Mat grey;
	//cvtColor(img, grey, COLOR_BGR2GRAY);
	//Mat sobelx;
	//Sobel(grey, sobelx, CV_32F, 1, 0);
	//double minVal, maxVal;
	//minMaxLoc(sobelx, &minVal, &maxVal); //find minimum and maximum intensities
	//Mat draw;
	//sobelx.convertTo(draw, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));
	//namedWindow("image", cv::WINDOW_AUTOSIZE);
	//imshow("image", draw);
	//waitKey();


	return 0;
}

void detectAndDisplay(Mat frame)
{
	std::vector<Rect> faces;
	Mat grayFrame;

	cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
	equalizeHist(grayFrame, grayFrame);

	/*Detect faces*/
	face_cascade.detectMultiScale(grayFrame, faces, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

	for (int i = 0; i < faces.size(); i++) 
	{

	}
}


