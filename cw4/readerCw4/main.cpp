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
    bool selectedDataHistogram = false;
    if(argc==2)
    {
        string selectionString = argv[1];
        if(selectionString == "true")
            selectedDataHistogram = true;
    }

    TH1F *h_m_data;
    TH1F *h_m_background;
    TH1F *h_m_signal;

    TFile *fileData;
    TFile *fileBackground;
    TFile *fileSignal;

    if(selectedDataHistogram)
        fileData = new TFile("../selectedData/data.root", "READ");
    else
        fileData = new TFile("../generatedData/data.root", "READ");
    fileData->GetObject("h_m", h_m_data);

    if(selectedDataHistogram)
        fileBackground = new TFile("../selectedData/mc_background.root", "READ");
    else
        fileBackground = new TFile("../generatedData/mc_background.root", "READ");
    fileBackground->GetObject("h_m", h_m_background);

    if(selectedDataHistogram)
        fileSignal = new TFile("../selectedData/mc_signal.root", "READ");
    else
        fileSignal = new TFile("../generatedData/mc_signal.root", "READ");
    fileSignal->GetObject("h_m", h_m_signal);

    TCanvas *canvas = new TCanvas();
    canvas->Clear();

    if(!selectedDataHistogram)
        canvas->SetLogy();

    h_m_data->SetLineColor(kRed);
    h_m_data->Draw("P E1");

    if(selectedDataHistogram)
    {
        canvas->SaveAs("selectedDataHistograms.jpg");
        fileData->Close();
        fileBackground->Close();
        fileSignal->Close();
        return 0;
    }

    h_m_background->Scale(h_m_data->GetEntries()/h_m_background->GetEntries());
    h_m_background->Draw("same");

    h_m_signal->Scale(h_m_data->GetEntries()/h_m_signal->GetEntries()/10000.0);
    h_m_signal->Draw("same");

    canvas->SaveAs("histograms.jpg");

    fileData->Close();
    fileBackground->Close();
    fileSignal->Close();

    return 0;
}

