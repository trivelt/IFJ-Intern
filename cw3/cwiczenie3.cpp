#include <iostream>
#include <TMath.h>
#include <TRandom.h>
#include <TH1F.h>
#include <TF1.h>
#include <TFormula.h>
#include <TCanvas.h>
//#define DEBUG

using namespace std;
double E = 6.5;

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

double computeMass(double x1, double x2)
{
    return 2*E*TMath::Power(x1*x2, 1/2.0);
}

double computeVelocity(double x1, double x2)
{
    return (x1-x2)/(x1+x2);
}

int main()
{
    TH1F *h_G = new TH1F("h_G", "h_G", 1000, 0, 1);
    TH1F *h_Q = new TH1F("h_Q", "h_Q", 1000, 0, 0);

//    cout << "x=4, G_x=" << G_x(0.0024) << ", inwersja_G=" << inwersja_G(0.0024) << endl;

    int n = 1e6;
    double* G_dist = G_distribution(n);
    double* Q_dist = Q_distribution(n);
    for(int i=0; i<n; i++)
    {
        h_G->Fill(G_dist[i]);
        h_Q->Fill(Q_dist[i]);
    }

    TFormula* formula = new TFormula("gFormula", "5*x-4*pow(x, 5/4.0)");
    cout << "Eval=" << formula->Eval(0.52) << endl;

    TF1* gFit = new TF1("gFit", "[0]*x*pow((1-x), [1])", 0, 1);
    gFit->SetParameter(0, 30.0);
    gFit->SetParameter(1, 4);
    h_G->Fit(gFit);

    TF1* qFit = new TF1("qFit", "[0]*([2]-pow(x, [1]))", -5, 10);
    qFit->SetParameter(0, 5.0);
    qFit->SetParameter(1, 1/4.0);
    qFit->SetParameter(2, 1);
    h_Q->Fit(qFit);


    TCanvas* canvas = new TCanvas();
    canvas->Clear();
    h_G->SetStats(kFALSE);
    h_G->SetTitle("G and Q");
    h_G->Draw();
    h_Q->SetLineColor(kRed);
    h_Q->Draw("same");

    gFit->Draw("same");
    qFit->SetLineColor(kBlue);
    qFit->Draw("same");

    canvas->SaveAs("histG_Q.jpg");




    TH1F* h_mass1 = new TH1F("h_mass1", "h_mass", 1000, 0, 1);
    TH1F* h_mass2 = new TH1F("h_mass2", "h_mass", 1000, 0, 1);
    TH1F* h_mass3 = new TH1F("h_mass3", "h_mass", 1000, 0, 1);

    TH1F* h_v1 = new TH1F("v_v1", "h_mass", 1000, 0, 1);
    TH1F* h_v2 = new TH1F("h_v2", "h_mass", 1000, 0, 1);
    TH1F* h_v3 = new TH1F("h_v3", "h_mass", 1000, 0, 1);

    for(int i=0;i<n;i++)
    {
        double x1 = G_dist[i];
        double x2 = Q_dist[i];
        double masaNiezmiennicza = computeMass(x1, x2);
        h_mass1->Fill(masaNiezmiennicza);
        masaNiezmiennicza = computeMass(x1, x1);
        h_mass2->Fill(masaNiezmiennicza);
        masaNiezmiennicza = computeMass(x2, x2);
        h_mass3->Fill(masaNiezmiennicza);

        double predkosc = computeVelocity(x1, x2);
        h_v1->Fill(predkosc);
        predkosc = computeVelocity(x1, x1);
        h_v2->Fill(predkosc);
        predkosc = computeVelocity(x2, x2);
        h_v3->Fill(predkosc);
    }

    canvas->Clear();
    h_mass1->Draw();
    h_mass2->SetLineColor(kRed);
    h_mass2->Draw("same");
    h_mass3->SetLineColor(kGreen);
    h_mass3->Draw("same");
    canvas->SaveAs("masaNiezmiennicza.jpg");


    canvas->Clear();
    h_v1->Draw();
    h_v2->SetLineColor(kRed);
    h_v2->Draw("same");
    h_v3->SetLineColor(kGreen);
    h_v3->Draw("same");
    canvas->SaveAs("predkosc.jpg");



    return 0;
}

