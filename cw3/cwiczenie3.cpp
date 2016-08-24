#include <iostream>
#include <TMath.h>
#include <TRandom.h>
#include <TH1F.h>
#include <TCanvas.h>
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

double* custom_distribution( double(*inwersja)(double), int n)
{
    TRandom random(0);
    double* array = new double[n];
    for(int i=0; i<n; i++)
    {
        double randNumber = inwersja(random.Rndm());
        array[i] = randNumber;
    }
    return array;
}

double* G_distribution(int n)
{
    return custom_distribution(inwersja_G, n);
}

double* Q_distribution(int n)
{
    return custom_distribution(inwersja_Q, n);
}

int main()
{
    TH1F *h_G = new TH1F("h_G", "h_G", 1000, 0, 1);
    TH1F *h_Q = new TH1F("h_Q", "h_Q", 1000, 0, 0);

//    cout << "x=4, G_x=" << G_x(0.0024) << ", inwersja_G=" << inwersja_G(0.0024) << endl;

    int n = 1000000;
    double* G_dist = G_distribution(n);
    double* Q_dist = Q_distribution(n);
    for(int i=0; i<n; i++)
    {
        h_G->Fill(G_dist[i]);
        h_Q->Fill(Q_dist[i]);
    }

    TCanvas* canvas = new TCanvas();
    canvas->Clear();
    h_G->SetStats(kFALSE);
    h_G->Draw();

    h_Q->SetLineColor(kRed);
    h_Q->Draw("same");
    canvas->SaveAs("histG_Q.jpg");

    return 0;
}

