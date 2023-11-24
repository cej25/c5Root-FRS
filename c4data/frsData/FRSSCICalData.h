#ifndef FRSSCICalData_H
#define FRSSCICalData_H

#include "TObject.h"


class FRSSCICalData : public TObject
{
    public:
        // Default Constructor
        FRSSCICalData();
        FRSSCICalData(double flead_time_sci41l,
        double flead_time_sci41r,
        double flead_time_sci_21l,
        double flead_time_sci_21r,
        double fsci41_dt,
        double fsci21_dt,
        double fsci41_x,
        double fsci21_x,
        double ftof_21_41,
        uint32_t fwr_subsystem_id,
        uint64_t fwr_t);
        // Destructor
        virtual ~FRSSCICalData() {};

        //Getters

        inline const double Get_lead_time_sci41l() const { return lead_time_sci41l; }
        inline const double Get_lead_time_sci41r() const { return lead_time_sci41r; }
        inline const double Get_lead_time_sci21l() const { return lead_time_sci21l; }
        inline const double Get_lead_time_sci21r() const { return lead_time_sci21r; }

        inline const double Get_sci41_dt() const { return sci41_dt; }
        inline const double Get_sci21_dt() const { return sci21_dt; }
        inline const double Get_sci41_x() const { return sci41_x; }
        inline const double Get_sci21_x() const { return sci21_x; }
        inline const double Get_tof_21_41() const { return tof_21_41; }


        inline const uint16_t Get_wr_subsystem_id() const { return fwr_subsystem_id; }
        inline const uint64_t Get_wr_t() const { return fwr_t; }



        // Setters

        void Set_lead_time_sci41l(double v) {lead_time_sci41l = v;}
        void Set_lead_time_sci41r(double v) {lead_time_sci41r = v;}
        void Set_lead_time_sci21l(double v) {lead_time_sci21l = v;}
        void Set_lead_time_sci21r(double v) {lead_time_sci21r = v;}
        
        void Set_sci41_dt(double v) {sci41_dt = v;}
        void Set_sci21_dt(double v) {sci21_dt = v;}
        void Set_sci41_x(double v) {sci41_x = v;}
        void Set_sci21_x(double v) {sci21_x = v;}
        void Set_tof_21_41(double v) {tof_21_41 = v;}
        

        void Set_wr_subsystem_id(uint32_t v) { fwr_subsystem_id = v; }
        void Set_wr_t(uint64_t v) { fwr_t = v; }


    protected:
        // Data items


        //SCI 41:
        double lead_time_sci41l;
        double lead_time_sci41r;

        //SCI 21:
        double lead_time_sci21l;
        double lead_time_sci21r;

        double sci41_dt;
        double sci21_dt;
        double sci41_x;
        double sci21_x;
        double tof_21_41;


        //whiterabbit
        uint32_t fwr_subsystem_id;
        uint64_t fwr_t;
    

    public:
        ClassDef(FRSSCICalData, 1);
};

#endif
