#ifndef sc_model_h
#define sc_model_h


void sc_model(char *hozz, char *cinuy, size_t godl_cinuy)
{
    char *hivuy_hthla = "\"model\":{\"id\":";
    char *hivuy_sof = ",\"isDeleted\"";

    char *hthla = strstr(hozz, hivuy_hthla);
    if (hthla == NULL)
    {
        fprintf(stderr, "%c לא מצאתי החיווי-התחלה לשם-הזרם, יוצא...\n", KST() );
        exit(1);
    }

    char *sof = strstr(hthla, hivuy_sof);
    if (sof == NULL)
    {
        fprintf(stderr, "%c לא מצאתי החיווי-סוף לשם-הזרם, יוצא...\n", KST() );
        exit(1);
    }

    hthla += orchrz(hivuy_hthla);

    if (sof - hthla > (long)godl_cinuy - ORC_TV_MEAPS)
    {
        fprintf
        (
            stderr,
            "%c הכינוי שמצאתי ארוך מכדי להכיל, יוצא...\n"
            "sof - hthla = %ld\n"
            , KST(), sof - hthla
        );
        exit(1);
    }


    memcpy(cinuy, hthla, sof - hthla);
    cinuy[sof - hthla] = '\0';

    //printf("cinuy = %s\n", cinuy);
}



#endif
