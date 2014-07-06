#include "opencv2/core/core_c.h"
#include "opencv2/core/core.hpp"
#include "opencv2/flann/miniflann.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/contrib/contrib.hpp"

using namespace cv;

/**
* @brief makeCanvas Makes composite image from the given images
* @param vecMat Vector of Images.
* @param windowHeight The height of the new composite image to be formed.
* @param nRows Number of rows of images. (Number of columns will be calculated
*              depending on the value of total number of images).
* @return new composite image.
*/
cv::Mat makeCanvas(std::vector<cv::Mat>& vecMat, int windowHeight, int nRows) {
       int N = vecMat.size();
       nRows  = nRows > N ? N : nRows;
       int edgeThickness = 10;
       int imagesPerRow = ceil(double(N) / nRows);
       int resizeHeight = floor(2.0 * ((floor(double(windowHeight - edgeThickness) / nRows)) / 2.0)) - edgeThickness;
       int maxRowLength = 0;

       std::vector<int> resizeWidth;
       for (int i = 0; i < N;) {
               int thisRowLen = 0;
               for (int k = 0; k < imagesPerRow; k++) {
                       double aspectRatio = double(vecMat.at(i).cols) / vecMat.at(i).rows;
                       int temp = int( ceil(resizeHeight * aspectRatio));
                       resizeWidth.push_back(temp);
                       thisRowLen += temp;
                       if (++i == N) break;
               }
               if ((thisRowLen + edgeThickness * (imagesPerRow + 1)) > maxRowLength) {
                       maxRowLength = thisRowLen + edgeThickness * (imagesPerRow + 1);
               }
       }
       int windowWidth = maxRowLength;
       cv::Mat canvasImage(windowHeight, windowWidth, CV_8UC3, Scalar(0, 0, 0));

       for (int k = 0, i = 0; i < nRows; i++) {
               int y = i * resizeHeight + (i + 1) * edgeThickness;
               int x_end = edgeThickness;
               for (int j = 0; j < imagesPerRow && k < N; k++, j++) {
                       int x = x_end;
                       cv::Rect roi(x, y, resizeWidth.at(k), resizeHeight);
                       cv::Mat target_ROI = canvasImage(roi);
                       cv::resize(vecMat.at(k), target_ROI, target_ROI.size());
                       x_end += resizeWidth.at(k) + edgeThickness;
               }
       }
       return canvasImage;
}

Mat asSamplesVectors(Mat img) {
    Mat float_img;
    img.convertTo(float_img, CV_32F);

    Mat samples = Mat(img.rows * img.cols, 3, CV_32FC1);
    /*Flatten*/
    int index = 0;
    for(int y = 0; y < img.rows; y++) {
        for(int x = 0; x < img.cols; x++ ) {
            samples.at<Vec3f>(index++, 0) = float_img.at<Point3f>(y, x, 0);
        }
    }
    return samples;
}

void EMSegmentation(Mat org_image, int no_of_clusters = 2) {
    Mat image = org_image;
    Mat gray_image;

    /// Convert the image to Gray
    cvtColor( image, gray_image, CV_RGB2GRAY );

    std::cout << "Flatten..." << std::endl;
    Mat samples = asSamplesVectors( gray_image );

    std::cout << "Train..." << std::endl;
    EM em( no_of_clusters );
    em.train( samples );

    vector<Mat> segmented;
    for( int i = 0; i < no_of_clusters; i++ ) {
        segmented.push_back( Mat::zeros( image.rows, image.cols, CV_8UC3 ));
    }

    std::cout << "Predict..." << std::endl;
    int index = 0;
    for( int y = 0; y < image.rows; y++ ) {
        for( int x = 0; x < image.cols; x++ ) {
            int result = em.predict( samples.row(index++) )[1];
            segmented.at(result).at<Point3i>(y, x, 0) = image.at<Point3i>(y, x, 0);
        }
    }

    std::cout << "Make Canvas..." << std::endl;
    namedWindow( "Final", CV_WINDOW_NORMAL );
    imshow("Final", makeCanvas(segmented, 480, 1));

//    const char * fgw = "Object";
//    const char * bgw = "Background";
//    const char * org = "Origin";
//
//    namedWindow( fgw, CV_WINDOW_NORMAL );
//    namedWindow( bgw, CV_WINDOW_NORMAL );
//    namedWindow( org, CV_WINDOW_NORMAL );
//
//    imshow(org, org_image);
//    imshow(fgw, segmented.at(1));
//    imshow(bgw, segmented.at(0));
}
