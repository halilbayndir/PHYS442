void calculateB() {
    const double mu0 = 4 * TMath::Pi() * 1e-7; 
    const double n = 154.0;       // Number of turns
    const double R = 0.2;         // Coil radius in meters
    const double dn = 1.0;        // Uncertainty in number of turns (assume ±1)
    const double dR = 0.001;      // Uncertainty in radius (assume ±1 mm)
    const double dI = 0.01;       // Uncertainty in current (assume ±0.01 A)
    
    const double factor = pow(4.0/5.0, 1.5);

    double I_vals[] = {3.16, 2.03, 1.45, 1.14, 2.98, 1.85, 1.36, 1.03, 1.83, 1.74};
    const int N = sizeof(I_vals)/sizeof(I_vals[0]);

    for (int i = 0; i < N; ++i) {
        double I = I_vals[i];
        
       
        double B = factor * mu0 * n * I / R;

        
        double rel_dI = dI / I;
        double rel_dn = dn / n;
        double rel_dR = dR / R;

      
        double rel_dB = sqrt(rel_dI * rel_dI + rel_dn * rel_dn + rel_dR * rel_dR);

    
        double dB = B * rel_dB;

  
        int exponent_B = floor(log10(B));
        int exponent_dB = floor(log10(dB));

    
        int common_exponent = std::max(exponent_B, exponent_dB);
        double B_norm = B / pow(10, common_exponent);
        double dB_norm = dB / pow(10, common_exponent);

 
        printf("I = %.2f A -> B ≈ (%.2f ± %.2f) × 10^%d T\n", I, B_norm, dB_norm, common_exponent);
    }
}



