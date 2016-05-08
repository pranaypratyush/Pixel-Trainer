/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: pranay
 *
 * Created on 8 May, 2016, 3:36 PM
 */

#include <cstdlib>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "helper.cpp"

using namespace std;
using namespace cv;

/*
 * 
 */
bool lbutton = 0;
string filename;
//bool ctrl_key_state=0;
Mat *dataptr;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
    Mat *image = (Mat*) userdata;
    if (event == EVENT_LBUTTONDOWN)
    {
        cout << "Left button of the mouse is pressed at position (" << x << ", " << y << ")" << endl;
        lbutton = 1;
    }
    else if (event == EVENT_LBUTTONUP)
    {
        cout << "Left button of the mouse is released at position (" << x << ", " << y << ")" << endl;
        lbutton = 0;
    }
    else if (event == EVENT_MOUSEMOVE)
    {
        cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;
        if (flags == EVENT_FLAG_CTRLKEY) //yellow
        {
            circle(*image, Point(x, y), 4, Scalar(0, 255, 255), -1);
            circle(*dataptr, Point(x, y), 4, Scalar(0, 255, 255), -1);
        }
        else if (flags == EVENT_FLAG_ALTKEY) //red
        {
            circle(*image, Point(x, y), 4, Scalar(0, 0, 255), -1);
            circle(*dataptr, Point(x, y), 4, Scalar(0, 0, 255), -1);
        }
        else if (flags == EVENT_FLAG_SHIFTKEY) //green
        {
            circle(*image, Point(x, y), 4, Scalar(0, 255, 0), -1);
            circle(*dataptr, Point(x, y), 4, Scalar(0, 255, 0), -1);
        }
    }
}

void saveCallback(int state, void *userdata)
{
    Mat *image = (Mat*) userdata;
    vector< vector<int> > labels;
    getLabels(*dataptr,labels);
    
    generateTrainFile(filename, getExamples(*image,labels));
    
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        cout << " Usage: display_image ImageToLoadAndDisplay" << endl;
        return -1;
    }

    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR); // Read the file
    filename = argv[1];
    filename += ".txt";
    Mat data(image.rows, image.cols, CV_8UC3);
    dataptr = &data;
    if (!image.data) // Check for invalid input
    {
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }

//    namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
//    imshow("Display window", image); // Show our image inside it.

    Mat denoised;
    fastNlMeansDenoisingColored(image, denoised);

    namedWindow("Denoised image", 1);
    setMouseCallback("Denoised image", CallBackFunc, &denoised);
    imshow("Denoised image", denoised);
//    namedWindow("Data",1);
        
    cvCreateButton("Save",saveCallback,&denoised);
    while (1)
    {
        imshow("Denoised image", denoised);
//        imshow("Data",data);
        if (waitKey(100) == 27)
            break;
    }

    return 0;
}


