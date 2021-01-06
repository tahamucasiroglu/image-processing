

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;

int main()
{
    cout << "Webcam Player " << endl;
    string wName = "Webcam Player";
    uchar red, green, blue, bw=0;
    cv::VideoCapture vCap(0);
    if (vCap.isOpened())
    {
        double fps = vCap.get(cv::CAP_PROP_FPS);
        if (fps < 1) // her zaman donanımdan doğru şekilde fps yi çekemiyor
            fps = 23;
        cv::Mat frame,temp;
        cv::namedWindow(wName);
       
        for (;;)
        {
            if (vCap.read(frame)) {
                
                for (int x = 0; x < frame.cols; x++)
                {
                    for (int y = 0; y < frame.rows; y++)
                    {
                        blue = frame.at<cv::Vec3b>(y, x)[0];
                        green = frame.at<cv::Vec3b>(y, x)[1];
                        red = frame.at<cv::Vec3b>(y, x)[2];
                       
                         bw = (red + green + blue) / 3;
                         if (bw <= 127) {
                             frame.at<cv::Vec3b>(y, x)[0] = 0;
                             frame.at<cv::Vec3b>(y, x)[1] = 0;
                             frame.at<cv::Vec3b>(y, x)[2] = 0;
                         }
                         else {
                          frame.at<cv::Vec3b>(y, x)[0] = 255;
                          frame.at<cv::Vec3b>(y, x)[1] = 255;
                          frame.at<cv::Vec3b>(y, x)[2] = 255;
                         }
                    }
                }
                frame.copyTo(temp);
                for (int x = 1; x < frame.cols-1; x++)
                {
                    for (int y = 1; y < frame.rows-1; y++)
                    {
                        if (frame.at<cv::Vec3b>(y - 1, x - 1)[0] == 0 || frame.at<cv::Vec3b>(y - 1, x)[0] == 0 || frame.at<cv::Vec3b>(y, x - 1)[0] == 0 || frame.at<cv::Vec3b>(y + 1, x)[0] == 0 || frame.at<cv::Vec3b>(y, x + 1)[0] == 0 ||frame.at<cv::Vec3b>(y + 1, x + 1)[0] == 0) {
                            temp.at<cv::Vec3b>(y, x)[0] = 0;
                            temp.at<cv::Vec3b>(y, x)[1] = 0;
                            temp.at<cv::Vec3b>(y, x)[2] = 0;

                            
                        }
                    }
                }

                cv::imshow(wName, frame);
                cv::imshow("temp", temp);
            }
            if (cv::waitKey(1000 / fps) == 27)
                break;
        }
        vCap.release();
        cv::destroyWindow(wName);
        cv::destroyWindow("temp");
    }
    else
    {
        cout << "Web Cam Not Opened ..." << endl;
    }
    return 0;
}
