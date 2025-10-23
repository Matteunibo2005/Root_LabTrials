#include "root_project.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TApplication.h"
#include "TBenchmark.h"
#include "TGraphErrors.h"
Young::Young()
{
    objList_ = new TList();
}

Young::Young(TList *l)
{
    objList_ = l;
}

void Young::Draw()
{
    int i = objList_->GetEntries();
    int col = i/2;
    int row = i/2;

    TCanvas *c1 = new TCanvas("c1", "TList example", 200, 10, 1000, 600);
    c1->Divide(row, col);

    for (int j = 0; j < i; j++)
    {
        c1->cd(j + 1);
        if (objList_->At(j)->InheritsFrom("TH1F"))
        {
            objList_->At(j)->Draw();
        }
        if (objList_->At(j)->InheritsFrom("TF1"))
        {
            objList_->At(j)->Draw();
        }
        if (objList_->At(j)->InheritsFrom("TGraphError"))
        {
            objList_->At(j)->Draw("APE");
        }
    }   
    c1->Update();
}

void Young::Generate()
{

    // 1 fillrandom
    // 2 getRAndom
    // 3 hit or miss

    TF1 *f;
    TBenchmark bench;
    // finding function
    for (int i = 0; i < objList_->GetEntries(); i++)
    {
        if (objList_->At(i)->InheritsFrom("TF1"))
        {
            f = static_cast<TF1 *>(objList_->At(i));
        }
    }

    int count{0};
    // std::cout << "f(5): " << f->Eval(5) << std::endl;
    for (int i = 0; i < objList_->GetEntries(); i++)
    {

        if (objList_->At(i)->InheritsFrom("TGraphErrors"))
        {
            double max = Origin_;
            double range = 0.03;
            for (float x = max - range; x <= max + range; x += samplingStep_)
            {
                double y = f->Eval(x);
                double y_Smeared = ySmearing_ + gRandom->Gaus();
                TGraphErrors *g = static_cast<TGraphErrors *>( objList_->At(i));
                g->SetPoint(g->GetN(), x, y_Smeared);
            }
        }

        if (objList_->At(i)->InheritsFrom("TH1F"))
        {
            if (count == 0)
            {
                
                TH1F *h1 = (TH1F *)objList_->At(i);
                bench.Start("FillRandom");
                h1->FillRandom(f->GetName(), nGen_);
                bench.Stop("FillRandom");

                count++;
            }
            else if (count == 1)
            {
                TH1F *h2 = (TH1F *)objList_->At(i);
                bench.Start("GetRandom");
                for (int i = 0; i < nGen_; i++)
                {
                    h2->Fill(f->GetRandom());
                }
                bench.Stop("GetRandom");

                count++;
            }
            else if (count == 2)
            {
                TH1F *h3 = (TH1F *)objList_->At(i);

                double fmax = f->GetMaximum(f->GetXmin(), f->GetXmax());

                int generated{0};
                bench.Start("HitMiss");
                while (generated < nGen_)
                {
                    double x = gRandom->Uniform(f->GetXmin(), f->GetXmax());
                    double y = gRandom->Uniform(0, fmax);

                    if (y < f->Eval(x))
                    {
                        h3->Fill(x);
                        ++generated;
                    }
                }
                bench.Stop("HitMiss");

                ++count;
            }
        }

    }
    bench.Show("FillRandom");
    bench.Show("GetRandom");
    bench.Show("HitMiss");

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
