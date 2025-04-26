#ifndef sug_media_nitmc_h
#define sug_media_nitmc_h


#include <stdint.h>
uint8_t sug_media_nitmc(int zovr_hzr)
    // נוודא שסוג המדיה נתמך
{
    // קודם כל נביא את מציין המקום לחלק שלאחר כותרי ה-הטטפ (שהוחזרו בתשובה)
    char *hozz = strstr(Kbl, SyumHttp);
    if (hozz == NULL)
    {
        fprintf
        (
            stderr,
            ANSI_COLOR_ZHOV_BHIR
            "%c לא מצאתי סיום כותרי ה-הטטפ, כדי להתחיל וידוא קובץ נתמך\n"
            "zovr_hzr = %d"
            ANSI_COLOR_RESET
            "\n",
            KST(), zovr_hzr

        );

        return 0;
    }

    int orc_hozz = zovr_hzr - (hozz - Kbl);

    // נקרא הקובץ ונחפש את מספר הקסם
    char *hruzy_ksm[] =
    {
        "JFIF",
        "sidx",
        "ftyp",
    };

    for (int h = 0; h < orc_hozz; h++)
    {
        for (uint8_t m = 0; m < sizeof(hruzy_ksm) /sizeof(hruzy_ksm[0]); m++)
        {
            if (Kbl[h] == hruzy_ksm[m][0] )
            {
                uint8_t s = 1;
                for ( ; s < orchrz(hruzy_ksm[m]) && h + s < orc_hozz; s++)
                    if (Kbl[h + s] != hruzy_ksm[m][s])
                        break;

                if (s == orchrz(hruzy_ksm[m]) )
                {
                    printf
                    (
                        "נמצא מספר הקסם של קובץ:\n"
                        "%s\n",
                        hruzy_ksm[m]
                    );

                    return 1;
                }
            }
        }

    }

    // נסיים בקובץ ts. כי זה רק תו אחד של G,
    // ואם בטעות קובץ אחר החל בתו הזה כדי לציין משהו אחר (גודל למשל)
    // אז יהיה לנו פה חיובי-שגוי
    // עשוי להיות מקרה שהקובץ לא יחל ב-G,
    // אך בעיקרון כל 188 בייטים צריך להיות G (נעדן הקוד בהתאם לצורך)
    if (hozz[0] == 'G')
    {
        printf
        (
            "נמצא מספר הקסם של קובץ:\n"
            "%s\n",
            ".ts"
        );

        return 1;
    }



    return 0;
}


#endif


/*
    // נקרא הקובץ לתוך חוצץ
    FILE *mk;
	mk = fopen(Sm, "r+");
	if (mk == NULL)
	{
		fprintf(stderr, "%c לא הצלחתי לפתוח הקובץ הסרת הכותרים\n%s\n", KST(), Sm);
		exit(1);
	}

	char *hozz = malloc(1);

	if (krakovz(mk, &hozz) )
		exit(1);

	printf("orc hozz = %ld\n", strlen(hozz) );


    // נמחק הכותרים מן החוצץ
    char *syum_cotrim = NULL;
    if ( (syum_cotrim = strstr(hozz, SyumHttp) ) == NULL)
    {
        fprintf(stderr, "%c הקובץ אינו מכיל כותרי הטטפ, יוצא\n", KST() );
        exit(1);
    }

    syum_cotrim += strlen(SyumHttp);
    fprintf(stderr, "hozz = %s\n", hozz + (syum_cotrim - hozz) );

    // נכתוב מחדש אל הקובץ ללא הכותרים
    fwrite(hozz + (syum_cotrim - hozz), sizeof(char), strlen(hozz), mk);

    int mispr_kovz = fileno(mk);

    // Truncate the file to a smaller size
    if (ftruncate(mispr_kovz, strlen(hozz) - (syum_cotrim - hozz) ) == 0 ) {
        printf("הקובץ נחתך בהצלחה\n");
    } else {
        perror("שגיאה בחיתוך הקובץ");
    }

    free(hozz);
    fclose(mk);
*/
