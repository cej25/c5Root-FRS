#ifndef FRSCrateRawData_H
#define FRSCrateRawData_H

#include "TObject.h"


const int NRBOARDS = 32;
const int NRHITS = 32;
const int NRCHANNEL_V7x5 = 32;

class FRSCrateRawData : public TObject
{
    public:
        // Default Constructor
        FRSCrateRawData();

        // Destructor
        virtual ~FRSCrateRawData() {};

        void Reset(){
            for (int j = 0; j<NRBOARDS; j++){
                for (int i = 0; i<NRCHANNEL_V7x5;i++){
                    frscrate_frs_v7x5_nhits[j][i] = 0;
                    for (int k = 0; k<NRHITS; k++) frscrate_frs_v7x5_data[j][i][k] = 0;
                }
            }
        };

        
        //Getters
        inline const uint32_t Get_frscrate_frs_v7x5_nhits(uint32_t board_id, uint32_t channel_id){return frscrate_frs_v7x5_nhits[board_id][channel_id];}
        inline const uint32_t Get_frscrate_frs_v7x5_data(uint32_t hitnr, uint32_t board_id, uint32_t channel_id){return frscrate_frs_v7x5_data[board_id][channel_id][hitnr];}

        inline const uint16_t Get_wr_subsystem_id() const { return fwr_subsystem_id; }
        inline const uint64_t Get_wr_t() const { return fwr_t; }

      
        // Setters
        void Set_frscrate_frs_v7x5_nhits(uint32_t board_id, uint32_t channel_id, uint32_t v){frscrate_frs_v7x5_nhits[board_id][channel_id] = v;}
        void Set_frscrate_frs_v7x5_data(uint32_t hitnr, uint32_t board_id, uint32_t channel_id, uint32_t data){frscrate_frs_v7x5_data[board_id][channel_id][hitnr] = data;}

        void Set_wr_subsystem_id(uint32_t v) { fwr_subsystem_id = v; }
        void Set_wr_t(uint64_t v) { fwr_t = v; }
    

    protected:
        // Data items


        //CAEN VME V785 in frs crate. MBS Signal: type = 12, subtype = 1, procid = 30, control = 20
        uint32_t frscrate_frs_v7x5_nhits[NRBOARDS][NRCHANNEL_V7x5]; // nhits
        uint32_t frscrate_frs_v7x5_data[NRBOARDS][NRCHANNEL_V7x5][NRHITS]; 


        //whiterabbit
        uint32_t fwr_subsystem_id;
        uint32_t fwr_t;
    

    public:
        ClassDef(FRSCrateRawData, 1);
};

#endif
