#include "root_project.h"

void Young::Generate(){}

Young::Young(){
    l_ = new TList();
}
Young::Young(TList *l){
    l_ =new TList(l);
}

void Young::Draw(){}

Young::~Young(){delete l_;}