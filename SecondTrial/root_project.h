#ifndef YOUNG_H
#define YOUNG_H

#include "TF1.h"
#include "TH1.h"
#include "TObject.h"
#include "TList.h"
#include "TGraphErrors.h"
#include <typeinfo>
#include "TMatrixD.h"

struct Param
{
    double value;
    double error;
};
struct FitResult
{   
    TMatrixD cov;
    TMatrixD cor;

};
// class MyClass : public TObject {
class Young : public TObject
{
public:
    Young();         // def ctor
    Young(TList *l); // parametric ctor
    Young(TList *l, int n); // parametric ctor
    //  public methods
    FitResult fitResult;

    void Generate(); // generate according to a given function
    void Generate_2(); // generate according to a given function
    void Draw();
    const TFitResultPtr Fitting(TGraphErrors *g);
    const TFitResultPtr Fitting(TGraphErrors *g, TF1 *func);

    ~Young(); // dtor

    void Set_NGen(int n);
    void Set_nToys(int n);
    void Set_samplingSteps(double n);
    void Set_ySmearing(double n);
    void Set_Origin(double n);
    void Set_samplingStep(double n);
    void Set_yError(double n);
    void Set_d(Param n);
    void Set_L(Param n);

    int Get_NGen() const;
    int Get_nToys() const;
    double Get_samplingSteps() const;
    double Get_ySmearing() const;
    double Get_yError() const;
    Param Get_d() const;
    Param Get_L() const;

    void Analyse();
    void Montecarlo();

private:
    TList *objList_;
    int nGen_ = 1E6;
    int nToys_;
    double samplingStep_{0.0006};
    double ySmearing_{1.0};
    double Origin_;
    double yError_{1.};  //incertezza sperimentale in y assegnata ai punti del grafico
    Param d_ { 0.0001, 0.};
    Param L_ {1., 0.};
    

    void fillSmearedGraph(TGraphErrors *g, TF1 *f);
};
#endif