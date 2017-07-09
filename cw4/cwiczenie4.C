#define cwiczenie4_cxx
#include "cwiczenie4.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <TMath.h>
#include <string>

using namespace std;

void cwiczenie4::Loop(const char *filename, bool selection)
{
   if (fChain == 0) return;

   TH1F *h_m;
   if(selection)
        h_m = new TH1F("h_m", "m value", 100, 0.0, 6.0);
   else
       h_m = new TH1F("h_m", "m value", 100, 0.0, 15.0);

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {

      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if(selection)
      {
          if(x1>0 && x2>0 && TMath::Abs(x3)<2 && TMath::Abs(x4+x5)<2 && (x7-x6)<0)
              h_m->Fill(m);
      }
      else
      {
          h_m->Fill(m);
      }

   }

   TFile *file = new TFile(filename, "RECREATE");
   h_m->Write();
   file->Close();

}

int main(int argc, char** argv)
{
    bool selection = false;
    if(argc < 3)
    {
        cout << "Zla liczba argumentow. Uruchom program z dwoma parametrami: ./prog input.root output.root" << endl;
        return -1;
    }
    if(argc == 4)
    {
        string selectionString = argv[3];
        if(selectionString == "true")
        {
            selection = true;
        }
    }

    char* inputFile = argv[1];
    char* outputFile = argv[2];

    cout << "Input set: " << inputFile << endl;
    cout << "Output set: " << outputFile << endl;

    TChain* chain = new TChain("ntuple");
    chain->Add(inputFile);

    cwiczenie4 cw(chain);
    cw.Loop(outputFile, selection);

    return 0;
}
