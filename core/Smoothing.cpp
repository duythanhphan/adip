/**
 * file Smoothing.cpp
 * brief Sample code for simple filters
 * author OpenCV team
 */

#include "adip.h"

using namespace std;
using namespace cv;

/// Global Variables
static int DELAY_CAPTION = 1500;
static int DELAY_BLUR = 100;
static int MAX_KERNEL_LENGTH = 31;

static Mat src, dst;
static char window_name[] = "Smoothing Demo";

/**
 * @function display_caption
 */
static int display_caption(const char* caption) {
    dst = Mat::zeros( src.size(), src.type() );
    putText( dst, caption,
           Point( src.cols/4, src.rows/2),
           CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255) );

    imshow( window_name, dst );
    int c = waitKey( DELAY_CAPTION );
    if( c >= 0 ) { return -1; }
    return 0;
}

/**
 * @function display_dst
 */
static int display_dst(int delay) {
    imshow( window_name, dst );
    int c = waitKey ( delay );
    if( c >= 0 ) { return -1; }
    return 0;
}

int adip::Smoothing(Mat org_image, Mat *mod_image) {
    namedWindow( window_name, CV_WINDOW_AUTOSIZE );

    /// Load the source image
    src = org_image;

    if( display_caption( "Original Image" ) != 0 ) { return 0; }

    dst = src.clone();
    if( display_dst( DELAY_CAPTION ) != 0 ) { return 0; }


    /// Applying Homogeneous blur
    if( display_caption( "Homogeneous Blur" ) != 0 ) { return 0; }

    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 ) {
        blur( src, dst, Size( i, i ), Point(-1,-1) );
        if( display_dst( DELAY_BLUR ) != 0 ) { return 0; }
    }

    /// Applying Gaussian blur
    if( display_caption( "Gaussian Blur" ) != 0 ) { return 0; }

    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 ) {
        GaussianBlur( src, dst, Size( i, i ), 0, 0 );
        if( display_dst( DELAY_BLUR ) != 0 ) { return 0; }
    }

    /// Applying Median blur
    if( display_caption( "Median Blur" ) != 0 ) { return 0; }

    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 ) {
        medianBlur ( src, dst, i );
        if( display_dst( DELAY_BLUR ) != 0 ) { return 0; }
    }

    /// Applying Bilateral Filter
    if( display_caption( "Bilateral Blur" ) != 0 ) { return 0; }

    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 ) {
        bilateralFilter ( src, dst, i, i*2, i/2 );
        if( display_dst( DELAY_BLUR ) != 0 ) { return 0; }
    }

    /// Wait until user press a key
    display_caption( "End: Press a key!" );

    waitKey(0);

    return 0;
}

