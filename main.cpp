/*
 * adip.h
 *
 *  Created on: Mar 18, 2014
 *      Author: duythanhphan
 */

#include "adip.h"

using namespace std;
using namespace cv;

typedef int (*FN_TYPE) (Mat org_image, Mat *mod_image);
FN_TYPE fn;

int main(int argc, char** argv) {
    Mat org_image, mod_image;

    if (argc < 2) {
        printf("Usage: <program> <image_file>\n");
        exit(EXIT_FAILURE);
    }

    // Load image
    org_image = imread(argv[1]);
    if( org_image.empty() ) {
        printf("Cannot read image file: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Test function

    //fn = adip::CalcHist;
    //fn = adip::CannyDetector;
    //fn = adip::DFT;
    //fn = adip::EqualizeHist;
    //fn = adip::Laplace;

    //fn = adip::Sobel;
    //fn = adip::Threshold;
    //fn = adip::Filter2D;
    //fn = adip::HoughCircle;
    //fn = adip::HoughLines;
    //fn = adip::Remap;
    //fn = adip::Geometric;
    //fn = adip::CopyMakeBorder;

    if (!fn) {
        printf("Please specify the test function\n");
        exit(EXIT_FAILURE);
    }

    // Process image and return
    if (fn(org_image, &mod_image) == 0) {
        // Show image
        imshow("Original Image", org_image);
        imshow("Modified Image", mod_image);

        waitKey();
    }

    return 0;
}

