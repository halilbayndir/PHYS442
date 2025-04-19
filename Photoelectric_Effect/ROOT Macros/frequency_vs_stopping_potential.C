void frequency_vs_stopping_potential() {
    // Speed of light and elementary charge
    const double c = 2.998e8;         // m/s
    const double q = 1.602e-19;       // Coulomb
    const double h_actual = 6.626e-34; // Actual Planck constant

    // Wavelengths (in nm) for the colors used
    std::vector<std::string> colors = {"Green", "Turquoise", "Violet", "Yellow", "Blue"};
    std::vector<double> wavelengths = {546, 492, 405, 578, 436}; // in nm
    std::vector<double> stopping_potentials = {429.65, 451.41, 953.81, 553.15, 913.58}; // in mV
    std::vector<double> stop_errors = {1.40, 2.50, 3.95, 1.50, 3.57}; // in mV

    const int n = wavelengths.size();
    double frequencies[n], Vs[n], Vs_errors[n];

    for (int i = 0; i < n; ++i) {
        double wavelength_m = wavelengths[i] * 1e-9; // Convert nm to meters
        frequencies[i] = c / wavelength_m;           // Frequency in Hz
        Vs[i] = stopping_potentials[i] / 1000.0;     // Convert mV to V
        Vs_errors[i] = stop_errors[i] / 1000.0;
    }

    TGraphErrors* graph = new TGraphErrors(n, frequencies, Vs, 0, Vs_errors);
    graph->SetTitle("Stopping Potential vs Frequency;Frequency (Hz);Stopping Potential (V)");
    graph->SetMarkerStyle(20);
    graph->SetMarkerColor(kBlue);

    TCanvas* canvas = new TCanvas("c1", "Frequency vs Stopping Potential", 800, 600);
    graph->Draw("AP");

    // Linear fit: Vs = (h/q) * f - φ/q
    TF1* fit = new TF1("fit", "[0]*x + [1]", frequencies[0], frequencies[n - 1]);
    graph->Fit(fit, "R");

    fit->SetLineColor(kRed);
    fit->Draw("same");

    double slope = fit->GetParameter(0);
    double intercept = fit->GetParameter(1);
    double slope_err = fit->GetParError(0);
    double intercept_err = fit->GetParError(1);

    double h_measured = slope * q;              // h = slope * q
    double phi = -intercept * q;                // φ = -intercept * q

    std::cout << "Fitted Slope (Vs/frequency) = " << slope << " ± " << slope_err << " V·s" << std::endl;
    std::cout << "Planck's constant (from fit) = " << h_measured << " J·s" << std::endl;
    std::cout << "Work function (phi) = " << phi << " J" << std::endl;

    
    TLatex latex;
    latex.SetNDC();
    latex.SetTextSize(0.03);
    latex.DrawLatex(0.15, 0.85, Form("Slope = %.3e ± %.1e V·s", slope, slope_err));
    latex.DrawLatex(0.15, 0.80, Form("Intercept = %.3f ± %.3f V", intercept, intercept_err));
    latex.DrawLatex(0.15, 0.75, Form("h (measured) = %.3e J·s", h_measured));
    latex.DrawLatex(0.15, 0.70, Form("Work function = %.3e J", phi));
}


