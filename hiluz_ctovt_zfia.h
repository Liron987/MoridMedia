#ifndef hiluz_ctovt_zfia_h
#define hiluz_ctovt_zfia_h

#include "zikuk_gusim.h"
#include "hiluz_gzip.h"
#include "hiluz_mstr.h"
#include "hiluz_srtonim.h"
#include "hiluz_sirton.h"
#include "hiluz_tmunot_rasi.h"
#include "hiluz_json_tmunot.h"


uint8_t hiluz_ctovt_zfia(char *mzbia_ctovt)
{
    FILE *mk;
	mk = fopen(Sm, "r");
	if (mk == NULL)
	{
		fprintf(stderr, "%c לא הצלחתי לפתוח הקובץ לצורך חילוץ רשימת הצפייה\n", KST() );
		exit(1);
	}

	char *hozz = malloc(1);

	if (krakovz(mk, &hozz) )
		exit(1);

	//printf("orc hozz = %ld\n", strlen(hozz) );
	//printf("hozz:\n %s\n", hozz);

	fclose(mk);

	// במידה והקובץ מכיל מטא-מידע (של גושים), נזקק החוצץ קודם כל
	if (strstr(hozz, "Transfer-Encoding: chunked") )
	{
		hdps("מזקק גושים\n");
        zikuk_gusim(hozz);
	}

	// במידה והקובץ מכיל מידע מקובץ (גזיפ), נחלצו קודם כל
	if (strstr(hozz, "Content-Encoding: gzip") )
	{
		hdps("מחלץ מכיווץ\n");
		if (hiluz_gzip(hozz) )
		{
			fprintf(stderr, "%c חילוץ הקובץ המכווץ הסתיים בכישלון, אנא בדוק\n", KST() );
			exit(1);
		}

		    // נקרא מחדש לתוך החוצץ את התוכן המחולץ:
		mk = fopen(Sm, "r");
		if (mk == NULL)
		{
			fprintf(stderr, "%c לא הצלחתי לפתוח הקובץ לקריאה: %s\n", KST(), Sm);
			exit(1);
		}
		if (krakovz(mk, &hozz) )
			exit(1);

		fclose(mk);
	}

    //hdps(hozz);


	char *sug_tocn = "Content-Type: text/html;",
		 *rsimt_m3u8 = ".m3u8",
		 *srt_ts = ".ts",
		 *str_mp4 = ".mp4",
		 *data_api = "data-api",
		 *app_json = "application/json";

	if (strstr(hozz, sug_tocn) )
	{
		hiluz_mstr(rsimt_m3u8, hozz);
	}
	else if (strstr(hozz, data_api) )
	{
		hiluz_tmunot_rasi(mzbia_ctovt);
	}
	else if (MoneSvvim)
	{
		if (strstr(hozz, rsimt_m3u8) )
			hiluz_srtonim(rsimt_m3u8, hozz);

		else if (strstr(hozz, srt_ts) && MoneSvvim)
		{
			hiluz_sirton(srt_ts, hozz);
		}
		else if (strstr(hozz, str_mp4) && MoneSvvim)
		{
			hiluz_sirton(str_mp4, hozz);
		}
		else if (strstr(hozz, app_json) && MoneSvvim)
		{
			hiluz_json_tmunot(hozz);
		}
		else
		{
			fprintf(stderr, "%c ...לא מצאתי רשימת ניגון בסבב, יוצא\n", KST() );
			exit(1);
		}

	}
	else
	{
		fprintf(stderr, "%c ...לא מצאתי רשימת ניגון, יוצא\n", KST() );
		exit(1);
	}

	free(hozz);




    return 0;
}


#endif
