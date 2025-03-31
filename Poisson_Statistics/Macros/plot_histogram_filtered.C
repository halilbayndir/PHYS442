#include <TCanvas.h>
#include <TH1F.h>
#include <TStyle.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

void plot_histogram_filtered() {
    std::ifstream file("Differences_n1.csv");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file!" << std::endl;
        return;
    }
    
    std::vector<double> data;
    std::string line;
    
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        double value;
        if (ss >> value) {
            data.push_back(value);
        }
    }
    file.close();
    
    if (data.empty()) {
        std::cerr << "Error: No data found!" << std::endl;
        return;
    }
    
   
    double sum = 0.0;
    for (double v : data) {
        sum += v;
    }
    double mean = sum / data.size();
    
    double sumSq = 0.0;
    for (double v : data) {
        sumSq += (v - mean) * (v - mean);
    }
    double stddev = std::sqrt(sumSq / data.size());
    
    
    std::vector<double> filtered_data;
    double lower_bound = mean - 3 * stddev;
    double upper_bound = mean + 3 * stddev;

    for (double v : data) {
        if (v >= lower_bound && v <= upper_bound) {
            filtered_data.push_back(v);
        }
    }
    
    if (filtered_data.empty()) {
        std::cerr << "Error: No data after filtering!" << std::endl;
        return;
    }
    
    
    double minValue = *std::min_element(filtered_data.begin(), filtered_data.end());
    double maxValue = *std::max_element(filtered_data.begin(), filtered_data.end());
    int bins = 20;  
    
    TCanvas *c1 = new TCanvas("c1", "The Data Differences", 800, 600);
    TH1F *hist = new TH1F("histo", "the data of n=1;Value;Frequency", bins, minValue, maxValue);
    
    for (double v : filtered_data) {
        hist->Fill(v);
    }
    
    hist->SetFillColor(kBlue);
    hist->Draw();
    
    std::cout << "Mean: " << mean << std::endl;
    std::cout << "Standard Deviation: " << stddev << std::endl;
}



