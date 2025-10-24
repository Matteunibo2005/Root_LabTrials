#ifndef MYCLASS_H
#define MYCLASS_H

#include "TF1.h"
#include "TH1.h"
#include "TObject.h"
#include "TList.h"
#include <typeinfo>
// class MyClass : public TObject {
class Young : public TObject
{
public:
    Young();         // def ctor
    Young(TList *l); // parametric ctor
    Young(TList *l, int n); // parametric ctor
    //  public methods
    void Generate(); // generate according to a given function
    void Draw();
    ~Young(); // dtor

    void Set_NGen(int n);
    void Set_nToys(int n);
    void Set_samplingSteps(double n);
    void Set_ySmearing(double n);
    void Set_Origin(double n);
    void Set_samplingStep(double n);

    int Get_NGen() const;
    int Get_nToys() const;
    double Get_samplingSteps() const;
    double Get_ySmearing() const;

private:
    TList *objList_;
    int nGen_ = 1E6;
    int nToys_;
    double samplingStep_{0.0006};
    double ySmearing_{1};
    double Origin_;
};
#endif