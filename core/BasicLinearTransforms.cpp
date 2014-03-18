/**
 * @file BasicLinearTransforms.cpp
 * @brief Simple program to change contrast and brightness
 * @author OpenCV team
 */

#include "adip.h"
#include <iostream>

using namespace cv;

static double alpha; /**< Simple contrast control */
static int beta;  /**< Simple brightness control */

int adip::BasicLinearTransforms(Mat org_image, Mat *mod_image) {
    /// Read image given by user
    Mat image = org_image;
    Mat new_image = Mat::zeros( image.size(), image.type() );

    /// Initialize values
    std::cout<<" Basic Linear Transforms "<<std::endl;
    std::cout<<"-------------------------"<<std::endl;
    std::cout<<"* Enter the alpha value [1.0-3.0]: ";std::cin>>alpha;
    std::cout<<"* Enter the beta value [0-100]: "; std::cin>>beta;


    /// Do the operation new_image(i,j) = alpha*image(i,j) + beta
    /// Instead of these 'for' loops we could have used simply:
    /// image.convertTo(new_image, -1, alpha, beta);
    /// but we wanted to show you how to access the pixels :)
    for( int y = 0; y < image.rows; y++ ) {
        for( int x = 0; x < image.cols; x++ ) {
            for( int c = 0; c < 3; c++ ) {
                new_image.at<Vec3b>(y,x)[c] = saturate_cast<uchar>( alpha*( image.at<Vec3b>(y,x)[c] ) + beta );
            }
        }
    }

    *mod_image = new_image;

    return 0;
}
