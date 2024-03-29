#ifndef GermaniumOnlineSpectra_H
#define GermaniumOnlineSpectra_H

#include "FairTask.h"

#include "TGermaniumConfiguration.h"

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;
class TFile;
class TFolder;

class GermaniumOnlineSpectra : public FairTask
{
    public:
        GermaniumOnlineSpectra();
        GermaniumOnlineSpectra(const TString& name, Int_t verbose = 1);


        void CreateHistograms();

        virtual ~GermaniumOnlineSpectra();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        virtual void Reset_Ge_Histo();

        virtual void Snapshot_Ge_Histo();


        void SetBinningEnergy(int nbins, float binlow, float binhigh){
            fenergy_nbins = nbins;
            fenergy_bin_low = binlow;
            fenergy_bin_high = binhigh; 
        };

        void AddReferenceDetector(int detector_id, int crystal_id){
            dt_reference_detectors.emplace_back(std::pair<int,int>(detector_id,crystal_id));
        }

        // range setters

    
    private:
        TClonesArray* fHitGe;

        const TGermaniumConfiguration * germanium_configuration;

        // ranges
        int number_of_detectors_to_plot;
        std::vector<std::pair<int,int>> crystals_to_plot;

        std::vector<std::pair<int,int>> dt_reference_detectors;

        int fenergy_nbins = 1500;
        int fenergy_bin_low = 0;
        int fenergy_bin_high = 1500;

        EventHeader* header;
        Int_t fNEvents;

        // Canvas
        TCanvas* c_germanium_time;
        TCanvas* c_germanium_energy;
        TCanvas* c_germanium_energy_vs_detidx;
        TCanvas* c_germanium_hitpattern;
        TCanvas* c_germanium_multiplicity;
        TCanvas* c_germanium_time_differences;
        TCanvas* c_germanium_time_differences_vs_energy;
        TCanvas* c_germanium_rates;
        
        

        TCanvas* c_germanium_snapshot;

        char ** detector_labels;

        // Folder and files
        TDirectory* dir_germanium;
        TFolder* folder_germanium;
        TFolder* folder_germanium_energy;
        TFolder* folder_germanium_time;
        TFolder* folder_germanium_hitpattern;
        TFolder* folder_germanium_multiplicity;
        TFolder* folder_germanium_time_differences;

        TFile* file_germanium_snapshot;

        // Histograms energy
        TH1F ** h1_germanium_energy;
        TH2F * h2_germanium_energy_vs_detidx;
        
        TH1F *** h1_germanium_time_differences; // [reference_dector][detector index]
        TH2F *** h2_germanium_time_differences_vs_energy; // [reference detector][detector index]

        TH1F * h1_germanium_multiplicity;
        TH1F * h1_germanium_hitpattern;

        // Histograms time
        TH1F ** h1_germanium_time;

    public:
        ClassDef(GermaniumOnlineSpectra, 1)
};

#endif