#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TLegend.h>
#include <TMarker.h>
#include <TLatex.h>

void photoelectric_fit(const char* input_file = "photoelectric_green.csv") {
    std::ifstream file(input_file);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << input_file << std::endl;
        return;
    }

    std::vector<double> currents, voltages, current_errors, voltage_errors;
    std::string line;
    bool first_line = true;

    while (std::getline(file, line)) {
        if (first_line) {
            first_line = false;
            continue;
        }

        std::stringstream ss(line);
        std::string current_str, voltage_str;

        std::getline(ss, current_str, ';');
        std::getline(ss, voltage_str, ';');

        try {
            double current = std::stod(current_str);
            double voltage = std::stod(voltage_str);

            currents.push_back(current);
            voltages.push_back(voltage);
            current_errors.push_back(0.01);
            voltage_errors.push_back(0.5);
        } catch (...) {
            std::cerr << "Invalid data row: " << line << std::endl;
            continue;
        }
    }

    if (currents.empty()) {
        std::cerr << "No valid data found." << std::endl;
        return;
    }

    TGraphErrors* graph = new TGraphErrors(currents.size(), &voltages[0], &currents[0], &voltage_errors[0], &current_errors[0]);

    TCanvas *canvas = new TCanvas("canvas", "Photoelectric Fit", 800, 600);
    graph->SetTitle("Stopping Potential vs Current for Green Light");
    graph->GetXaxis()->SetTitle("Voltage (mV)");
    graph->GetYaxis()->SetTitle("Current (mA)");
    graph->SetMarkerStyle(20);
    graph->SetMarkerColor(kBlue);
    graph->Draw("AP");

    // Fit functions
    TF1 *fit_start = new TF1("fit_start", "[0]*x + [1]", -500, 3000);
    TF1 *fit_end = new TF1("fit_end", "[0]*x + [1]", -500, 3000);

    // Perform fits
    graph->Fit(fit_start, "R", "",0,500);
    graph->Fit(fit_end, "R+", "", 1000, 3000);

    fit_start->SetLineColor(kRed);
    fit_end->SetLineColor(kGreen);
    fit_start->Draw("same");
    fit_end->Draw("same");

    // fit parameters
    double m1 = fit_start->GetParameter(0);
    double b1 = fit_start->GetParameter(1);
    double m2 = fit_end->GetParameter(0);
    double b2 = fit_end->GetParameter(1);

    double m1_error = fit_start->GetParError(0);
    double b1_error = fit_start->GetParError(1);
    double m2_error = fit_end->GetParError(0);
    double b2_error = fit_end->GetParError(1);

    // Intersection point
    double x_intersect = (b2 - b1) / (m1 - m2);
    double y_intersect = m1 * x_intersect + b1;

    double dx_intersect = std::sqrt(b1_error * b1_error + b2_error * b2_error) / std::abs(m1 - m2);

   
    printf("Stopping Potential (V) = %.2f mV ± %.2f mV\n", x_intersect, dx_intersect);

    printf("\nFit (initial region):\n");
    printf("Slope (m1) = %.4f ± %.4f\n", m1, m1_error);
    printf("Intercept (b1) = %.4f ± %.4f\n", b1, b1_error);

    printf("\nFit (final region):\n");
    printf("Slope (m2) = %.4f ± %.4f\n", m2, m2_error);
    printf("Intercept (b2) = %.4f ± %.4f\n", b2, b2_error);

   
    TMarker *intersection_marker = new TMarker(x_intersect, y_intersect, 29);
    intersection_marker->SetMarkerColor(kMagenta + 2);
    intersection_marker->SetMarkerSize(2);
    intersection_marker->Draw("same");

    
    TLatex *text = new TLatex(x_intersect + 50, y_intersect, Form("V_{stop} = %.1f #pm %.1f mV", x_intersect, dx_intersect));
    text->SetTextColor(kMagenta + 2);
    text->SetTextSize(0.03);
    text->Draw();


   
    graph->GetXaxis()->SetLimits(-500, 3000);
    graph->SetMinimum(*std::min_element(currents.begin(), currents.end()) - 0.1);
    graph->SetMaximum(*std::max_element(currents.begin(), currents.end()) + 0.1);
}



