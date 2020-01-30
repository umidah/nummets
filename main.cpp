#include "nummets.h"

int main(){
    float x = 1.23456789f;
    nummets eq1;
    cout << eq1.truncate(x) << endl;
    eq1.coefficient0(2); //initialize a power 2 equation with 0 as the coefficients
    eq1.setCoefficient(0, 4);//set x^0 coefficient to 4
    cout << 1 << endl;
    eq1.setCoefficient(1, 4);
    cout << 2 << endl;
    eq1.setCoefficient(2, 1);
    cout << 3 << endl;
    //f(x) = x^2 + 4x + 4
    eq1.secantAlgo(-1, 0, 2, 8);
    eq1.printSecData();
    return 0;
}
