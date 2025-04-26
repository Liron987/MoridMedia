#ifndef hiluz_gzip_h
#define hiluz_gzip_h

#include "zlib.h"


#define CHUNK 16384

int hiluz_gzip(char *hozz)
{


/* Decompress from file source to file dest until stream ends or EOF.
   inf() returns Z_OK on success, Z_MEM_ERROR if memory could not be
   allocated for processing, Z_DATA_ERROR if the deflate data is
   invalid or incomplete, Z_VERSION_ERROR if the version of zlib.h and
   the version of the library linked do not match, or Z_ERRNO if there
   is an error reading or writing the files. */
//int inf(FILE *source, FILE *dest)
//{
/*
The local variables have the same functionality as they do for def(). The only difference is that there is no flush variable, since inflate() can tell from the zlib stream itself when the stream is complete.
*/

    int ret;
    unsigned have;
    z_stream strm;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];
/*
The initialization of the state is the same, except that there is no compression level, of course, and two more elements of the structure are initialized. avail_in and next_in must be initialized before calling inflateInit(). This is because the application has the option to provide the start of the zlib stream in order for inflateInit() to have access to information about the compression method to aid in memory allocation. In the current implementation of zlib (up through versions 1.2.x), the method-dependent memory allocations are deferred to the first call of inflate() anyway. However those fields must be initialized since later versions of zlib that provide more compression methods may take advantage of this interface. In any case, no decompression is performed by inflateInit(), so the avail_out and next_out fields do not need to be initialized before calling.

Here avail_in is set to zero and next_in is set to Z_NULL to indicate that no input data is being provided.
*/

    // allocate inflate state
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit2(&strm, 16);
    if (ret != Z_OK)
        return ret;
/*
The outer do-loop decompresses input until inflate() indicates that it has reached the end of the compressed data and has produced all of the uncompressed output. This is in contrast to def() which processes all of the input file. If end-of-file is reached before the compressed data self-terminates, then the compressed data is incomplete and an error is returned.
*/

    // נכין כמה משתנים לסיוע
    char *tocn = strstr(hozz, SyumHttp);
    if (tocn == NULL)
    {
        fprintf
        (
            stderr,
            "%c לא ניתן לחלץ תוכן הקובץ המכווץ, לא מצאנו את סוף הכותרים ותחילת התוכן\n",
            KST()
        );
        exit(1);
    }
    tocn += strlen(SyumHttp);
    //printf("tocn - hozz = %ld\n", tocn - hozz);

    int mikum_kria = 0,
        orc_tocn = 0;
    // נמצא האורך תוכן
    char *hruz = "Content-Length: ",
         *hivuy = NULL;

    if ( (hivuy = strstr(hozz, hruz) ) == NULL)
    {
        fprintf(stderr, "%c לא מצאנו האורך תוכן (המכווץ), אנא בדוק\n", KST() );
        exit(1);
    }

    char *sof_orc_tocn = strchr(hivuy, '\r');
    char mispr[16] = { 0 };
    if ( (sof_orc_tocn - hozz) - (hivuy - hozz + strlen(hruz) ) >= 16)
    {
        fprintf(stderr, "%c אורך התוכן שמצאנו גדול מדי או לא קיים, אנא בדוק\n", KST() );
        exit(1);
    }

    memcpy
    (
        mispr, hivuy + strlen(hruz),
        (sof_orc_tocn - hozz) - (hivuy - hozz + strlen(hruz) )
    );
    // לא צריך לאפס, כבר איתחלנו המשתנה עם אפסים
    orc_tocn = (int)hruzlmispr(mispr);
    printf("mispr = %s, %d\n", mispr, orc_tocn);

    FILE *mk;
    //Sm[strlen(Sm) - strlen(SyomtKovzRsima) - 1] = 'g';

    // נעדכן השם בתוספת g עבור gzip:
    for (short h = strlen(Sm); h > 0; h--)
        if (Sm[h] == '-')
        {
            snprintf(Sm + ++h, sizeof(Sm), "%ldg%s", MoneSvvim, SyomtKovzRsima);

            break;
        }

    mk = fopen(Sm, "w");
    if (mk == NULL)
    {
        fprintf(stderr, "%c לא הצלחתי לפתוח הקובץ לכתיבה: %s\n", KST(), Sm);
        exit(1);
    }

    // decompress until deflate stream ends or end of file
    do {
/*
We read input data and set the strm structure accordingly. If we've reached the end of the input file, then we leave the outer loop and report an error, since the compressed data is incomplete. Note that we may read more data than is eventually consumed by inflate(), if the input file continues past the zlib stream. For applications where zlib streams are embedded in other data, this routine would need to be modified to return the unused data, or at least indicate how much of the input data was not used, so the application would know where to pick up after the zlib stream.
*/

        //strm.avail_in = fread(in, 1, CHUNK, source);
        //if (ferror(source)) {
            //(void)inflateEnd(&strm);
            //return Z_ERRNO;
        //}

        printf("mikum_kria = %d\n", mikum_kria);

        // נוודא שאנו לא יוצאים מחוץ לתחום:
        if (mikum_kria > orc_tocn)
        {
            fprintf(stderr, "%c חריגה מהתחום בחילוץ הנתונים, יוצא...\n", KST() );
            exit(1);
        }
        else if (mikum_kria == orc_tocn)
        {
            in[0] = 0;
            strm.avail_in = 0;
            break;
        }
        else if (orc_tocn - mikum_kria < CHUNK)
        {
            memcpy(in, tocn + mikum_kria, orc_tocn - mikum_kria);
            strm.avail_in = orc_tocn - mikum_kria;
            mikum_kria = orc_tocn;
        }
        else
        {
            memcpy(in, tocn + mikum_kria, CHUNK);
            strm.avail_in = CHUNK;
            mikum_kria += CHUNK;
        }

        //if (strm.avail_in == 0)
            //break;
        strm.next_in = in;
/*
The inner do-loop has the same function it did in def(), which is to keep calling inflate() until has generated all of the output it can with the provided input.
*/

        // run inflate() on input until output buffer not full
        do {
/*
Just like in def(), the same output space is provided for each call of inflate().
*/

            strm.avail_out = CHUNK;
            strm.next_out = out;
/*
Now we run the decompression engine itself. There is no need to adjust the flush parameter, since the zlib format is self-terminating. The main difference here is that there are return values that we need to pay attention to. Z_DATA_ERROR indicates that inflate() detected an error in the zlib compressed data format, which means that either the data is not a zlib stream to begin with, or that the data was corrupted somewhere along the way since it was compressed. The other error to be processed is Z_MEM_ERROR, which can occur since memory allocation is deferred until inflate() needs it, unlike deflate(), whose memory is allocated at the start by deflateInit().

Advanced applications may use deflateSetDictionary() to prime deflate() with a set of likely data to improve the first 32K or so of compression. This is noted in the zlib header, so inflate() requests that that dictionary be provided before it can start to decompress. Without the dictionary, correct decompression is not possible. For this routine, we have no idea what the dictionary is, so the Z_NEED_DICT indication is converted to a Z_DATA_ERROR.

inflate() can also return Z_STREAM_ERROR, which should not be possible here, but could be checked for as noted above for def(). Z_BUF_ERROR does not need to be checked for here, for the same reasons noted for def(). Z_STREAM_END will be checked for later.
*/

            ret = inflate(&strm, Z_NO_FLUSH);
            assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
            printf("ret = %d\n", ret);
/*
            switch (ret) {
            case Z_NEED_DICT:
                ret = Z_DATA_ERROR;     // and fall through
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                (void)inflateEnd(&strm);
                //return ret;
                KST("כישלון בחילוץ הקובץ המכווץ\n");
                exit(1);
            }
*/
            if (ret == Z_NEED_DICT)
                ret = Z_DATA_ERROR;

            if (ret == Z_DATA_ERROR) { ; }

            if (ret == Z_MEM_ERROR)
            {
                (void)inflateEnd(&strm);

                fprintf(stderr, "%c כישלון בחילוץ הקובץ המכווץ\n", KST() );
                exit(1);
            }

/*
The output of inflate() is handled identically to that of deflate().
*/

            have = CHUNK - strm.avail_out;
            if (fwrite(out, 1, have, mk) != have || ferror(mk)) {
                (void)inflateEnd(&strm);
                fprintf(stderr, "%c לא הצלחנו לכתוב לקובץ המכווץ\n", KST() );
                exit(1);
            }
            printf("have = %d\n", have);
/*
The inner do-loop ends when inflate() has no more output as indicated by not filling the output buffer, just as for deflate(). In this case, we cannot assert that strm.avail_in will be zero, since the deflate stream may end before the file does.
*/

        } while (strm.avail_out == 0);
/*
The outer do-loop ends when inflate() reports that it has reached the end of the input zlib stream, has completed the decompression and integrity check, and has provided all of the output. This is indicated by the inflate() return value Z_STREAM_END. The inner loop is guaranteed to leave ret equal to Z_STREAM_END if the last chunk of the input file read contained the end of the zlib stream. So if the return value is not Z_STREAM_END, the loop continues to read more input.
*/

        // done when inflate() says it's done
    } while (ret != Z_STREAM_END);
/*
At this point, decompression successfully completed, or we broke out of the loop due to no more data being available from the input file. If the last inflate() return value is not Z_STREAM_END, then the zlib stream was incomplete and a data error is returned. Otherwise, we return with a happy return value. Of course, inflateEnd() is called first to avoid a memory leak.
*/

    // clean up and return
    (void)inflateEnd(&strm);
    // נסגור הקובץ שפתחנו קודם לכן
    fclose(mk);

    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
//}


}

#endif
