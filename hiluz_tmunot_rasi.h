#ifndef hiluz_tmunot_rasi_h
#define hiluz_tmunot_rasi_h


#include "clli.h"
#include <stdint.h>


void hiluz_tmunot_rasi(char *mzbia_ctovt)
{
    //printf("mzbia_ctovt = %s\n", mzbia_ctovt);

    char *api_v1 = "/api/v1";

    uint8_t spor = 0;
    for (uint16_t h = 0; h < orchrz(mzbia_ctovt); h++)
    {
        if (mzbia_ctovt[h] == '/')
            spor++;

        if (spor == 3)
        {
            // נוודא שיש מספיק מקום להכיל הכתובת
            if (orchrz(mzbia_ctovt) + ORC_TV_MEAPS + orchrz(api_v1) > sizeof(Ctovt) )
            {
                fprintf
                (
                    stderr,
                    "%c הכתובת להשגת התמונות גדולה מכדי להכיל במשתנה כתובת:\n"
                    "%s + %s\n"
                    "יוצא...\n",
                    KST(), mzbia_ctovt, api_v1
                );

                exit(1);
            }

            memcpy(Ctovt, mzbia_ctovt, h);
            sprintf(Ctovt + h, "%s%s", api_v1, mzbia_ctovt + h);

            break;
        }
    }

    printf("Ctovt = %s\n", Ctovt);


}


#endif
