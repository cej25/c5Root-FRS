/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_EXT_H101_FRS_H__
#define __GUARD_H101_EXT_H101_FRS_H__

#ifndef __CINT__
# include <stdint.h>
#else
/* For CINT (old version trouble with stdint.h): */
# ifndef uint32_t
typedef unsigned int uint32_t;
typedef          int  int32_t;
# endif
#endif
#ifndef EXT_STRUCT_CTRL
# define EXT_STRUCT_CTRL(x)
#endif

/********************************************************
 *
 * Plain structure (layout as ntuple/root file):
 */

typedef struct EXT_STR_h101_FRS_t
{
  /* UNPACK */
  uint32_t frswhiterabbit_ts_subsystem_id /* [0,65535] */;
  uint32_t frswhiterabbit_ts_t1 /* [0,65535] */;
  uint32_t frswhiterabbit_ts_t2 /* [0,65535] */;
  uint32_t frswhiterabbit_ts_t3 /* [0,65535] */;
  uint32_t frswhiterabbit_ts_t4 /* [0,65535] */;
  uint32_t frsmaincrate_data_v1290_nM /* [1,32] */;
  uint32_t frsmaincrate_data_v1290_nMI[32 EXT_STRUCT_CTRL(frsmaincrate_data_v1290_nM)] /* [1,32] */;
  uint32_t frsmaincrate_data_v1290_nME[32 EXT_STRUCT_CTRL(frsmaincrate_data_v1290_nM)] /* [1,1024] */;
  uint32_t frsmaincrate_data_v1290_n /* [0,1024] */;
  uint32_t frsmaincrate_data_v1290_data[1024 EXT_STRUCT_CTRL(frsmaincrate_data_v1290_n)] /* [0,16777215] */;
  uint32_t frsmaincrate_data_v1290_channel /* [0,32] */;
  uint32_t frsmaincrate_data_v1290_channelv[32 EXT_STRUCT_CTRL(frsmaincrate_data_v1290_channel)] /* [0,255] */;
  uint32_t frsmaincrate_data_v1290_leadOrTrail /* [0,32] */;
  uint32_t frsmaincrate_data_v1290_leadOrTrailv[32 EXT_STRUCT_CTRL(frsmaincrate_data_v1290_leadOrTrail)] /* [0,255] */;
  uint32_t frsmaincrate_data_v830_n /* [0,32] */;
  uint32_t frsmaincrate_data_v830_nI[32 EXT_STRUCT_CTRL(frsmaincrate_data_v830_n)] /* [1,32] */;
  uint32_t frsmaincrate_data_v830_data[32 EXT_STRUCT_CTRL(frsmaincrate_data_v830_n)] /* [-1,-1] */;
  uint32_t tpat_data_n /* [-1,-1] */;
  uint32_t tpat_data_tpat /* [0,170] */;
  uint32_t tpat_data_tpatv[170 EXT_STRUCT_CTRL(tpat_data_tpat)] /* [0,65535] */;
  uint32_t tpat_data_trig /* [0,170] */;
  uint32_t tpat_data_trigv[170 EXT_STRUCT_CTRL(tpat_data_trig)] /* [0,255] */;
  uint32_t tpat_data_ts_lo /* [0,170] */;
  uint32_t tpat_data_ts_lov[170 EXT_STRUCT_CTRL(tpat_data_ts_lo)] /* [-1,-1] */;
  uint32_t tpat_data_ts_hi /* [0,170] */;
  uint32_t tpat_data_ts_hiv[170 EXT_STRUCT_CTRL(tpat_data_ts_hi)] /* [-1,-1] */;
  uint32_t frstofcrate_data_coarse_timeM /* [1,32] */;
  uint32_t frstofcrate_data_coarse_timeMI[32 EXT_STRUCT_CTRL(frstofcrate_data_coarse_timeM)] /* [1,32] */;
  uint32_t frstofcrate_data_coarse_timeME[32 EXT_STRUCT_CTRL(frstofcrate_data_coarse_timeM)] /* [1,1024] */;
  uint32_t frstofcrate_data_coarse_time /* [0,1024] */;
  uint32_t frstofcrate_data_coarse_timev[1024 EXT_STRUCT_CTRL(frstofcrate_data_coarse_time)] /* [-1,-1] */;
  uint32_t frstofcrate_data_fine_timeM /* [1,32] */;
  uint32_t frstofcrate_data_fine_timeMI[32 EXT_STRUCT_CTRL(frstofcrate_data_fine_timeM)] /* [1,32] */;
  uint32_t frstofcrate_data_fine_timeME[32 EXT_STRUCT_CTRL(frstofcrate_data_fine_timeM)] /* [1,1024] */;
  uint32_t frstofcrate_data_fine_time /* [0,1024] */;
  uint32_t frstofcrate_data_fine_timev[1024 EXT_STRUCT_CTRL(frstofcrate_data_fine_time)] /* [-1,-1] */;
  uint32_t frstofcrate_data_qdc_n /* [0,32] */;
  uint32_t frstofcrate_data_qdc_nI[32 EXT_STRUCT_CTRL(frstofcrate_data_qdc_n)] /* [1,32] */;
  uint32_t frstofcrate_data_qdc_data[32 EXT_STRUCT_CTRL(frstofcrate_data_qdc_n)] /* [0,65535] */;
  uint32_t frstofcrate_data_tdc_n /* [0,34] */;
  uint32_t frstofcrate_data_tdc_nI[34 EXT_STRUCT_CTRL(frstofcrate_data_tdc_n)] /* [1,34] */;
  uint32_t frstofcrate_data_tdc_data[34 EXT_STRUCT_CTRL(frstofcrate_data_tdc_n)] /* [0,65535] */;
  uint32_t frstofcrate_data_sis3820_n /* [0,32] */;
  uint32_t frstofcrate_data_sis3820_nI[32 EXT_STRUCT_CTRL(frstofcrate_data_sis3820_n)] /* [1,32] */;
  uint32_t frstofcrate_data_sis3820_data[32 EXT_STRUCT_CTRL(frstofcrate_data_sis3820_n)] /* [-1,-1] */;
  uint32_t frscrate_frs_v830_n /* [0,32] */;
  uint32_t frscrate_frs_v830_nI[32 EXT_STRUCT_CTRL(frscrate_frs_v830_n)] /* [1,32] */;
  uint32_t frscrate_frs_v830_data[32 EXT_STRUCT_CTRL(frscrate_frs_v830_n)] /* [-1,-1] */;
  uint32_t frscrate_frs_v7x5_n /* [0,32] */;
  uint32_t frscrate_frs_v7x5_nI[32 EXT_STRUCT_CTRL(frscrate_frs_v7x5_n)] /* [1,32] */;
  uint32_t frscrate_frs_v7x5_data[32 EXT_STRUCT_CTRL(frscrate_frs_v7x5_n)] /* [0,65535] */;
  uint32_t frscrate_frs_v7x5_channel /* [0,32] */;
  uint32_t frscrate_frs_v7x5_channelI[32 EXT_STRUCT_CTRL(frscrate_frs_v7x5_channel)] /* [1,32] */;
  uint32_t frscrate_frs_v7x5_channelv[32 EXT_STRUCT_CTRL(frscrate_frs_v7x5_channel)] /* [0,255] */;
  uint32_t frscrate_frs_v7x5_geo /* [0,32] */;
  uint32_t frscrate_frs_v7x5_geoI[32 EXT_STRUCT_CTRL(frscrate_frs_v7x5_geo)] /* [1,32] */;
  uint32_t frscrate_frs_v7x5_geov[32 EXT_STRUCT_CTRL(frscrate_frs_v7x5_geo)] /* [0,255] */;

} EXT_STR_h101_FRS;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_FRS_onion_t
{
  /* UNPACK */
  uint32_t frswhiterabbit_ts_subsystem_id;
  uint32_t frswhiterabbit_ts_t[4];
  uint32_t frsmaincrate_data_v1290_nM;
  uint32_t frsmaincrate_data_v1290_nMI[32 /* frsmaincrate_data_v1290_nM */];
  uint32_t frsmaincrate_data_v1290_nME[32 /* frsmaincrate_data_v1290_nM */];
  uint32_t frsmaincrate_data_v1290_n;
  uint32_t frsmaincrate_data_v1290_data[1024 /* frsmaincrate_data_v1290_n */];
  uint32_t frsmaincrate_data_v1290_channel;
  uint32_t frsmaincrate_data_v1290_channelv[32 /* frsmaincrate_data_v1290_channel */];
  uint32_t frsmaincrate_data_v1290_leadOrTrail;
  uint32_t frsmaincrate_data_v1290_leadOrTrailv[32 /* frsmaincrate_data_v1290_leadOrTrail */];
  uint32_t frsmaincrate_data_v830_n;
  uint32_t frsmaincrate_data_v830_nI[32 /* frsmaincrate_data_v830_n */];
  uint32_t frsmaincrate_data_v830_data[32 /* frsmaincrate_data_v830_n */];
  uint32_t tpat_data_n;
  uint32_t tpat_data_tpat;
  uint32_t tpat_data_tpatv[170 /* tpat_data_tpat */];
  uint32_t tpat_data_trig;
  uint32_t tpat_data_trigv[170 /* tpat_data_trig */];
  uint32_t tpat_data_ts_lo;
  uint32_t tpat_data_ts_lov[170 /* tpat_data_ts_lo */];
  uint32_t tpat_data_ts_hi;
  uint32_t tpat_data_ts_hiv[170 /* tpat_data_ts_hi */];
  uint32_t frstofcrate_data_coarse_timeM;
  uint32_t frstofcrate_data_coarse_timeMI[32 /* frstofcrate_data_coarse_timeM */];
  uint32_t frstofcrate_data_coarse_timeME[32 /* frstofcrate_data_coarse_timeM */];
  uint32_t frstofcrate_data_coarse_time;
  uint32_t frstofcrate_data_coarse_timev[1024 /* frstofcrate_data_coarse_time */];
  uint32_t frstofcrate_data_fine_timeM;
  uint32_t frstofcrate_data_fine_timeMI[32 /* frstofcrate_data_fine_timeM */];
  uint32_t frstofcrate_data_fine_timeME[32 /* frstofcrate_data_fine_timeM */];
  uint32_t frstofcrate_data_fine_time;
  uint32_t frstofcrate_data_fine_timev[1024 /* frstofcrate_data_fine_time */];
  uint32_t frstofcrate_data_qdc_n;
  uint32_t frstofcrate_data_qdc_nI[32 /* frstofcrate_data_qdc_n */];
  uint32_t frstofcrate_data_qdc_data[32 /* frstofcrate_data_qdc_n */];
  uint32_t frstofcrate_data_tdc_n;
  uint32_t frstofcrate_data_tdc_nI[34 /* frstofcrate_data_tdc_n */];
  uint32_t frstofcrate_data_tdc_data[34 /* frstofcrate_data_tdc_n */];
  uint32_t frstofcrate_data_sis3820_n;
  uint32_t frstofcrate_data_sis3820_nI[32 /* frstofcrate_data_sis3820_n */];
  uint32_t frstofcrate_data_sis3820_data[32 /* frstofcrate_data_sis3820_n */];
  uint32_t frscrate_frs_v830_n;
  uint32_t frscrate_frs_v830_nI[32 /* frscrate_frs_v830_n */];
  uint32_t frscrate_frs_v830_data[32 /* frscrate_frs_v830_n */];
  uint32_t frscrate_frs_v7x5_n;
  uint32_t frscrate_frs_v7x5_nI[32 /* frscrate_frs_v7x5_n */];
  uint32_t frscrate_frs_v7x5_data[32 /* frscrate_frs_v7x5_n */];
  uint32_t frscrate_frs_v7x5_channel;
  uint32_t frscrate_frs_v7x5_channelI[32 /* frscrate_frs_v7x5_channel */];
  uint32_t frscrate_frs_v7x5_channelv[32 /* frscrate_frs_v7x5_channel */];
  uint32_t frscrate_frs_v7x5_geo;
  uint32_t frscrate_frs_v7x5_geoI[32 /* frscrate_frs_v7x5_geo */];
  uint32_t frscrate_frs_v7x5_geov[32 /* frscrate_frs_v7x5_geo */];

} EXT_STR_h101_FRS_onion;

/*******************************************************/

#define EXT_STR_h101_FRS_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* UNPACK */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frswhiterabbit_ts_subsystem_id,  UINT32,\
                    "frswhiterabbit_ts_subsystem_id",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frswhiterabbit_ts_t1,            UINT32,\
                    "frswhiterabbit_ts_t1",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frswhiterabbit_ts_t2,            UINT32,\
                    "frswhiterabbit_ts_t2",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frswhiterabbit_ts_t3,            UINT32,\
                    "frswhiterabbit_ts_t3",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frswhiterabbit_ts_t4,            UINT32,\
                    "frswhiterabbit_ts_t4",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsmaincrate_data_v1290_nM,      UINT32,\
                    "frsmaincrate_data_v1290_nM",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsmaincrate_data_v1290_nMI,     UINT32,\
                    "frsmaincrate_data_v1290_nMI",     "frsmaincrate_data_v1290_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsmaincrate_data_v1290_nME,     UINT32,\
                    "frsmaincrate_data_v1290_nME",     "frsmaincrate_data_v1290_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsmaincrate_data_v1290_n,       UINT32,\
                    "frsmaincrate_data_v1290_n",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsmaincrate_data_v1290_data,    UINT32,\
                    "frsmaincrate_data_v1290_data",    "frsmaincrate_data_v1290_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsmaincrate_data_v1290_channel, UINT32,\
                    "frsmaincrate_data_v1290_channel",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsmaincrate_data_v1290_channelv,UINT32,\
                    "frsmaincrate_data_v1290_channelv","frsmaincrate_data_v1290_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsmaincrate_data_v1290_leadOrTrail,UINT32,\
                    "frsmaincrate_data_v1290_leadOrTrail",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsmaincrate_data_v1290_leadOrTrailv,UINT32,\
                    "frsmaincrate_data_v1290_leadOrTrailv","frsmaincrate_data_v1290_leadOrTrail",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsmaincrate_data_v830_n,        UINT32,\
                    "frsmaincrate_data_v830_n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsmaincrate_data_v830_nI,       UINT32,\
                    "frsmaincrate_data_v830_nI",       "frsmaincrate_data_v830_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsmaincrate_data_v830_data,     UINT32,\
                    "frsmaincrate_data_v830_data",     "frsmaincrate_data_v830_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tpat_data_n,                     UINT32,\
                    "tpat_data_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tpat_data_tpat,                  UINT32,\
                    "tpat_data_tpat",170,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tpat_data_tpatv,                 UINT32,\
                    "tpat_data_tpatv",                 "tpat_data_tpat",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tpat_data_trig,                  UINT32,\
                    "tpat_data_trig",170,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tpat_data_trigv,                 UINT32,\
                    "tpat_data_trigv",                 "tpat_data_trig",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tpat_data_ts_lo,                 UINT32,\
                    "tpat_data_ts_lo",170,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tpat_data_ts_lov,                UINT32,\
                    "tpat_data_ts_lov",                "tpat_data_ts_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tpat_data_ts_hi,                 UINT32,\
                    "tpat_data_ts_hi",170,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tpat_data_ts_hiv,                UINT32,\
                    "tpat_data_ts_hiv",                "tpat_data_ts_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frstofcrate_data_coarse_timeM,   UINT32,\
                    "frstofcrate_data_coarse_timeM",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstofcrate_data_coarse_timeMI,  UINT32,\
                    "frstofcrate_data_coarse_timeMI",  "frstofcrate_data_coarse_timeM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstofcrate_data_coarse_timeME,  UINT32,\
                    "frstofcrate_data_coarse_timeME",  "frstofcrate_data_coarse_timeM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frstofcrate_data_coarse_time,    UINT32,\
                    "frstofcrate_data_coarse_time",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstofcrate_data_coarse_timev,   UINT32,\
                    "frstofcrate_data_coarse_timev",   "frstofcrate_data_coarse_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frstofcrate_data_fine_timeM,     UINT32,\
                    "frstofcrate_data_fine_timeM",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstofcrate_data_fine_timeMI,    UINT32,\
                    "frstofcrate_data_fine_timeMI",    "frstofcrate_data_fine_timeM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstofcrate_data_fine_timeME,    UINT32,\
                    "frstofcrate_data_fine_timeME",    "frstofcrate_data_fine_timeM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frstofcrate_data_fine_time,      UINT32,\
                    "frstofcrate_data_fine_time",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstofcrate_data_fine_timev,     UINT32,\
                    "frstofcrate_data_fine_timev",     "frstofcrate_data_fine_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frstofcrate_data_qdc_n,          UINT32,\
                    "frstofcrate_data_qdc_n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstofcrate_data_qdc_nI,         UINT32,\
                    "frstofcrate_data_qdc_nI",         "frstofcrate_data_qdc_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstofcrate_data_qdc_data,       UINT32,\
                    "frstofcrate_data_qdc_data",       "frstofcrate_data_qdc_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frstofcrate_data_tdc_n,          UINT32,\
                    "frstofcrate_data_tdc_n",34,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstofcrate_data_tdc_nI,         UINT32,\
                    "frstofcrate_data_tdc_nI",         "frstofcrate_data_tdc_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstofcrate_data_tdc_data,       UINT32,\
                    "frstofcrate_data_tdc_data",       "frstofcrate_data_tdc_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frstofcrate_data_sis3820_n,      UINT32,\
                    "frstofcrate_data_sis3820_n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstofcrate_data_sis3820_nI,     UINT32,\
                    "frstofcrate_data_sis3820_nI",     "frstofcrate_data_sis3820_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstofcrate_data_sis3820_data,   UINT32,\
                    "frstofcrate_data_sis3820_data",   "frstofcrate_data_sis3820_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frscrate_frs_v830_n,             UINT32,\
                    "frscrate_frs_v830_n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frscrate_frs_v830_nI,            UINT32,\
                    "frscrate_frs_v830_nI",            "frscrate_frs_v830_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frscrate_frs_v830_data,          UINT32,\
                    "frscrate_frs_v830_data",          "frscrate_frs_v830_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frscrate_frs_v7x5_n,             UINT32,\
                    "frscrate_frs_v7x5_n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frscrate_frs_v7x5_nI,            UINT32,\
                    "frscrate_frs_v7x5_nI",            "frscrate_frs_v7x5_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frscrate_frs_v7x5_data,          UINT32,\
                    "frscrate_frs_v7x5_data",          "frscrate_frs_v7x5_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frscrate_frs_v7x5_channel,       UINT32,\
                    "frscrate_frs_v7x5_channel",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frscrate_frs_v7x5_channelI,      UINT32,\
                    "frscrate_frs_v7x5_channelI",      "frscrate_frs_v7x5_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frscrate_frs_v7x5_channelv,      UINT32,\
                    "frscrate_frs_v7x5_channelv",      "frscrate_frs_v7x5_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frscrate_frs_v7x5_geo,           UINT32,\
                    "frscrate_frs_v7x5_geo",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frscrate_frs_v7x5_geoI,          UINT32,\
                    "frscrate_frs_v7x5_geoI",          "frscrate_frs_v7x5_geo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frscrate_frs_v7x5_geov,          UINT32,\
                    "frscrate_frs_v7x5_geov",          "frscrate_frs_v7x5_geo",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_h101_FRS_EXT_h101_FRS_FRS_H__*/

/*******************************************************/
