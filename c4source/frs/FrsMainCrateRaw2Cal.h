#ifndef FrsMainCrateRaw2Cal_H
#define FrsMainCrateRaw2Cal_H

#include "FairTask.h"


class TClonesArray;
class EventHeader;
class FatimaTwinpeaksData;
class FatimaTwinpeaksCalData;
class FRSMainCrateRawData;
class TimeMachineData;
class TRandom3;

class FrsMainCrateRaw2Cal : public FairTask
{
    public:
        FrsMainCrateRaw2Cal();

        FrsMainCrateRaw2Cal(const TString& name, Int_t verbose);

        ~FrsMainCrateRaw2Cal();

        void Exec(Option_t* option);

        void FinishEvent();
        void FinishTask();

        void SetParameters(TSCIParameter * frs_sci_params){params_sci = frs_sci_params;}

        void SetOnline(Bool_t set_online){fOnline = set_online;}

        virtual void SetParContainers();

        virtual InitStatus Init();


    private:
        Bool_t fOnline;        
        EventHeader * header;
        Int_t fNEvents = 0;


        TClonesArray* fcal_data;
        TClonesArray* fraw_data;
        FRSMainCrateRawData * fhit;


        TSCIParameter * params_sci;
        TRandom3 * randomGenerator;


        double leading_time_sci41l;
        double leading_time_sci41r;
        double leading_time_sci21l;
        double leading_time_sci21r;
        double sci41_dt;
        double sci21_dt;
        double sci41_x;
        double sci21_x;
        double tof_21_41;
        


    public:
        ClassDef(FrsMainCrateRaw2Cal, 1);
};

#endif

