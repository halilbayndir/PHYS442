#include <TCanvas.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TStyle.h>
#include <TFile.h>
#include <TLine.h>
#include <iostream>
#include <fstream>
#include <vector>

void Op_Volt_Plot() {
    
    std::ifstream file("Operating_Voltage.csv");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file!" << std::endl;
        return;
    }
    
    std::vector<double> voltage, count;
    std::string csv_line;
    
  
    std::getline(file, csv_line);
    
   
    while (std::getline(file, csv_line)) {
        double v, c;
        char sep;
        std::istringstream ss(csv_line);
        if (ss >> v >> sep >> c) {
            voltage.push_back(v);
            count.push_back(c);
        }
    }
    file.close();
    

    TCanvas *c1 = new TCanvas("c1", "Voltage vs Count", 800, 600);
    TGraph *graph = new TGraph(voltage.size(), &voltage[0], &count[0]);
    
    graph->SetTitle("Voltage vs Count");
    graph->GetXaxis()->SetTitle("Voltage (V)");
    graph->GetYaxis()->SetTitle("Count");
    graph->SetMarkerStyle(20);
    graph->SetMarkerSize(1);
    graph->SetMarkerColor(kBlue);
    graph->Draw("AP");
    
    
    double minY = *std::min_element(count.begin(), count.end());
    double maxY = *std::max_element(count.begin(), count.end());
    TLine *vline = new TLine(440, minY, 440, maxY);
    vline->SetLineColor(kRed);
    vline->SetLineStyle(2);
    vline->Draw();
    
    c1->SaveAs("Voltage_vs_Count.png");
}

