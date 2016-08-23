#include <iostream>

//biblioteki ROOTa
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h> //histogramy jednowymiarowe
#include <TCanvas.h>
#include <TLegend.h>

using namespace std;

void analiza(){
//deklaracje zmiennych
  int liczba_paczek_S;
  int liczba_paczek_M;
  int liczba_paczek_L;
  int liczba_paczek_XL;
  int liczba_paczek_XXL;
  int numer_transportu;
  int czas_transportu;

//deklaracje gałęzi
  TBranch *b_l_paczek_S;
  TBranch *b_l_paczek_M;
  TBranch *b_l_paczek_L;
  TBranch *b_l_paczek_XL;
  TBranch *b_l_paczek_XXL;
  TBranch *b_nr_transportu;
  TBranch *b_cz_transportu;

//wczytywanie pliku z danymi
  TFile *f = new TFile("ROOT_cw1.root", "READ");
//tworzenie oraz wczytywanie drzewa z danymi
  TTree * ntuple;
  f->GetObject("ntuple",ntuple);

//przypisanie zmiennej nr_tran odpowiedniego adresu
  ntuple->SetBranchAddress("l_paczek_S", &liczba_paczek_S, &b_l_paczek_S);
  ntuple->SetBranchAddress("l_paczek_M", &liczba_paczek_M, &b_l_paczek_M);
  ntuple->SetBranchAddress("l_paczek_L", &liczba_paczek_L, &b_l_paczek_L);
  ntuple->SetBranchAddress("l_paczek_XL", &liczba_paczek_XL, &b_l_paczek_XL);
  ntuple->SetBranchAddress("l_paczek_XXL", &liczba_paczek_XXL, &b_l_paczek_XXL);
  ntuple->SetBranchAddress("nr_transportu", &numer_transportu, &b_nr_transportu);
  ntuple->SetBranchAddress("czas_transportu", &czas_transportu, &b_cz_transportu);

//ustalenie maksymalnej liczby przypadków (w naszym przykładzie: transportów koszulek)
  int nevents = ntuple->GetEntries();

//deklaracja histogramu jednowymiarowego
  TH1F * h_liczba_paczek_S = new TH1F("h_liczba_paczek_S", "Ilosc paczek z koszulkami o rozmarze \"S\" w transporcie", 20, 0., 20.);
  TH1F * h_liczba_paczek_XL = new TH1F("h_liczba_paczek_XL", "Liczba paczek z koszulkami o rozmiarze XL w transporcie", 20, 0., 20.);
  TH1F * h_rozmiar = new TH1F("h_rozmiar", "rozmiar", 5, 0.5, 5.5);
  TH1F * h_rozmiar_koszulka = new TH1F("h_rozmiar_koszulka", "rozmiar_koszulka", 5, 0.5, 5.5);

  for (int a=0; a<nevents; a++)
  {
    ntuple->GetEntry(a); //wczytanie danych o przypadku (transporcie) nr a

//    cout << "Przypadek nr:\t" << a << "\tilość paczek:\t" << liczba_paczek_S << endl; //po wczytaniu danych zmiennej liczba_paczek_S została przypisana odpowiednia wartość


    h_liczba_paczek_S->Fill(liczba_paczek_S); //wypełnienie histogramu
    h_liczba_paczek_XL->Fill(liczba_paczek_XL);

    for(int b=0;b<liczba_paczek_S; b++)
    {
        h_rozmiar->Fill(1);
        h_rozmiar_koszulka->Fill(1, 15.0);
    }
    for(int b=0; b<liczba_paczek_M; b++)
    {
        h_rozmiar->Fill(2);
        h_rozmiar_koszulka->Fill(2, 20.0);
    }
    for(int b=0; b<liczba_paczek_L; b++)
    {
        h_rozmiar->Fill(3);
        h_rozmiar_koszulka->Fill(3, 25.0);
    }
    for(int b=0; b<liczba_paczek_XL; b++)
    {
        h_rozmiar->Fill(4);
        h_rozmiar_koszulka->Fill(4, 25.0);
    }
    for(int b=0; b<liczba_paczek_XXL; b++)
    {
        h_rozmiar->Fill(5);
        h_rozmiar_koszulka->Fill(5, 15.0);
    }

  }

  TCanvas * c1 = new TCanvas();
  c1->Clear(); //czyszczenie kanwy

  h_liczba_paczek_S->SetLineColor(kRed);
  h_liczba_paczek_S->SetStats(kFALSE);
  h_liczba_paczek_S->SetTitle("Liczba paczek z koszulkami o danym rozmiarze w transporcie");
  h_liczba_paczek_S->GetXaxis()->SetTitle("Liczba paczek");
  h_liczba_paczek_S->GetYaxis()->SetTitle("Liczba transportow");
  h_liczba_paczek_S->SetMaximum(150);
  h_liczba_paczek_S->Draw();

  h_liczba_paczek_XL->SetLineColor(kBlue);
  h_liczba_paczek_XL->SetStats(kFALSE);
  h_liczba_paczek_XL->SetLineStyle(2);
  h_liczba_paczek_XL->Draw("same");

  TLegend* legend = new TLegend(0.65, 0.7, 0.9, 0.9);
  legend->SetHeader("Liczba paczek");
  legend->AddEntry(h_liczba_paczek_S, "rozmiar S");
  legend->AddEntry(h_liczba_paczek_XL, "rozmiar XL");
  legend->Draw();

  c1->SaveAs("wyk_liczba_paczek_S.eps"); //format eps
  c1->SaveAs("wyk_liczba_paczek_S.jpg"); //format jpg

  c1->Clear();
  h_rozmiar->SetTitle("Rozklad rozmiaru paczek");
  h_rozmiar->SetMaximum(1.5e5);
  h_rozmiar->SetStats(kFALSE);
  h_rozmiar->Draw();
  h_rozmiar_koszulka->SetLineColor(kRed);
  h_rozmiar_koszulka->SetLineStyle(3);
  h_rozmiar_koszulka->Draw("same hist");
  c1->SaveAs("wyk_rozmiar_koszulek.jpg");
  c1->SaveAs("wyk_rozmiar_koszulek.eps");


  c1->Clear();
  c1->SetLogy();
  h_rozmiar->Draw();
  h_rozmiar_koszulka->Draw("same hist");
  c1->SaveAs("wyk_rozmiar_koszulek_log.jpg");
  c1->SaveAs("wyk_rozmiar_koszulek_log.eps");

}

int main(){
  analiza();
  return 0;
}
