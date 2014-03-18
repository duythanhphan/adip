/**
 * @file Threshold.cpp
 * @brief Sample code that shows how to use the diverse threshold options offered by OpenCV
 * @author OpenCV team
 */

#include "adip.h"

using namespace cv;

/// Global variables

static int threshold_value = 0;
static int threshold_type = 3;;
static int const max_value = 255;
static int const max_type = 4;
static int const max_BINARY_value = 255;

static Mat src, src_gray, dst;
static const char* window_name = "Threshold Demo";

static const char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
static const char* trackbar_value = "Value";

/**
 * @function Threshold_Demo
 */
void adip::Threshold_Demo(int, void*) {
    /* 0: Binary
     1: Binary Inverted
     2: Threshold Truncated
     3: Threshold to Zero
     4: Threshold to Zero Inverted
    */

    threshold( src_gray, dst, threshold_value, max_BINARY_value,threshold_type );

    imshow( window_name, dst );
}

int adip::Threshold(Mat org_image, Mat *mod_image) {
    /// Load an image
    src = org_image;

    /// Convert the image to Gray
    cvtColor( src, src_gray, CV_RGB2GRAY );

    /// Create a window to display results
    namedWindow( window_name, CV_WINDOW_AUTOSIZE );

    /// Create Trackbar to choose type of Threshold
    createTrackbar( trackbar_type,
          window_name, &threshold_type,
          max_type, Threshold_Demo );

    createTrackbar( trackbar_value,
          window_name, &threshold_value,
          max_value, Threshold_Demo );

    /// Call the function to initialize
    Threshold_Demo( 0, 0 );

    /// Wait until user finishes program
    for(;;) {
        int c;
        c = waitKey( 20 );
        if( (char)c == 27 ) { break; }
    }

    return 1;
}
