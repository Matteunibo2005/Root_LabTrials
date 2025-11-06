#include "root_project.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TApplication.h"
#include "TBenchmark.h"
#include "TGraphErrors.h"
#include "TLegend.h"
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

    double countH{0};
    double countF{0};
    double countG{0};
    // count histos

    for (int j = 1; j < i; j++)
    {

        if (objList_->At(j)->InheritsFrom("TH1F"))
        {
            countH++;
        }
        if (objList_->At(j)->InheritsFrom("TF1"))
        {
            countF++;
        }
        if (objList_->At(j)->InheritsFrom("TGraphErrors"))
        {
            countG++;
        }
    }

    // std::cout << "i: " << i << " col: " << col << " row: " << row << std::endl;
    TCanvas *c1 = new TCanvas("c1", "Histos", 200, 10, 1000, 600);
    c1->Divide(std::ceil((countH + countF) / 2), std::floor((countH + countF) / 2));

    int padIndex{0};
    for (int j = 1; j < i; j++)
    {
        c1->cd(++padIndex);
        if (objList_->At(j)->InheritsFrom("TH1F"))
        {
            TH1F *h = static_cast<TH1F *>(objList_->At(j));
            h->SetFillColorAlpha(kBlue - 9, 0.8); // blu chiaro semi-trasparente
            h->SetLineColor(kBlue + 2);
            h->SetLineWidth(2);
            h->SetBarWidth(0.45); // larghezza colonne
            h->SetBarOffset(0.05);
            objList_->At(j)->Draw();
        }
        if (objList_->At(j)->InheritsFrom("TF1"))
        {
            objList_->At(j)->Draw();
        }
    }
    c1->Update();
    c1->SaveAs("Histos.png");

    TCanvas *c3 = new TCanvas("c3", "Graphs", 200, 10, 1000, 600);
    c3->Divide(std::ceil(countG / 2), std::floor(countG / 2));
    padIndex = 0;
    for (int j = 1; j < i; j++)
    {

        if (objList_->At(j)->InheritsFrom("TGraphErrors"))
        {
            c3->cd(++padIndex);
            TGraphErrors *g = static_cast<TGraphErrors *>(objList_->At(j));
            // g->SetMarkerSize(20.0);
            // std::cout << "graph: " << g->GetMean() <<std::endl;
            // std::cout << "Pad " << j+1 << " -> TGraphErrors ptr: " << g << std::endl;

            g->SetMarkerStyle(21);
            g->SetMarkerSize(0.7);
            g->SetMarkerColor(kRed + 1);
            g->SetLineColor(kRed + 1);
            g->SetLineWidth(2);
            g->SetFillColorAlpha(kRed - 9, 0.2);

            std::string lbl{"a"};

            if (padIndex == 1)
            {
                lbl = "smearing: " + std::to_string(0);
            }
            if (padIndex == 2)
            {
                lbl = "smearing: " + std::to_string(1);
            }
            if (padIndex == 3)
            {
                lbl = "smearing: " + std::to_string(10);
            }
            if (padIndex == 4)
            {
                lbl = "smearing: " + std::to_string(100);
            }

            TLegend *leg = new TLegend(0.68, 0.75, 0.88, 0.88);
            leg->AddEntry(g, "Grafico Misura Errore", "pl");
            leg->AddEntry((TObject *)0, lbl.c_str(), "");
            leg->SetFillStyle(0);
            g->Draw();
            leg->Draw();
        }
    }
    c3->SaveAs("SmearedGraphs.png");
}

void Young::fillSmearedGraph(TGraphErrors *g, TF1 *f)
{
    double max = f->GetMaximumX();
    double range = 0.03;
    for (double x = max - range; x <= max + range; x += samplingStep_)
    {
        double y = f->Eval(x);
        double y_Smeared = gRandom->Gaus(y, ySmearing_);
        g->SetPoint(g->GetN(), x, y_Smeared);
    }
    TF1 *func = static_cast<TF1 *>(objList_->At(0));
    func->SetParameter(0,d_);
    func->SetParameter(3,L_);
    func->SetLineColor(kGreen);
    func->SetLineWidth(2);
    g->Fit(func, "ERS");
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
    int count_g{0};
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
            if (count_g == 0)
            {
                ySmearing_ = 0.;
            }
            else if (count_g == 1)
            {
                ySmearing_ = 1.;
            }
            else if (count_g == 2)
            {
                ySmearing_ = 10.;
            }
            else if (count_g == 3)
            {
                ySmearing_ = 100.;
            }
            fillSmearedGraph(static_cast<TGraphErrors *>(objList_->At(i)), f);
            count_g++;
        }

        // if (ySmearing_ == 1. && i > 3)
        // {
        //     TH1 *hist = static_cast<TH1 *>(objList_->At(i));

        //     hist->Fit(func, "ERS");
        // }

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

void Young::Set_yError(double n)
{
    yError_ = n;
}

void Young::Set_d(double n)
{
    d_ = n;
}

void Young::Set_L(double n)
{
    L_ = n;
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

double Young::Get_yError() const
{
    return yError_;
}

double Young::Get_d() const
{
    return d_;
}

double Young::Get_L() const
{
    return L_;
}

void Young::Analyse() {}
