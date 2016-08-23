#include <iostream>
#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>
#include <TFile.h>
#include <TROOT.h>

using namespace std;

int main()
{
    TH1F *h_m;
    TH1F *h_x1;
    TH1F *h_m_cond;
    TH1F *h_x1_cond;

    TH1F *h_m_2;

    TFile *file = new TFile("../histogramy1.root", "READ");
    file->GetObject("h_m", h_m);
    file->GetObject("h_x1", h_x1);
    file->GetObject("h_m_cond", h_m_cond);
    file->GetObject("h_x1_cond", h_x1_cond);

    TFile *file2 = new TFile("../histogramy2.root", "READ");
    file2->GetObject("h_m", h_m_2);

    TCanvas *canvas = new TCanvas();
    canvas->Clear();

    h_m->Fit("gaus", "0");
    h_m->Draw();

    TF1 *fit1 = (TF1*)h_m->GetFunction("gaus");
    fit1->Draw("same");

    h_m_2->SetLineColor(kGreen);
    h_m_2->Draw("same");

    canvas->SaveAs("histogramy.eps");
    canvas->SaveAs("histogramy.jpg");

    file->Close();
    file2->Close();
    return 0;
}

