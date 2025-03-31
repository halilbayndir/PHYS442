void fitHistogramWithGaussian() {
   
    TH1F *histo = new TH1F("histo", "First Excitation Levels", 10, 4.8, 5.1);

   
    float data[10] = {5.00254, 4.91946, 4.88651, 4.94475, 4.88771, 4.84428, 4.80067, 4.88911, 4.89048, 4.88116};
    float errors[10] = {0.669538, 0.641498, 0.637047, 0.601809, 0.634622, 0.61116, 0.592831, 0.628509, 0.603545, 0.636492};

    
    for (int i = 0; i < 10; i++) {
        int bin = histo->FindBin(data[i]);
        histo->SetBinContent(bin, histo->GetBinContent(bin) + 1);
        histo->SetBinError(bin, errors[i]);
    }

   
    TF1* gaussFit = new TF1("gaussFit", "gaus", 4.8, 5.1);

   
    histo->SetMarkerStyle(20);
    histo->SetMarkerSize(1);
    histo->Draw("E1");  //

  
    histo->Fit(gaussFit, "Q");


    double mean = gaussFit->GetParameter(1);
    double sigma = gaussFit->GetParameter(2);
    double amplitude = gaussFit->GetParameter(0);

    double mean_error = gaussFit->GetParError(1);
    double sigma_error = gaussFit->GetParError(2);
    double amplitude_error = gaussFit->GetParError(0);

    
    std::cout << "Mean: " << mean << " ± " << mean_error << std::endl;
    std::cout << "Sigma: " << sigma << " ± " << sigma_error << std::endl;
    std::cout << "Amplitude: " << amplitude << " ± " << amplitude_error << std::endl;
}

