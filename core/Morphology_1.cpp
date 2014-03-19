/**
 * @file Morphology_1.cpp
 * @brief Erosion and Dilation sample code
 * @author OpenCV team
 */

#include "adip.h"

using namespace cv;

/// Global variables
static Mat src, erosion_dst, dilation_dst;

static int erosion_elem = 0;
static int erosion_size = 0;
static int dilation_elem = 0;
static int dilation_size = 0;
static int const max_elem = 2;
static int const max_kernel_size = 21;

/** Function Headers */
static void Erosion( int, void* );
static void Dilation( int, void* );

int adip::Morphology_1(Mat org_image, Mat *mod_image) {
    /// Load an image
    src = org_image;

    /// Create windows
    namedWindow( "Erosion Demo", CV_WINDOW_AUTOSIZE );
    namedWindow( "Dilation Demo", CV_WINDOW_AUTOSIZE );
    cvMoveWindow( "Dilation Demo", src.cols, 0 );

    /// Create Erosion Trackbar
    createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erosion Demo",
          &erosion_elem, max_elem,
          Erosion );

    createTrackbar( "Kernel size:\n 2n +1", "Erosion Demo",
          &erosion_size, max_kernel_size,
          Erosion );

    /// Create Dilation Trackbar
    createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Dilation Demo",
          &dilation_elem, max_elem,
          Dilation );

    createTrackbar( "Kernel size:\n 2n +1", "Dilation Demo",
          &dilation_size, max_kernel_size,
          Dilation );

    /// Default start
    Erosion( 0, 0 );
    Dilation( 0, 0 );

    waitKey(0);
    return 1;
}

/**
 * @function Erosion
 */
static void Erosion( int, void* )
{
    int erosion_type = 0;
    if( erosion_elem == 0 ){ erosion_type = MORPH_RECT; }
    else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; }
    else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }

    Mat element = getStructuringElement( erosion_type,
                       Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                       Point( erosion_size, erosion_size ) );
    /// Apply the erosion operation
    erode( src, erosion_dst, element );
    imshow( "Erosion Demo", erosion_dst );
}

/**
 * @function Dilation
 */
static void Dilation( int, void* )
{
    int dilation_type = 0;
    if( dilation_elem == 0 ){ dilation_type = MORPH_RECT; }
    else if( dilation_elem == 1 ){ dilation_type = MORPH_CROSS; }
    else if( dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }

    Mat element = getStructuringElement( dilation_type,
                       Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                       Point( dilation_size, dilation_size ) );
    /// Apply the dilation operation
    dilate( src, dilation_dst, element );
    imshow( "Dilation Demo", dilation_dst );
}
