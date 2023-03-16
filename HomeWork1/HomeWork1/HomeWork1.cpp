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
    //waitKey();

    //modify the brightness using a random gamma
    double gamma = rand() / 25.0;


    Mat lookupTable(1, 256, CV_8U);
    uchar* p = lookupTable.ptr();
    for (int i = 0; i < 256; i++) {
        //saturate_cast to clamp the resulting value correctly
        //uchar range [0, 255]
        p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma) * 255.0);
    }

    //using look up table
    Mat lookUpTableImage;
    TickMeter timer1;
    timer1.start();
    LUT(image, lookupTable, lookUpTableImage);
    timer1.stop();


    //modifying each pixel individually
    TickMeter timer2;
    timer2.start();
    Mat eachPixelImage(400, 600, CV_8UC1);

    for (int i = 0; i < 400; i++) {
        for (int j = 0; j < 600; j++) {
            eachPixelImage.at<uchar>(i, j) = saturate_cast<uchar>(pow(image.at<uchar>(i, j) / 255.0, gamma) * 255.0);
        }
    }
    timer2.stop();

    //show the resultant images
    imshow("Look Up Table Image", lookUpTableImage);
    imshow("Each Pixel Individually Image", eachPixelImage);
    //waitKey();

    //show the comparision result
    cout << "Look Up Table method required time: " << timer1.getTimeMilli() << "ms" << endl
        << "Modifying Each Pixel Individually required time: " << timer2.getAvgTimeMilli() << "ms" << endl;
    waitKey();

    imshow("image", image);
    waitKey(0);

    return 0;
}
