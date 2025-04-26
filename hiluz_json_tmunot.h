#ifndef hiluz_json_tmunot_h
#define hiluz_json_tmunot_h


uint16_t hbr_hlk(uint16_t, char *, char *);

static inline void hiluz_json_tmunot(char *hozz)
{

    const char *server = "server\":\"";
    char *mzbia_hlk = NULL;

    uint16_t hthla = 0;

    while( (mzbia_hlk = strstr(hozz + hthla, server) ) )
    {

        memset(Ctovt, 0, sizeof(Ctovt) );

        hthla = mzbia_hlk - hozz;

          // נמנע מלולאה אינסופית, ונתקדם הלאה כמובן
        hthla += orchrz(server) + hbr_hlk(orchrz(server), mzbia_hlk, NULL);


        const char *path = "path\":\"";
        mzbia_hlk = strstr(hozz + hthla, path);
        hbr_hlk(orchrz(path), mzbia_hlk, "/data");


        const char *name = "name\":\"";
        mzbia_hlk = strstr(hozz + hthla, name);
        hbr_hlk(orchrz(name), mzbia_hlk, "?f=");

        // נשלח הבקשה להביא התמונה/התמונות
        if (yozr_vsolh_bksot(Ctovt) == 0)
			hdps("יצירה ושליחת בקשה בוצעה בהצלחה\n");


    }


    Ctovt[0] = '\0';


}




uint16_t hbr_hlk(uint16_t hthla, char *mzbia_hlk, char *kidomt)
{

    uint16_t sof = (strchr(mzbia_hlk + hthla, '"') - mzbia_hlk) - hthla;
    //printf("sof = %d\n", sof);

    uint8_t orc_kidomt = 0;
    if (kidomt)
        orchrz(kidomt);

    if (sof + orchrz(Ctovt) + orc_kidomt >= sizeof(Ctovt) )
    {
        fprintf
        (
            stderr, "%c אורך מחרוזת כתובת השרת נראית לא תקינה, אנא בדוק:\n"
            "%s\n"
            "יוצא...\n",
            KST(), mzbia_hlk
        );

        exit(1);
    }

    uint16_t orc_ctovt = orchrz(Ctovt);

    if (kidomt)
    {
        sprintf(Ctovt + orc_ctovt, "%s", kidomt);
        orc_ctovt = orchrz(Ctovt);
    }

    memcpy(Ctovt + orc_ctovt, mzbia_hlk + hthla, sof);
    Ctovt[orc_ctovt + sof] = '\0';
    //printf("Ctovt = %s\n", Ctovt);


    return sof;
}


#endif


/*
 for ( ; hthla < orchrz(hozz) - (mzbia_hlk - hozz); hthla++)
        if(mzbia_hlk[hthla] == 'h')
            break;

    if (hthla < orchrz(server) )
    {
        fprintf
        (
            stderr, "%c התחלת מחרוזת כתובת השרת נראית לא תקינה, אנא בדוק:\n"
            "%s\n"
            "יוצא...\n",
            KST(), mzbia_hlk
        );

        exit(1);
    }
*/

/*
 * for ( ; sof < orchrz(hozz) - (mzbia_hlk - hozz); sof++)
        if(mzbia_hlk[hthla + sof] == '"')
            break;
*/
