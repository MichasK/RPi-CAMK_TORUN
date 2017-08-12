#ifndef configuration_h
#define configuration_h
    class Configuration
        {
        public:
            std::string config_file_name;
            cv::Point slit_center;
            char metod;//w-weighted , h-houghtransform , r-rectanglecenter, a-default srednia z wszystkich
            float error_treshold;/* jeżeli odległość znalezionego środka od środka szczeliny
                                jest większa od wartości tresholdu błedu to uważamy że
                                jest to nieprawidłowe i przesyłamy wektor translacji*/
        };
#endif
