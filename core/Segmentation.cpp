#include "adip.h"

static void drawText(cv::Mat &img, string text) {
    int fontFace = FONT_HERSHEY_SIMPLEX;
    double fontScale = 1;
    int thickness = 3;

    int baseline=0;
    Size textSize = getTextSize(text, fontFace,
                                fontScale, thickness, &baseline);
    baseline += thickness;

    // center the text
    const int row_offset = 20;
    Point textOrg((img.cols - textSize.width)/2,
                  (textSize.height)/2 + row_offset);

    // draw the box
//    rectangle(img, textOrg + Point(0, baseline),
//              textOrg + Point(textSize.width, -textSize.height),
//              Scalar(0,0,255));

    // ... and the baseline first
//    line(img, textOrg + Point(0, thickness),
//         textOrg + Point(textSize.width, thickness),
//         Scalar(0, 0, 255));

    // then put the text itself
    putText(img, text, textOrg, fontFace, fontScale,
            Scalar(127, 127, 127, 0), thickness, 8);
}

static cv::Mat makeCanvas(std::vector<cv::Mat>& vecMat, int windowHeight, int nRows) {
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
           Rect roi(x, y, resizeWidth.at(k), resizeHeight);
           cv::Mat target_ROI = canvasImage(roi);
           resize(vecMat.at(k), target_ROI, target_ROI.size());
           x_end += resizeWidth.at(k) + edgeThickness;
       }
   }

   return canvasImage;
}

static cv::Mat asSamplesVectors(cv::Mat img) {
    cv::Mat float_img;
    img.convertTo(float_img, CV_32F);

    cv::Mat samples = cv::Mat( img.rows * img.cols, 3, CV_32FC1 );

    int index = 0;
    for(int y = 0; y < img.rows; y++) {
        for(int x = 0; x < img.cols; x++ ) {
            samples.at<Vec3f>(index++, 0) = float_img.at<Point3f>(y, x, 0);
        }
    }

    return samples;
}

static std::vector<cv::Mat> EMSegmentation(cv::Mat image, int no_of_clusters = 2) {
    cv::Mat samples = asSamplesVectors( image );

    std::cout << "Training..." << std::endl;
    EM em( no_of_clusters );
    em.train( samples );

    std::vector<cv::Mat> segmented;
    for( int i = 0; i < no_of_clusters; i++ ) {
        segmented.push_back( cv::Mat::zeros( image.rows, image.cols, CV_8UC3 ));
    }

    std::cout << "Predicting..." << std::endl;
    int index = 0;
    for( int y = 0; y < image.rows; y++ ) {
        for( int x = 0; x < image.cols; x++ ) {
            int result = em.predict( samples.row(index++) )[1];
            segmented.at(result).at<Point3i>(y, x, 0) = image.at<Point3i>(y, x, 0);
        }
    }

    return segmented;
}

static std::vector<cv::Mat> KMeanSegmentation(cv::Mat image, int no_of_clusters = 2) {
    cv::Mat samples = asSamplesVectors( image );

    const int iters = 100;
    cv::Mat labels;

    kmeans(samples, no_of_clusters, labels,
            TermCriteria( TermCriteria::COUNT, iters, 0.0), 0,
            KMEANS_PP_CENTERS, noArray() );

    std::vector<cv::Mat> segmented;
    for( int i = 0; i < no_of_clusters; i++ ) {
        segmented.push_back( cv::Mat::zeros( image.rows, image.cols, CV_8UC3 ));
    }

    bool isFlt = labels.type() == CV_32FC1;
    int index = 0, result = 0;
    for( int y = 0; y < image.rows; y++ ) {
        for( int x = 0; x < image.cols; x++ ) {
            if (isFlt) result = labels.at<float>(index++);
            else       result = labels.at<int>(index++);
            segmented.at(result).at<Point3i>(y, x, 0) = image.at<Point3i>(y, x, 0);
        }
    }

    return segmented;
}

static std::vector<cv::Mat> OtsuSegmentation(cv::Mat image, const int no_of_clusters = 2) {
    cv::Mat grey_img, dst_img;
    std::vector<cv::Mat> segmented;

    // convert to greyscale image
    cvtColor(image, grey_img, CV_RGB2GRAY);

    // do otsu threshoding method
    threshold(grey_img, dst_img, 0, 1, THRESH_OTSU);

    for( int i = 0; i < no_of_clusters; i++ ) {
        segmented.push_back( cv::Mat::zeros( image.rows, image.cols, CV_8UC3 ));
    }

    int result = 0;
    for( int y = 0; y < image.rows; y++ ) {
        for( int x = 0; x < image.cols; x++ ) {
            result = (dst_img.at<uchar>(y, x, 0) == 1) ? 0 : 1;
            segmented.at(result).at<Point3i>(y, x, 0) = image.at<Point3i>(y, x, 0);
        }
    }

    return segmented;
}

void EMDemo( cv::Mat org_image) {
    const char * org_window = "Original Image";
    const char * mod_window = "EM Segmentation";

    // image segmentation
    std::vector<cv::Mat> segmented_vec = EMSegmentation( org_image, 2 );
    drawText(segmented_vec.at(0), "Background");
    drawText(segmented_vec.at(1), "Object");

    cv::Mat segmented_image = makeCanvas(segmented_vec, org_image.rows, 1);

    // create a window to display results
    namedWindow( org_window, CV_WINDOW_AUTOSIZE );
    namedWindow( mod_window, CV_WINDOW_AUTOSIZE );

    // show images
    imshow(org_window, org_image);
    imshow(mod_window, segmented_image);

    // wait for termination
    waitKey();
}

void KMeanDemo( cv::Mat org_image) {
    const char * org_window = "Original Image";
    const char * mod_window = "KMean Segmentation";

    // image segmentation
    std::vector<cv::Mat> segmented_vec = KMeanSegmentation( org_image, 2 );
    drawText(segmented_vec.at(0), "Background");
    drawText(segmented_vec.at(1), "Object");

    cv::Mat segmented_image = makeCanvas(segmented_vec, org_image.rows, 1);

    // create a window to display results
    namedWindow( org_window, CV_WINDOW_AUTOSIZE );
    namedWindow( mod_window, CV_WINDOW_AUTOSIZE );

    // show images
    imshow(org_window, org_image);
    imshow(mod_window, segmented_image);

    // wait for termination
    waitKey();
}

void OtsuDemo( cv::Mat org_image) {
    const char * org_window = "Original Image";
    const char * mod_window = "Otsu Segmentation";

    // image segmentation
    std::vector<cv::Mat> segmented_vec = OtsuSegmentation( org_image, 2 );
    drawText(segmented_vec.at(0), "Background");
    drawText(segmented_vec.at(1), "Object");

    cv::Mat segmented_image = makeCanvas(segmented_vec, org_image.rows, 1);


    // create a window to display results
    namedWindow( org_window, CV_WINDOW_AUTOSIZE );
    namedWindow( mod_window, CV_WINDOW_AUTOSIZE );

    // show images
    imshow(org_window, org_image);
    imshow(mod_window, segmented_image);

    // wait for termination
    waitKey();
}

void SegmentationDemo( cv::Mat org_image) {
    const char * mod_window = "Segmentation (Otsu, KMean, EM)";
    cv::Mat first_image, segmented_image;
    std::vector<cv::Mat> all_image_vec;

    org_image.copyTo(first_image);
    drawText(first_image, "Original");
    all_image_vec.push_back(first_image);

    std::cout << "Otsu Segmentation..." << std::endl;
    // otsu segmentation
    std::vector<cv::Mat> otsu_segmented_vec = OtsuSegmentation( org_image, 2 );
    drawText(otsu_segmented_vec.at(1), "Otsu");
    all_image_vec.push_back(otsu_segmented_vec.at(1));
    segmented_image = makeCanvas(all_image_vec, org_image.rows * 1, 2);

    // create a window to display results
    namedWindow( mod_window, CV_WINDOW_AUTOSIZE );
    // show images
    imshow(mod_window, segmented_image);

    std::cout << "KMean Segmentation..." << std::endl;
    // kmeans segmentation
    std::vector<cv::Mat> kmean_segmented_vec = KMeanSegmentation( org_image, 2 );
    drawText(kmean_segmented_vec.at(1), "KMeans");
    all_image_vec.push_back(kmean_segmented_vec.at(1));
    segmented_image = makeCanvas(all_image_vec, org_image.rows * 2, 2);

    // show images
    imshow(mod_window, segmented_image);

    std::cout << "EM Segmentation..." << std::endl;
    // em segmentation
    std::vector<cv::Mat> em_segmented_vec = EMSegmentation( org_image, 2 );
    drawText(em_segmented_vec.at(1), "EM");
    all_image_vec.push_back(em_segmented_vec.at(1));
    segmented_image = makeCanvas(all_image_vec, org_image.rows * 2, 2);

    // show images
    imshow(mod_window, segmented_image);

    // wait for termination
    waitKey();
}
