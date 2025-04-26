#ifndef ysr_cotry_mp4_h
#define ysr_cotry_mp4_h


uint8_t ysr_cotry_mp4(int *zovr_hzr)
{
    // נמצא כמה כותרי טראק וכמה כותרי מדהד יש
    struct CotrVCmut
    {
        char cotr[5];
        uint8_t cmut;
        int mikum_ahron;
    };

    struct CotrVCmut trak = { "trak", 0, 0 };
    struct CotrVCmut mdhd = { "mdhd", 0, 0 };


    for (int h = 0; h < *zovr_hzr; h++)
    {
        // נבדוק כמות טראק
        if (Kbl[h] == 't')
        {
            uint8_t m = 1;
            for ( ; m < orchrz(trak.cotr) && h + m < *zovr_hzr; m++)
                if (Kbl[h + m] != trak.cotr[m])
                    break;

            if (m == orchrz(trak.cotr) )
            {
                trak.cmut++;
                trak.mikum_ahron = h;
            }

        }

        // נבדוק כמות מדהד
        if (Kbl[h] == 'm')
        {
            uint8_t m = 1;
            for ( ; m < orchrz(mdhd.cotr) && h + m < *zovr_hzr; m++)
                if (Kbl[h + m] != mdhd.cotr[m])
                    break;

            if (m == orchrz(mdhd.cotr) )
            {
                mdhd.cmut++;
                mdhd.mikum_ahron = h;
            }
        }

    }


    // נשווה הכמויות ונבצע שינויים בהתאם
    if (trak.cmut < mdhd.cmut)
    {
        printf
        (
            "כמות הטראק קטנה מכמות המדהד\n"
            "trak.cmut = %d, mdhd.cmut = %d\n",
            trak.cmut, mdhd.cmut
        );

        // נוריד המדהד היתום/המיותר כולל 4 בייטים שלפניו שמכריזים על גודלו
        if (mdhd.mikum_ahron - ORC_MDHD <= 0)
        {
            fprintf
            (
                stderr,
                "%c המיקום האחרון של המדהד שמצאנו קרוב מדי לתחילת הקובץ = לא תקין\n"
                "יוצא\n",
                KST()
            );

            exit(1);
        }

        printf("zovr_hzr = %d\n", *zovr_hzr);
        *zovr_hzr = mdhd.mikum_ahron - ORC_MDHD;
        printf("* zovr_hzr = %d\n", *zovr_hzr);

    }
    else if (trak.cmut > mdhd.cmut)
    {
        fprintf
        (
            stderr,
            "%c כמות הטראק גדולה מכמות המדהד, עלינו לכתוב תיפקוד מטפל,\n"
            "trak.cmut = %d, mdhd.cmut = %d\n"
            "יוצא...\n",
            KST(), trak.cmut, mdhd.cmut
        );

        exit(1);
    }


    return 0;
}


#endif
