#include "FRSSCICalData.h"

FRSSCICalData::FRSSCICalData()
    : 
      lead_time_sci41l(0),
      lead_time_sci41r(0),
      lead_time_sci21l(0),
      lead_time_sci21r(0),
      sci41_dt(0),
      sci21_dt(0),
      sci41_x(0),
      sci21_x(0),
      tof_21_41(0),
      fwr_subsystem_id(0),
      fwr_t(0)
{
}

FRSSCICalData::FRSSCICalData(
        double flead_time_sci41l,
        double flead_time_sci41r,
        double flead_time_sci21l,
        double flead_time_sci21r,
        double fsci41_dt,
        double fsci21_dt,
        double fsci41_x,
        double fsci21_x,
        double ftof_21_41,
        uint32_t ffwr_subsystem_id,
        uint64_t ffwr_t) : 
      lead_time_sci41l(flead_time_sci41l),
      lead_time_sci41r(flead_time_sci41r),
      lead_time_sci21l(flead_time_sci21l),
      lead_time_sci21r(flead_time_sci21r),
    sci41_dt(fsci41_dt),
    sci21_dt(fsci21_dt),
    sci41_x(fsci41_x),
    sci21_x(fsci21_x),
    tof_21_41(ftof_21_41),
      fwr_subsystem_id(ffwr_subsystem_id),
      fwr_t(ffwr_t)
{}

ClassImp(FRSSCICalData)