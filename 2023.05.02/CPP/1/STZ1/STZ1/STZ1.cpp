#define _USE_MATH_DEFINES

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <ratio>
#include <chrono>
#include <fstream>
using namespace std::chrono;
using namespace cv;
using namespace std;
int main(int, char**)
{
    setlocale(LC_ALL, "Russian");
    Mat frame;
    //--- INITIALIZE VIDEOCAPTURE
    VideoCapture cap;

    cout << "¬ведите название файла или путь файла"<<endl;

    string videoFile = "";
    cin>>videoFile;

    cap.open(videoFile);//"20191119_1241_Cam_1_03_00.mp4");

    int fps= cap.get(CAP_PROP_FPS);
    cout << endl << endl <<"FPS: "<< fps << endl << endl;
    VideoWriter video;


    // check if we succeeded
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open file to read\n";
        return -1;
    }
    //--- GRAB AND WRITE LOOP
    cout << "Start grabbing" << endl
        << "Press any key to terminate" << endl;
    
    int frameID = 0;

    bool videoIsReady = false;


    fstream file;
    file.open("Time.txt", ios::out);

    for (;;)
    {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);

        if (!videoIsReady) {
            
            cout << Size(frame.cols, frame.rows)<<endl;
            video = VideoWriter("ready_Video.mp4", VideoWriter::fourcc('a', 'v', 'c', '1'), fps, Size(frame.cols, frame.rows));
            videoIsReady = true;
        }

        //cout << "\n" << "\n" << frame.cols << " " << frame.rows << "\n" << "\n";
        // check if we succeeded
        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed (stopping)\n";
            break;
        }
        Mat gray;
        cv::cvtColor(frame, gray, COLOR_RGB2GRAY);

        const auto start = 
            steady_clock::now();
        Mat dst;
        cv::Canny(gray, dst, 50, 150);

        vector<Vec4i> linesP; // will hold the results of the detection
        HoughLinesP(dst, linesP, 1, CV_PI / 180, 15, 10, 3); // runs the actual detection
        for (size_t i = 0; i < linesP.size(); i++)
        {
            Vec4i l = linesP[i];
            line(frame, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 1, LINE_AA);
        }
        const auto end = steady_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(end - start);

        // show live and wait for a key with timeout long enough to show images
        imshow("Live", frame);
        if (frame.empty())
            break;

        video.write(frame);
        
        file <<"FrameID=" << frameID << endl;
        file << time_span.count()<<" Seconds spent on this frame" << endl;
        
        
        frameID++;
        if (waitKey(5) >= 0)
            break;
    }
    cout <<endl<<"Video is Opened="<< video.isOpened();
    cout << endl << "Release" << endl;
    video.release();
    cap.release();
    
    destroyAllWindows();
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}