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

    float scale = 0.00001;
    vector<float> co;
    stack<secantData> secantStack;

    void coefficient0(int pow){
        vector<float> temp(pow+1, 0);
        co = temp;
    }

    void coefficient1(int pow){
        vector<float> temp(pow+1, 1);
        co = temp;
    }

    void coefficient(int pow, int value){
        vector<float> temp(pow+1, value);
        co = temp;
    }

    void setCoefficient(int power, float coefficient){
        this->co[power] = coefficient;
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
        cout << "rec level " << current << endl;
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

};
