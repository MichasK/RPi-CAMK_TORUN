#ifndef OutputData_h
#define OutputData_h
    class OutputData
        {
        public:
            Point hough_center;
            Point rectangle_center;
            Point weighted_center;
            Point vector_error; //srodek znalezionego srodka - srodek szczeliny
            float norm_of_vector_error;
        public:
            friend ostream &operator<<(ostream &out, OutputData &output);
            friend void Rectangle(Mat &image,Point &left_up_corner, Point &right_down_corner,Point &rectangle_center);
            friend int PhotoEditor(Picture &picture1,OutputData &output);
            friend void Hough_Center(Picture &picture1,OutputData &output);
            friend void WeightedCenter(Picture &picture1,OutputData &output);
            friend void RPiPrintf(OutputData output, Configuration config);
        };
#endif
