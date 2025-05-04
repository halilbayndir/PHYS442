void plotconstant160V() {
    const double V = 160.0; // Volt
    const double dV = 1.0;
    const double dr = 0.001; // 1 mm
    const double r_vals[] = {2, 3, 4, 5}; // cm
    const int N = 4;

    
    const double B_vals[] = {2.19e-3, 1.41e-3, 1.00e-3, 7.89e-4};
    const double dB_vals[] = {0.02e-3, 0.01e-3, 0.01e-3, 0.09e-4};

    TGraphErrors *graph = new TGraphErrors();

    for (int i = 0; i < N; ++i) {
        double r = r_vals[i] / 100.0; 
        double y = 2 * V / (r * r);
        double dy = y * sqrt(pow(dV / V, 2) + 4 * pow(dr / r, 2));

        double B = B_vals[i];
        double dB = dB_vals[i];
        double x = B * B;
        double dx = 2 * B * dB;

        graph->SetPoint(i, x, y);
        graph->SetPointError(i, dx, dy);
    }
    
    TCanvas *c = new TCanvas("c", "160V: 2V/r^2 vs B^2", 800, 600);

    graph->SetTitle("160V: B^{2} vs 2V/r^{2};B^{2} [T^{2}];2V/r^{2} [V/m^{2}]");

    graph->SetMarkerStyle(21);
    graph->SetMarkerColor(kBlue + 1);
    graph->Draw("AP");

    TF1 *fit = new TF1("fit", "pol1", 0, 6e5);
    graph->Fit("fit");

    double slope = fit->GetParameter(1);
    double slope_err = fit->GetParError(1);
    std::cout << "Slope (k) = " << slope << " ± " << slope_err << "C/kg" << std::endl;

    c->SaveAs("fit_givenB_160V.pdf");

}


