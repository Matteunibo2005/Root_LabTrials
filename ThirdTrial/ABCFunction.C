#include "TMath.h"
#include <vector>
#include "root_project.h"
#include "TCanvas.h"
#include "TRootApplication.h"
#include "TStyle.h"
#include <TROOT.h>
#include "TApplication.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include <TRandom.h>

void setStyle()
{
    gROOT->SetStyle("Plain");
    gStyle->SetOptFit(1111);
    gStyle->SetPalette(57);
    gStyle->SetOptTitle(0);
}
void ABCMacro()
{
    TList *TL1 = new TList();

    auto ABCFunction = [](double *x, double *par)
    {
        double xx = x[0];
        double alpha = (TMath::Pi() * par[0] * (xx - par[1])) / (par[2] * sqrt(pow((xx - par[1]), 2) + pow(par[3], 2)));
        double val = (par[4] * pow(sin(alpha), 2)) / pow(alpha, 2);
        return val;
    };

    const double d = 0.0001;
    const double L = 1.;
    const double x0 = 0.057;

    TF1 *f1 = new TF1("f1", ABCFunction, 0., 0.1, 5);
    TF1 *f2 = new TF1("f2", ABCFunction, 0., 0.1, 5);
    TF1 *f3 = new TF1("f3", ABCFunction, 0., 0.1, 5);
    TF1 *f4 = new TF1("f4", ABCFunction, 0., 0.1, 5);
    TF1 *f5 = new TF1("f5", ABCFunction, 0., 0.1, 5);
    f1->SetParameters(d, 0.057, 632.8e-9, L, 500.);
    f2->SetParameters(0.1 * d, 0.057, 632.8e-9, L, 500.);
    f3->SetParameters(10. * d, 0.057, 632.8e-9, L, 500.);
    f4->SetParameters(d, 0.057, 632.8e-9, 0.5 * L, 500.);
    f5->SetParameters(d, 0.057, 632.8e-9, 2 * L, 500.);

    TF1 *ffit = new TF1("ffit", ABCFunction, 0., 0.1, 5);
    ffit->SetParameters(0.0001, 0.057, 632.8e-9, 1., 500.);
    TL1->Add(ffit);

    // // === Stile globale ===
    // gStyle->SetOptStat(0);
    gStyle->SetTitleFont(42, "XYZ");
    gStyle->SetLabelFont(42, "XYZ");
    gStyle->SetTitleSize(0.045, "XYZ");
    gStyle->SetLabelSize(0.04, "XYZ");

    //    // === Canvas 1: Varying d ===
    // TCanvas *c = new TCanvas("myCanvas", "Varying d", 100, 100, 800, 600);
    // c->Divide(2, 2);
    // c->SetFillColor(0);
    //
    //// --- Primo pad ---
    // c->cd(1);
    // f1->SetLineColor(kBlue + 1);
    // f1->SetLineWidth(2);
    // f1->SetTitle("Varying d = 0.0001");
    // f1->Draw("L");
    // auto leg1 = new TLegend(0.65, 0.75, 0.88, 0.88);
    // leg1->AddEntry(f1, "Base: f(x)", "l");
    // leg1->Draw();
    //
    //// --- Secondo pad ---
    // c->cd(2);
    // f2->SetLineColor(kRed + 1);
    // f2->SetLineWidth(2);
    // f2->SetTitle("Varying d = 0.00001");
    // f2->Draw("L");
    // auto leg2 = new TLegend(0.65, 0.75, 0.88, 0.88);
    // leg2->AddEntry(f2, "Resized: f2(x)", "l");
    // leg2->Draw();
    //
    //// --- Terzo pad ---
    // c->cd(3);
    // f3->SetLineColor(kGreen + 2);
    // f3->SetLineWidth(2);
    // f3->SetTitle("Varying d = 0.001");
    // f3->Draw("L");
    // auto leg3 = new TLegend(0.60, 0.75, 0.88, 0.88);
    // leg3->AddEntry(f3, "Resized: f3(x)", "l");
    // leg3->Draw();
    //
    // c->SaveAs("D_Resizing.png");
    //
    ////    // === Canvas 2: Varying L ===
    // TCanvas *c2 = new TCanvas("myCanvas2", "Varying L", 950, 100, 800, 600);
    // c2->Divide(2, 2);
    // c2->SetFillColor(0);
    //
    ////    // --- Primo pad ---
    // c2->cd(1);
    // f1->SetLineColor(kMagenta + 1);
    // f1->SetTitle("Varying L = 1.0");
    // f1->Draw("L");
    ////
    // auto leg4 = new TLegend(0.65, 0.75, 0.88, 0.88);
    // leg4->AddEntry(f1, "Base Function: f(x)", "l");
    // leg4->Draw();
    ////
    //// --- Secondo pad ---
    // c2->cd(2);
    // f4->SetLineColor(kOrange + 7);
    // f4->SetLineWidth(2);
    // f4->SetTitle("Varying L = 0.5");
    // f4->Draw("L");
    ////
    // auto leg5 = new TLegend(0.65, 0.75, 0.88, 0.88);
    // leg5->AddEntry(f4, "Resized: f4(x)", "l");
    // leg5->Draw();
    ////
    ////    // --- Terzo pad ---
    // c2->cd(3);
    // f5->SetLineColor(kCyan + 2);
    // f5->SetLineWidth(2);
    // f5->SetTitle("Varying L = 2.0");
    // f5->Draw("L");
    //
    // auto leg6 = new TLegend(0.65, 0.75, 0.88, 0.88);
    // leg6->AddEntry(f5, "Resized: f5(x)", "l");
    // leg6->Draw();
    //
    // c2->SaveAs("L_Resizing.png");

    f1->SetTitle("Base Function");
    TH1F *h1m = new TH1F("h1m", "histo 1", 100, x0 - 0.03, x0 + 0.03);
    TH1F *h2m = new TH1F("h2m", "histo 2", 100, x0 - 0.03, x0 + 0.03);
    TH1F *h3m = new TH1F("h3m", "histo 3", 100, x0 - 0.03, x0 + 0.03);
    // TH1F *h4m = new TH1F("h4m", "histo 4", 100, x0 - 0.03, x0 + 0.03);
    TGraphErrors *g1 = new TGraphErrors;
    TGraphErrors *g2 = new TGraphErrors;
    TGraphErrors *g3 = new TGraphErrors;
    TGraphErrors *g4 = new TGraphErrors;
    // TGraphErrors *g5 = new TGraphErrors;

    TL1->Add(f1);
    TL1->Add(h1m);
    // TL1->Add(h2m);
    // TL1->Add(h3m);
    // TL1 ->Add(h4m);
    TL1->Add(g1);
    // TL1->Add(g2);
    // TL1->Add(g3);
    // TL1->Add(g4);
    // TL1->Add(g5);

    Young A(TL1, 1E6);
    // A.Set_ySmearing(100.0);

    // A.Generate();
    // A.Draw();

    // A.Montecarlo();
    // A.fitResult.cov.Print();
    // A.fitResult.cor.Print(); // 0-3 0-2 0=d 3=L 2=lambda

    for (int i = 0; i < 10; i++) // 1000 trials
    {
        double error = gRandom->Uniform(0.999, 1.001);
        // A.Generate();
        //std::cout << "error: " << L << std::endl;

        A.Analyse(error);
    }
    A.DrawHistos();
}

int main(int argc, char **argv)
{
    TApplication app("app", &argc, argv);
    // setStyle();
    ABCMacro();
    app.Run(); // mantiene la finestra aperta
}