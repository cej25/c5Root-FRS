// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "FRSUnpackEventData.h"
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
    , fArray(new TClonesArray("FRSUnpackEventData"))
{
}

FrsReader::~FrsReader() 
{ 
    delete fArray;
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
    FairRootManager::Instance()->RegisterAny("FRSUnpackEventData", fArray, !fOnline);
    //fArray->Clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t FrsReader::Read()
{
    c4LOG(debug1, "Event data");

    if(!fData) return kTRUE;


    // MAIN CRATE
    FRSUnpackEventData this_event;

    wr_t = (((uint64_t)fData->frswhiterabbit_ts_t[3]) << 48) + (((uint64_t)fData->frswhiterabbit_ts_t[2]) << 32) + (((uint64_t)fData->frswhiterabbit_ts_t[1]) << 16) + (uint64_t)(fData->frswhiterabbit_ts_t[0]);
    
    this_event.Set_wr_t(wr_t);
    this_event.Set_wr_subsystem_id(fData->frswhiterabbit_ts_subsystem_id);


    for (int nHits = 0; nHits < fData->frsmaincrate_data_v1290_n; nHits ++ ){
        UInt_t channel_nr = fData->frsmaincrate_data_v1290_channelv[nHits];
        UInt_t is_trail = fData->frsmaincrate_data_v1290_leadOrTrailv[nHits];
        UInt_t data = fData->frsmaincrate_data_v1290_data[nHits];
        UInt_t hit_nr = this_event.Get_nhit_v1290_main(channel_nr,is_trail) + 1;

        c4LOG(info,data);

        if (is_trail == 0){ //from v1290 manual, 0 == lead and conversely.
        this_event.Set_nhit_v1290_main(hit_nr, channel_nr, is_trail);
        this_event.Set_leading_v1290_main(data,channel_nr, hit_nr);
        }else if(is_trail == 1){
        this_event.Set_nhit_v1290_main(hit_nr, channel_nr, is_trail);
        this_event.Set_trailing_v1290_main(data, channel_nr, hit_nr);
        }
    }

    if (fData->frsmaincrate_data_v1290_n > 0) new ((*fArray)[fArray->GetEntriesFast()]) FRSUnpackEventData(this_event);



    fNEvent += 1;
    return kTRUE;

}

void FrsReader::Reset()
{
    // reset output array
    fArray->Clear();
}

ClassImp(FrsReader);