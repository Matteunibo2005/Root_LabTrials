#include "TMath.h"
#include <vector>
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

    TCanvas *c1 = new TCanvas("myCanvas", "ABC", 100, 100, 700, 500);
    c1->Divide(2, 2);
    c1->cd(1);
    f1->Draw();
    c1->cd(2);
    f2->Draw();
    c1->cd(3);
    f3->Draw();

    TCanvas *c2 = new TCanvas("myCanvas 2", "ABC 2", 100, 100, 700, 500);
    c2->Divide(2, 2);
    c2->cd(1);
    f1->Draw();
    c2->cd(2);
    f4->Draw();
    c2->cd(3);
    f5->Draw();

    TH1F *h1m = new TH1F("h1m", "histo 1", 100, x0 - 0.03, x0 + 0.03);
    TH1F *h2m = new TH1F("h2m", "histo 2", 100, x0 - 0.03, x0 + 0.03);
    TH1F *h3m = new TH1F("h3m", "histo 3", 100, x0 - 0.03, x0 + 0.03);


    TL1 ->Add(f1);
    TL1 ->Add(h1m);
    TL1 ->Add(h2m);
    TL1 ->Add(h3m);

    Young *A = new Young(TL1);

    A->Generate();
    A->Draw();
}