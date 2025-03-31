#include <TCanvas.h>
#include <TH1F.h>
#include <TF1.h>
#include <TMath.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

void poisson_fit_with_alpha() {
   
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
    
    // Modified Poisson
    // f(x) = A * (alpha * t)^x * exp(-alpha * t) / x!
    TF1 *fitFunc = new TF1("fitFunc", "[0] * TMath::Poisson(x, [1]*[2])", minValue, maxValue);
    fitFunc->SetParameter(0, 1);
    fitFunc->SetParameter(1, mean);
    fitFunc->SetParameter(2, 1);
    hist->Fit(fitFunc, "R");
    
    
    double alpha = fitFunc->GetParameter(1);
    double alpha_error = fitFunc->GetParError(1);
    double t = fitFunc->GetParameter(2);
    double t_error = fitFunc->GetParError(2);
    double chi2 = fitFunc->GetChisquare();
    double ndf = fitFunc->GetNDF();
    double chi2_ndf = chi2 / ndf;

   
    std::cout << "Best Fit Parameters:" << std::endl;
    std::cout << "Alpha (lambda): " << alpha << " +/- " << alpha_error << std::endl;
    std::cout << "t: " << t << " +/- " << t_error << std::endl;
    std::cout << "Chi2/ndf: " << chi2_ndf << std::endl;
    
    
    TPaveText *pave = new TPaveText(0.65, 0.15, 0.85, 0.35, "NDC");
    pave->SetFillColor(0);
    pave->SetTextAlign(12);
    pave->SetTextFont(42); 
    pave->AddText(Form("Alpha = %.3f #pm %.3f", alpha, alpha_error));
    pave->AddText(Form("t = %.3f #pm %.3f", t, t_error));
    pave->AddText(Form("#chi^{2}/ndf = %.3f", chi2_ndf));
    pave->Draw();
}





