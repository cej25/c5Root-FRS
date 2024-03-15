#ifndef FatimaVmeOnlineSpectra_H
#define FatimaVmeOnlineSpectra_H

#include "FairTask.h"
#include "TFolder.h"
#include "TCanvas.h"
#include <vector>
#include "TH1.h"

class EventHeader;

class TH1I;
class TH1D;
class TH2D;

class FatimaVmeOnlineSpectra : public FairTask
{
    public:
        FatimaVmeOnlineSpectra();
        FatimaVmeOnlineSpectra(TString& name, Int_t verbose = 1);

        virtual ~FatimaVmeOnlineSpectra();

        void Reset_Hist();
        void Snapshot_Histo();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();
        virtual void FinishTask();
        virtual void Reset_Histo();

    private:
        TClonesArray* fHitFatimaVme;

        EventHeader* header;
        Int_t fNEvents;

        // Folders
        TFolder* folder_fatima_vme;
        TFolder* folder_stats_vme;
        TFolder* folder_raw_vme;
        TFolder* folder_cal_vme;
        TFolder* folder_raw_energy;
        TFolder* folder_raw_time;
        TFolder* folder_cal_energy;
        TFolder* folder_cal_time;

        // Canvases
        TCanvas* c_FatVME_E;
        TCanvas* c_FatVME_RawE;
        TCanvas* c_FatVME_RawT;

        // Histograms
        // these should be vectors based on detector config.
        TH1D* h1_FatVME_RawE[36];
        TH1D* h1_FatVME_RawT[36];
        TH1D* h1_FatVME_E[36];
        TH1D* h1_TDC_dt_refCh1[36];
        TH1D* h1_TDC_dT_refSC41L[36];
        TH1D* h1_FatVME_E_Sum;
        TH1D* h1_FatVME_E_Sum_Large; // large range
        TH1I* h1_FatVME_QDC_HitPattern;
        TH1I* h1_FatVME_TDC_HitPattern;
        TH1I* h1_FatVME_QDCMult;
        TH1I* h1_FatVME_TDCMult;
        TH2D* h1_FatVME_EvsT;
        TH1D* h1_FatVME_Time;


    public:
        ClassDef(FatimaVmeOnlineSpectra, 1);
};



#endif
