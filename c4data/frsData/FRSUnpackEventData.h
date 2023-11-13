#ifndef FRSUnpackEventData_H
#define FRSUnpackEventData_H

#include "TObject.h"


const int NRCHANNEL_V1290 = 32;
const int MAX_HITS_V1290 = 32;

class FRSUnpackEventData : public TObject
{
    public:
        // Default Constructor
        FRSUnpackEventData();

        // Destructor
        virtual ~FRSUnpackEventData() {};

        void Reset(){
            for (int i = 0; i<NRCHANNEL_V1290;i++){
                nhit_v1290_main[i][0] = 0;
                nhit_v1290_main[i][1] = 0;

                for (int j = 0; j<MAX_HITS_V1290; j++){
                    leading_v1290_main[i][j] = 0;
                    trailing_v1290_main[i][j] = 0;
                }
            }
        };

        
        //Getters
        inline const uint32_t Get_nhit_v1290_main(int channel, int lead_or_trail){return nhit_v1290_main[channel][lead_or_trail];}
        inline const uint32_t Get_leading_v1290_main(int channel, int hitnr){return leading_v1290_main[channel][hitnr];}
        inline const uint32_t Get_trailing_v1290_main(int channel, int hitnr){return trailing_v1290_main[channel][hitnr];}

        inline const uint16_t Get_wr_subsystem_id() const { return fwr_subsystem_id; }
        inline const uint64_t Get_wr_t() const { return fwr_t; }



        // Setters
        void Set_nhit_v1290_main(uint32_t value, int channel, int lead_or_trail){nhit_v1290_main[channel][lead_or_trail] = value;}
        void Set_leading_v1290_main(uint32_t value, int channel, int hitnr){leading_v1290_main[channel][hitnr] = value;}
        void Set_trailing_v1290_main(uint32_t value, int channel, int hitnr){trailing_v1290_main[channel][hitnr] = value;}


        void Set_wr_subsystem_id(uint32_t v) { fwr_subsystem_id = v; }
        void Set_wr_t(uint64_t v) { fwr_t = v; }


    protected:
        // Data items


        //CAEN VME V1290 in main crate. MBS Signal: type = 12, subtype = 1, procid = 10, control = 20
        uint32_t nhit_v1290_main[NRCHANNEL_V1290][2];    // number of hits TDC in main crate [channel][leading = 0 or trailing = 1]
        uint32_t leading_v1290_main[NRCHANNEL_V1290][MAX_HITS_V1290];     // leading timing V1290 in main crate [channel][hit nr.]
        uint32_t trailing_v1290_main[NRCHANNEL_V1290][MAX_HITS_V1290];    // trailing timing V1290 in main crate [channel][hit nr.]




        //whiterabbit
        uint32_t fwr_subsystem_id;
        uint32_t fwr_t;
    

    public:
        ClassDef(FRSUnpackEventData, 1);
};

#endif
