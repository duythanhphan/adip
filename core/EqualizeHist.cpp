/**
 * @function EqualizeHist_Demo.cpp
 * @brief Demo code for equalizeHist function
 * @author OpenCV team
 */

#include "adip.h"

using namespace cv;
using namespace std;

int adip::EqualizeHist(Mat org_image, Mat *mod_image) {
    Mat src, dst;

    /// Load image
    src = org_image;

    /// Convert to grayscale
    cvtColor( src, src, CV_BGR2GRAY );

    /// Apply Histogram Equalization
    equalizeHist( src, dst );

    *mod_image = dst;

    return 0;
}

