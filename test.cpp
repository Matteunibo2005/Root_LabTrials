#include "root_project.h"
#include "TH1.h"
#include "TApplication.h"
#include "TStyle.h"
#include "TRootApplication.h"
#include <TROOT.h>
#include "TGraphErrors.h"

//g++ -o test test.cpp root_project.cpp $(root-config --cflags --libs)


void setStyle(){
  gROOT->SetStyle("Plain");
  gStyle->SetOptFit(1111);
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(0);
}
void Test()
{
    TF1 *f = new TF1 ("f1", "[0]+[1]*x", 0, 10);
    f->SetParameters(1, 1);


    TH1F *h = new TH1F( "histo" , "histo1", 10, 0, 20); 
    TH1F *h2 = new TH1F( "histo2" , "histo2", 10, 0, 20); 
    TH1F *h3 = new TH1F( "histo3" , "histo3", 10, 0, 20); 

    TGraphErrors *g = new TGraphErrors;

    TList *t = new TList;
    t->Add(f);
    t->Add(h);
    t->Add(h2);
    t->Add(h3);
    //t->Add(g);



    Young y(t);
    //y.Set_Origin(0);

    y.Generate();
    y.Draw();



}

int main(int argc, char **argv) {
    TApplication app("app", &argc, argv);
    setStyle();
    Test();
    app.Run(); // mantiene la finestra aperta
    
}
