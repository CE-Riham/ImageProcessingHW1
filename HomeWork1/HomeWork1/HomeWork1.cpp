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
    imshow("Grayscale Image", image);
    //waitKey();


    //to make the histogram of the image
    MatND histogram;
    int histSize = 256; //maximum value
    const int* channel_numbers = { 0 }; //grayscale has a single channel
    float channel_range[] = { 0.0, 256.0 };
    const float* channel_ranges = channel_range;
    int number_bins = histSize;

    //images, number of images, channels, mask, hist, dims, histSize, ranges, uniform = true, accumulate = false
    //from opencv2/imgproc.hpp
    calcHist(&image, 1, 0, Mat(), histogram, 1, &number_bins, &channel_ranges);

    //to show the histogram
    int hist_w = 600, hist_h = 400;
    int bin_w = cvRound((double)hist_w / histSize);

    //rows, columns, type, const scalar
    // Use CV_8UC1, ..., CV_64FC4 to create 1-4 channel matrices, or CV_8UC(n), ..., CV_64FC(n) 
    Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));

    //normalize -> to scale and shift the pixel values of an image so that they fall within a specified range.
    //input, output, alpha (the scaling factor), beta (the shifting factor), norm_type, dtype (the data type of the output), mask
    normalize(histogram, histogram, 0, histImage.rows, NORM_MINMAX, -1, Mat());


    for (int i = 1; i < histSize; i++) {

        //input image, point1, point2, scalar
        line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(histogram.at<float>(i - 1))),
            Point(bin_w * i, hist_h - cvRound(histogram.at<float>(i))),
                Scalar(255, 0, 0), 2, 8, 0);
    }

    imshow("histogram", histImage);
    waitKey();


    return 0;
}
