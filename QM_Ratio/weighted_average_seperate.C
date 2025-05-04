#include <iostream>
#include <cmath>

void weighted_average_seperate() {
 
    double values[] = {
        1.6648e+11,
        1.67358e+11,
        1.57962e+11,
        1.61401e+11
    };


    double errors[] = {
        1.25277e+10,
        1.27677e+10,
        7.5852e+09,
        7.80837e+09
    };

    const int N = 4;


    double numerator1 = 0.0;
    double denominator1 = 0.0;
    for (int i = 0; i < 2; ++i) {
        double weight = 1.0 / (errors[i] * errors[i]);
        numerator1 += values[i] * weight;
        denominator1 += weight;
    }
    double weighted_avg1 = numerator1 / denominator1;
    double weighted_err1 = std::sqrt(1.0 / denominator1);


    double numerator2 = 0.0;
    double denominator2 = 0.0;
    for (int i = 2; i < 4; ++i) {
        double weight = 1.0 / (errors[i] * errors[i]);
        numerator2 += values[i] * weight;
        denominator2 += weight;
    }
    double weighted_avg2 = numerator2 / denominator2;
    double weighted_err2 = std::sqrt(1.0 / denominator2);

    std::cout << std::fixed;
    std::cout << "Weighted average (q/m) for first two values = " << weighted_avg1 << " ± " << weighted_err1 << " C/kg" << std::endl;
    std::cout << "Weighted average (q/m) for last two values  = " << weighted_avg2 << " ± " << weighted_err2 << " C/kg" << std::endl;
}


