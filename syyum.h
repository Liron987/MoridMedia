#ifndef syyum_h
#define syyum_h

#include "./sug_media_nitmc.h"


uint8_t syyum()
{

	if (strstr(Ntiv, ".m3u8") )
	// מוריד רשימות
	{
		// נעדכן השם בהתאם למספר החלק:
		for (short h = strlen(Sm); h > 0; h--)
			if (Sm[h] == '-')
			{
				snprintf(Sm + ++h, sizeof(Sm), "%ld%s", MoneSvvim, SyomtKovzRsima);

				break;
			}
	}
	else if
	(
		strstr(Ntiv, ".ts")
        || strstr(Ntiv, ".mp4")
        || strstr(Ntiv, ".jpg")
	)
	// מוריד מדיה (סירטונים, סרטים, תמונות)
	{
		// נאתר את מיספור החלק
		short hthlt_mispr_hlk = 0;
		for (short h = strlen(Ctovt); h > 0; h--)
			if (Ctovt[h] == '_')
			{
				hthlt_mispr_hlk = h + 1;
				break;
			}
			else if (Ctovt[h] == '-')
			// נוודא שהמיספור אינו מכיל מקף (לצורך שִיוּם בהמשך)
			{
				fprintf
				(
					stderr,
					"%c שים לב! יתכן ומיספור-החלק מכיל מקף"
					"\nאנו מסתמכים על כך שהוא לא אנא בדוק\n",
					KST()
				);
			}

		// נאתר את סיום השם (אנו מסתמכים על שהמיספור עצמו אינו מכיל מקף)
		short sof_sm = 0;
		for (short h = strlen(Sm); h > 0; h--)
			if (Sm[h] == '-')
			{
				sof_sm = h + 1;
				break;
			}

		snprintf
		(
			Sm + sof_sm,
			sizeof(Sm), "%s",
			Ctovt + hthlt_mispr_hlk
		);

		printf("Sm-hds = %s\n", Sm);


	}
	else
	// מוריד דפים המכילים רשימות
	{
		short hthlt_sm = 0;
		char sm_horda[1536] = { 0 };

		// נוודא שאורך הנתיב גדול מספיק כדי להכיל שם (שלא מדובר בתיקיית השורש, במקרה)
		if (strlen(Ntiv) <= 2)
		{
			fprintf
			(
				stderr,
				"%c שים לב: אורך הנתיב קטן מדי מכדי להכיל שם, יוצא...\n"
				"%s\n",
				KST(), Ntiv
			);
			exit(1);
		}

		for(short h = strlen(Ntiv) - 2;	h >= 0; h--)
		{
			//printf("Ntiv[%d] = %c | ", h, Ntiv[h]);
			if (Ntiv[h] == '/')
			{
				hthlt_sm = h + 1;
				break;
			}
		}
		//printf("\nhthlt_sm = %d\n", hthlt_sm);

		// ניתן שם להורדה
		snprintf(sm_horda, sizeof(sm_horda), "%s", Ntiv + hthlt_sm);
		//printf("sm_horda = %s\n", sm_horda);
		// נוודא שאין לוכסן בסוף
		if (sm_horda[strlen(sm_horda) - 1] == '/')
			sm_horda[strlen(sm_horda) - 1] = '\0';

		//printf("* sm_horda = %s\n", sm_horda);

		// נביא התיקיית עבודה הנוכחית
		char cwd[512];

		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror("getcwd() error");

			return 1;
		}


		snprintf
		(
			Sm, sizeof(Sm),
			//"/home/liron/Scripts/c-code/moridvid/rsimot-nigun/%s",
			"%s/%s",
			cwd, sm_horda
		);

		if (MoneSvvim == 0)
		{
			printf
			(
				ANSI_COLOR_YAROK
				" :ההורדה תתבצע לתיקייה"
				ANSI_COLOR_RESET
				"\n%s\n",
				Sm
			);
		}

		// נייצר תיקיה קודם:
		if (mkdir(Sm, 0755) == -1)
		{
			if (errno != EEXIST) {  // במידה והתיקיה קיימת, נתעלם
				fprintf
				(
					stderr,
					"%c לא הצלחתי לייצר תיקייה עבור ההורדות\n"
					"Sm = %s\n",
					KST(), Sm
				);
				exit(1);
			}
		}

		// נייצר את הנתיב לקובץ שיהיה בתוך התיקיה
		snprintf
		(
			Sm + strlen(Sm),
			sizeof(Sm), "/%s-%ld%s",
			sm_horda, MoneSvvim, SyomtKovzRsima
		);
	}




	return 0;

}



#endif
