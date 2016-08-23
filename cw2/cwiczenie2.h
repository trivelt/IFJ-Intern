//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Aug 23 12:20:16 2016 by ROOT version 6.06/06
// from TTree ntuple/ntuple
// found on file: mc_sample1.root
//////////////////////////////////////////////////////////

#ifndef cwiczenie2_h
#define cwiczenie2_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class cwiczenie2 {
public :
   TChain          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         m;
   Float_t         x1;
   Float_t         x2;
   Float_t         x3;
   Float_t         x4;
   Float_t         x5;
   Float_t         x6;
   Float_t         x7;

   // List of branches
   TBranch        *b_m;   //!
   TBranch        *b_x1;   //!
   TBranch        *b_x2;   //!
   TBranch        *b_x3;   //!
   TBranch        *b_x4;   //!
   TBranch        *b_x5;   //!
   TBranch        *b_x6;   //!
   TBranch        *b_x7;   //!

   cwiczenie2(TChain *tree=0);
   virtual ~cwiczenie2();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TChain *tree);
   virtual void     Loop(const char* filename);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef cwiczenie2_cxx
cwiczenie2::cwiczenie2(TChain *tree) : fChain(0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("mc_sample1.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("mc_sample1.root");
      }
      f->GetObject("ntuple",tree);

   }
   Init(tree);
}

cwiczenie2::~cwiczenie2()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t cwiczenie2::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t cwiczenie2::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void cwiczenie2::Init(TChain *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("m", &m, &b_m);
   fChain->SetBranchAddress("x1", &x1, &b_x1);
   fChain->SetBranchAddress("x2", &x2, &b_x2);
   fChain->SetBranchAddress("x3", &x3, &b_x3);
   fChain->SetBranchAddress("x4", &x4, &b_x4);
   fChain->SetBranchAddress("x5", &x5, &b_x5);
   fChain->SetBranchAddress("x6", &x6, &b_x6);
   fChain->SetBranchAddress("x7", &x7, &b_x7);
   Notify();
}

Bool_t cwiczenie2::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void cwiczenie2::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t cwiczenie2::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef cwiczenie2_cxx
