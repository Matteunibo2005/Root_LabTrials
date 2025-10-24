#include "TMath.h"
#include <vector>
#include "root_project.h"
#include "TCanvas.h"
#include "TRootApplication.h"
#include "TStyle.h"
#include <TROOT.h>
#include "TApplication.h"
#include "TGraphErrors.h"


void setStyle(){
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

    TCanvas *c = new TCanvas("myCanvas", "Varing d", 100, 100, 700, 500);
    c->Divide(2, 2);
    c->cd(1);
    f1->Draw();
    c->cd(2);
    f2->Draw();
    c->cd(3);
    f3->Draw();

    TCanvas *c2 = new TCanvas("myCanvas 2", "Varing L", 100, 100, 700, 500);
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
    //TH1F *h4m = new TH1F("h4m", "histo 4", 100, x0 - 0.03, x0 + 0.03);
    TGraphErrors *g = new TGraphErrors;



    TL1 ->Add(f1);
    TL1 ->Add(h1m);
    TL1 ->Add(h2m);
    TL1 ->Add(h3m);
    //TL1 ->Add(h4m);
    TL1 ->Add(g);


    Young A(TL1, 1E3);
    A.Set_ySmearing(10.);
    A.Generate();
    A.Draw();
}

int main(int argc, char **argv) {
    TApplication app("app", &argc, argv);
    setStyle();
    ABCMacro();
    app.Run(); // mantiene la finestra aperta
    
}