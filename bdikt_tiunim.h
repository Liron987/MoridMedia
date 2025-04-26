#ifndef bdikt_tiunim_h
#define bdikt_tiunim_h

uint8_t bdikt_tiunim(int mispr_tiunim, char **tiun)
{
    if (mispr_tiunim < 2)
	{
		fprintf(stderr, "%c מספר הטיעונים קטן מדי (<2), אנא בדוק שרשמת הפקודה כראוי\n", KST() );
		exit(1);
	}

	for (uint8_t h = 0; h < mispr_tiunim && h < (uint8_t)~0; h++)
		printf("tiun mispr %d, tiun[%d] = %s\n", h, h, tiun[h]);

    return 0;
}

#endif
