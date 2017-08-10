#include "Includes.h"
#include "Picture.h"
#include "OutputData.h"
#include "Configuration.h"
#include "image_processing.h"
#include "image_matfunctions.h"




Point WeightedCenter(Picture &picture1,OutputData &output)
        {
            Point weighted_center;
            float sum=accumulate(picture1.cuted_array.begin(),picture1.cuted_array.end(),0.0);
            float Mx=0.0;
            float My=0.0;

            for(int i=0;i<picture1.cuted_image.rows;i++)
                {
                    for(int j=0; j<picture1.cuted_image.cols;j++)
                        {

                            Mx += (picture1.cuted_array[(i*picture1.cuted_image.cols) + j]*j/sum);
                            My += (picture1.cuted_array[(i*picture1.cuted_image.cols) + j]*i/sum);
                        }

                }
                weighted_center.x += picture1.left_up_corner.x + Mx -1 ;
                weighted_center.y += picture1.left_up_corner.y + My-1;
                circle(picture1.image, weighted_center, 1, Scalar(255,20,147), -1, 8, 0);
                return weighted_center;
    }

Point Hough_Center(Picture &picture1,OutputData &output)

        {
            Point center;
            vector<Vec3f> circles;
            HoughCircles(picture1.bin_image,circles,CV_HOUGH_GRADIENT,1,picture1.image.rows,200,5,15,3*(picture1.right_down_corner.x-picture1.left_up_corner.x)/2);
            if(circles.size()==0)
                {
                    return output.result_center;
                }
            center.x=circles[0][0];
            center.y=circles[0][1];
            if(center.x<picture1.left_up_corner.x || center.x>picture1.right_down_corner.x ||
            center.y<picture1.left_up_corner.y || center.y>picture1.right_down_corner.y)
                {
                    return output.result_center;
                }
            return center;

        }

int PhotoEditor (Picture &picture1, OutputData &output)

        {
            medianBlur(picture1.image,picture1.blurred_image,3);
            cvtColor(picture1.image,picture1.gray_image, CV_BGR2GRAY);
            GaussianBlur( picture1.gray_image,picture1.gray_image, Size( 5, 5), 3, 3 );
            MatToVector(picture1.gray_array,picture1.gray_image);
            picture1.median1=Average(picture1.gray_array);
            picture1.stdev1=StandardDeviation(picture1.gray_array,picture1.median1);
            picture1.th1=TreshHold(picture1.stdev1,picture1.median1);
            threshold(picture1.gray_image, picture1.bin_image, picture1.th1, 255 , THRESH_BINARY);
            MatToVector(picture1.bin_array,picture1.bin_image);
            output.result_center=Rectangle(picture1.image,picture1.bin_array,picture1.left_up_corner,picture1.right_down_corner,output.result_center);
            int length = picture1.right_down_corner.x-picture1.left_up_corner.x;
            int hight = picture1.right_down_corner.y-picture1.left_up_corner.y;
            if(length<0 || hight < 0)
                {
                    return -1;
                }
            else
                {
                    Rect ROI(picture1.left_up_corner.x,picture1.left_up_corner.y,picture1.right_down_corner.x-picture1.left_up_corner.x,picture1.right_down_corner.y-picture1.left_up_corner.y);
                    picture1.cuted_image=picture1.image(ROI);
                    MatToVector(picture1.cuted_array,picture1.cuted_image);
                }
            return 0;

        }

Point Rectangle (Mat &image, vector<short int> bin_array, Point &left_up_corner, Point &right_down_corner, Point &result_center)

        {
            unsigned int minrows = 0;
            unsigned int mincols = 0;
            unsigned int maxrows = image.rows;
            unsigned int maxcols = image.cols;
            for (unsigned int i=0; i<bin_array.size(); i++)
                {
                    if(bin_array[i] == 255)
                        {
                            if((i/image.cols)<maxrows) maxrows=(i/image.cols);
                            if(i/image.cols>minrows) minrows=i/image.cols;
                            if(i%image.cols<maxcols) maxcols=i%image.cols;
                            if(i%image.cols>mincols) mincols=i%image.cols;
                        }
                }
            swap(minrows, maxrows);
            swap(mincols, maxcols);
            left_up_corner.x = mincols;
            left_up_corner.y = minrows;
            right_down_corner.x = maxcols;
            right_down_corner.y = maxrows;
            result_center.x = left_up_corner.x + (maxcols-mincols)/2;
            result_center.y = left_up_corner.y + (maxrows-minrows)/2;
            return result_center;

        }

        /*
        Funkcja konwertuje obraz w skali szarosci do tablicy jednowymiarowej wiersz po wierszu.
        */

void MatToVector (vector<short int> &array, Mat &image)

        {
            if (image.isContinuous())
                {
                    array.assign(image.datastart, image.dataend);
                }
            else
                {
                    for(int i=0; i<image.rows;i++)
                            {
                                array.insert(array.end(), image.ptr<uchar>(i), image.ptr<uchar>(i)+image.cols);
                            }
                }
        }
