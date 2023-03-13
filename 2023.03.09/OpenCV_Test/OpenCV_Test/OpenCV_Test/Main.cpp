#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/highgui/highgui_c.h"
#include <iostream>
#include <fstream>
using namespace cv;
using namespace std;
int main() {
	const char* windname = "image";
	// create a window 
	namedWindow(windname, CV_WINDOW_AUTOSIZE);
	//load the image
	char path[] = "D:\\Projects\\CPP\\Software_Inf_Robot_MSU_spring_2023\\2023.03.09\\OpenCV_Test\\OpenCV_Test\\OpenCV_Test\\x64\\Release\\landscape.png";
	cout << path<<endl;
	ifstream ifile;
	ifile.open(path);
	if (ifile) {
		cout<<("file exists")<<"\n";
	}
	else {
		cout<<("file doesn't exist") << "\n";
	}
	ifile.close();
	Mat frame = imread(path, IMREAD_UNCHANGED);
	// check if the image is valid if( frame.empty())
	if (frame.empty()) {

		cout << "Image cannot be loaded..." << endl;
		return -1;
	}
	// display the image 
	imshow( windname, frame);
	// wait for pressed key
	waitKey(0);
	// destroy the window 
	destroyWindow( windname);
	return 0;
}