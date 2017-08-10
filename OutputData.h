#ifndef OutputData_h
#define OutputData_h
    using namespace cv;
    class OutputData
        {
        public:
            Point result_center;
            Point vector_error; //srodek znalezionego srodka - srodek szczeliny
            float norm_of_vector_error;
        };
#endif
