#include "nummets.h"

int main(){
    float x = 1.23456789f;
    nummets eq1;
    cout << eq1.truncate(x) << endl;
    eq1.coefficient0(2);
    eq1.setCoefficient(0,8);
    eq1.setCoefficient(1,-6);
    eq1.setCoefficient(2, 1);
    eq1.secantAlgo(0, 1, 2, 8);
    eq1.otherAlgo(1, 2, 8);
    eq1.printSecData();
    cout << endl << endl;
    eq1.printOtherData();
    return 0;
}
