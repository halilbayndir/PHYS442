#include <TCanvas.h>
#include <TH1F.h>
#include <TStyle.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <TF1.h>
#include <TLegend.h>
#include <TPaveText.h>

void Gauss_Poisson_Fit() {
    std::ifstream file("Barium_1s.csv");
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
    int bins = 10;

    TCanvas *c1 = new TCanvas("c1", "Histogram of Barium Data", 900, 700);

    TH1F *hist = new TH1F("histo", "Barium 1s Measurement", bins, minValue, maxValue);

    for (double v : data) {
        hist->Fill(v);
    }

    hist->SetFillColor(kBlue);
    hist->Draw();

    TF1 *gausFit = new TF1("gausFit", "gaus", minValue, maxValue);
    gausFit->SetLineColor(kRed);
    hist->Fit(gausFit, "R");

    TF1 *poissonFit = new TF1("poissonFit", "[0]*TMath::Poisson(x, [1])", minValue, maxValue);
    poissonFit->SetParameters(hist->GetMaximum(), hist->GetMean());
    poissonFit->SetLineColor(kGreen);
    hist->Fit(poissonFit, "R+");

    double gauss_A = gausFit->GetParameter(0);
    double gauss_mean = gausFit->GetParameter(1);
    double gauss_sigma = gausFit->GetParameter(2);

    double poisson_scale = poissonFit->GetParameter(0);
    double poisson_lambda = poissonFit->GetParameter(1);

    std::cout << "Gaussian Fit Parameters: A = " << gauss_A
              << ", Mean = " << gauss_mean
              << ", Sigma = " << gauss_sigma << std::endl;

    std::cout << "Poisson Fit Parameters: Scale = " << poisson_scale
              << ", Lambda = " << poisson_lambda << std::endl;

    double chi2_gauss = gausFit->GetChisquare();
    double ndf_gauss = gausFit->GetNDF();
    double chi2_ndf_gauss = chi2_gauss / ndf_gauss;

    double chi2_poisson = poissonFit->GetChisquare();
    double ndf_poisson = poissonFit->GetNDF();
    double chi2_ndf_poisson = chi2_poisson / ndf_poisson;

    std::cout << "Gaussian Fit χ²/ndf = " << chi2_ndf_gauss << std::endl;
    std::cout << "Poisson Fit χ²/ndf = " << chi2_ndf_poisson << std::endl;

    TLegend *legend = new TLegend(0.7, 0.15, 0.9, 0.3);
    legend->SetBorderSize(1);
    legend->SetTextSize(0.03);
    legend->SetFillColor(0);
    legend->AddEntry(gausFit, "Gaussian Fit", "l");
    legend->AddEntry(poissonFit, "Poisson Fit", "l");
    legend->Draw();

    TPaveText *pave = new TPaveText(0.1, 0.1, 0.3, 0.4, "NDC");
    pave->SetFillColor(0);
    pave->SetBorderSize(1);
    pave->SetTextSize(0.02);  
    pave->SetTextFont(42);
    pave->AddText(Form("Gaussian:"));
    pave->AddText(Form("  A = %.2f", gauss_A));
    pave->AddText(Form("  Mean = %.2f", gauss_mean));
    pave->AddText(Form("  Sigma = %.2f", gauss_sigma));
    pave->AddText(Form("Poisson:"));
    pave->AddText(Form("  Scale = %.2f", poisson_scale));
    pave->AddText(Form("  Lambda = %.2f", poisson_lambda));
    pave->AddText(Form("Gaussian χ²/ndf = %.2f", chi2_ndf_gauss));
    pave->AddText(Form("Poisson χ²/ndf = %.2f", chi2_ndf_poisson));
    pave->Draw();
}








