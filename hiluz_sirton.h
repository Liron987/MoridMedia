#ifndef hiluz_sirton_h
#define hiluz_sirton_h


void hiluz_sirton(char *sirton, char *hozz)
{
    // כבר בדקנו לפני שהגענו לתפקוד הזה שאכן יש סיומת .ts בחוצץ
    char *sof_hlk = strstr(hozz, sirton);
    // האם זה הקטע הראשון?
    //uint8_t kta_rison = 1;

    //int cmut_ktaim = 0;

    // נמצא את סוף הכתובת של הקטע אותו אנו רוצים להוריד
    // (בחלק הזה נמצא גם המיספור של הקטע)
    while (sof_hlk != NULL)
    {
        int hthlt_hlk = -1;

        for(int h = (int)(sof_hlk - hozz); h > 0; h--)
        {
            if (hozz[h] == '\n')
            {
                hthlt_hlk = h + 1;
                break;
            }
        }

        sof_hlk += strlen(sirton);

        // נמצא המיקום בכתובת שממנו נבצע החלפה
        int mikum = 0;
        if (hrzhrzo(hozz + hthlt_hlk, "http", sof_hlk - hozz - hthlt_hlk) == NULL)
        {
            for (short h = strlen(Ctovt); h > 0; h--)
                if (Ctovt[h] == '/')
                {
                    mikum = h + 1;
                    break;
                }
        }

        // נוודא שהכתובת החלקית שמצאנו תקינה ושיש מספיק מקום עבור ההחלפה
        if (sof_hlk - hozz - hthlt_hlk + mikum >= (int)sizeof(Ctovt) )
        {
            fprintf
            (
                stderr,
                "%c לא ניתן לחבר החלק כתובת עם הכתובת הקיימת\n"
                "sof_hlk - hozz = %ld, mikum = %d\n",
                KST(), sof_hlk - hozz - hthlt_hlk, mikum
            );
            exit(1);
        }

        // נחבר החלק כתובת
        int orc_hlk = sof_hlk - hozz - hthlt_hlk;
        memcpy(Ctovt + mikum, hozz + hthlt_hlk, orc_hlk);
        Ctovt[mikum + orc_hlk] = '\0';
        printf("* Ctovt hdsa = %s\n", Ctovt);

        // להימנע מלולאה אינסופית:
        sof_hlk = strstr(hozz + hthlt_hlk + orc_hlk, sirton);

        // במקרה של מפ4, ישנו קובץ איתחול שמכיל מידע חיוני לניגון
        // הקובץ מסומן בכל רשימת מ3ו8 ע"י: #EXT-X-MAP:URI=
        // קובץ זה מתברר, עשוי להכיל גם נתונים שאינם בשימוש כמו שמע (audio) נוסף וכו'
        // לכן עלינו לבדוק כמה כותרי טראק (trak) יש בו לעומת מדהד (mdhd)
        // ולהסיר המדהד המיותר
        char *moov_atom = "#EXT-X-MAP:URI=\"";
        if (strstr(Ctovt, moov_atom) )
        {
            if (MoneMapUri)
                continue;

            short orc_Ctovt = orchrz(Ctovt);
            memmove(Ctovt, Ctovt + orchrz(moov_atom), orc_Ctovt - orchrz(moov_atom) );
            Ctovt[orc_Ctovt - orchrz(moov_atom)] = '\0';

            printf("** Ctovt = %s\n", Ctovt);

            MoneMapUri = 1;
        }

        if (yozr_vsolh_bksot(Ctovt) == 0)
			hdps("יצירה ושליחת בקשה בוצעה בהצלחה\n");
/*

        // אבל, אולי תרצה לבדוק שהקובץ אינו מושחת ע"י:
        // ffmpeg -v error -i <FILE-NAME> -f null -
*/
        // סיימנו הסבב הראשון
        //kta_rison = 0;
        //cmut_ktaim++;
    }

    //memset(Ctovt, 0, sizeof(Ctovt) );
    // נעתיק הכתובת-המשך בחזרה לכתובת עימה אנו עובדים כדי להמשיך להביא עוד סרטונים
	sprintf(Ctovt, "%s", Ctovt_hmsc);

    // נחזיר השם של הקובץ ל-מלל (.txt)
    for (short h = strlen(Sm); h > 0; h--)
        if (Sm[h] == '-')
        {
            snprintf(Sm + ++h, sizeof(Sm), "%ld%s", MoneSvvim, SyomtKovzRsima);

            break;
        }



}

#endif



/*
        // בטרם נחבר החלק כתובת, נוודא שלא מדובר בחתיכה שכבר הבאנו
        if (kta_rison)
        {
            char *hthlt_mispr_hlk = sof_hlk - strlen(sirton) - 1;

            while (hthlt_mispr_hlk - hozz > 0)
            {
                if (hthlt_mispr_hlk[0] == '_')
                {
                    hthlt_mispr_hlk++;
                    break;
                }

                hthlt_mispr_hlk--;
            }


            if (MisprHlkRison[0] ^ 0 && strstr(hthlt_mispr_hlk, MisprHlkRison) )
            {
                fprintf
                (
                    stderr, "כבר הורדנו החתיכה הזו, מבטל הורדה\n"
                    "hthlt_mispr_hlk = %s\n",
                    hthlt_mispr_hlk
                );
                break;
            }

            // נכניס המספר חלק למשתנה לצורך השוואה בהמשך
            // נוודא קודם שיש מקום במספר-חלק:
            if (sof_hlk - hthlt_mispr_hlk > (int)sizeof(MisprHlkRison) )
            {
                fprintf
                (
                    stderr,
                    "%c אין מספיק מקום במספר-חלק להכיל את מיספור החלק, יוצא\n"
                    "hthlt_mispr_hlk = %s\n",
                    KST(), hthlt_mispr_hlk
                );

                exit(1);
            }
            memcpy(MisprHlkRison, hthlt_mispr_hlk, sof_hlk - hthlt_mispr_hlk);
            MisprHlkRison[sof_hlk - hthlt_mispr_hlk] = '\0';

            printf("MisprHlkRison = %s\n", MisprHlkRison);

        }
*/


/*
    // לפני שנמשיך להביא סרטונים חדשים, נבדוק כמה זמן אורך כל קטע (לכל היותר)
    // כדי שנדע מתי להגיש בקשה נוספת לחלקים נוספים
    char zmn_kta[8] = { 2, 0 };
    char *mgdir_zmn = "#EXT-X-TARGETDURATION:",
         *hthlt_zmn,
         *sof_zmn;

    if ( (hthlt_zmn = strstr(hozz, mgdir_zmn) ) == NULL)
    {
        fprintf(stderr, "לא מצאנו כמה זמן אורך כל סרטון, קובע ברירת מחדל של 2 שניות\n");
    }
    else
    {
        hthlt_zmn += strlen(mgdir_zmn);
        sof_zmn = strchr(hthlt_zmn, '\n');
        if (sof_zmn == NULL)
        {
            fprintf
            (
                stderr, "לא מצאתי את סוף חרוז הזמן, קובע ברירת מחדל של 2 שניות, אנא בדוק\n"
                "hthlt_zmn = %s\n",
                hthlt_zmn
            );
        }

        // נוודא שהחרוז נכנס במשתנה
        int orc_hruz_zmn = sof_zmn - hthlt_zmn;
        if (orc_hruz_zmn > (int)sizeof(zmn_kta) - 1)
            fprintf
            (
                stderr, "אין מקום להכיל את חרוז הזמן במשתנה, קובע ברירת מחדל של 2 שניות, "
        " אנא בדוק\n"
                "orc_hruz_zmn = %d, hthlt_zmn = %s\n",
                orc_hruz_zmn, hthlt_zmn
            );

        memcpy(zmn_kta, hthlt_zmn, orc_hruz_zmn);
        zmn_kta[orc_hruz_zmn] = '\0';
    }

    // עתה משמצאנו/קבענו את כמות הזמן לסרטון,
    // נמירו למשתנה מספר,
    // נכפיל בכמות החלקים ונקבע זמן המתנה עד לבקשה הבאה
    // צריך גם להתחשב בזמן בו פורסמה הרשימה:
    // #EXT-X-PROGRAM-DATE-TIME:2025-03-22T10:47:49.145+00:00
    // נכתוב כבר בהמשך
    Hmtna = hruzlmispr(zmn_kta) / 2;
    //Hmtna *= cmut_ktaim / 2;
    printf("Hmtna = %d\n", Hmtna);
*/
