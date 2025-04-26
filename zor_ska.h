#ifndef zor_ska_h
#define zor_ska_h


// תפקוד ליצירת שקע והתחברות לשרת
int zor_ska()
{
    int mtaer_ska;
    struct sockaddr_in ctovt_srt;
    struct hostent *srt;

    mtaer_ska = socket(AF_INET, SOCK_STREAM, 0);
    if (mtaer_ska < 0) {
        perror("לא הצלחתי לפתוח שקע");
        exit(1);
    }

    //printf("Mearh = %s\n", Mearh);
    if (Mearh[0] == '\0' || strchr(Mearh, '.') == NULL)
    {
        fprintf(stderr, "%c לא הועבר מארח תקין לשקע, אנא בדוק\n", KST() );
        exit(1);
    }

    srt = gethostbyname(Mearh);
    if (srt == NULL) {
        fprintf(stderr, "No such host: %s\n", Mearh);
        exit(1);
    }

    bzero( (char *)&ctovt_srt, sizeof(ctovt_srt) );
    ctovt_srt.sin_family = AF_INET;
    bcopy( (char *)srt->h_addr, (char *)&ctovt_srt.sin_addr.s_addr, srt->h_length);
    ctovt_srt.sin_port = htons(atoi(Nml));

    if (connect(mtaer_ska, (struct sockaddr *)&ctovt_srt, sizeof(ctovt_srt) ) < 0) {
        perror("שגיאה בהתחברות לשקע");
        exit(1);
    }

    return mtaer_ska;
}


#endif
