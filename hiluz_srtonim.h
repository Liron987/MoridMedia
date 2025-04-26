#ifndef hiluz_srtonim_h
#define hiluz_srtonim_h


void hiluz_srtonim(char *rsimt_srtonim, char *hozz)
{
    // נחפש האיכות הגבוה ביותר קודם:
    char *rohv_ps = "BANDWIDTH=",
         *hivuy = NULL;
    int mikum = 0,
        mone_eicuyot = 0;

    struct Eicuyot
    {
        int ps,
            mikum;
    } eicuyot[12] = {
        { 0 },
        { 0 }
    };

    while ( (hivuy = strstr(hozz + mikum, rohv_ps) ) )
    {
        char hruz[24] = { 0 };
        for (uint8_t h = 0; h < sizeof(hruz); h++)
        {
            if (hivuy[strlen(rohv_ps) + h] == ',')
                break;

            hruz[h] = hivuy[strlen(rohv_ps) + h];
        }

        // נכניס את רמות האיכות למערך ואח"כ נברור ביניהם
        eicuyot[mone_eicuyot].ps = hruzlmispr(hruz);

        mikum = hivuy - hozz + strlen(rohv_ps);
        eicuyot[mone_eicuyot].mikum = mikum;

        mone_eicuyot++;
    }

    if (mone_eicuyot == 0)
    {
        fprintf(stderr, "%c לא הצלחנו למצוא את איכות התוכן, אנא בדוק, יוצא...\n", KST() );
        exit(1);
    }

    int8_t eicut_nivhrt = 0;
    for (uint8_t h = 0; h < mone_eicuyot; h++)
    {
        if (eicuyot[h].ps > eicuyot[eicut_nivhrt].ps)
            eicut_nivhrt = h;

        printf
        (
            "eicuyot[%d].ps = %d, mikum = %d, eicut_nivhrt = %d\n",
            h, eicuyot[h].ps, eicuyot[h].mikum, eicut_nivhrt

        );

    }
/*
 * לא צריך, כבר יש לנו בדיקה למעלה יותר לגבי זה
    // במידה ולא מצאנו איכויות:
    if (eicut_nivhrt == -1)
    {
        fprintf(stderr, "%c לא מצאנו איכות נבחרת, אנא בדוק\n", KST() );
        exit(1);
    }
*/
    printf("eicut[%d].ps = %d\n", eicut_nivhrt, eicuyot[eicut_nivhrt].ps);


    // נשיג הכתובת (או החלק הכתובת):
    char *sof_hlk_ctovt = NULL;

    if ( (sof_hlk_ctovt = strstr(hozz + eicuyot[eicut_nivhrt].mikum, rsimt_srtonim) ) == NULL)
    {
        fprintf(stderr, "%c לא מצאתי החלק כתובת התואם לאיכות , אנא בדוק\n", KST() );
        exit(1);
    }

    hivuy = strchr(hozz + eicuyot[eicut_nivhrt].mikum, '\n');
    if (hivuy == NULL)
    {
        fprintf(stderr, "%c לא מצאתי את תחילת החלק כתובת התואם לאיכות , אנא בדוק\n", KST() );
        exit(1);
    }
    hivuy++;



    // נמצא המיקום בכתובת שממנו נבצע החלפה (במידה והכתובת היא חלקית)
    mikum = 0;
    if (hrzhrzo(hivuy, "http", sof_hlk_ctovt - hivuy) == NULL)
    {
        for (short h = strlen(Ctovt); h > 0; h--)
            if (Ctovt[h] == '/')
            {
                mikum = h + 1;
                break;
            }
    }

    // נוודא שהכתובת החלקית שמצאנו תקינה ושיש מספיק מקום עבור ההחלפה
    if (sof_hlk_ctovt - hivuy < 0 || sof_hlk_ctovt - hivuy + mikum >= (long)sizeof(Ctovt) )
    {
        fprintf
        (
            stderr,
            "%c לא ניתן לחבר החלק כתובת עם הכתובת הקיימת\n"
            "sof_hlk_ctovt - hivuy = %ld, mikum = %d\n",
            KST(), sof_hlk_ctovt - hivuy, mikum
        );
        exit(1);
    }

    // נחבר החלק כתובת
    memcpy(Ctovt + mikum, hivuy, sof_hlk_ctovt - hivuy + strlen(rsimt_srtonim) );
    Ctovt[mikum + (sof_hlk_ctovt - hivuy + strlen(rsimt_srtonim) ) ] = '\0';
    printf("Ctovt hdsa = %s\n", Ctovt);


}


#endif
