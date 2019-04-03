#include "FaceDetection.h"

FaceDetection::FaceDetection()
{
	if (!face_cascade.load(face_cascade_name))  printf("--(!)Error loading face cascade\n");
	if (!eyes_cascade.load(eyes_cascade_name))  printf("--(!)Error loading eyes cascade\n"); 
}

FaceDetection::~FaceDetection()
{

}

void FaceDetection::detectFace(cv::Mat frame) 
{
	std::vector<cv::Rect> faces;
	/*Need to convert to gray frames first*/
	cv::Mat grayFrame;

	cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
	/*Histogram equalization then store it back to grayFrame*/
	/*To improve the contrast of the image*/
	cv::equalizeHist(grayFrame, grayFrame);

	//Detect face
	face_cascade.detectMultiScale(grayFrame, faces, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

	for (size_t i = 0; i < faces.size(); i++)
	{
		cv::Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
		cv::ellipse(frame, center, cv::Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, cv::Scalar(255, 0, 255), 4, 8, 0);

		cv::Mat faceROI = grayFrame(faces[i]);
		std::vector<cv::Rect> eyes;

		//-- In each face, detect eyes
		eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

		for (size_t j = 0; j < eyes.size(); j++)
		{
			cv::Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2);
			int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
			circle(frame, eye_center, radius, cv::Scalar(255, 0, 0), 4, 8, 0);
		}
	}

	cv::imshow(window_title, frame);
}
