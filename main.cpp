#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#define window_name1 "Edge map : Canny default (Sobel gradient)"

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    VideoCapture cap(0); //capture the video from web cam

    if ( !cap.isOpened() )  // if not success, exit program
    {
        cout << "Cannot open the web cam" << endl;
        return -1;
    }

    int edgeThresh = 40;

    namedWindow(window_name1, 1);

    while (true)
    {
        Mat image;

        bool bSuccess = cap.grab();

        if (!bSuccess) //if not success, break loop
        {
            cout << "Cannot read a frame from video stream" << endl;
            break;
        }

        cap.retrieve(image);

        cvtColor(image, image, COLOR_BGR2GRAY);
        // blur
        blur(image, image, Size(3,3));
        // Run the edge detector on grayscale
        Canny(image, image, edgeThresh, edgeThresh*5, 3);

        imshow(window_name1, image);

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            cout << "esc key is pressed by user" << endl;
            break;
        }
    }

    return 0;

}

