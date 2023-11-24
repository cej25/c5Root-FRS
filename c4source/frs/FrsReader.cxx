// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "FRSMainCrateRawData.h"
#include "FRSCrateRawData.h"
#include "FrsReader.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h" 
    #include "ext_h101_frs.h"
}

//../c4Root/unpack/exps/s452/s452 S452f103_0037.lmd --ntuple=UNPACK,frswhiterabbit,frsmaincrate,tpat,frstofcrate,frscrate,NOTRIGEVENTNO,STRUCT_HH,ext_h101_frs.h

FrsReader::FrsReader(EXT_STR_h101_FRS_onion* data, size_t offset)
    : c4Reader("FrsReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(false) // kFALSE
    , fArrayFRSMainCrate(new TClonesArray("FRSMainCrateRawData"))
    , fArrayFRSCrate(new TClonesArray("FRSCrateRawData"))
{
}

FrsReader::~FrsReader() 
{ 
    delete fArrayFRSMainCrate;
    delete fArrayFRSCrate;
}

Bool_t FrsReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    c4LOG(info, "");
    
    EXT_STR_h101_FRS_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_FRS, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to setup structure information");
        return kFALSE;
    }

    // Register output array in a tree
    
    FairRootManager::Instance()->Register("FRSMainCrateRawData", "FRS main crate data", fArrayFRSMainCrate, !fOnline);
    FairRootManager::Instance()->Register("FRSCrateRawData", "FRS crate data", fArrayFRSCrate, !fOnline);
    //fArrayFRSMainCrate->Clear();

    memset(fData, 0, sizeof *fData);
    c4LOG(info,"FRSReader init setup.");

    return kTRUE;
}

Bool_t FrsReader::Read()
{
    c4LOG(debug1, "Event data");

    if(!fData) return kTRUE;


    // MAIN CRATE
    FRSMainCrateRawData this_event;

    wr_t = (((uint64_t)fData->frswhiterabbit_ts_t[3]) << 48) + (((uint64_t)fData->frswhiterabbit_ts_t[2]) << 32) + (((uint64_t)fData->frswhiterabbit_ts_t[1]) << 16) + (uint64_t)(fData->frswhiterabbit_ts_t[0]);
    
    // frs main crate:
    this_event.Set_wr_t(wr_t);
    this_event.Set_wr_subsystem_id(fData->frswhiterabbit_ts_subsystem_id);
    for (int nHits = 0; nHits < fData->frsmaincrate_data_v1290_n; nHits ++ ){
        UInt_t channel_nr = fData->frsmaincrate_data_v1290_channelv[nHits];
        c4LOG(info,Form("Channel tdc = %i",channel_nr));
        UInt_t is_trail = fData->frsmaincrate_data_v1290_leadOrTrailv[nHits];
        UInt_t data = fData->frsmaincrate_data_v1290_data[nHits];
        UInt_t hit_nr = this_event.Get_nhit_v1290_main(channel_nr,is_trail) + 1;

        //c4LOG(info,Form("data = %i, channel = %i, is_trail = %i, hit_nr = %i",data,channel_nr,is_trail,hit_nr));

        if (is_trail == 0){ //from v1290 manual, 0 == lead and conversely.
        this_event.Set_nhit_v1290_main(hit_nr, channel_nr, is_trail);
        this_event.Set_leading_v1290_main(data, channel_nr, hit_nr-1);
        }else if(is_trail == 1){
        this_event.Set_nhit_v1290_main(hit_nr, channel_nr, is_trail);
        this_event.Set_trailing_v1290_main(data, channel_nr, hit_nr-1);
        }
    }

    if (fData->frsmaincrate_data_v1290_n > 0) new ((*fArrayFRSMainCrate)[fArrayFRSMainCrate->GetEntriesFast()]) FRSMainCrateRawData(this_event);

    //frs crate:
    FRSCrateRawData frscrate_event; // dont allocate unless n>0?
    frscrate_event.Set_wr_t(wr_t);
    frscrate_event.Set_wr_subsystem_id(fData->frswhiterabbit_ts_subsystem_id);
  

    for (int nHits = 0; nHits < fData->frscrate_frs_v7x5_n; nHits++){
        if ((nHits > fData->frscrate_frs_v7x5_channel) || (nHits > fData->frscrate_frs_v7x5_geo)) break; //zero suppression


        int geo = fData->frscrate_frs_v7x5_geov[nHits];
        int ch = fData->frscrate_frs_v7x5_channelv[nHits];
        int data = fData->frscrate_frs_v7x5_data[nHits] & 0xfff;
        
        //c4LOG(info,Form("geo = %i, ch = %i, data = %i, hitnr = %i", fData->frscrate_frs_v7x5_geov[nHits],fData->frscrate_frs_v7x5_channelv[nHits], (fData->frscrate_frs_v7x5_data[nHits] & 0xfff),frscrate_event.Get_frscrate_frs_v7x5_nhits(geo,ch)+1));
        
        frscrate_event.Set_frscrate_frs_v7x5_nhits(geo,ch,frscrate_event.Get_frscrate_frs_v7x5_nhits(geo,ch)+1);
        frscrate_event.Set_frscrate_frs_v7x5_data(frscrate_event.Get_frscrate_frs_v7x5_nhits(geo,ch)-1, geo, ch, data);
    }

    if (fData->frscrate_frs_v7x5_n > 0) new ((*fArrayFRSCrate)[fArrayFRSCrate->GetEntriesFast()]) FRSCrateRawData(frscrate_event);

    fNEvent += 1;
    return kTRUE;

}

void FrsReader::Reset()
{
    // reset output array
    fArrayFRSMainCrate->Clear();
    fArrayFRSCrate->Clear();
}

ClassImp(FrsReader);