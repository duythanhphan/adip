/**
 * @function Remap_Demo.cpp
 * @brief Demo code for Remap
 * @author Ana Huaman
 */

#include "adip.h"

using namespace cv;

/// Global variables
static Mat src, dst;
static Mat map_x, map_y;
static const char* remap_window = "Remap demo";
static int ind = 0;

/// Function Headers
static void update_map( void );

int adip::Remap(Mat org_image, Mat *mod_image) {
    /// Load the image
    src = org_image;

    /// Create dst, map_x and map_y with the same size as src:
    dst.create( src.size(), src.type() );
    map_x.create( src.size(), CV_32FC1 );
    map_y.create( src.size(), CV_32FC1 );

    /// Create window
    namedWindow( remap_window, CV_WINDOW_AUTOSIZE );

    /// Loop
    for(;;) {
        /// Each 1 sec. Press ESC to exit the program
        int c = waitKey( 1000 );

        if( (char)c == 27 )
          { break; }

        /// Update map_x & map_y. Then apply remap
        update_map();
        remap( src, dst, map_x, map_y, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0) );

        // Display results
        imshow( remap_window, dst );
    }

    return 1;
}

/**
 * @function update_map
 * @brief Fill the map_x and map_y matrices with 4 types of mappings
 */
static void update_map( void )
{
  ind = ind%4;

  for( int j = 0; j < src.rows; j++ )
    { for( int i = 0; i < src.cols; i++ )
     {
           switch( ind )
         {
         case 0:
           if( i > src.cols*0.25 && i < src.cols*0.75 && j > src.rows*0.25 && j < src.rows*0.75 )
                 {
               map_x.at<float>(j,i) = 2*( i - src.cols*0.25f ) + 0.5f ;
               map_y.at<float>(j,i) = 2*( j - src.rows*0.25f ) + 0.5f ;
              }
           else
         { map_x.at<float>(j,i) = 0 ;
               map_y.at<float>(j,i) = 0 ;
                 }
                   break;
         case 1:
               map_x.at<float>(j,i) = (float)i ;
               map_y.at<float>(j,i) = (float)(src.rows - j) ;
           break;
             case 2:
               map_x.at<float>(j,i) = (float)(src.cols - i) ;
               map_y.at<float>(j,i) = (float)j ;
           break;
             case 3:
               map_x.at<float>(j,i) = (float)(src.cols - i) ;
               map_y.at<float>(j,i) = (float)(src.rows - j) ;
           break;
             } // end of switch
     }
    }
  ind++;
}
