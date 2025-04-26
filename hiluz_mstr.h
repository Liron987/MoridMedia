#ifndef hiluz_mstr_h
#define hiluz_mstr_h

#include "./sc_model.h"


void hiluz_mstr(char *rsimt_mstr, char *hozz)
{
    memset(Ctovt, 0, MRV_HOZZ);
    char *sof_Ctovt = strstr(hozz, rsimt_mstr);
	if (sof_Ctovt == NULL)
	{
		fprintf(stderr, "%c לא מצאתי הסוף כתובת רשימת מאסטר, יוצא...\n", KST() );
		exit(1);
	}

	int orc_msof_ctovet = (int)(sof_Ctovt - hozz);
	char *ptih_ctovt = "https:";
/*
	if (orc_msof_ctovet < (int)strlen(ptih_ctovt) )
	{
		fprintf(stderr, "%s; אורך הכתובת שמצאנו קטן מדי, יוצא\n", KST() );
		exit(1);
	}
*/
	for (int h = orc_msof_ctovet; h > 0; h--)
	{
		uint8_t m = 0;
		for ( ; m < (uint8_t)strlen(ptih_ctovt) && h + m < orc_msof_ctovet; m++)
			if (hozz[h + m] ^ ptih_ctovt[m])
				break;

		// במידה ולא זיהינו הפתיח, נמשיך לחפש
		if (m != (uint8_t)strlen(ptih_ctovt) )
			continue;

		// במידה וזיהינו הפתיח, נעבד הכתובת
		orc_msof_ctovet += strlen(rsimt_mstr);

		//printf("orc_msof_ctovet = %ld, h = %d\n", orc_msof_ctovet, h);

		if (orc_msof_ctovet - h > (int)sizeof(Ctovt) - ORC_TV_MEAPS)
		{
			fprintf
			(
				stderr,
				"%c אורך כתובת הרשימת-ניגון גדול מכדי להכיל = %d/%ld\n",
				KST(), orc_msof_ctovet - h, sizeof(Ctovt)
			);
			exit(1);
		}

		// לבסוף, כאשר התנאים בשלו, נכניס הכתובת
		memcpy
		(
			Ctovt,
			hozz + h,
			orc_msof_ctovet - h
		);
		Ctovt[orc_msof_ctovet - h] = '\0';

		break;

	}
	hdps(Ctovt);
/*
	// נוודא שאכן נמצאה כתובת
	if (Ctovt[0] == '\0')
	{
		fprintf(stderr, "%s; לא נמצאה כתובת רשימת מסטר, יוצא..\n", KST() );
		exit(1);
	}
*/
	// במידה והכתובת מכילה תוי בריחה או כינויים, נזקקהּ:
	// סינונים נוספים
	char cinuy[32] = { 0 };

	if ( strstr(Ctovt, "{streamName}") )
		sc_model(hozz, cinuy, sizeof(cinuy) );

	//printf("cinuy = %s\n", cinuy);


	struct Simnim
	{
		char *simn;
		char *thlif;
	} simnim[] =
	{
		{ "\\u002D", "-" },
		{ "\\u002F", "/" },
		{ "{streamName}", cinuy },
		{ "{suffix}", "_auto" },
		{ "pixelate", "edge" }
	};



	for (uint8_t m = 0; m < sizeof(simnim) / sizeof(simnim[0]); m++)
	{
		for (short h = orchrz(Ctovt); h > (short)0; h--)
		{
			if (Ctovt[h] == simnim[m].simn[0])
			{
				uint8_t syvonoim = 1;

				for ( ; syvonoim < orchrz(simnim[m].simn); syvonoim++)
					if (Ctovt[h + syvonoim] != simnim[m].simn[syvonoim])
						break;

				if (syvonoim == orchrz(simnim[m].simn) )
				{
					short orc_Ctovt = (short)orchrz(Ctovt);

					memmove
					(
						Ctovt + h + orchrz(simnim[m].thlif),
						Ctovt + h + orchrz(simnim[m].simn),
						orc_Ctovt - (h + orchrz(simnim[m].simn) )
					);
					Ctovt
					[
						orc_Ctovt - orchrz(simnim[m].simn) + orchrz(simnim[m].thlif)
					] = '\0';

					//fprintf(stderr, "*** %s\n", Ctovt);

					if (h + orchrz(simnim[m].thlif) >= sizeof(Ctovt) )
					{
						fprintf
						(
							stderr,
							"%c אין מספיק מקום בכתובת להכיל התליף לסימן, יוצא...\n"
							"simnim[m].thlif = %s\n",
							KST(), simnim[m].thlif
						);

						exit(1);
					}

					memcpy(Ctovt + h, simnim[m].thlif, orchrz(simnim[m].thlif) );

				}

			}
		}
	}

	fprintf(stderr, "* %s\n", Ctovt);



	// נעתיק הכתובת למשתנה נוסף כדי שאח"כ נוכל לבקש את המשך הסרטונים
	sprintf(Ctovt_hmsc, "%s", Ctovt);
}


#endif
