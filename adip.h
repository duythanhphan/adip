/*
 * adip.h
 *
 *  Created on: Mar 18, 2014
 *      Author: duythanhphan
 */

#ifndef ADIP_H_
#define ADIP_H_

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;

namespace adip {

int DFT(Mat org_image, Mat *mod_image);

int CalcHist(Mat org_image, Mat *mod_image);

int CannyDetector(Mat org_image, Mat *mod_image);

int EqualizeHist(Mat org_image, Mat *mod_image);

int Laplace(Mat org_image, Mat *mod_image);

int MatchTemplate(int argc, char** argv);

int Smoothing(Mat org_image, Mat *mod_image);

int Sobel(Mat org_image, Mat *mod_image);

int Threshold(Mat org_image, Mat *mod_image);

int Filter2D(Mat org_image, Mat *mod_image);

int HoughCircle(Mat org_image, Mat *mod_image);
int HoughLines(Mat org_image, Mat *mod_image);

int Remap(Mat org_image, Mat *mod_image);

int Geometric(Mat org_image, Mat *mod_image);

int CopyMakeBorder(Mat org_image, Mat *mod_image);

int BasicLinearTransforms(Mat org_image, Mat *mod_image);

}  // namespace adip


#endif /* ADIP_H_ */
