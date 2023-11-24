// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FRSSCICalData.h"
#include "FRSMainCrateRawData.h"
#include "TFRSParameter.h"
#include "TimeMachineData.h"
#include "c4Logger.h"

#include "TRandom3.h"
#include "TClonesArray.h"

#include "FrsMainCrateRaw2Cal.h"

/*
empty constructor required for FairRoot.
*/
FrsMainCrateRaw2Cal::FrsMainCrateRaw2Cal()
: FairTask(), 
fNEvents(0),
header(nullptr),
fOnline(kFALSE),
fraw_data(new TClonesArray("FRSMainCrateRawData")),
fcal_data(new TClonesArray("FRSSCICalData"))
{

    randomGenerator = new TRandom3();
}

/*
Named constructor with verbosity level.
*/
FrsMainCrateRaw2Cal::FrsMainCrateRaw2Cal(const TString& name, Int_t verbose) 
: FairTask(name, verbose),
fNEvents(0),
header(nullptr),
fOnline(kFALSE),
fraw_data(new TClonesArray("FRSMainCrateRawData")),
fcal_data(new TClonesArray("FRSSCICalData"))
{
    randomGenerator = new TRandom3();
}

FrsMainCrateRaw2Cal::~FrsMainCrateRaw2Cal(){
    c4LOG(info, "Deleting FrsMainCrateRaw2Cal task");
    if (fraw_data) delete fraw_data;
    if (fcal_data) delete fcal_data;
    if (randomGenerator) delete randomGenerator;
}



void FrsMainCrateRaw2Cal::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

/*
Initializer called by the FairRoot manager. Gets the required FairRootManager, objects to read and registers the data to be written to the tree.
*/
InitStatus FrsMainCrateRaw2Cal::Init(){
    //grab instance managers and handles.

    c4LOG(info, "Grabbing FairRootManager, RunOnline and EventHeader.");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");


    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fraw_data = (TClonesArray*)mgr->GetObject("FRSMainCrateRawData");
    c4LOG_IF(fatal, !fraw_data, "branch of FRSMainCrateRawData not found.");
    

    FairRootManager::Instance()->Register("FRSSCICalData", "FRS main crate tdc calibrated data", fcal_data, !fOnline);

    fcal_data->Clear();
    fraw_data->Clear();

    c4LOG(info,"FRS main crate raw 2 cal setup.");

    return kSUCCESS;
};



void FrsMainCrateRaw2Cal::Exec(Option_t* option){
    if (fraw_data && fraw_data->GetEntriesFast() > 0){ // only get events with two hits or more
        Int_t event_multiplicity = fraw_data->GetEntriesFast();
        for (Int_t ihit = 0; ihit < event_multiplicity; ihit++){
            fhit = (FRSMainCrateRawData*)fraw_data->At(ihit);
            
            for (int nhit = 0; nhit < fhit->Get_nhit_v1290_main(0,0); nhit ++){
                //they all need to be hit multiple times i assume? - follow up
                leading_time_sci41l = fhit->Get_leading_v1290_main(0,nhit); //currently mapping here:
                leading_time_sci41r = fhit->Get_leading_v1290_main(1,nhit);
                leading_time_sci21l = fhit->Get_leading_v1290_main(2,nhit);
                leading_time_sci21r = fhit->Get_leading_v1290_main(3,nhit);

                sci41_dt = params_sci->mhtdc_factor_ch_to_ns*(leading_time_sci41l - leading_time_sci41r + randomGenerator->Uniform(-0.5,0.5));
                sci21_dt = params_sci->mhtdc_factor_ch_to_ns*(leading_time_sci21l - leading_time_sci21r + randomGenerator->Uniform(-0.5,0.5));
                sci41_x = sci41_dt*params_sci->mhtdc_factor_41l_41r + params_sci->mhtdc_offset_41l_41r;
                sci21_x = sci21_dt*params_sci->mhtdc_factor_21l_21r + params_sci->mhtdc_offset_21l_21r;
                tof_21_41 = params_sci->mhtdc_factor_ch_to_ns*( 0.5*(leading_time_sci41l+leading_time_sci41r)  - 0.5*(leading_time_sci21l+leading_time_sci21r) ) + params_sci->mhtdc_offset_41_21;
            
                new ((*fcal_data)[fcal_data->GetEntriesFast()]) FRSSCICalData(
                    leading_time_sci41l,
                    leading_time_sci41r,
                    leading_time_sci21l,
                    leading_time_sci21r,
                    sci41_dt,
                    sci21_dt,
                    sci41_x,
                    sci21_x,
                    tof_21_41,
                    fhit->Get_wr_subsystem_id(),
                    fhit->Get_wr_t());
            }
            
        }
    }
}



/*
THIS FUNCTION IS EXTREMELY IMPORTANT!!!!

Clears the TClonesArray used in the function. If they are not cleared after each event they will eat all your RAM.

*/
void FrsMainCrateRaw2Cal::FinishEvent(){
    // reset output array
    fraw_data->Clear();
    fcal_data->Clear();
};


/*
Some stats are written when finishing.
*/
void FrsMainCrateRaw2Cal::FinishTask(){
    c4LOG(info, Form("Wrote %i events.",fNEvents));
}


ClassImp(FrsMainCrateRaw2Cal)
