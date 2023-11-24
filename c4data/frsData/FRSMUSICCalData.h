#ifndef FRSMUSICCalData_H
#define FRSMUSICCalData_H

#include "TObject.h"

class FRSMUSICCalData : public TObject
{
    public:
        // Default Constructor
        FRSMUSICCalData();
        FRSMUSICCalData(
        uint32_t fwr_subsystem_id,
        uint64_t fwr_t);
        // Destructor
        virtual ~FRSMUSICCalData() {};

        //Getters


        inline const double Get_music41_energy_cal(int anode_nr) const {return music41_energy_cal[anode_nr];}
        inline const double Get_music42_energy_cal(int anode_nr) const {return music42_energy_cal[anode_nr];}
        
        inline const double Get_music41_time(int anode_nr) const {return music41_time[anode_nr];}
        inline const double Get_music42_time(int anode_nr) const {return music42_time[anode_nr];}
        

        inline const double Set_music41_energy_calr(){return music41_energy_calr;}
        inline const double Set_music42_energy_calr(){return music42_energy_calr;}
        

        inline const uint16_t Get_wr_subsystem_id() const { return fwr_subsystem_id; }
        inline const uint64_t Get_wr_t() const { return fwr_t; }



        // Setters
        
        void Set_music41_energy_cal(int anode_nr, double e) {music41_energy_cal[anode_nr] = e;}
        void Set_music42_energy_cal(int anode_nr, double e) {music42_energy_cal[anode_nr] = e;}

        void Set_music41_energy_calr(double e){music41_energy_calr = e;}
        void Set_music42_energy_calr(double e){music42_energy_calr = e;}
        
        void Set_music41_time(int anode_nr, double e) {music41_time[anode_nr] = e;}
        void Set_music42_time(int anode_nr, double e) {music42_time[anode_nr] = e;}
        

        void Set_wr_subsystem_id(uint32_t v) { fwr_subsystem_id = v; }
        void Set_wr_t(uint64_t v) { fwr_t = v; }


    protected:
        // Data items
        
        double music41_energy_cal[8] = {0,0,0,0,0,0,0,0}; // [anode nr.]
        double music41_time[8] = {0,0,0,0,0,0,0,0};
        double music42_energy_cal[8] = {0,0,0,0,0,0,0,0};
        double music42_time[8] = {0,0,0,0,0,0,0,0};


        double music41_energy_calr; // MUSIC_energy = sqrt( sqrt( sqrt(r1) * sqrt(r2) ) * sqrt ( sqrt(r3) * sqrt(r4) ) )
        double music42_energy_calr;

        



        //whiterabbit
        uint32_t fwr_subsystem_id;
        uint64_t fwr_t;
    

    public:
        ClassDef(FRSMUSICCalData, 1);
};

#endif
