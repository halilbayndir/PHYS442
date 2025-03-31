
    TCanvas* c1 = new TCanvas("c1", "Franck-Hertz Experiment T=165", 1400, 900);

    // Load your data (make sure the file path is correct)
    TGraphErrors* mygraph = new TGraphErrors("T_1.65_U2_IA.txt");

    // Graph cosmetics
    mygraph->SetTitle(" U1=1.40 V,  U3=1.81 V,  T=165 C");
    mygraph->SetMarkerStyle(20);
    mygraph->SetMarkerSize(1.0);
    mygraph->SetMarkerColor(kBlack);

    mygraph->GetXaxis()->SetTitle("U2 Voltage (V)");
    mygraph->GetYaxis()->SetTitle("Anode Current (nA)");
    mygraph->GetXaxis()->SetLimits(0, 25);
    mygraph->SetMinimum(0);
    mygraph->SetMaximum(14);

    mygraph->Draw("AP");

    // Peak 1
    TF1* gauss1 = new TF1("gauss1", "[0]*TMath::Gaus(x,[1],[2])", 4, 6);
    gauss1->SetParameters(2, 2, 0.5);
    gauss1->SetLineColor(kRed);
    mygraph->Fit(gauss1, "R+");

    // Peak 2
    TF1* gauss2 = new TF1("gauss2", "[0]*TMath::Gaus(x,[1],[2])", 8.1, 12.1);
    gauss2->SetParameters(4, 4, 0.5);
    gauss2->SetLineColor(kBlue);
    mygraph->Fit(gauss2, "R+");

    // Peak 3
    TF1* gauss3 = new TF1("gauss3", "[0]*TMath::Gaus(x,[1],[2])",12.9 ,16.4);
    gauss3->SetParameters(5.5, 15, 0.5);
    gauss3->SetLineColor(kGreen + 2);
    mygraph->Fit(gauss3, "R+");

    // Peak 4
    TF1* gauss4 = new TF1("gauss4", "[0]*TMath::Gaus(x,[1],[2])", 18.2, 21.3);
    gauss4->SetParameters(6.5, 20, 0.5);
    gauss4->SetLineColor(kMagenta);
    mygraph->Fit(gauss4, "R+");

    // Mean (center) values of Gaussian fits
    double mean1 = gauss1->GetParameter(1);
    double mean2 = gauss2->GetParameter(1);
    double mean3 = gauss3->GetParameter(1);
    double mean4 = gauss4->GetParameter(1);

    // Sigma (standard deviation) values
     double sigma1 = gauss1->GetParameter(2);
    double sigma2 = gauss2->GetParameter(2);
    double sigma3 = gauss3->GetParameter(2);
    double sigma4 = gauss4->GetParameter(2);

    // Compute peak-to-peak differences
    double diff12 = mean2 - mean1;
    double diff23 = mean3 - mean2;
    double diff34 = mean4 - mean3;

    // Compute sigma uncertainties
    double sigma_delta_12 = sqrt(pow(sigma1, 2) + pow(sigma2, 2));
    double sigma_delta_23 = sqrt(pow(sigma2, 2) + pow(sigma3, 2));
    double sigma_delta_34 = sqrt(pow(sigma3, 2) + pow(sigma4, 2));

    // Weighted Average Calculation
    double sum_weights = (1 / pow(sigma_delta_12, 2)) + (1 / pow(sigma_delta_23, 2)) + (1 / pow(sigma_delta_34, 2));
    double weighted_sum = (diff12 / pow(sigma_delta_12, 2)) + (diff23 / pow(sigma_delta_23, 2)) + (diff34 / pow(sigma_delta_34,2)) ;

    double weighted_delta = weighted_sum / sum_weights;
    double weighted_sigma = sqrt(1 / sum_weights);

    // Print results
    cout << "Peak 2 - Peak 1 Difference: " << diff12 << " ± " << sigma_delta_12 << " V" << endl;
    cout << "Peak 3 - Peak 2 Difference: " << diff23 << " ± " << sigma_delta_23 << " V" << endl;
    cout << "Peak 4 - Peak 3 Difference: " << diff34 << " ± " << sigma_delta_34 << " V" << endl;
    cout << "Weighted Mean of Peak Differences: " << weighted_delta << " ± " << weighted_sigma << " V" << endl;

    // Optional: Add legend to identify peaks
    TLegend* leg = new TLegend(0.65, 0.65, 0.9, 0.9);
    leg->AddEntry(gauss1, "Peak 1 Fit", "l");
    leg->AddEntry(gauss2, "Peak 2 Fit", "l");
    leg->AddEntry(gauss3, "Peak 3 Fit", "l");
    leg->AddEntry(gauss4, "Peak 4 Fit", "l");
    leg->Draw();

    c1->Update();

