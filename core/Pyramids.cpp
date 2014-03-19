/**
 * @file Pyramids.cpp
 * @brief Sample code of image pyramids (pyrDown and pyrUp)
 * @author OpenCV team
 */

#include "adip.h"

using namespace cv;

/// Global variables
static Mat src, dst, tmp;

static const char* window_name = "Pyramids Demo";

int adip::Pyramids(Mat org_image, Mat *mod_image) {
    /// General instructions
    printf( "\n Zoom In-Out demo  \n " );
    printf( "------------------ \n" );
    printf( " * [u] -> Zoom in  \n" );
    printf( " * [d] -> Zoom out \n" );
    printf( " * [ESC] -> Close program \n \n" );

    /// Test image - Make sure it s divisible by 2^{n}
    src = imread( "images/chicky_512.png" );
    if( !src.data )
    { printf(" No data! -- Exiting the program \n");
      return -1; }

    tmp = src;
    dst = tmp;

    /// Create window
    namedWindow( window_name, CV_WINDOW_AUTOSIZE );
    imshow( window_name, dst );

    /// Loop
    for(;;) {
        int c;
        c = waitKey(10);

        if( (char)c == 27 ) { break; }

        if( (char)c == 'u' ) {
            pyrUp( tmp, dst, Size( tmp.cols*2, tmp.rows*2 ) );
            printf( "** Zoom In: Image x 2 \n" );
        } else if( (char)c == 'd' ) {
            pyrDown( tmp, dst, Size( tmp.cols/2, tmp.rows/2 ) );
            printf( "** Zoom Out: Image / 2 \n" );
        }

        imshow( window_name, dst );
        tmp = dst;
    }

    return 1;
}







