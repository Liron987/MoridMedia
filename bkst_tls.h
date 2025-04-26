#ifndef bkst_tls_h
#define bkst_tls_h

#include <sys/stat.h>

#include "syyum.h"
#include "./ysr_cotry_mp4.h"


void tcp_close(int sd);
uint8_t morid_cotrim(int);

uint8_t bkst_tls(int ska)
{
	// טרם ביצוע הבקשה, נוודא שהכתובת שהועברה לנו תקינה
	if (strchr(Ctovt, ' ') )
	{
		fprintf
		(
			stderr,
			"%c הכתובת שהועברה מכילה תוים לא חוקיים, חודל\n"
			"%s; אנא בדוק\n",
			KST(), Ctovt
		);
		exit(1);
	}

	/// טרם הורדת התוכן, נוודא שלא הורדנוהו קודם
	// ניתן שם לקובץ
	if (syyum() == 0)
		hdps("נתינת שם בוצעה בהצלחה\n");

	// ננסה לפתוח הקובץ, במידה והוא נפתח - הקובץ קיים
	FILE *mk;
	mk = fopen(Sm, "r");
	if (mk != NULL)
	{
		printf
		(
			"שים לב: קובץ בעל השם הנ\"ל כבר קיים:\n"
			"%s\n"
			"מדלג\n",
			Sm
		);


		fclose(mk);

		return 1;
	}


/*
    // Initialize GnuTLS
    CHECK(gnutls_global_init() );


	// Load the system's trusted certificates (this may vary based on the system)
    gnutls_certificate_credentials_t xcredh;
    CHECK(gnutls_certificate_allocate_credentials(&xcredh) ); // X509 stuff
    CHECK(gnutls_certificate_set_x509_system_trust(xcredh) ); // sets the system trusted CAs for Internet PKI
*/

    gnutls_session_t sih;
    gnutls_init(&sih, GNUTLS_CLIENT);

/*
	// Set the priority string to prefer TLS 1.3 and disable older versions
    //const char *priority = "SECURE128:-VERS-SSL3.0:-VERS-TLS1.0:-VERS-TLS1.1:+VERS-TLS1.3";

    // Set the priority for the session
    gnutls_priority_t priority;
    gnutls_priority_init
    (
		&priority,
		"SECURE128:-VERS-SSL3.0:-VERS-TLS1.0:-VERS-TLS1.1:+VERS-TLS1.3",
		NULL
	);
*/
    gnutls_priority_set(sih, Mivne_Gnutls.adifut);

	CHECK(gnutls_credentials_set(sih, GNUTLS_CRD_CERTIFICATE, Mivne_Gnutls.asra) );

	// Set up the server's hostname for Server Name Indication (SNI)
    gnutls_server_name_set(sih, GNUTLS_NAME_DNS, Mearh,	strlen(Mearh) );

    // Connect the socket to the GnuTLS session
    gnutls_transport_set_int(sih, ska);
	// default value is GNUTLS_DEFAULT_HANDSHAKE_TIMEOUT (instead of 10000 milliseconds)
	gnutls_handshake_set_timeout(sih, GNUTLS_DEFAULT_HANDSHAKE_TIMEOUT);


    // Perform the TLS handshake
	int hzr;
	char *desc;
/*
    gnutls_datum_t gnuout;
    int type;
    unsigned status;
*/
	do
	{
		hzr = gnutls_handshake(sih);
	}
	while (hzr < 0 && gnutls_error_is_fatal(hzr) == 0);

	if (hzr < 0) {
/*
		if (hzr == GNUTLS_E_CERTIFICATE_VERIFICATION_ERROR) {
				// check certificate verification status
				type = gnutls_certificate_type_get(sih);
				status = gnutls_session_get_verify_cert_status(sih);
				CHECK(gnutls_certificate_verification_status_print(status,
					type, &gnuout, 0));
				printf("cert verify output: %s\n", gnuout.data);
				gnutls_free(gnuout.data);
		}
		fprintf(stderr, "*** Handshake failed: %s\n", gnutls_strerror(hzr));
*/
		fprintf(stderr, "%c לחיצת יד טי.אל.אס כשלה %d\n", KST(), hzr);
        exit(1);

	} else {
			desc = gnutls_session_get_desc(sih);
			printf("- Session info: %s\n", desc);
			gnutls_free(desc);
	}


/*
	hzr = gnutls_handshake(sih);
    if (hzr < 0) {
        fprintf(stderr, "%s; TLS handshake failed: sgia (%d)\n", KST(), hzr);
        exit(1);
    }
*/
    //gnutls_record_send(sih, slh, strlen(slh) );
    // נשלח בקשה
    LOOP_CHECK(hzr, gnutls_record_send(sih, Slh, strlen(Slh) ) );
	if (hzr < 0)
	{
		fprintf(stderr, "%c הבקשה שנשלחה לא הצליחה, מספר שגיאה שחזר %d\n", KST(), hzr);
		exit(1);
	}
/*
    // Receive the server's response
    while ( (hzr = gnutls_record_recv(sih, kbl, sizeof(kbl) ) ) > 0) {
        fwrite(kbl, 1, hzr, stdout);
    }
*/

	// נקבל תשובה
	int zovr_hzr = 0;

	do
	{
		hzr = gnutls_record_recv(sih, Kbl + zovr_hzr, MRV_HOZZ - 1);
		if (hzr > 0)
		{
			zovr_hzr += hzr;
			Kbl = realloc(Kbl, zovr_hzr + MRV_HOZZ);
		}
/*
		printf("hzr = %d\nKbl = %.*s\n", hzr, hzr, Kbl + (zovr_hzr - hzr) );
		for (int h = 0; h < hzr; h++)
		{
			printf("-%d-", Kbl[zovr_hzr - hzr + h]);
		}
		printf("\n");
*/
		if (Kbl == NULL)
			continue;

		Kbl[zovr_hzr] = '\0';

		if (strstr(Kbl, "\r\n0\r\n\r\n") )
			break;
/*
		uint8_t mone_syum = 0;

		for
		(
			char *ys = strstr(Kbl, SyumHttp);
			ys != NULL;
			ys = strstr(Kbl + (ys - Kbl + strlen(SyumHttp) ), SyumHttp)
		)
			mone_syum++;

		if (mone_syum == 2)
			break;
*/

	}
	while
	(
		hzr > 0
		|| hzr == GNUTLS_E_AGAIN
		|| hzr == GNUTLS_E_INTERRUPTED
	);
	//Kbl[zovr_hzr] = '\0';


	// Perform TLS shutdown
    gnutls_bye(sih, GNUTLS_SHUT_RDWR);
	// Clean up session
    gnutls_deinit(sih);
/*
	// Clean up the priority object explicitly after use to avoid memory leaks
    gnutls_priority_deinit(priority);
	// Clean up the session and close the socket
    gnutls_certificate_free_credentials(xcredh);
    // Finalize GnuTLS
    gnutls_global_deinit();
*/

	// נתייק התשובה בקובץ
	if (Kbl != NULL)
	{
		if (sug_media_nitmc(zovr_hzr) )
		{
			// נוריד הכותרים מן הקובץ שירד על מנת להפוכו לנגין
			// (בקבצי ts זה לא קריטי, אבל עדיף להוריד בכל זאת בשביל השירשור)
			if (morid_cotrim(zovr_hzr) == 0)
				printf(":הורדת כותרים בוצעה בהצלחה\n%s\n", Sm);

			// במקרה של קובץ איתחול לרשימת מפ4,
			// נדאג שהכותרים של האיתחול תואמים לכותרי-החלקים
			// קובץ זה מתברר, עשוי להכיל גם נתונים שאינם בשימוש כמו שמע (audio) נוסף וכו'
			// לכן עלינו לבדוק כמה כותרי טראק (trak) יש בו לעומת מדהד (mdhd)
			// ולהסיר המדהד המיותר
			if (strstr(Ntiv, ".mp4") && MoneMapUri == 1)
			{
				if (ysr_cotry_mp4(&zovr_hzr) == 0)
					hdps("כותרי מפ4 נבדקו בהצלחה\n");

				MoneMapUri = 2;
			}

		}



		mk = fopen(Sm, "w");
		if (mk == NULL)
		{
			fprintf(stderr, "%c לא הצלחתי לפתוח הקובץ לכתיבה: %s\n", KST(), Sm);
			exit(1);
		}

		fwrite(Kbl, 1, zovr_hzr, mk);
		fclose(mk);
	}


    return 0;
}


uint8_t morid_cotrim(int zovr_hzr)
{
    // נמחק הכותרים מן החוצץ
    char *syum_cotrim = NULL;
    if ( (syum_cotrim = strstr(Kbl, SyumHttp) ) == NULL)
    {
        fprintf(stderr, "%c הקובץ אינו מכיל כותרי הטטפ, יוצא\n", KST() );
        exit(1);
    }

    syum_cotrim += strlen(SyumHttp);

    int orc_bli_cotrim = zovr_hzr - (syum_cotrim - Kbl);

    memmove(Kbl, syum_cotrim, orc_bli_cotrim);
    Kbl[orc_bli_cotrim] = '\0';

    return 0;
}

// A proper way to Close TCP connection, taken from GnuTLS documentation
void tcp_close(int sd) {
    shutdown(sd, SHUT_RDWR);        /* no more receptions */
    close(sd);
}


#endif

/*

if (mone == 0)
		{

			short hthlt_sm = 0;
			char sm_horda[256] = { 0 };

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
			printf("sm_horda = %s\n", sm_horda);
			// נוודא שאין לוכסן בסוף
			if (sm_horda[strlen(sm_horda) - 1] == '/')
				sm_horda[strlen(sm_horda) - 1] = '\0';

			printf("* sm_horda = %s\n", sm_horda);

			snprintf
			(
				Sm, sizeof(Sm),
				"/home/liron/Scripts/c-code/moridvid/rsimot-nigun/%s",
				sm_horda
			);


			// נייצר תיקיה קודם:
			if (mkdir(Sm, 0755) == -1)
			{
				if (errno != EEXIST) {  // במידה והתיקיה קיימת, נתעלם
                    KST("לא הצלחתי לייצר תיקייה עבור ההורדות\n");
					fprintf(stderr, "Sm = %s\n", Sm);
                    exit(1);
                }
			}

			// נייצר את הנתיב לקובץ שיהיה בתוך התיקיה
			snprintf
			(
				Sm + strlen(Sm),
				sizeof(Sm), "/%s-%d%s",
				sm_horda, mone, SyomtKovzRsima
			);


		}
		else
		{
			Sm[strlen(Sm) - strlen(SyomtKovzRsima) - 1] = mone + 48;
		}
*/
