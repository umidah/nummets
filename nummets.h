#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <cmath>

using namespace std;

class nummets{
public:

    struct secantData{
        float x;
        float fx;
        float xPrev;
        float fxPrev;
        float error;

        secantData(float x, float fx, float xPrev, float fxPrev, float error){
            this->x = x;
            this->fx = fx;
            this->xPrev = xPrev;
            this->fxPrev = fxPrev;
            this->error = error;
        }
    };

    struct otherData{
        float x;
        float fx;
        float fxPrime;
        float error;

        otherData(float x, float fx, float fxPrime, float error){
            this->x = x;
            this->fx = fx;
            this->fxPrime = fxPrime;
            this->error = error;
        }
    };

    float scale = 0.00001;
    vector<float> co;
    vector<float> coPrime;
    stack<secantData> secantStack;
    stack<otherData> otherStack;

    void coefficient0(int pow){
        vector<float> temp(pow, 0);
        coPrime = temp;
        temp.push_back(0);
        co = temp;
    }

    void coefficient1(int pow){
        vector<float> temp(pow, 1);
        coPrime = temp;
        temp.push_back(1);
        co = temp;

    }

    void coefficient(int pow, int value){
        vector<float> temp(pow+1, value);
        co = temp;
        vector<float> tempPrime;
        int size = temp.size()-1;
        float der;
        for(int x=0; x< size; x++){
            der = temp[x]*(x+1);
            tempPrime.insert(tempPrime.begin(), der);
        }
        coPrime = tempPrime;
    }

    void setCoefficient(int power, float coefficient){
        this->co[power] = coefficient;
        this->coPrime[power-1] = coefficient*power;
    }


    float truncate(float value){
        return (int)(value/this->scale) * scale;
    }

    float relativeError(float current, float previous){
        return truncate(abs(current-previous)/current);
    }

    void secantAlgo(float x1, float x2, int power, int limit){
        float fx1, fx2;
        for (int x = 0; x <= power; x++){
            fx1 += co[x]*(pow(x1, x));
        }
        for (int x = 0; x <= power; x++){
            fx2 += co[x]*(pow(x2, x));
        }
        fx1 = truncate(fx1);
        fx2 = truncate(fx2);
        secantData i1(x1, fx1, 0, 0, 0);
        secantData i2(x2, fx2, x1, fx1, relativeError(x2, x1));
        int current = 0;
        secantAlgoRec(x2, fx2, x1, fx1, power, limit, current);
        secantStack.push(i2);
        secantStack.push(i1);
    }

    void secantAlgoRec(float x, float fx, float xPrev, float fxPrev, int power, int limit, int current){
        if(limit == current) return;
        //cout << "rec level " << current << endl;
        float xNow = x - ((fx * (x-xPrev))/(fx-fxPrev));
        xNow = truncate(xNow);
        float fxNow;
        for (int x = 0; x <= power; x++){
            fxNow += co[x]*(pow(xNow, x));
        }
        fxNow = truncate(fxNow);
        secantAlgoRec(xNow, fxNow, x, fx, power, limit, current+1);
        secantData temp(xNow, fxNow, x, fx, relativeError(xNow, x));
        this->secantStack.push(temp);
    }

    void printSecData(){
        int base = 10;
        char fill = ' ';
        while(!this->secantStack.empty()){
            secantData &curr = this->secantStack.top();
            cout << setw(base) << setfill(fill) << curr.x;
            cout << setw(base) << setfill(fill) << curr.fx;
            cout << setw(base) << setfill(fill) << curr.xPrev;
            cout << setw(base) << setfill(fill) << curr.fxPrev;
            cout << setw(base) << setfill(fill) << curr.error << "";
            cout << endl;
            this->secantStack.pop();
        }
    }

    void otherAlgo(float xi, int power, int limit){
        float fxi, fxPrime;
        for (int x = 0; x <= power; x++){
            fxi += co[x]*(pow(xi, x));
        }
        for (int x = 0; x <= power-1; x++){
            fxPrime += co[x]*(pow(xi, x));
        }
        fxi = truncate(fxi);
        fxPrime = truncate(fxPrime);
        otherData temp(xi, fxi, fxPrime, 0);
        int current = 0;
        otherAlgoRec(xi, fxi, fxPrime, power, limit, current);
        this->otherStack.push(temp);
    }

    void otherAlgoRec(float x, float fx, float fxPrime, int power, int limit, int current){
        if(limit == current) return;
        //cout << "rec level " << current << endl;
        float xNow = x - (fx/fxPrime);
        xNow = truncate(xNow);
        float fxNow, fxPrimeNow;
        for (int x = 0; x <= power; x++){
            fxNow += co[x]*(pow(xNow, x));
        }
        for (int x = 0; x <= power-1; x++){
            fxPrimeNow += coPrime[x]*(pow(xNow, x));
        }
        fxNow = truncate(fxNow);
        fxPrimeNow = truncate(fxPrimeNow);
        otherAlgoRec(xNow, fxNow, fxPrimeNow, power, limit, current+1);
        otherData temp(xNow, fxNow, fxPrimeNow, relativeError(xNow, x));
        this->otherStack.push(temp);
    }

    void printOtherData(){
        int base = 10;
        char fill = ' ';
        while(!this->otherStack.empty()){
            otherData &curr = this->otherStack.top();
            cout << setw(base) << setfill(fill) << curr.x;
            cout << setw(base) << setfill(fill) << curr.fx;
            cout << setw(base) << setfill(fill) << curr.fxPrime;
            cout << setw(base) << setfill(fill) << curr.error;
            cout << endl;
            this->otherStack.pop();
        }
    }
};
