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
    if(argc != 3)
    {
        cout << "Bledna liczba argumentow. Wywolaj program z dwoma parametrami, np.: ./prog x4 x5" << endl;
        return -1;
    }

    string firstVar = argv[1];
    string secondVar = argv[2];

    TTree *ntuple_background;
    TTree *ntuple_signal;

    TBranch *branch_background_first;
    TBranch *branch_background_second;
    TBranch *branch_signal_first;
    TBranch *branch_signal_second;

    Float_t first_var_background;
    Float_t second_var_background;
    Float_t first_var_signal;
    Float_t second_var_signal;

    TH2F* h_background = new TH2F("h_background", "h_background", 100, -10.0, 10.0, 100, -10.0, 10.0);
    TH2F* h_signal = new TH2F("h_signal", "h_signal", 100, -10.0, 10.0, 100, -10.0, 10.0);

    TFile *fileBackground = new TFile("../mc_background.root", "READ");
    fileBackground->GetObject("ntuple", ntuple_background);
    ntuple_background->SetBranchAddress(firstVar.c_str(), &first_var_background, &branch_background_first);
    ntuple_background->SetBranchAddress(secondVar.c_str(), &second_var_background, &branch_background_second);

    for(int i=0; i<ntuple_background->GetEntries(); i++)
    {
        ntuple_background->GetEntry(i);
        h_background->Fill(first_var_background, second_var_background);
    }

    TFile *fileSignal = new TFile("../mc_signal.root", "READ");
    fileSignal->GetObject("ntuple", ntuple_signal);
    ntuple_signal->SetBranchAddress(firstVar.c_str(), &first_var_signal, &branch_signal_first);
    ntuple_signal->SetBranchAddress(secondVar.c_str(), &second_var_signal, &branch_signal_second);

    for(int i=0; i<ntuple_signal->GetEntries(); i++)
    {
        ntuple_signal->GetEntry(i);
        h_signal->Fill(first_var_signal, second_var_signal);
    }

    TCanvas *canvas = new TCanvas();
    canvas->Clear();

    h_background->Scale(1/h_background->GetEntries());
    h_background->SetLineColor(kRed);
//    h_background->SetMaximum(550);
//    h_background->SetTitle(var.c_str());
    h_background->Draw("colz");

    h_signal->SetLineColor(kGreen);
    h_signal->Scale(1/h_signal->GetEntries());
    h_signal->Draw("colz same");

    canvas->SaveAs("histograms.jpg");

    fileBackground->Close();
    fileSignal->Close();

    return 0;
}

