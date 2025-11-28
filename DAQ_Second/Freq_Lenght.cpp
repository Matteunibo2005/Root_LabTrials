void doppio_fit_diviso() {

    // ======= Lettura dei due TGraphErrors =======
    TGraphErrors *g1 = new TGraphErrors("FreqLenght1.txt", "%lg %lg %lg");
    TGraphErrors *g2 = new TGraphErrors("FreqLenght2.txt", "%lg %lg %lg");
    TGraphErrors *g3 = new TGraphErrors("FreqLenght3.txt", "%lg %lg %lg");

    g1->SetMarkerStyle(20);
    g1->SetMarkerColor(kRed);

    g2->SetMarkerStyle(21);
    g2->SetMarkerColor(kBlue);    
    
    g3->SetMarkerStyle(21);
    g3->SetMarkerColor(kGreen);

    // ======= Creazione Canvas diviso =======
    TCanvas *c = new TCanvas("c", "Fit doppi", 900, 800);
    c->Divide(2,2);

    // ======= Fit lineare =======
    TF1 *f1 = new TF1("f1", "[0] + [1]*x");
    TF1 *f2 = new TF1("f2", "[0] + [1]*x");
    TF1 *f3 = new TF1("f3", "[0] + [1]*x");

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

       // ======= TERZO GRAFICO =======
    c->cd(3);
    g3->SetTitle("Grafico 3 con fit lineare;X;Y");
    g3->Draw("APE");
    g3->Fit(f3, "Q");

    c->Update();

    // ======= Stampa delle pendenze =======
    double m1 = f1->GetParameter(1);
    double m2 = f2->GetParameter(1);
    double m3 = f3->GetParameter(1);

    std::cout << "Pendenza grafico 1: " << m1 << std::endl;
    std::cout << "Pendenza grafico 2: " << m2 << std::endl;
    std::cout << "Pendenza grafico 3: " << m3 << std::endl;
}
