/**
 * @file copyMakeBorder_demo.cpp
 * @brief Sample code that shows the functionality of copyMakeBorder
 * @author OpenCV team
 */

#include "adip.h"

using namespace cv;

/// Global Variables
static Mat src, dst;
static int top, bottom, left, right;
static int borderType;
static Scalar value;
static const char* window_name = "copyMakeBorder Demo";
static RNG rng(12345);

int adip::CopyMakeBorder(Mat org_image, Mat *mod_image) {
    int c;

    /// Load an image
    src = org_image;

    /// Brief how-to for this program
    printf( "\n \t copyMakeBorder Demo: \n" );
    printf( "\t -------------------- \n" );
    printf( " ** Press 'c' to set the border to a random constant value \n");
    printf( " ** Press 'r' to set the border to be replicated \n");
    printf( " ** Press 'ESC' to exit the program \n");

    /// Create window
    namedWindow( window_name, CV_WINDOW_AUTOSIZE );

    /// Initialize arguments for the filter
    top = (int) (0.05*src.rows); bottom = (int) (0.05*src.rows);
    left = (int) (0.05*src.cols); right = (int) (0.05*src.cols);
    dst = src;

    imshow( window_name, dst );

    for(;;) {
        c = waitKey(500);

        if( (char)c == 27 ) { break; }
        else if( (char)c == 'c' ) { borderType = BORDER_CONSTANT; }
        else if( (char)c == 'r' ) { borderType = BORDER_REPLICATE; }

        value = Scalar( rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255) );
        copyMakeBorder( src, dst, top, bottom, left, right, borderType, value );

        imshow( window_name, dst );
    }

    return 1;
}
