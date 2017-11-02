#ifndef image_matfunctions_h
#define image_matfunctions_h
double Median(std::vector<short int> &array);
double Average(std::vector<short int> &array);
double StandardDeviation(std::vector<short int> &array, double average);
double TreshHold(double standard_deviation, double median);
std::string GetActualTime(void);
#endif
