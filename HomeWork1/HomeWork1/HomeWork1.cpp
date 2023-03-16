#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
    
int main()
{
    //to show the image in grayscale
    string path = "image.jpg";
    Mat image = imread(path, IMREAD_GRAYSCALE);

    //resize the image (w, h)
    resize(image, image, Size(600, 400));
    imshow("image", image);
    waitKey(0);


    //to make the histogram of the image
    MatND histogram;
    int histSize = 256; //maximum value
    const int* channel_numbers = { 0 }; //grayscale has a single channel
    float channel_range[] = { 0.0, 256.0 };
    const float* channel_ranges = channel_range;
    int number_bins = histSize;

    //image, channels, mask, histSize, ranges
    //from opencv2/imgproc.hpp
    calcHist(&image, 1, 0, Mat(), histogram, 1, &number_bins, &channel_ranges);


}
