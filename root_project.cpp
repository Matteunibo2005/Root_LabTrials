#include "root_project.h"
#include "TRandom.h"
#include "TCanvas.h"

Young::Young()
{
    objList_ = new TList();
}

Young::Young(TList *l){
    objList_ = l;
}

void Young::Draw()
{
    int i = objList_->GetEntries();
    int col = 4;
    int row = 4;

    TCanvas *c1 = new TCanvas("c1", "TList example", 200, 10, 600, 400);
    c1->Divide(row, col);

    for (int j = 0; j < i; j++)
    {
        c1->cd(j + 1);
        if (objList_->At(j)->InheritsFrom("TH1F"))
        {
            objList_->At(j)->Draw("APE");
        }
        if (objList_->At(j)->InheritsFrom("TF1"))
        {
            objList_->At(j)->Draw("APE");
        }
        if (objList_->At(j)->InheritsFrom("TGraphError"))
        {
            objList_->At(j)->Draw("APE");
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

        if (objList_->At(i)->InheritsFrom("TGraphErrors"))
        {
            double max = Origin_;
            double range = 0.03;
            double samplingStep = this->Get_samplingSteps();
            double ySmearing = this->Get_ySmearing();
            for (float x = max - range; x <= max + range; x += samplingStep)
            {
                double y = f->Eval(x);
                double y_Smeared = gRandom->Gaus(y, ySmearing);
            };
        }

        if (objList_->At(i)->InheritsFrom("TH1F"))
        {
            int count = 0;
            if (count == 0)
            {
                TH1F *h1 = (TH1F *)objList_->At(i);
                h1->FillRandom(f->GetName(), nGen_);
                count++;
                break;
            }
            else if (count == 1)
            {
                TH1F *h2 = (TH1F *)objList_->At(i);
                h2->Fill(f->GetRandom(),nGen_);
                count++;

                break;
            }
            else if (count == 2)
            {
                TH1F *h3 = (TH1F *)objList_->At(i);

                int generated{0};
                while (generated < nGen_)
                {
                    double x = gRandom->Rndm();
                    double y = gRandom->Rndm();

                    if (!(y > f->Eval(x)))
                    {
                        h3->Fill(y,nGen_);
                        ++generated;
                    }
                }
                ++count;
                break;
            }
            else
            {
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
ClassImp(1);
