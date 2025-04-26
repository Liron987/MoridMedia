#ifndef bkst_ssl_h
#define bkst_ssl_h

#define FAIL    -1

SSL_CTX* InitCTX(void)
{   SSL_METHOD *method;
    SSL_CTX *ctx;

    OpenSSL_add_all_algorithms();		/* Load cryptos, et.al. */
    SSL_load_error_strings();			/* Bring in and register error messages */
    method = SSLv23_client_method();		/* Create new client-method instance */
    ctx = SSL_CTX_new(method);			/* Create new context */
    if ( ctx == NULL )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}

void ShowCerts(SSL* ssl)
{   X509 *cert;
    char *line;

    cert = SSL_get_peer_certificate(ssl);	/* get the server's certificate */
    if ( cert != NULL )
    {
        printf("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("Subject: %s\n", line);
        free(line);							/* free the malloc'ed string */
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("Issuer: %s\n", line);
        free(line);							/* free the malloc'ed string */
        X509_free(cert);					/* free the malloc'ed certificate copy */
    }
    else
        printf("No certificates.\n");
}


uint8_t bkst_ssl(int ska)
{

    SSL_CTX *ctx;
    SSL *ssl;
    int hzr;

    ctx = InitCTX();
    ssl = SSL_new(ctx);						/* create new SSL connection state */
    SSL_set_fd(ssl, ska);				/* attach the socket descriptor */
    if ( SSL_connect(ssl) == FAIL )			/* perform the connection */
    {
        ERR_print_errors_fp(stderr);
        exit(1);
    }


    printf("Connected with %s encryption\n", SSL_get_cipher(ssl));
    ShowCerts(ssl);								/* get any certs */
    SSL_write(ssl, Slh, strlen(Slh) );			/* encrypt & send message */

    // נקבל תשובה
	char *kbl = malloc(MRV_HOZZ);
	int zovr_hzr = 0;

    do
	{
		hzr = SSL_read(ssl, kbl + zovr_hzr, MRV_HOZZ - 1);	/* get reply & decrypt */
		if (hzr > 0)
		{
			zovr_hzr += hzr;
			kbl = realloc(kbl, zovr_hzr + MRV_HOZZ);
		}
/*
		printf("hzr = %d\nkbl = %.*s\n", hzr, hzr, kbl + (zovr_hzr - hzr) );
		for (int h = 0; h < hzr; h++)
		{
			printf("-%d-", kbl[zovr_hzr - hzr + h]);
		}
		printf("\n");
*/
		/*if (kbl == NULL)
			continue;*/

		kbl[zovr_hzr] = '\0';

		if (kbl != NULL && strstr(kbl, "\r\n0\r\n\r\n") )
			break;
/*
		uint8_t mone_syum = 0;

		for
		(
			char *ys = strstr(kbl, SyumHttp);
			ys != NULL;
			ys = strstr(kbl + (ys - kbl + strlen(SyumHttp) ), SyumHttp)
		)
			mone_syum++;

		if (mone_syum == 2)
			break;
*/

	}
	while
	(
		hzr > 0
		|| hzr == SSL_ERROR_WANT_READ
	);

    SSL_free(ssl);								/* release connection state */

    SSL_CTX_free(ctx);								/* release context */


    if (kbl != NULL)
	{
		//printf("kbl = %s\n", kbl);

		FILE *mk;
		snprintf(Sm, sizeof(Sm), "/home/liron/Scripts/c-code/moridvid/rsimot-nigun/%s", Ntiv + 1);
		if (Sm[strlen(Sm) - 1] == '/')
			snprintf(Sm + (strlen(Sm) - 1), sizeof(Sm), ".txt");
		else
			snprintf(Sm + strlen(Sm), sizeof(Sm), ".txt");

		mk = fopen(Sm, "w");
		if (mk != NULL)
		{
			fwrite(kbl, 1, zovr_hzr, mk);
			fclose(mk);
		}
	}


	free(kbl);


    return 0;
}


#endif
