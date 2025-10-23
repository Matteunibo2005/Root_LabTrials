#ifndef MYCLASS_H
#define MYCLASS_H

#include "TF1.h"
#include "TH1F.h"
#include "TObject.h"
#include "TList.h"
//class MyClass : public TObject {
class Young : public TObject{
public:
Young(); //def ctor
Young(TList *l); //parametric ctor
//public methods
void Generate(); //generate according to a given function
void Draw();
~Young(); //dtor
private:
TList *l_;
int nGen_;
int nToys_;
double samplingStep_;
double ySmearing_;
ClassDef(Young,1)
};
#endif