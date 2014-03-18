/**
 * @file Laplace_Demo.cpp
 * @brief Sample code showing how to detect edges using the Laplace operator
 * @author OpenCV team
 */

#include "adip.h"

using namespace cv;

int adip::Laplace(Mat org_image, Mat *mod_image) {
    Mat src, src_gray, dst;
    int kernel_size = 3;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    /// Load an image
    src = org_image;

    /// Remove noise by blurring with a Gaussian filter
    GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

    /// Convert the image to grayscale
    cvtColor( src, src_gray, CV_RGB2GRAY );

    /// Apply Laplace function
    Mat abs_dst;

    Laplacian( src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( dst, abs_dst );

    *mod_image = abs_dst;

    return 0;
}
