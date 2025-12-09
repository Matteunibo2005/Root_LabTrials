void doppio_fit_diviso()
{

    // ======= Lettura dei due TGraphErrors =======
    TGraphErrors *g1 = new TGraphErrors("LateLenght1.txt", "%lg %lg");

    g1->SetMarkerStyle(20);
    g1->SetMarkerColor(kRed);

    // ======= Creazione Canvas diviso =======
    TCanvas *c = new TCanvas("c", "Fit doppi", 900, 800);

    // ======= Fit lineare =======
    TF1 *f1 = new TF1("f1", "[0] + [1]*x");

    // ======= PRIMO GRAFICO =======

    g1->SetTitle("Grafico 1 con fit lineare;X;Y");
    g1->Draw("APE");
    g1->Fit(f1, "Q"); // Q = quiet

    c->Update();
    c->SaveAs("fit.png");
        // ======= Stampa delle pendenze =======
    double m1 = f1->GetParameter(1);

    std::cout << "Pendenza grafico 1: " << m1 << std::endl;
}