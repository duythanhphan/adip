/*
 * adip.h
 *
 *  Created on: Mar 18, 2014
 *      Author: duythanhphan
 */

#include "adip.h"

using namespace std;
using namespace cv;

adip::FN_TYPE fn;

uchar* adip::GetData(Mat image) {
    return image.data;
}

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

    // Show image
    const char *org_name = "Original Image";
    const char *mod_name = "Modified Image";

    namedWindow( org_name, CV_WINDOW_NORMAL );
    namedWindow( mod_name, CV_WINDOW_NORMAL );

    imshow(org_name, org_image);

    // Test function

    //fn = adip::CalcHist;
    //fn = adip::CannyDetector;
    //fn = adip::DFT;
    //fn = adip::EqualizeHist;
    //fn = adip::Laplace;
    fn = adip::Sobel;
    //fn = adip::Threshold;
    //fn = adip::Filter2D;
    //fn = adip::HoughCircle;
    //fn = adip::HoughLines;
    //fn = adip::Remap;
    //fn = adip::Geometric;
    //fn = adip::CopyMakeBorder;
    //fn = adip::BasicLinearTransforms;
    //fn = adip::Smoothing;
    //fn = adip::Morphology_1;
    //fn = adip::Morphology_2;
    //fn = adip::Pyramids;
    //fn = adip::AddingImages;
    //fn = adip::ConnectedComponents;

    //fn = adip::logpolar_bsm;
    //fn = adip::letter_recognize;

    if (!fn) {
        printf("Please specify the test function\n");
        exit(EXIT_FAILURE);
    }

    // Process image and return
    if (fn(org_image, &mod_image) == 0) {
        imshow(mod_name, mod_image);
//        cvtColor(mod_image, org_image, CV_GRAY2RGB);
//        adip::ConnectedComponents(org_image, &mod_image);

        waitKey();
    }

    return 0;
}

