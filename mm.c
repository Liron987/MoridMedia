#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
//#include <sys/socket.h>
#include <unistd.h>
//#include <arpa/inet.h>
//#include <netinet/in.h>
#include <netdb.h>
// GnuTLS!
#include <gnutls/gnutls.h>
#include <gnutls/x509.h>
#include <assert.h>
// OpenSSL
//#include <openssl/ssl.h>
//#include <openssl/err.h>

#include "../tifkudim.h"
#include "../btuhim.h"
#include "./clli.h"
#include "./bdikt_tiunim.h"
#include "./hiluz_prty_ctovet.h"
#include "./zor_ska.h"
#include "./bkst_tls.h"
//#include "./bkst_ssl.h"
#include "./yozr_vsolh_bksot.h"
#include "./hiluz_ctovt_zfia.h"


MivneGnutls tan_gnutls();
void nke_gnutls();


int main(int mispr_tiunim, char **tiun) {

	// נבצע כמה בדיקות כדי לוודא תקינות הטיעונים
	if (bdikt_tiunim(mispr_tiunim, tiun) == 0 )
		hdps("בדיקת טיעונים בוצעה בהצלחה!\n");


	char *mzbia_ctovt = tiun[1];


	// נטען כמה משתני הצפנה (גנוטלס) שישמשונו לכל הבקשות הבאות
	Mivne_Gnutls = tan_gnutls();

	while (mzbia_ctovt != NULL)
	{
		//if (Hmtna ^ 0) Hmtna = 0;

		if (yozr_vsolh_bksot(mzbia_ctovt) == 0)
			hdps("יצירה ושליחת בקשה בוצעה בהצלחה\n");

		// נחלץ את כתובות הוידאו מתוך קובץ הרשימה שהורד
		// (לפעמים הרשימה מכילה בעצמה רשימה ולכן צריך לחזור על הפעולות)
		if (hiluz_ctovt_zfia(mzbia_ctovt) == 0)
			hdps("חילוץ כתובת צפיה בוצע בהצלחה!\n");


		if (Ctovt[0] == '\0')
			mzbia_ctovt = NULL;
		else
			mzbia_ctovt = Ctovt;

		MoneSvvim++;

		//sleep(Hmtna);

	}

	// ננקה את משתני הגנוטלס שפתחנו בתחילת הריצה
	nke_gnutls();


	return 0;
}



MivneGnutls tan_gnutls()
{
	// Initialize GnuTLS
    CHECK(gnutls_global_init() );


	// Load the system's trusted certificates (this may vary based on the system)
    gnutls_certificate_credentials_t xcredh;
    CHECK(gnutls_certificate_allocate_credentials(&xcredh) ); // X509 stuff
    CHECK(gnutls_certificate_set_x509_system_trust(xcredh) ); // sets the system trusted CAs for Internet PKI

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

	MivneGnutls mivne_gnutls = {xcredh, priority};
	return mivne_gnutls;
}

void nke_gnutls()
{
	// Clean up the priority object explicitly after use to avoid memory leaks
    gnutls_priority_deinit(Mivne_Gnutls.adifut);
	// Clean up the session and close the socket
    gnutls_certificate_free_credentials(Mivne_Gnutls.asra);
    // Finalize GnuTLS
    gnutls_global_deinit();
}
