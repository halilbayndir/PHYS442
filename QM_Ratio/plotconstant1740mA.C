void plotconstant1740mA() {
    const double B = 1.20e-3;     // Tesla
    const double dB = 0.01e-3;    // Tesla
    const double dr = 0.001;      // (1 mm)
    const double dV = 1.0;        // Volt
    const double r_vals[] = {2, 3, 4, 5};             // cm
    const double V_vals[] = {75, 127, 212, 321};      // Volt
    const int N = 4;

    TGraphErrors *graph = new TGraphErrors();

    for (int i = 0; i < N; ++i) {
        double r = r_vals[i] / 100.0; // cm → m
        double V = V_vals[i];

        double x = B * B * r * r;
        double x_scaled = x * 1e9;
        double dx = x * sqrt(pow(2 * dB / B, 2) + pow(2 * dr / r, 2));
        double dx_scaled = dx * 1e9;

        double y = 2 * V;
        double dy = 2 * dV;

        graph->SetPoint(i, x_scaled, y);
        graph->SetPointError(i, dx_scaled, dy);

        std::cout << "Point " << i << ": x = " << x_scaled << ", y = " << y
                  << ", dx = " << dx_scaled << ", dy = " << dy << std::endl;
    }

    TCanvas *c = new TCanvas("c", "2V vs B^2 r^2", 800, 600);
    graph->SetTitle("1.74A : 2V vs B^{2}r^{2};B^{2}r^{2} [10^{-9} T^{2}·m^{2}];2V [V]");
    graph->SetMarkerStyle(21);
    graph->SetMarkerColor(kBlue + 1);
    graph->Draw("AP");


    double x_max = graph->GetX()[N-1] * 1.2;
    TF1 *fit = new TF1("fit", "[0] + [1]*x", 0, x_max);
    fit->SetParameters(0, 200);

    int fitStatus = graph->Fit("fit", "RE"); 

    if (fitStatus != 0) {
        std::cerr << "Fit failed with status: " << fitStatus << std::endl;
    } else {
        double slope = fit->GetParameter(1);
        double slope_err = fit->GetParError(1);
        std::cout << "Slope (k) = " << slope << " ± " << slope_err << " V / [10⁻⁹ T²·m²]" << std::endl;
    }

    c->SaveAs("fit_variableV_fixedB_scaled.pdf");
}

