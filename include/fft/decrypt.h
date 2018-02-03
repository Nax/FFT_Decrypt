#ifndef INCLUDED_FFT_DECRYPT_H
#define INCLUDED_FFT_DECRYPT_H

#include <stdio.h>

#if defined(__cplusplus)
# define FFT_DECRYPT_API extern "C"
#else
# define FFT_DECRYPT_API
#endif

#define FFT_DECRYPT_VERSION "1.0.0"

struct FFTD_Decryptor_
{
    FILE*   file;
    size_t  file_size;
};

typedef struct FFTD_Decryptor_ FFTD_Decryptor;

/*
 * init.c
 */

FFT_DECRYPT_API FFTD_Decryptor* FFTD_Open(const char* path);
FFT_DECRYPT_API void            FFTD_Close(FFTD_Decryptor* decryptor);

/*
 * validate.c
 */

FFT_DECRYPT_API int FFTD_IsTactics(FFTD_Decryptor* decryptor);
FFT_DECRYPT_API int FFTD_IsDecrypted(FFTD_Decryptor* decryptor);

/*
 * decrypt.c
 */

FFT_DECRYPT_API int FFTD_Decrypt(FFTD_Decryptor* decryptor);

#endif
