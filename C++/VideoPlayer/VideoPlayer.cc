/*
 * VideoPlayer.cc
 *
 *  Created on: Feb 27, 2014
 *      Author: vix
 */

#include <iostream>
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

int main(int argc, char* argv[]){

	cout<<"Test"<<endl;

	VideoCapture cap;

	cap.open("http://88.212.10.27:81/streams/joj.m3u8");

	if ( !cap.isOpened() )  // if not success, exit program
	{
		cout << "Cannot open the video file" << endl;
		return -1;
	}

	double fps = cap.get(CV_CAP_PROP_FPS); //get the frames per seconds of the video
	int width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	int height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	int fourcc = cap.get(CV_CAP_PROP_FOURCC);
	int format = cap.get(CV_CAP_PROP_FORMAT);
	int mode = cap.get(CV_CAP_PROP_MODE);

	cout << "Frame per seconds : " << fps << endl;
	cout << "Width : " << width << endl;
	cout << "Height : " << height << endl;
	cout << "Fourcc : " << fourcc << endl;
	cout << "Format : " << format << endl;
	cout << "Mode : " << mode << endl;

	namedWindow("My Video Player",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

	while(1)
	{
		Mat frame;

		bool bSuccess = cap.read(frame); // read a new frame from video

		 if (!bSuccess) //if not success, break loop
		{
						cout << "Cannot read the frame from video file" << endl;
					   break;
		}

		imshow("My Video Player", frame); //show the frame in "MyVideo" window

		if(waitKey(30) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
	   {
				cout << "esc key is pressed by user" << endl;
				break;
	   }
	}

	return 0;
}
