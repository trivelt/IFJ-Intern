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
    TH1F *h_m_data;
    TH1F *h_m_background;
    TH1F *h_m_signal;

    TFile *fileData = new TFile("../generatedData/data.root", "READ");
    fileData->GetObject("h_m", h_m_data);

    TFile *fileBackground = new TFile("../generatedData/mc_background.root", "READ");
    fileBackground->GetObject("h_m", h_m_background);

    TFile *fileSignal = new TFile("../generatedData/mc_signal.root", "READ");
    fileSignal->GetObject("h_m", h_m_signal);

    TCanvas *canvas = new TCanvas();
    canvas->Clear();
    canvas->SetLogy();

    h_m_data->SetLineColor(kRed);
    h_m_data->Draw("P E1");

    h_m_background->Scale(h_m_data->GetEntries()/h_m_background->GetEntries());
    h_m_background->Draw("same");

    h_m_signal->Scale(h_m_data->GetEntries()/h_m_signal->GetEntries()/10000.0);
    h_m_signal->Draw("same");

    canvas->SaveAs("histogramy.jpg");
    canvas->SaveAs("histogramy.eps");

    fileData->Close();
    fileBackground->Close();
    fileSignal->Close();

    return 0;
}

