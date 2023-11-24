// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FRSMUSICCalData.h"
#include "FRSCrateRawData.h"
#include "FRSMainCrateRawData.h"
#include "TFRSParameter.h"
#include "TimeMachineData.h"
#include "c4Logger.h"

#include "TRandom3.h"
#include "TMath.h"
#include "TClonesArray.h"

#include "FRSCrateRaw2Cal.h"

/*
empty constructor required for FairRoot.
*/
FRSCrateRaw2Cal::FRSCrateRaw2Cal()
: FairTask(), 
fNEvents(0),
header(nullptr),
fOnline(kFALSE),
fraw_data(new TClonesArray("FRSCrateRawData")),
fraw_time_data(new TClonesArray("FRSMainCrateRawData")),
fcal_data(new TClonesArray("FRSMUSICCalData"))
{

    randomGenerator = new TRandom3();
}

/*
Named constructor with verbosity level.
*/
FRSCrateRaw2Cal::FRSCrateRaw2Cal(const TString& name, Int_t verbose) 
: FairTask(name, verbose),
fNEvents(0),
header(nullptr),
fOnline(kFALSE),
fraw_data(new TClonesArray("FRSCrateRawData")),
fraw_time_data(new TClonesArray("FRSMainCrateRawData")),
fcal_data(new TClonesArray("FRSMUSICCalData"))
{
    randomGenerator = new TRandom3();
}

FRSCrateRaw2Cal::~FRSCrateRaw2Cal(){
    c4LOG(info, "Deleting FRSCrateRaw2Cal task");
    if (fraw_data) delete fraw_data;
    if (fraw_time_data) delete fraw_time_data;
    if (fcal_data) delete fcal_data;
    if (randomGenerator) delete randomGenerator;
}



void FRSCrateRaw2Cal::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

/*
Initializer called by the FairRoot manager. Gets the required FairRootManager, objects to read and registers the data to be written to the tree.
*/
InitStatus FRSCrateRaw2Cal::Init(){
    //grab instance managers and handles.

    c4LOG(info, "Grabbing FairRootManager, RunOnline and EventHeader.");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");


    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fraw_data = (TClonesArray*)mgr->GetObject("FRSCrateRawData");
    c4LOG_IF(fatal, !fraw_data, "branch of FRSCrateRawData not found.");
    
    fraw_time_data = (TClonesArray*)mgr->GetObject("FRSMainCrateRawData");
    c4LOG_IF(fatal, !fraw_time_data, "branch of FRSMainCrateRawData not found.");
    

    FairRootManager::Instance()->Register("FRSMUSICCalData", "FRS main crate tdc calibrated data", fcal_data, !fOnline);

    fcal_data->Clear();
    fraw_data->Clear();

    c4LOG(info,"FRS main crate raw 2 cal setup.");

    return kSUCCESS;
};



void FRSCrateRaw2Cal::Exec(Option_t* option){
    if (fraw_data && fraw_data->GetEntriesFast() > 0 && fraw_time_data && fraw_time_data->GetEntriesFast() > 0){
        Int_t event_multiplicity = fraw_data->GetEntriesFast();
        ftime = (FRSMainCrateRawData*)fraw_time_data->At(0);
        FRSMUSICCalData music_event;
        music_event.Set_wr_t(ftime->Get_wr_t());
        music_event.Set_wr_subsystem_id(ftime->Get_wr_subsystem_id());
        
        for (Int_t ihit = 0; ihit < event_multiplicity; ihit++){
            fhit = (FRSCrateRawData*)fraw_data->At(ihit);

            double de1 = 1;
            int anodecnt1 = 0;
            double de2 = 1;
            int anodecnt2 = 0;
            
            for (int anodenr = 0; anodenr < 8; anodenr ++){ // v785 is in slot 12 in frs crate
                
                if (fhit->Get_frscrate_frs_v7x5_nhits(12, anodenr) == 0) continue;
                if (fhit->Get_frscrate_frs_v7x5_nhits(12, anodenr+8) == 0) continue;

                double e1 = fhit->Get_frscrate_frs_v7x5_data(0,12,anodenr)*params_music->e1_gain[anodenr] + params_music->e1_off[anodenr];
                double e2 = fhit->Get_frscrate_frs_v7x5_data(0,12,anodenr+8)*params_music->e2_gain[anodenr] + params_music->e2_off[anodenr];

                uint32_t t1 = ftime->Get_leading_v1290_main(16+anodenr,0);
                uint32_t t2 = ftime->Get_leading_v1290_main(24+anodenr,0);

                de1 *= e1;
                anodecnt1++;
                de2 *= e2;
                anodecnt2++;

                c4LOG(info,Form("anode = %i, e1 = %f, e2 = %f, t1 = %i, t2 = %i",anodenr,e1,e2,t1,t2));
                
                music_event.Set_music41_energy_cal(anodenr,e1);
                music_event.Set_music41_time(anodenr,t1);

                music_event.Set_music42_energy_cal(anodenr,e2);
                music_event.Set_music42_time(anodenr,t2);
            }

            music_event.Set_music41_energy_calr(TMath::Power(de1,1.0/(double)anodecnt1)); // algo from go4 code music ana new
            music_event.Set_music42_energy_calr(TMath::Power(de2,1.0/(double)anodecnt2));

            new ((*fcal_data)[fcal_data->GetEntriesFast()]) FRSMUSICCalData(music_event);
        }
    }    
}



/*
THIS FUNCTION IS EXTREMELY IMPORTANT!!!!

Clears the TClonesArray used in the function. If they are not cleared after each event they will eat all your RAM.

*/
void FRSCrateRaw2Cal::FinishEvent(){
    // reset output array
    fraw_data->Clear();
    fraw_time_data->Clear();
    fcal_data->Clear();
};


/*
Some stats are written when finishing.
*/
void FRSCrateRaw2Cal::FinishTask(){
    c4LOG(info, Form("Wrote %i events.",fNEvents));
}


ClassImp(FRSCrateRaw2Cal)
