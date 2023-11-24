#include "FRSMUSICCalData.h"

FRSMUSICCalData::FRSMUSICCalData()
    : 
      fwr_subsystem_id(0),
      fwr_t(0)
{
}

FRSMUSICCalData::FRSMUSICCalData(
        uint32_t ffwr_subsystem_id,
        uint64_t ffwr_t) : 
      fwr_subsystem_id(ffwr_subsystem_id),
      fwr_t(ffwr_t)
{}

ClassImp(FRSMUSICCalData)