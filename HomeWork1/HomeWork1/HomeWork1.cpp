#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
    
int main()
{
    string path = "image.jpg";
    Mat image = imread(path, IMREAD_GRAYSCALE);
    imshow("image", image);
    waitKey(0);
    cout << "Hello World!\n";
}
