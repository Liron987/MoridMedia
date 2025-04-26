#ifndef hiluz_prty_ctovet_h
#define hiluz_prty_ctovet_h


uint8_t hiluz_prty_ctovet(char* tiun)
{
// נחלץ את פרטי הדף להורדה
	char *hivuy_tvnit = strstr(tiun, TVNIT);
	// נבדוק שגיאות תבנית
	if (hivuy_tvnit == NULL)
	{
		fprintf
		(
			stderr,
			"%c לא הצלחתי לזהות כתובת אתר (%s), אנא בדוק תצורת הכתובת\n",
			KST(), TVNIT
		);

		exit(1);
	}
	else if (strlen(tiun) < strlen(TVNIT) + 3)
	{
		fprintf(stderr, "%c הכתובת קצרה מדי מכדי להיות תקינה, אנא בדוק\n", KST() );
		exit(1);
	}

	char *hivuy_sof_mearh = strchr(tiun + strlen(TVNIT), '/');
	// נבדוק שגיאות מארח
	if (hivuy_sof_mearh == NULL)
	{
		fprintf(stderr, "%c לא מצאתי את שם המארח של האתר, אנא בדוק\n", KST() );
		exit(1);
	}
	else if ( (short)(hivuy_sof_mearh - tiun) <= (short)(strlen(TVNIT) + 3) )
	{
		fprintf(stderr, "%c אורך מחרוזת המארח קטן מדי, אנא בדוק\n", KST() );
		exit(1);
	}

	snprintf
	(
        Mearh,
        sizeof(Mearh),
        "%.*s",
        (short)(hivuy_sof_mearh - tiun - strlen(TVNIT) ),
        tiun + strlen(TVNIT)
    );

	// נבדוק שגיאות נתיב
	if ( (short)strlen(tiun) <= (short)(hivuy_sof_mearh - tiun) )
	{
		fprintf(stderr, "%c הנתיב של דף ההורדה קצר מדי, אנא בדוק\n", KST() );
		exit(1);
	}

	snprintf
	(
        Ntiv,
        sizeof(Ntiv),
        "%.*s",
        (short)(strlen(tiun) - (short)(hivuy_sof_mearh - tiun) ),
		tiun + (hivuy_sof_mearh - tiun)
    );

	// נכניס את פרטי הדף להורדה לתוך בקשת הטטפ:
	snprintf
	(
		Slh,
		sizeof(Slh),
		"GET %s HTTP/1.1\r\n"
		"Host: %s\r\n"
		"Connection: close\r\n"
		"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
		"\r\n",
		Ntiv,
		Mearh
	);

	printf("Slh = %s\n", Slh);

	return 0;
}

#endif
