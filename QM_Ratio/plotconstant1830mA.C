void plotconstant1830mA() {
    const double B = 1.27e-3;
    const double dB = 0.01e-3;
    const double dr = 0.001;   // 1 mm
    const double dV = 1.0;
    const double r_vals[] = {2, 3, 4, 5};
    const double V_vals[] = {83, 135, 229, 355};
    const int N = 4;

    TGraphErrors *graph = new TGraphErrors();

    for (int i = 0; i < N; ++i) {
        double r = r_vals[i] / 100.0; // cm → m
        double V = V_vals[i];

        double x = B * B * r * r;
        double dx = x * sqrt(pow(2 * dB / B, 2) + pow(2 * dr / r, 2));

        double y = 2 * V;
        double dy = 2 * dV;

        graph->SetPoint(i, x, y);
        graph->SetPointError(i, dx, dy);
    }

    TCanvas *c = new TCanvas("c", "2V vs B^2 r^2", 800, 600);
    graph->SetTitle("1.83A : 2V vs B^{2}r^{2};B^{2}r^{2} [T^{2}·m^{2}];2V [V]");
    graph->SetMarkerStyle(21);
    graph->SetMarkerColor(kBlue + 1);
    graph->Draw("AP");

    TF1 *fit = new TF1("fit", "pol1", 0, graph->GetX()[N-1]*1.2);
    graph->Fit("fit");

    double slope = fit->GetParameter(1);
    double slope_err = fit->GetParError(1);
    std::cout << "Slope (k) = " << slope << " ± " << slope_err << " C/kg" << std::endl;

    c->SaveAs("fit_variableV_fixedB.pdf");
}

