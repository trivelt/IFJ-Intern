#include <iostream>
#include <TMath.h>

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

double inwersja_G(double u)
{

}

double inwersja_Q(double u)
{

}

int main()
{
    cout << "x=3, G_x=" << Q_x(4) << endl;
    return 0;
}

