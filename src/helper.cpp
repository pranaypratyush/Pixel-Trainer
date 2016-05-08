#include <iostream>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
using namespace cv;

Mat createImage(int height, int width)
/* 
        This function creates a black image
        with values (0, 0, 0) intially 
 */
{
    Mat image(height, width, CV_8UC3, Scalar(0, 0, 0));
    return image;
}

void getLabels(Mat &data, vector< vector<int> > &label)
/*
        This function outputs a 2d vector label which 
        has information about label of each pixel
 */
{
    for (int i = 0; i < data.rows; ++i)
    {
        for (int j = 0; j < data.cols; ++j)
        {
            Vec3b &Color = data.at<Vec3b>(Point(i, j));

            if (Color[0] == 0 && Color[1] == 255 && Color[0] == 255) // Yellow pixel
                label[i][j] = 0;

            else if (Color[0] == 0 && Color[1] == 255 && Color[2] == 0) // GREEN pixel
                label[i][j] = 1;

            else if (Color[0] == 0 && Color[1] == 0 && Color[2] == 255) // RED pixel
                label[i][j] = 1;

            else // BLACK pixel
                label[i][j] = -1;
        }
    }
}

void writeExamples(String filename, Mat image, vector < vector<int> > label)
/*
        This function writes every pixel attributes to specified 
        text file	
 */
{
    ofstream trainfile(filename.c_str());
    if (!trainfile.is_open())
        cout << "Error opening " << filename << ".txt file";

    else
    {
        String example = "";
        Mat hsv_image;
        ostringstream ss;
        cvtColor(image, hsv_image, CV_BGR2HSV);
        for (int i = 0; i < hsv_image.rows; ++i)
        {
            for (int j = 0; j < hsv_image.cols; ++j)
            {
                example = "";

                Vec3b hsv = hsv_image.at<Vec3b>(Point(i, j));

                ss << label[i][j];
                example += ss.str(); // Append label
                example += ",";

                ss << hsv[0];
                example += ss.str(); // Append H value
                example += ",";

                ss << hsv[1];
                example += ss.str(); // Append S value
                example += ",";

                ss << hsv[2];
                example += ss.str(); // Append V value
                example += ";";

                example += "\n";

                trainfile << example;
            }
        }
    }

}