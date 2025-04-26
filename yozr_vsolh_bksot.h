#ifndef yozr_vsolh_bksot_h
#define yozr_vsolh_bksot_h


#include <stdint.h>
uint8_t yozr_vsolh_bksot(char *mzbia_ctovt)
{
	// נחלץ את פרטי הדף להורדה
	if (hiluz_prty_ctovet(mzbia_ctovt) == 0)
		hdps("חילוץ פרטי כתובת בוצע בהצלחה!\n");

	// ניצור השקע המתאים:
	int ska = zor_ska();
	if (ska < 0) {
		fprintf(stderr, "%c לא הצלחתי ליצור השקע המתאים\n", KST() );
		exit(1);
	}

	// נתחבר לאתר ונוריד את הרשימה של קטעי הוידאו
	Kbl = malloc(MRV_HOZZ);
	uint8_t hzr_bkst_tls = bkst_tls(ska);

	switch (hzr_bkst_tls)
	{
		case 0:
			hdps("בקשת טי.אל.אס בוצעה בהצלחה!\n");
			break;
		case 1:
			hdps("בקשת טי.אל.אס לא בוצעה, הקובץ כבר קיים\n");
			break;
		default:
			fprintf
			(
				stderr,
				"בקשת טי.אל.אס החזירה ערך לא צפוי\n"
				"hzr_bkst_tls = %d\n"
				"אנא בדוק, יוצא...\n",
				hzr_bkst_tls
			);

			exit(1);
	}


/*
	// באמצעות אופןססל במקום גנוטלס:
	if (bkst_ssl(ska) == 0)
		hdps("בקשת טי.אל.אס בוצעה בהצלחה!\n");
*/
	free(Kbl);
	// נסגור השקע
	close(ska);


    return 0;
}


#endif
