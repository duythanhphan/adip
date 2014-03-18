/**
 * @file HoughCircle_Demo.cpp
 * @brief Demo code for Hough Transform
 * @author OpenCV team
 */

#include "adip.h"

using namespace cv;

int adip::HoughCircle(Mat org_image, Mat *mod_image) {
   Mat src, src_gray;

   /// Read the image
   src = org_image;

   /// Convert it to gray
    cvtColor( src, src_gray, CV_BGR2GRAY );

   /// Reduce the noise so we avoid false circle detection
    GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );

    vector<Vec3f> circles;

   /// Apply the Hough Transform to find the circles
    HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows/8, 200, 100, 0, 0 );

   /// Draw the circles detected
    for( size_t i = 0; i < circles.size(); i++ )
    {
         Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
         int radius = cvRound(circles[i][2]);

         // circle center
         circle( src, center, 3, Scalar(0,255,0), -1, 8, 0 );

         // circle outline
         circle( src, center, radius, Scalar(0,0,255), 3, 8, 0 );
    }

    *mod_image = src;

    return 0;
}
