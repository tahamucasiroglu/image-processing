#include <iostream>
#include <string>
#include <locale.h> 
#include <windows.h>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2\opencv.hpp>


using namespace std;




int middle(int d1, int d2, int d3, int d4, int d5, int d6, int d7, int d8);



int main()
{
    uchar r2, r3, r4, r5, r6, r7, r8, r9, g2, g3, g4, g5, g6, g7, g8, g9, b2, b3, b4, b5, b6, b7, b8, b9;
    cv::VideoCapture vCap(0);
    if (vCap.isOpened())
    {
        double fps = vCap.get(cv::CAP_PROP_FPS);
        if (fps < 1)
            fps = 23;
        cv::Mat image, img;
        cv::namedWindow("medyan filter");

        for (;;)
        {
            if (vCap.read(image)) {
                image.copyTo(img);
                for (int x = 1; x < image.rows-1; x++)
                {
                    for (int y = 1; y < image.cols-1; y++)
                    {
                        b2 = image.at<cv::Vec3b>(x - 1, y - 1).val[0];
                        b3 = image.at<cv::Vec3b>(x - 1, y).val[0];
                        b4 = image.at<cv::Vec3b>(x, y - 1).val[0];
                        b5 = image.at<cv::Vec3b>(x + 1, y).val[0];
                        b6 = image.at<cv::Vec3b>(x, y + 1).val[0];
                        b7 = image.at<cv::Vec3b>(x + 1, y + 1).val[0];
                        b8 = image.at<cv::Vec3b>(x + 1, y - 1).val[0];
                        b9 = image.at<cv::Vec3b>(x - 1, y + 1).val[0];
                        img.at<cv::Vec3b>(x, y)[0] = middle(b2, b3, b4, b5, b6, b7, b8, b9);

                        g2 = image.at<cv::Vec3b>(x - 1, y - 1).val[1];
                        g3 = image.at<cv::Vec3b>(x, y - 1).val[1];
                        g4 = image.at<cv::Vec3b>(x - 1, y).val[1];
                        g5 = image.at<cv::Vec3b>(x + 1, y + 1).val[1];
                        g6 = image.at<cv::Vec3b>(x, y + 1).val[1];
                        g7 = image.at<cv::Vec3b>(x + 1, y).val[1];
                        g8 = image.at<cv::Vec3b>(x + 1, y - 1).val[1];
                        g9 = image.at<cv::Vec3b>(x - 1, y + 1).val[1];
                        img.at<cv::Vec3b>(x, y)[1] = middle(g2, g3, g4, g5, g6, g7, g8, g9);

                        r2 = image.at<cv::Vec3b>(x - 1, y - 1).val[2];
                        r3 = image.at<cv::Vec3b>(x, y - 1).val[2];
                        r4 = image.at<cv::Vec3b>(x - 1, y).val[2];
                        r5 = image.at<cv::Vec3b>(x + 1, y + 1).val[2];
                        r6 = image.at<cv::Vec3b>(x, y + 1).val[2];
                        r7 = image.at<cv::Vec3b>(x + 1, y).val[2];
                        r8 = image.at<cv::Vec3b>(x + 1, y - 1).val[2];
                        r9 = image.at<cv::Vec3b>(x - 1, y + 1).val[2];
                        img.at<cv::Vec3b>(x, y)[2] = middle(r2, r3, r4, r5, r6, r7, r8, r9);
                    }
                }
            }
            cv::imshow("medyan filter", img);
            cv::imshow("orjinal", image);
            if (cv::waitKey(30) == 27) {
                break;
            }
        }
    } 
    else
    {
        cout << "Webcam açılamadı ..." << endl;
    }

        
    
    
            
    
        
        vCap.release();
        cv::destroyWindow("medyan filter");
        cv::destroyWindow("orjinal");
    
   
    return 0;
}







int middle(int d1, int d2, int d3, int d4, int d5, int d6, int d7, int d8) {//ortanca bulma 

    int arr[8] = { d1,d2,d3,d4,d5,d6,d7,d8 };

    for (int i = 0; i < 8; i++) 
    {

        for (int j = 0; j < 7; j++) 
        {

            if (arr[i] < arr[j]) {

                int tmp;

                tmp = arr[j];
                arr[j] = arr[i];
                arr[i] = tmp;
            }
        }
    }
    return (arr[3]+arr[4])/2;
}
