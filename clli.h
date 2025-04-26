#ifndef clli_h
#define clli_h


// GnuTLS vars
#define CHECK(x) assert((x) >= 0)
#define LOOP_CHECK(rval, cmd) \
    do { \
            rval = cmd; \
    } while(rval == GNUTLS_E_AGAIN || rval == GNUTLS_E_INTERRUPTED);


#define MRV_HOZZ 2048

char *TVNIT = "https://",
     *SyumHttp = "\r\n\r\n",
     *SyomtKovzRsima = ".txt",
     *Kbl;

char Nml[] = "443",
     Mearh[64] = { 0 },
     Ntiv[1024] = { 0 },
     Slh[MRV_HOZZ] = { 0 },
     Sm[MRV_HOZZ] = { 0 },
     Ctovt[MRV_HOZZ] = { 0 },
     Ctovt_hmsc[MRV_HOZZ],
     MisprHlkRison[16] = { 0 };

typedef struct
{
    gnutls_certificate_credentials_t asra;
    gnutls_priority_t adifut;
} MivneGnutls;

MivneGnutls Mivne_Gnutls;

// int Hmtna = 0; // ככל הנראה אין צורך בזה כאשר מדבור בצפייה ישירה
unsigned long MoneSvvim = 0;
uint8_t MoneMapUri = 0;
#define ORC_MDHD 4


#endif
