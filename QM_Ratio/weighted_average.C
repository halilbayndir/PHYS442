void weighted_average() {
 
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
    double numerator = 0.0;
    double denominator = 0.0;

    for (int i = 0; i < N; ++i) {
        double weight = 1.0 / (errors[i] * errors[i]);
        numerator += values[i] * weight;
        denominator += weight;
    }

    double weighted_avg = numerator / denominator;
    double weighted_err = sqrt(1.0 / denominator);

    std::cout << std::fixed;
    std::cout << "Weighted average (q/m) = " << weighted_avg << " ± " << weighted_err << " C/kg" << std::endl;
}

