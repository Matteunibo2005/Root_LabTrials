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
        double val = (par[4]*par[5] * pow(sin(alpha), 2)) / pow(alpha, 2);
        return val;
    };

    TF1 *ffit = new TF1("ffit", ABCFunction, 0., 0.1, 6);


    TGraphErrors *g = new TGraphErrors("centrale60.txt", "%lg %lg %lg");
    ffit->SetParameters(6.e-5, 0.057, 632.8e-9, 1., 0.7, 1.);
    ffit->FixParameter(0, 6.e-5);
    ffit->FixParameter(2, 632.8e-9);

    ffit->SetParName(0, "d");      // larghezza fenditura o separazione
    ffit->SetParName(1, "x0");     // posizione centrale
    ffit->SetParName(2, "lambda"); // lunghezza d'onda
    ffit->SetParName(3, "L");      // distanza schermo
    ffit->SetParName(4, "I0");

    g->Draw("APE");
    TL1 -> Add(ffit);
    //TL1 -> Add(g);

    g->Fit(ffit, "SE");


    //A.Fitting(g);






}
int main(int argc, char **argv)
{
    TApplication app("app", &argc, argv);
    // setStyle();
    ABCMacro();
    app.Run(); // mantiene la finestra aperta
}