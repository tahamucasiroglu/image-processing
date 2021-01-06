#include <iostream>
#include <string>
#include<locale.h> 
#include "opencv2/imgcodecs.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2\opencv.hpp>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Turkish");
    string resim_adresi = "cami.jpg";
    string panelismi = "kontrol paneli";
    cv::Mat resim,temp,img,img2,opening,closing, opening_temp,closing_temp;
    string resimadi = "black or white changing with trackbar";
    int sinir = 128;
    int eresyon = 0;
    int dilation = 0;
    int opening_ = 0;
    int closing_ = 0;
    int w=300,h=300;
    resim = cv::imread(resim_adresi);
    if (resim.empty()) { cout << "resim açýlamadý"; }
    cv::namedWindow(panelismi, cv::WINDOW_AUTOSIZE);
    
    cv::namedWindow(resimadi, cv::WINDOW_AUTOSIZE);
    uchar red, green, blue, bw;

    cv::createTrackbar("sinir",panelismi , &sinir, 255);
    cv::createTrackbar("erode", panelismi, &eresyon, 1);
    cv::createTrackbar("dilate", panelismi, &dilation, 1);
    cv::createTrackbar("opening", panelismi, &opening_, 1);
    cv::createTrackbar("closing", panelismi, &closing_, 1);
    cv::createTrackbar("boyut-W", panelismi, &w, 1920);
    cv::createTrackbar("boyut-H", panelismi, &h, 1080);

    
    while (true) {
    cv::resize(resim, resim, cv::Size(w, h));
        resim.copyTo(temp);
        for (int x = 0; x < temp.cols; x++)
        {
            for (int y = 0; y < temp.rows; y++)
            {
                blue = temp.at<cv::Vec3b>(y, x)[0];
                green = temp.at<cv::Vec3b>(y, x)[1];
                red = temp.at<cv::Vec3b>(y, x)[2];

                bw = (red + green + blue) / 3;
                if (bw <= sinir) {
                    temp.at<cv::Vec3b>(y, x)[0] = 0;
                    temp.at<cv::Vec3b>(y, x)[1] = 0;
                    temp.at<cv::Vec3b>(y, x)[2] = 0;
                }
                else {
                    temp.at<cv::Vec3b>(y, x)[0] = 255;
                    temp.at<cv::Vec3b>(y, x)[1] = 255;
                    temp.at<cv::Vec3b>(y, x)[2] = 255;
                }
            }
        }
        if (eresyon == 1) {
            temp.copyTo(img2);
            for (int x = 1; x < temp.cols - 1; x++)
            {
                for (int y = 1; y < temp.rows - 1; y++)
                {
                    if (temp.at<cv::Vec3b>(y - 1, x - 1)[0] == 255 || temp.at<cv::Vec3b>(y - 1, x)[0] == 255 || temp.at<cv::Vec3b>(y, x - 1)[0] == 255 || temp.at<cv::Vec3b>(y + 1, x)[0] == 255 || temp.at<cv::Vec3b>(y, x + 1)[0] == 255 || temp.at<cv::Vec3b>(y + 1, x + 1)[0] == 255 || temp.at<cv::Vec3b>(y + 1, x - 1)[0] == 255 || temp.at<cv::Vec3b>(y - 1, x + 1)[0] == 255) {
                    img2.at<cv::Vec3b>(y, x)[0] = 255;
                    img2.at<cv::Vec3b>(y, x)[1] = 255;
                    img2.at<cv::Vec3b>(y, x)[2] = 255;

                    }
                }
            }
            cv::imshow("erode", img2);
        }
        else {
            cv::destroyWindow("erode");
        }
        if (dilation == 1) {
            temp.copyTo(img);
            for (int x = 1; x < temp.cols - 1; x++)
            {
                for (int y = 1; y < temp.rows - 1; y++)
                {
                    if (temp.at<cv::Vec3b>(y - 1, x - 1)[0] == 0 || temp.at<cv::Vec3b>(y - 1, x)[0] == 0 || temp.at<cv::Vec3b>(y, x - 1)[0] == 0 || temp.at<cv::Vec3b>(y + 1, x)[0] == 0 || temp.at<cv::Vec3b>(y, x + 1)[0] == 0 || temp.at<cv::Vec3b>(y + 1, x + 1)[0] == 0 || temp.at<cv::Vec3b>(y + 1, x - 1)[0] == 0 || temp.at<cv::Vec3b>(y - 1, x + 1)[0] == 0) {
                        img.at<cv::Vec3b>(y, x)[0] = 0;
                        img.at<cv::Vec3b>(y, x)[1] = 0;
                        img.at<cv::Vec3b>(y, x)[2] = 0;

                    }
                }
            }
            cv::imshow("dilation", img);
        }
        else {
            cv::destroyWindow("dilation");
        }
            
        if (opening_ == 1) {
            temp.copyTo(opening);
            for (int x = 1; x < temp.cols - 1; x++)
            {
                for (int y = 1; y < temp.rows - 1; y++)
                {
                    if (temp.at<cv::Vec3b>(y - 1, x - 1)[0] == 255 || temp.at<cv::Vec3b>(y - 1, x)[0] == 255 || temp.at<cv::Vec3b>(y, x - 1)[0] == 255 || temp.at<cv::Vec3b>(y + 1, x)[0] == 255 || temp.at<cv::Vec3b>(y, x + 1)[0] == 255 || temp.at<cv::Vec3b>(y + 1, x + 1)[0] == 255 || temp.at<cv::Vec3b>(y + 1, x - 1)[0] == 255 || temp.at<cv::Vec3b>(y - 1, x + 1)[0] == 255) {
                        opening.at<cv::Vec3b>(y, x)[0] = 255;
                        opening.at<cv::Vec3b>(y, x)[1] = 255;
                        opening.at<cv::Vec3b>(y, x)[2] = 255;

                    }
                }
            }
           opening.copyTo(opening_temp);
            for (int x = 1; x < opening.cols - 1; x++)
            {
                for (int y = 1; y < opening.rows - 1; y++)
                {
                    if (opening.at<cv::Vec3b>(y - 1, x - 1)[0] == 0 || opening.at<cv::Vec3b>(y - 1, x)[0] == 0 || opening.at<cv::Vec3b>(y, x - 1)[0] == 0 || opening.at<cv::Vec3b>(y + 1, x)[0] == 0 || opening.at<cv::Vec3b>(y, x + 1)[0] == 0 || opening.at<cv::Vec3b>(y + 1, x + 1)[0] == 0 || opening.at<cv::Vec3b>(y + 1, x - 1)[0] == 0 || opening.at<cv::Vec3b>(y - 1, x + 1)[0] == 0) {
                        opening_temp.at<cv::Vec3b>(y, x)[0] = 0;
                        opening_temp.at<cv::Vec3b>(y, x)[1] = 0;
                        opening_temp.at<cv::Vec3b>(y, x)[2] = 0;

                    }
                }
            }

            cv::imshow("opening", opening_temp);
        }
        else {
            cv::destroyWindow("opening");
        }
        if (closing_ == 1) {
            temp.copyTo(closing);
            for (int x = 1; x < temp.cols - 1; x++)
            {
                for (int y = 1; y < temp.rows - 1; y++)
                {
                    if (temp.at<cv::Vec3b>(y - 1, x - 1)[0] ==0 || temp.at<cv::Vec3b>(y - 1, x)[0] ==0 || temp.at<cv::Vec3b>(y, x - 1)[0] == 0 || temp.at<cv::Vec3b>(y + 1, x)[0] == 0 || temp.at<cv::Vec3b>(y, x + 1)[0] == 0 || temp.at<cv::Vec3b>(y + 1, x + 1)[0] == 0 || temp.at<cv::Vec3b>(y + 1, x - 1)[0] == 0 || temp.at<cv::Vec3b>(y - 1, x + 1)[0] == 0) {
                        closing.at<cv::Vec3b>(y, x)[0] = 0;
                        closing.at<cv::Vec3b>(y, x)[1] = 0;
                        closing.at<cv::Vec3b>(y, x)[2] = 0;

                    }
                }
            }
            closing.copyTo(closing_temp);
            for (int x = 1; x < closing.cols - 1; x++)
            {
                for (int y = 1; y < closing.rows - 1; y++)
                {
                    if (opening.at<cv::Vec3b>(y - 1, x - 1)[0] == 255 || opening.at<cv::Vec3b>(y - 1, x)[0] == 255 || opening.at<cv::Vec3b>(y, x - 1)[0] == 255|| opening.at<cv::Vec3b>(y + 1, x)[0] == 255 || opening.at<cv::Vec3b>(y, x + 1)[0] == 255 || opening.at<cv::Vec3b>(y + 1, x + 1)[0] == 255 || opening.at<cv::Vec3b>(y + 1, x - 1)[0] == 255 || opening.at<cv::Vec3b>(y - 1, x + 1)[0] == 255) {
                        closing_temp.at<cv::Vec3b>(y, x)[0] = 255;
                        closing_temp.at<cv::Vec3b>(y, x)[1] = 255;
                        closing_temp.at<cv::Vec3b>(y, x)[2] = 255;

                    }
                }
            }

            cv::imshow("closing",closing_temp);
        }
        else {
            cv::destroyWindow("closing");
        }
        cv::imshow(resimadi, temp);
        cv::imshow("orginal", resim);
        if (cv::waitKey(100) == 27) {
            break;
        }
    }
    

    cv::destroyAllWindows();
    return 0;



}
