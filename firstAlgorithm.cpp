#include <math.h>
#include <algorithm>
#include <iostream>
#include <boost/dynamic_bitset.hpp>

using namespace std;

void getInitialValues(int &P1, int &P2, int &Q, int &max);
void setInitialValues(int &P1, int &P2, int &Q, int &max);
void doubleAndAddOne(double wPrev[4], int max, int P1, int P2, int Q);
int getBinaryDigits(int n);


int main(){
    double w[4];        //representing {Lm, Km, Lm+1, Km+1}
    int max;            //i value representing the number of times the algorithm is to be repeated
    int P1, P2, Q;

    //getInitialValues(P1, P2, Q, max);
    setInitialValues(P1, P2, Q, max);

    //compute first double and add algorithm
    doubleAndAddOne(w, max, P1, P2, Q);

    //recover U2m from Km
    cout << "K" << max << " = " << w[1] << endl;
    cout << "U" << max*2 << ": " << 2*w[1]*pow(Q, max);

    return 0;
}


void getInitialValues(int &P1, int &P2, int &Q, int &max){
    cout << "Enter P1: ";
    cin >> P1;
    cout << "Enter P2: ";
    cin >> P2;
    cout << "Enter Q: ";        //remove in final program since Q will always equal 1
    cin >> Q;
    cout << "Enter a (or b): ";
    cin >> max;

    //need error checking to ensure values meet specifications
}


//Function for testing question 5
void setInitialValues(int &P1, int &P2, int &Q, int &max){
    P1 = 1;     //2|P1 to avoid fractions
    P2 = 1;    
    Q = 2;      //Q will always equal 1 for the crypto algorithm
    max = 5;
}


void doubleAndAddOne(double wPrev[4], int max, int P1, int P2, int Q){
    double L1, K1;
    double *A = &wPrev[0], *B = &wPrev[1], *C = &wPrev[2], *D = &wPrev[3]; //so equations resemble those in the paper
    double U2 = P1;
    double V2 = pow((double)P1, 2) - 2*P2 - 4*Q;
    double delta = pow((double)P1, 2) - 4*P2;
    double wNext[4];                                //Wi+1 representing {Lm, Km, Lm+1, Km+1}
    int h = getBinaryDigits(max);
    boost::dynamic_bitset<> m(h, max);              //binary expansion of max

    //Set initial values L1, K1 for W0
    wPrev[0] = V2/(2*Q);
    L1 = wPrev[0];
    wPrev[1] = U2/(2*Q);
    K1 = wPrev[1];
    //Set L2 and K2 using (5)
    wPrev[2] = pow(wPrev[0], 2) + delta * pow(wPrev[1], 2) - 2;
    wPrev[3] = 2 * wPrev[0] * wPrev[1];

    //Compute Wi+1 using Wi until Wh = {Lm, Km, Lm+1, Km+1}
    for(int i = h-1; i > 0; i--){
        if(m[i-1] == 0){
            wNext[0] = (pow(*A, 2) + delta * pow(*B, 2) - 2);
            wNext[1] = (2 * *A * *B);
            wNext[2] = (*A * *C + delta * *B * *D - L1);
            wNext[3] = (*B * *C + *A * *D - K1);
        }
        else{
            wNext[0] = (*A * *C + delta * *B * *D - L1);
            wNext[1] = (*B * *C + *A * *D - K1);
            wNext[2] = (pow(*C, 2) + delta * pow(*D, 2) - 2);
            wNext[3] = (2 * *C * *D);
        }

        //reset wPrev as wNext
        copy(wNext, wNext+4, wPrev);
    }
}


//given a decimal integer, return the number of digits in the binary expansion of that number
int getBinaryDigits(int n){
    return 1 + (int) log2 ((double) n);
}