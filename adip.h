/*
 * adip.h
 *
 *  Created on: Mar 18, 2014
 *      Author: duythanhphan
 */

#ifndef ADIP_H_
#define ADIP_H_

#include "opencv2/core/core.hpp"
#include "opencv2/flann/miniflann.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/contrib/contrib.hpp"

#include <iostream>
#include <cmath>

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

using namespace cv;

namespace adip {

int DFT(Mat org_image, Mat *mod_image);
int CalcHist(Mat org_image, Mat *mod_image);
int CannyDetector(Mat org_image, Mat *mod_image);
int EqualizeHist(Mat org_image, Mat *mod_image);
int Laplace(Mat org_image, Mat *mod_image);
int MatchTemplate(Mat org_image, Mat *mod_image);
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
int Morphology_1(Mat org_image, Mat *mod_image);
int Morphology_2(Mat org_image, Mat *mod_image);
int Pyramids(Mat org_image, Mat *mod_image);
int AddingImages(Mat org_image, Mat *mod_image);
int ConnectedComponents(Mat org_image, Mat *mod_image);

typedef int (*FN_TYPE) (Mat org_image, Mat *mod_image);

uchar* GetData(Mat image);

int logpolar_bsm(Mat org_image, Mat *mod_image);
int letter_recognize(Mat org_image, Mat *mod_image);

}  // namespace adip


#endif /* ADIP_H_ */
