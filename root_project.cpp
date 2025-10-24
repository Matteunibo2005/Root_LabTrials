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
Young::Young(TList *l, int n)
{
    objList_ = l;
    nGen_ = n;
}

void Young::Draw()
{
    float i = objList_->GetEntries();
    //    int col = std::ceil(i / 2);
    //    int row = std::ceil(i / 2);

    int col = 2;
    int row = 2;

    // std::cout << "i: " << i << " col: " << col << " row: " << row << std::endl;
    TCanvas *c1 = new TCanvas("c1", "Histos", 200, 10, 1000, 600);
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
    }
    c1->Update();

    TCanvas *c3 = new TCanvas("c3", "Graphs", 200, 10, 1000, 600);
    c3->Divide(row, col);

    for (int j = 0; j < i; j++)
    {
       // c2->cd(j + 1);

        if (objList_->At(j)->InheritsFrom("TGraphErrors"))
        {
            objList_->At(j)->Draw("APL");
        }
    }
}

void Young::Generate()
{

    // 1 fillrandom
    // 2 getRAndom
    // 3 hit or miss

    TF1 *f;
    TBenchmark bench;
    // finding function
    int count_h{0};
    for (int i = 0; i < objList_->GetEntries(); i++)
    {
        
        if (objList_->At(i)->InheritsFrom("TF1"))
        {
            f = static_cast<TF1 *>(objList_->At(i));
        }
    }


    // std::cout << "f(5): " << f->Eval(5) << std::endl;
    for (int i = 0; i < objList_->GetEntries(); i++)
    {

        if (objList_->At(i)->InheritsFrom("TGraphErrors"))
        {
            double max = f->GetMaximumX();
            double range = 0.03;
            TGraphErrors *g = static_cast<TGraphErrors *>(objList_->At(i));
            std::cout << "Filling Graph   max:" << max << std::endl;

            for (double x = max - range; x <= max + range; x += samplingStep_)
            {
                double y = f->Eval(x);
                double y_Smeared = gRandom->Gaus(y, ySmearing_);
                g->SetPoint(g->GetN(), x, y_Smeared);
            }
            std::cout << "Filling Finished" << std::endl;
        }

        if (objList_->At(i)->InheritsFrom("TH1F"))
        {
            if (count_h == 0)
            {

                TH1F *h1 = (TH1F *)objList_->At(i);
                bench.Start("FillRandom");
                h1->FillRandom(f->GetName(), nGen_);
                bench.Stop("FillRandom");
                h1->SetName("FillRandom");
                count_h++;
            }
            else if (count_h == 1)
            {
                TH1F *h2 = (TH1F *)objList_->At(i);
                bench.Start("GetRandom");
                for (int i = 0; i < nGen_; i++)
                {
                    h2->Fill(f->GetRandom());
                }
                bench.Stop("GetRandom");
                h2->SetName("GetRandom");

                count_h++;
            }
            else if (count_h == 2)
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
                h3->SetName("HitOrMiss");

                ++count_h;
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
