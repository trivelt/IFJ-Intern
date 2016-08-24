#include <iostream>
#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>
#include <TH2.h>
#include <TFile.h>
#include <TROOT.h>
#include <TTree.h>

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

    // ******************************************************************
    // p. 13

    float x4;
    float x5;
    TBranch *b_x4;
    TBranch *b_x5;
    TTree *ntuple;
    TH2F *h_x4_x5;
    TFile *file3 = new TFile("../mc_sample1.root", "READ");
    file3->GetObject("ntuple", ntuple);
    ntuple->SetBranchAddress("x4", &x4, &b_x4);
    ntuple->SetBranchAddress("x5", &x5, &b_x5);
    int nevents = ntuple->GetEntries();

    h_x4_x5 = new TH2F("h_x4_x5", "x4_x5", 100, -4.0, 4.0, 100, -5.0, 3.0);


    for(int i=0; i<nevents; i++)
    {
        ntuple->GetEntry(i);
        h_x4_x5->Fill(x4, x5);
    }

    canvas->Clear();
    h_x4_x5->SetStats(kFALSE);
    h_x4_x5->Draw("SURF5");
//    h_x4_x5->Draw("COLZ");
    canvas->SaveAs("x4x5.jpg");
    canvas->SaveAs("x4x5.eps");


    return 0;
}

