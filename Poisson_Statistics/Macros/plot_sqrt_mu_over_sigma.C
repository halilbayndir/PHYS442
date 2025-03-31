void plot_sqrt_mu_over_sigma() {
    
    std::vector<double> mu_values = {106.0, 10.37, 22.83, 2.303};
    std::vector<double> sigma_values = {9.44, 2.898, 4.202, 1.432};

    TGraph* graph = new TGraph(4);
    
    for (int i = 0; i < 4; i++) {
        double y_value = sqrt(mu_values[i]) / sigma_values[i];
        graph->SetPoint(i, mu_values[i], y_value);
    }


    TCanvas* c1 = new TCanvas("c1", "Plot of sqrt(mu)/sigma vs mu", 800, 600);
    
    
    graph->SetTitle("#sqrt{#mu}/#sigma vs #mu; #mu (Mean); #sqrt{#mu}/#sigma");

    graph->SetMarkerStyle(20);
    graph->SetMarkerSize(1);
    graph->Draw("AP");

    c1->Update();
}










