#ifndef FRSCrateRaw2Cal_H
#define FRSCrateRaw2Cal_H

#include "FairTask.h"


class TClonesArray;
class EventHeader;
class FRSCrateRawData;
class FRSMainCrateRawData;
class TimeMachineData;
class TRandom3;

class FRSCrateRaw2Cal : public FairTask
{
    public:
        FRSCrateRaw2Cal();

        FRSCrateRaw2Cal(const TString& name, Int_t verbose);

        ~FRSCrateRaw2Cal();

        void Exec(Option_t* option);

        void FinishEvent();
        void FinishTask();

        void SetParameters(TMUSICParameter * frs_music_params){params_music = frs_music_params;}

        void SetOnline(Bool_t set_online){fOnline = set_online;}

        virtual void SetParContainers();

        virtual InitStatus Init();


    private:
        Bool_t fOnline;        
        EventHeader * header;
        Int_t fNEvents = 0;


        TClonesArray* fcal_data;
        TClonesArray* fraw_data;
        TClonesArray* fraw_time_data;
        FRSCrateRawData * fhit;
        FRSMainCrateRawData* ftime;


        TMUSICParameter * params_music;
        TRandom3 * randomGenerator;

        


    public:
        ClassDef(FRSCrateRaw2Cal, 1);
};

#endif

