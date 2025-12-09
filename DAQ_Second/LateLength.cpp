void doppio_fit_diviso() {

    // ======= Lettura dei due TGraphErrors =======
    TGraphErrors *g1 = new TGraphErrors("LateLenght1.txt", "%lg %lg %lg %lg");
    TGraphErrors *g2 = new TGraphErrors("LateLenght2.txt", "%lg %lg %lg %lg");

    g1->SetMarkerStyle(20);
    g1->SetMarkerColor(kRed);

    g2->SetMarkerStyle(21);
    g2->SetMarkerColor(kBlue);

    // ======= Creazione Canvas diviso =======
    TCanvas *c = new TCanvas("c", "Fit doppi", 900, 800);
    c->Divide(1,2);

    // ======= Fit lineare =======
    TF1 *f1 = new TF1("f1", "[0] + [1]*x");
    TF1 *f2 = new TF1("f2", "[0] + [1]*x");

    // ======= PRIMO GRAFICO =======
    c->cd(1);
    g1->SetTitle("Grafico 1 con fit lineare;X;Y");
    g1->Draw("APE");
    g1->Fit(f1, "Q");  // Q = quiet
    
    // ======= SECONDO GRAFICO =======
    c->cd(2);
    g2->SetTitle("Grafico 2 con fit lineare;X;Y");
    g2->Draw("APE");
    g2->Fit(f2, "Q");

    c->Update();

    // ======= Stampa delle pendenze =======
    double m1 = f1->GetParameter(1);
    double m2 = f2->GetParameter(1);

    std::cout << "Pendenza grafico 1: " << 1/m1 << std::endl;
    std::cout << "Pendenza grafico 2: " << 1/m2 << std::endl;
}

