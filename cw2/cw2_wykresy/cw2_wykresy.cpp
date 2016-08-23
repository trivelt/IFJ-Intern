#include <iostream>
#include <TCanvas.h>
#include <TH1.h>
#include <TFile.h>
#include <TROOT.h>

using namespace std;

int main()
{
    TH1F *h_m;
    TH1F *h_x1;
    TH1F *h_m_cond;
    TH1F *h_x1_cond;

    TFile *file = new TFile("../histogramy1.root", "READ");
    file->GetObject("h_m", h_m);
    file->GetObject("h_x1", h_x1);
    file->GetObject("h_m_cond", h_m_cond);
    file->GetObject("h_x1_cond", h_x1_cond);

    TCanvas *canvas = new TCanvas();
    canvas->Clear();
    h_m->Draw();

    canvas->SaveAs("histogramy.eps");
    canvas->SaveAs("histogramy.jpg");

    file->Close();
    return 0;
}

