#include <iostream>
#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>
#include <TH2.h>
#include <TFile.h>
#include <TROOT.h>
#include <TTree.h>

using namespace std;

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        cout << "Bledna liczba argumentow. Wywolaj program z dwoma parametrami, np.: ./prog x1" << endl;
        return -1;
    }

    string var = argv[1];

    TTree *ntuple_background;
    TTree *ntuple_signal;

    TBranch *branch_background;
    TBranch *branch_signal;

    Float_t var_background;
    Float_t var_signal;

    TH1F *h_background = new TH1F("h_background", "h_background", 100, -2.0, 4.5);
    TH1F *h_signal = new TH1F("h_signal", "h_signal", 100, -2.0, 4.5);

    TFile *fileBackground = new TFile("../mc_background.root", "READ");
    fileBackground->GetObject("ntuple", ntuple_background);
    ntuple_background->SetBranchAddress(var.c_str(), &var_background, &branch_background);

    for(int i=0; i<ntuple_background->GetEntries(); i++)
    {
        ntuple_background->GetEntry(i);
        h_background->Fill(var_background);
    }

    TFile *fileSignal = new TFile("../mc_signal.root", "READ");
    fileSignal->GetObject("ntuple", ntuple_signal);
    ntuple_signal->SetBranchAddress(var.c_str(), &var_signal, &branch_signal);

    for(int i=0; i<ntuple_signal->GetEntries(); i++)
    {
        ntuple_signal->GetEntry(i);
        h_signal->Fill(var_signal);
    }

    TCanvas *canvas = new TCanvas();
    canvas->Clear();

//    h_m_background->Scale(h_m_data->GetEntries()/h_m_background->GetEntries());
//    h_background->Scale(h_signal->GetEntries()/h_background->GetEntries());
    h_background->Scale(1/h_background->GetEntries());
    h_background->SetLineColor(kRed);
//    h_background->SetMaximum(550);
    h_background->SetTitle(var.c_str());
    h_background->Draw();


//    h_m_signal->Scale(h_m_data->GetEntries()/h_m_signal->GetEntries()/10000.0);
    h_signal->SetLineColor(kGreen);
    h_signal->Scale(1/h_signal->GetEntries());
    h_signal->Draw("same");

    canvas->SaveAs("histograms.jpg");

    fileBackground->Close();
    fileSignal->Close();

    return 0;
}

