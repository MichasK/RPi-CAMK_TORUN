#include "Includes.h"
#include "Picture.h"
#include "OutputData.h"
#include "Configuration.h"
#include <time.h>
#include <unistd.h>

double Median (std::vector<short int> &array)

    {

        size_t n = array.size() /  2;
        nth_element(array.begin(), array.begin() + n, array.end());
        return array[n];

    }


double Average (std::vector<short int> &array)

    {
        double sum=0.0;
        float dominator=array.size();
        for (unsigned int i=0; i<array.size(); i++)
            {
                sum += array[i] /dominator;
            }
        return sum ;
    }


double StandardDeviation (std::vector<short int> &array, double average)

    {
        double accum = 0.0;
        for(unsigned int i=0; i<array.size(); i++)
            {
                accum += (array[i]-average)/(array.size()-1)*(array[i]-average);
            }

        double stdev = sqrt(accum);
        return stdev;
    }


double TreshHold (double standard_deviation, double median)

    {
        return median + (6 * standard_deviation);
    }

/*
*Przeciążony operator wyświetlania obrazu
*/

std::ostream &operator<<(std::ostream &out, Picture &picture1)

    {
                namedWindow("Wykryte koło",CV_WINDOW_AUTOSIZE);

                namedWindow("Obraz binarny",CV_WINDOW_AUTOSIZE);

                imshow("Obraz binarny",picture1.bin_image);

                imshow("Wykryte koło",picture1.image);

                sleep(1);

                cvDestroyWindow("Wykryte koło");

                cvDestroyWindow("Obraz binarny");

                return out;
    }
/*
*   String zawierajacy aktualna date
*/
std::string GetActualTime(void)

    {
        time_t czas;
        struct tm * ptr;
        time( & czas );
        ptr= localtime( & czas );
        string data(asctime( ptr ));
        data.erase(std::remove(data.begin(), data.end(), '\n'), data.end());
        return data;
    }
