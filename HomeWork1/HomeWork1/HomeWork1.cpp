#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
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

    return 0;
}
