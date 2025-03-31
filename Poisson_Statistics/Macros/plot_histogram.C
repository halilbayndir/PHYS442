#include <TCanvas.h>
#include <TH1F.h>
#include <TStyle.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

void plot_histogram() {
    std::ifstream file("Differences_n0.csv");
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
    
    
    double minValue = *std::min_element(data.begin(), data.end());
    double maxValue = *std::max_element(data.begin(), data.end());
    int bins = 20;
    
    TCanvas *c1 = new TCanvas("c1", "The Data Differences", 800, 600);
    TH1F *hist = new TH1F("histo", "the data of n=0;Value;Frequency", bins, minValue, maxValue);
    
    for (double v : data) {
        hist->Fill(v);
    }
    
    hist->SetFillColor(kBlue);
    hist->Draw();
    
    double mean = hist->GetMean();
    double stddev = hist->GetStdDev();
    
    std::cout << "Mean: " << mean << std::endl;
    std::cout << "Standard Deviation: " << stddev << std::endl;
    
}


