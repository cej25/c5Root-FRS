// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "GermaniumOnlineSpectra.h"
#include "EventHeader.h"
#include "GermaniumFebexData.h"
#include "GermaniumCalData.h"
#include "TGermaniumConfiguration.h"

#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraph.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include "TFile.h"

GermaniumOnlineSpectra::GermaniumOnlineSpectra() : GermaniumOnlineSpectra("GermaniumOnlineSpectra")
{
    germanium_configuration = TGermaniumConfiguration::GetInstance();
}

GermaniumOnlineSpectra::GermaniumOnlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitGe(NULL)
    , fNEvents(0)
    , header(nullptr)
{    
    germanium_configuration = TGermaniumConfiguration::GetInstance();
}

GermaniumOnlineSpectra::~GermaniumOnlineSpectra()
{
    c4LOG(info, "");
    if (fHitGe)
        delete fHitGe;
}

void GermaniumOnlineSpectra::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus GermaniumOnlineSpectra::Init()
{

    // number of crystals, number of dets 

    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline * run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitGe = (TClonesArray*)mgr->GetObject("GermaniumCalData");
    c4LOG_IF(fatal, !fHitGe, "Branch GermaniumCalData not found!");


    crystals_to_plot.clear();
    std::map<std::pair<int,int>,std::pair<int,int>> gmap = germanium_configuration->Mapping();

    for (auto it_mapping = gmap.begin(); it_mapping != gmap.end(); ++it_mapping){
        if (it_mapping->second.first >= 0) crystals_to_plot.emplace_back(std::pair<int,int>(it_mapping->second.first,it_mapping->second.second));
    }

    number_of_detectors_to_plot = crystals_to_plot.size();


    folder_germanium = new TFolder("DEGAS", "DEGAS");

    run->AddObject(folder_germanium);

    folder_germanium_energy = new TFolder("Calibrated Energy Spectra", "Calibrated Energy Spectra");
    folder_germanium_time = new TFolder("Time Spectra", "Time Spectra");
    folder_germanium_hitpattern = new TFolder("Hit pattern", "Hit pattern");
    folder_germanium_multiplicity = new TFolder("Multiplicity", "Multiplicity");

    folder_germanium->Add(folder_germanium_energy);
    folder_germanium->Add(folder_germanium_time);
    folder_germanium->Add(folder_germanium_hitpattern);
    folder_germanium->Add(folder_germanium_multiplicity);


    // energy spectra:
    c_germanium_energy  = new TCanvas("c_germanium_energy","Calibrated Germanium spectra",650,350);
    c_germanium_energy->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
    h1_germanium_energy = new TH1F*[number_of_detectors_to_plot];
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){
        c_germanium_energy->cd(ihist+1);
        h1_germanium_energy[ihist] = new TH1F(Form("h1_germanium_energy_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("DEGAS energy spectrum detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),10e3,0,10e3);
        h1_germanium_energy[ihist]->GetXaxis()->SetTitle("energy (keV)");
        h1_germanium_energy[ihist]->Draw();
        folder_germanium_energy->Add(h1_germanium_energy[ihist]);
    }
    c_germanium_energy->cd(0);
    folder_germanium_energy->Add(c_germanium_energy);


    c_germanium_energy_vs_detidx = new TCanvas("c_germanium_energy_vs_detidx","Calibrated Germanium spectra vs. detector index",650,350);
    h2_germanium_energy_vs_detidx = new TH2F("h2_germanium_energy_vs_detidx","Calibrated Germanium spectra vs. detector index",10e3,0,10e3,number_of_detectors_to_plot,0,number_of_detectors_to_plot);
    h2_germanium_energy_vs_detidx->GetXaxis()->SetTitle("energy (keV)");
    h2_germanium_energy_vs_detidx->GetYaxis()->SetTitle("detector index");
    h2_germanium_energy_vs_detidx->Draw("COLZ");
    c_germanium_energy_vs_detidx->cd(0);
    folder_germanium_energy->Add(c_germanium_energy_vs_detidx);
    folder_germanium_energy->Add(h2_germanium_energy_vs_detidx);

    

    // time spectra:
    c_germanium_time  = new TCanvas("c_germanium_time","Calibrated Germanium spectra",650,350);
    c_germanium_time->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
    h1_germanium_time = new TH1F*[number_of_detectors_to_plot];
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){
        c_germanium_time->cd(ihist+1);
        h1_germanium_time[ihist] = new TH1F(Form("h1_germanium_time_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("DEGAS time spectrum detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),10e3,0,1e16);
        h1_germanium_time[ihist]->GetXaxis()->SetTitle("time (ns)");
        h1_germanium_time[ihist]->Draw();
        folder_germanium_time->Add(h1_germanium_time[ihist]);
    }
    c_germanium_time->cd(0);
    folder_germanium_time->Add(c_germanium_time);


    c_germanium_multiplicity = new TCanvas("c_germanium_multiplicity","Multiplicity of Germanium events",650,350);
    h1_germanium_multiplicity = new TH1F("h1_germanium_multiplicity","Multiplicity of Germanium events",number_of_detectors_to_plot,0,number_of_detectors_to_plot);
    h1_germanium_multiplicity->GetXaxis()->SetTitle("event multiplicity");
    h1_germanium_multiplicity->GetYaxis()->SetTitle("counts");
    h1_germanium_multiplicity->Draw();
    folder_germanium_multiplicity->Add(c_germanium_multiplicity);
    folder_germanium_multiplicity->Add(h1_germanium_multiplicity);


    //time differences!
    int number_reference_detectors = dt_reference_detectors.size();
    h1_germanium_time_differences = new TH1F ** [number_reference_detectors];
    h2_germanium_time_differences_vs_energy = new TH2F ** [number_reference_detectors];
    for (int ihist = 0; ihist < number_reference_detectors; ihist++){
        folder_germanium_time_differences = new TFolder(Form("time_differences_rel_%d_%d",dt_reference_detectors.at(ihist).first,dt_reference_detectors.at(ihist).second), Form("time_differences_rel_%d_%d",dt_reference_detectors.at(ihist).first,dt_reference_detectors.at(ihist).second));
        folder_germanium->Add(folder_germanium_time_differences);

        c_germanium_time_differences  = new TCanvas(Form("c_germanium_time_differences_rel_det_%d_%d",dt_reference_detectors.at(ihist).first,dt_reference_detectors.at(ihist).second),"germanium relative time differences",650,350);
        c_germanium_time_differences->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
        h1_germanium_time_differences[ihist] = new TH1F*[number_of_detectors_to_plot];

        for (int detid_idx = 0; detid_idx < number_of_detectors_to_plot; detid_idx++){
            c_germanium_time_differences->cd(detid_idx+1);
            h1_germanium_time_differences[ihist][detid_idx] = new TH1F(Form("h1_germanium_rel_time_det_%d_%d_to_det_%d_%d",crystals_to_plot.at(detid_idx).first,crystals_to_plot.at(detid_idx).second,dt_reference_detectors.at(ihist).first,dt_reference_detectors.at(ihist).second),Form("Germanium delta time t(%d%c) - t(%d%c)",crystals_to_plot.at(detid_idx).first,(char)(crystals_to_plot.at(detid_idx).second+65),dt_reference_detectors.at(ihist).first,(char)(dt_reference_detectors.at(ihist).second+65)),1000,-2000,2000); 
            h1_germanium_time_differences[ihist][detid_idx]->GetXaxis()->SetTitle(Form("dt t(%d%c) - t(%d%c) (ns)",crystals_to_plot.at(detid_idx).first,(char)(crystals_to_plot.at(detid_idx).second+65),dt_reference_detectors.at(ihist).first,(char)(dt_reference_detectors.at(ihist).second+65)));
            h1_germanium_time_differences[ihist][detid_idx]->Draw();
            folder_germanium_time_differences->Add(h1_germanium_time_differences[ihist][detid_idx]);
            
        }
        c_germanium_time_differences->cd(0);
        folder_germanium_time_differences->Add(c_germanium_time_differences);



        c_germanium_time_differences_vs_energy  = new TCanvas(Form("c_germanium_time_differences_rel_det_%d_%d_vs_energy",dt_reference_detectors.at(ihist).first,dt_reference_detectors.at(ihist).second),"germanium relative time differences vs energy",650,350);
        c_germanium_time_differences_vs_energy->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
        h2_germanium_time_differences_vs_energy[ihist] = new TH2F*[number_of_detectors_to_plot];

        for (int detid_idx = 0; detid_idx < number_of_detectors_to_plot; detid_idx++){
            c_germanium_time_differences_vs_energy->cd(detid_idx+1);
            h2_germanium_time_differences_vs_energy[ihist][detid_idx] = new TH2F(Form("h1_germanium_rel_time_det_%d_%d_to_det_%d_%d_vs_energy",crystals_to_plot.at(detid_idx).first,crystals_to_plot.at(detid_idx).second,dt_reference_detectors.at(ihist).first,dt_reference_detectors.at(ihist).second),Form("germanium delta time t(%d%c) - t(%d%c) vs energy",crystals_to_plot.at(detid_idx).first,(char)(crystals_to_plot.at(detid_idx).second+65),dt_reference_detectors.at(ihist).first,(char)(dt_reference_detectors.at(ihist).second+65)),fenergy_nbins,fenergy_bin_low,fenergy_bin_high,1000,-2000,2000); 
            h2_germanium_time_differences_vs_energy[ihist][detid_idx]->GetYaxis()->SetTitle(Form("dt t(%d%c) - t(%d%c) (ns)",crystals_to_plot.at(detid_idx).first,(char)(crystals_to_plot.at(detid_idx).second+65),dt_reference_detectors.at(ihist).first,(char)(dt_reference_detectors.at(ihist).second+65)));
            h2_germanium_time_differences_vs_energy[ihist][detid_idx]->GetXaxis()->SetTitle(Form("energy det %d%c (keV)",crystals_to_plot.at(detid_idx).first,(char)(crystals_to_plot.at(detid_idx).second+65)));
            h2_germanium_time_differences_vs_energy[ihist][detid_idx]->Draw("COLZ");
            folder_germanium_time_differences->Add(h2_germanium_time_differences_vs_energy[ihist][detid_idx]);
            
        }
        c_germanium_time_differences_vs_energy->cd(0);
        folder_germanium_time_differences->Add(c_germanium_time_differences_vs_energy);
    }
        
    
    c_germanium_hitpattern = new TCanvas("c_germanium_hitpattern","Hit pattern DEGAS",650,350);
    detector_labels = new char*[number_of_detectors_to_plot];
    h1_germanium_hitpattern = new TH1F("h1_germanium_hitpattern","Hit pattern of DEGAS",number_of_detectors_to_plot,0,number_of_detectors_to_plot);
    h1_germanium_hitpattern->GetXaxis()->SetAlphanumeric();
    
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){
        detector_labels[ihist] = Form("%d%c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65));
        h1_germanium_hitpattern->GetXaxis()->SetBinLabel(ihist+1,detector_labels[ihist]);
    }    
    h1_germanium_hitpattern->GetXaxis()->LabelsOption("a");
    h1_germanium_hitpattern->GetXaxis()->SetTitle("crystal");
    h1_germanium_hitpattern->GetYaxis()->SetTitle("counts");
    h1_germanium_hitpattern->SetStats(0);
    h1_germanium_hitpattern->Draw();
    c_germanium_hitpattern->cd(0);
    folder_germanium_hitpattern->Add(h1_germanium_hitpattern);
    folder_germanium_hitpattern->Add(c_germanium_hitpattern);

    run->GetHttpServer()->RegisterCommand("Reset_Ge_Histo", Form("/Objects/%s/->Reset_Ge_Histo()", GetName()));
    run->GetHttpServer()->RegisterCommand("Snapshot_Ge_Histo", Form("/Objects/%s/->Snapshot_Ge_Histo()", GetName()));

    return kSUCCESS;
}

void GermaniumOnlineSpectra::Reset_Ge_Histo()
{
    c4LOG(info, "Reset command received. Clearing histograms.");
    h1_germanium_multiplicity->Reset();
    h1_germanium_hitpattern->Reset();
    h2_germanium_energy_vs_detidx->Reset();
    for (int ihist = 0; ihist<number_of_detectors_to_plot; ihist++) 
    {
        h1_germanium_energy[ihist]->Reset();
        h1_germanium_time[ihist]->Reset();
        for (int ihist2 = 0; ihist2 < dt_reference_detectors.size(); ihist2++){
            h1_germanium_time_differences[ihist2][ihist]->Reset();
            h2_germanium_time_differences_vs_energy[ihist2][ihist]->Reset();
        }

    }
}

void GermaniumOnlineSpectra::Snapshot_Ge_Histo()
{
    c4LOG(fatal, "NOT FULLY IMPLEMENTED: TODO!!!");
    //date and time
    time_t now = time(0);
    tm *ltm = localtime(&now);
    //make folder with date and time
    const char* snapshot_dir = Form("Germanium_snapshot_%d_%d_%d_%d_%d_%d",ltm->tm_year+1900,ltm->tm_mon,ltm->tm_mday,ltm->tm_hour,ltm->tm_min,ltm->tm_sec);
    gSystem->mkdir(snapshot_dir);
    gSystem->cd(snapshot_dir);

    // save histograms to canvases
    c_germanium_snapshot = new TCanvas("c","c",650,350);

    for (int ihist = 0; ihist<number_of_detectors_to_plot; ihist++)
    {
        if(h1_germanium_energy[ihist]->GetEntries()!=0)
        {
            h1_germanium_energy[ihist]->Draw();
            c_germanium_snapshot->SaveAs(Form("h1_germanium_energy_%d_%d.png",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second));
            c_germanium_snapshot->Clear();
        }

    }
    delete c_germanium_snapshot;

    // snapshot .root file with data and time
    file_germanium_snapshot = new TFile(Form("Germanium_snapshot_%d_%d_%d_%d_%d_%d.root",ltm->tm_year+1900,ltm->tm_mon,ltm->tm_mday,ltm->tm_hour,ltm->tm_min,ltm->tm_sec),"RECREATE");
    file_germanium_snapshot->cd();
    folder_germanium->Write();
    file_germanium_snapshot->Close();
    delete file_germanium_snapshot;

    gSystem->cd("..");
    c4LOG(info, "Snapshot saved to:" << snapshot_dir);
}

void GermaniumOnlineSpectra::Exec(Option_t* option)
{   
    if (fHitGe && fHitGe->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitGe->GetEntriesFast();
        int event_multiplicity = 0;
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            GermaniumCalData* hit = (GermaniumCalData*)fHitGe->At(ihit);
            if (!hit) continue;
            int detector_id1 = hit->Get_detector_id();
            int crystal_id1 = hit->Get_crystal_id();
            double energy1 = hit->Get_channel_energy();
            double time1 = hit->Get_channel_trigger_time();


            
            if (!(detector_id1 == germanium_configuration->TM_Delayed() || detector_id1 == germanium_configuration->TM_Undelayed() || detector_id1 == germanium_configuration->SC41L() || detector_id1 == germanium_configuration->SC41R())) event_multiplicity ++;
            
            int crystal_index1 = std::distance(crystals_to_plot.begin(), std::find(crystals_to_plot.begin(),crystals_to_plot.end(),std::pair<int,int>(detector_id1,crystal_id1)));
            
            h1_germanium_energy[crystal_index1]->Fill(energy1);
            h2_germanium_energy_vs_detidx->Fill(hit->Get_channel_energy(),crystal_index1);
            h1_germanium_time[crystal_index1]->Fill(time1);
            h1_germanium_hitpattern->Fill(detector_labels[crystal_index1],1);

            if (nHits >= 2 && dt_reference_detectors.size()>0){
                for (int ihit2 = 0; ihit2 < nHits; ihit2++){
                    if (ihit == ihit2) continue;
                    GermaniumCalData * hit2 = (GermaniumCalData*)fHitGe->At(ihit2);
                    int detector_id2 = hit2->Get_detector_id();
                    int crystal_id2 = hit2->Get_crystal_id();
                    
                    int crystal_index2 = std::distance(dt_reference_detectors.begin(), std::find(dt_reference_detectors.begin(),dt_reference_detectors.end(),std::pair<int,int>(detector_id2,crystal_id2)));
                    if (crystal_index2 >= dt_reference_detectors.size()) continue;

                    double energy2 = hit2->Get_channel_energy();
                    double time2 = hit2->Get_channel_trigger_time();

                    h1_germanium_time_differences[crystal_index2][crystal_index1]->Fill(time1 - time2);
                    h2_germanium_time_differences_vs_energy[crystal_index2][crystal_index1]->Fill(energy1,time1-time2);
                }
            }
        }

        h1_germanium_multiplicity->Fill(event_multiplicity);
    }

    fNEvents += 1;
}

void GermaniumOnlineSpectra::FinishEvent()
{
    if (fHitGe)
    {
        fHitGe->Clear();
    }
}

void GermaniumOnlineSpectra::FinishTask()
{
    if (fNEvents == 0)
    {
        c4LOG(warning, "No events processed, no histograms written.");
        return;
    }
    if (fHitGe)
    {
        folder_germanium->Write();
        c4LOG(info, "DEGAS histograms written to file.");
    }
}

ClassImp(GermaniumOnlineSpectra)