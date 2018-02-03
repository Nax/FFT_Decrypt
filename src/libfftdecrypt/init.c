#include <stdlib.h>
#include <fft/decrypt.h>

FFTD_Decryptor* FFTD_Open(const char* path)
{
    FFTD_Decryptor* decryptor;

    decryptor = malloc(sizeof(FFTD_Decryptor));
    decryptor->file = fopen(path, "r+b");
    if (decryptor->file == NULL)
    {
        free(decryptor);
        return NULL;
    }
    fseek(decryptor->file, 0, SEEK_END);
    decryptor->file_size = ftell(decryptor->file);
    fseek(decryptor->file, 0, SEEK_SET);
    return decryptor;
}

void FFTD_Close(FFTD_Decryptor* decryptor)
{
    if (decryptor)
    {
        if (decryptor->file)
            fclose(decryptor->file);
        free(decryptor);
    }
}
