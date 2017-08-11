#ifndef image_matfunctions_h
#define image_matfunctions_h
    double Median (vector<short int> &array);
    double Average (vector<short int> &array);
    double StandardDeviation (vector<short int> &array, double average);
    double TreshHold (double standard_deviation, double median);
    std::string GetActualTime(void);
#endif
