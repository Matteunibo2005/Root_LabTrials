#include "root_project.h"
#include "TRandom.h"
#include "TCanvas.h"

Young::Young()
{
    objList_ = new TList();
}
Young::Young(TList *l)
{
    objList_ = new TList(l);
}

void Young::Draw()
{
    int i = objList_->GetEntries();
    int col = objList_->GetEntries() / 3;
    int row = objList_->GetEntries() / 3;

    TCanvas *c1 = new TCanvas("c1", "TList example", 200, 10, 600, 400);
    c1->Divide(row, col);

    for (int j = 0; j < i; j++)
    {
        c1->cd(j + 1);
        if (objList_->At(i)->InheritsFrom("TH1"))
        {
            objList_->At(i)->Draw("H,E,P");
        }
        if (objList_->At(i)->InheritsFrom("TF1"))
        {
            objList_->At(i)->Draw("APE");
        }
        if (objList_->At(i)->InheritsFrom("TGraphError"))
        {
            objList_->At(i)->Draw("APE");
        }
    }
}

void Young::Generate()
{

    // 1 fillrandom
    // 2 getRAndom
    // 3 hit or miss

    TF1 *f;
    // finding function
    for (int i = 0; i < objList_->GetEntries(); i++)
    {
        if (objList_->At(i)->InheritsFrom("TF1"))
        {
            f = (TF1 *)objList_->At(i);
        }
    }

    int count{0};
    for (int i = 0; i < objList_->GetEntries(); i++)
    {

            if(objList_->At(i)-> InheritsFrom("TGraphErrors"))
            {
                double max = Origin_;
                double range = 0.03;
                double samplingStep=Samplingstep_;
                for (float x= max - range; x <= max + range; x+=samplingStep) {
                    y= f -> Eval(x);
                    y_smeared= gRandom->Gaus(y, ySmearing_);
                };
            }

        if (objList_->At(i)->InheritsFrom("TH1"))
        {
            switch (count)
            {
            case 0:
                TH1 *h1 = (TH1 *)objList_->At(i);
                h1->FillRandom(f->GetName(), nGen_);
                count++;
                break;
            case 1:
                TH1 *h2 = (TH1 *)objList_->At(i);
                h1->Fill(f->GetRandom());
                count++;

                break;
            case 2:
                TH1 *h3 = (TH1 *)objList_->At(i);

                int generated{0};
                while (generated < nGen_)
                {
                    double x = gRandom->Rndm();
                    double y = gRandom->Rndm();

                    if (!(y > f->Eval(x)))
                    {
                        h1->Fill(y);
                        ++generated;
                    }
                }
                ++count;
                break;

            default:
                break;
            }
        }
    }
}

Young::~Young() { delete objList_; }

void Young::Set_NGen(int n)
{
    nGen_ = n;
}

void Young::Set_nToys(int n)
{
    nToys_ = n;
}

void Young::Set_samplingSteps(double n)
{
    samplingStep_ = n;
}

void Young::Set_ySmearing(double n)
{
    ySmearing_ = n;
}

void Young::Set_Origin(double n)
{
    Origin_ = n;
}

void Young::Set_samplingStep(double n)
{
    samplingStep_ = n;
}

int Young::Get_NGen() const
{
    return nGen_;
}

int Young::Get_nToys() const
{
    return nToys_;
}

double Young::Get_samplingSteps() const
{
    return samplingStep_;
}

double Young::Get_ySmearing() const
{
    return ySmearing_;
}
