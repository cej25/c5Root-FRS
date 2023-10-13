VME_CAEN_V830_FRS()
{
    UINT32 v830_header NOENCODE
    {   
        0_15: trigger_number;
        16_17: ts;
        18_23: nwords;
        24_25: unused;
        26: 0b1; // distinguish header from 26bit word
        27_31: geo;
    };

    list (0 <= i < v830_header.nwords)
    {
        UINT32 data_word NOENCODE
        {
            0_31: data;
        };
    }
}