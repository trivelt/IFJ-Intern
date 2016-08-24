#include <iostream>
#include <TMath.h>
//#define DEBUG

using namespace std;
double G_x(double x)
{
    double exp = 5/4.0;
    return 5*x - 4*TMath::Power(x, exp);
}

double Q_x(double x)
{
    return 5*TMath::Power((x-1), 6) + 6*TMath::Power((x-1), 5) + 1;
}

double inwersja( double(*func)(double), double u)
{
    double e = 1e-10;
    double x_min = 0.0;
    double x_max = 1.0;
    double x;
    while(true)
    {
        x = (x_min + x_max) / 2.0;
        if(func(x) > u)
            x_max = x;
        else
            x_min = x;

#ifdef DEBUG
        cout << "inwersja x=" << x << ", x_max=" << x_max << "x_min=" << x_min << "max-min=" << x_max-x_min << endl;
#endif

        if(x_max - x_min < e)
            break;
    }
    return x;
}

double inwersja_G(double u)
{
    return inwersja(G_x, u);
}

double inwersja_Q(double u)
{
    return inwersja(Q_x, u);
}

int main()
{
    cout << "x=4, G_x=" << G_x(0.0024) << ", inwersja_G=" << inwersja_G(0.0024) << endl;
    return 0;
}

