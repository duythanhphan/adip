#include "adip.h"

using namespace cv;

static Mat img, img_src;
static int threshval = 100;

static void on_trackbar(int, void*)
{
    Mat bw = threshval < 128 ? (img < threshval) : (img > threshval);

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    findContours( bw, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );

    Mat dst = Mat::zeros(img.size(), CV_8UC3);

    if( !contours.empty() && !hierarchy.empty() )
    {
        // iterate through all the top-level contours,
        // draw each connected component with its own random color
        int idx = 0;
        for( ; idx >= 0; idx = hierarchy[idx][0] )
        {
            Scalar color( (rand()&255), (rand()&255), (rand()&255) );
            drawContours( dst, contours, idx, color, CV_FILLED, 8, hierarchy );
        }
    }

    imshow( "Connected Components", dst );
}

const char* keys =
{
    "{1| |stuff.jpg|image for converting to a grayscale}"
};

int adip::ConnectedComponents(Mat org_image, Mat *mod_image) {
    img_src = org_image;

    /// Convert the image to grayscale
    cvtColor( img_src, img, CV_BGR2GRAY );

    namedWindow( "ConnectedComponents", 1 );
    imshow( "ConnectedComponents", img_src );

    namedWindow( "Connected Components", 1 );
    createTrackbar( "Threshold", "Connected Components", &threshval, 255, on_trackbar );
    on_trackbar(threshval, 0);

    waitKey(0);
    return 1;
}
