#ifndef zikuk_gusim_h
#define zikuk_gusim_h


void zikuk_gusim(char *hozz)
{
    // נאתר את כל המטא-מידע שמפריד הגושים ונוציא אותו
    char *df_html = strstr(hozz, SyumHttp);
    if (df_html == NULL)
    {
        fprintf(stderr, "%c ...הקובץ אינו מכיל סיומת הטטפ כלל, יוצא\n", KST() );
        exit(1);
    }

    df_html += strlen(SyumHttp);
    //printf("df_html - hozz = %ld, strlen(df_html) = %ld\n", df_html - hozz, strlen(df_html));

    // אנו בכוונה סופרים לאחור, כך ל-MEMMOVE יש פחות עבודה
    int RN_sof = -1;
    //const uint16_t hruz_mhubr = '\r' << 8 | '\n';

    for (int h = strlen(df_html) - sizeof(uint16_t); h > 0; h--)
    {
        if (df_html[h - 1] == '\r' && df_html[h] == '\n')

        // השיטה הזו יותר איטית מהשוואה ישירה, אך יותר מהירה מפוינטר דירפרנסינג:
        /*uint16_t zug = (unsigned)df_html[h - 1] << 8 | (unsigned)df_html[h];
        //printf("zug = 0x%04X, hruz_mhubr = 0x%04X\n", zug, hruz_mhubr);
        if (zug == hruz_mhubr)*/
        {
            //printf("mzati rn, RN_sof = %d, h = %d\n", RN_sof, h);
            if (RN_sof == -1)
                RN_sof = h;
            else
            {
                int orc_df_html = strlen(df_html);
/*
                printf
                (
                    "orc_df_html = %d, RN_sof = %d, h = %d\n",
                    orc_df_html, RN_sof, h
                );
*/
                memmove
                (
                    df_html + h - 1,
                    df_html + RN_sof,
                    orc_df_html - RN_sof
                );
                df_html[orc_df_html - (RN_sof - (h - 1) ) ] = '\0';

                RN_sof = -1;
            }
            //printf("df_html = %s\n", df_html);
        }
    }


    printf("* orc hozz = %ld\n", strlen(hozz) );
}

#endif



/*
    char *rn_hthla = strstr(hozz, SyumHttp);
    if (rn_hthla == NULL)
    {
        KST("...הקובץ אינו מכיל סיומת הטטפ כלל, יוצא\n");
        exit(1);
    }

    rn_hthla += strlen(SyumHttp);
    char *syum_gus = "\r\n";

    do
    {
        char *rn_sof = strstr(rn_hthla + 1, syum_gus);
        if (rn_sof == NULL)
            break;

        rn_sof += strlen(syum_gus);
        int orc_hozz = strlen(hozz);
        memmove
        (
            hozz + (rn_hthla - hozz),
            hozz + (rn_sof - hozz),
            orc_hozz - (rn_sof - hozz)
        );
        hozz[orc_hozz - (rn_sof - rn_hthla)] = '\0';

    }
    while ( (rn_hthla = strstr(rn_hthla, syum_gus) ) );
*/
