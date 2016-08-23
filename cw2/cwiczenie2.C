#define cwiczenie2_cxx
#include "cwiczenie2.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
using namespace std;

void cwiczenie2::Loop()
{
   if (fChain == 0) return;

   TH1F *h_m = new TH1F("h_m", "m value", 100, 2.5, 3.5);
   TH1F *h_x1 = new TH1F("h_x1", "x1 value", 100, -2.5, 4.5);
   TH1F *h_m_cond = new TH1F("h_m_cond", "m cond", 100, 2.5, 3.5);
   TH1F *h_x1_cond = new TH1F("h_x1_cond", "x1 cond", 100, -2.5, 4.5);

   Long64_t nentries = fChain->GetEntriesFast();
   cout << "Liczba przypadkow:\t" << nentries << endl;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;

      h_m->Fill(m);
      h_x1->Fill(x1);
      if(x1 >1)
      {
          h_m_cond->Fill(m);
          h_x1_cond->Fill(x1);
      }

      if(jentry < 10)
      {
          cout << "Przypadek nr " << jentry << "\tm=" << m << endl;
      }

      if(x1 > 3)
      {
          cout << "Przypadek nr " << jentry << "\tx1=" << x1 << "\tm=" << m << endl;
      }
      nb = fChain->GetEntry(jentry);   nbytes += nb;
   }

   TFile *file = new TFile("histogramy1.root", "RECREATE");
   h_m->Write();
   h_x1->Write();
   h_m_cond->Write();
   h_x1_cond->Write();
   file->Close();

}

int main()
{
    cwiczenie2 cw;
    cw.Loop();
    return 0;
}
