#include "GermaniumCalData.h"

GermaniumCalData::GermaniumCalData()
    : fevent_trigger_time(0),
      fpileup(0),
      foverflow(0),
      fchannel_trigger_time(0),
      fchannel_energy(0),
      fcrystal_id(0),
      fdetector_id(0),
      fwr_subsystem_id(0),
      fwr_t(0)
{
}

GermaniumCalData::GermaniumCalData(
        uint64_t event_trigger_time,
        uint8_t pileup,
        uint8_t overflow,
        uint64_t channel_trigger_time,
        double channel_energy, // calibrated in energy of keVs
        uint32_t crystal_id,
        uint32_t detector_id,
        uint16_t wr_subsystem_id,
        uint64_t wr_t)
    : 
    fevent_trigger_time(event_trigger_time),
    fpileup(pileup),
    foverflow(overflow),
    fchannel_trigger_time(channel_trigger_time),
    fchannel_energy(channel_energy),
    fcrystal_id(crystal_id),
    fdetector_id(detector_id),
    fwr_subsystem_id(wr_subsystem_id),
    fwr_t(wr_t)
{
}

ClassImp(GermaniumCalData)