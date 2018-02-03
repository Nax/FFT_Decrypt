#include <stdlib.h>
#include <fft/decrypt.h>

#define EBOOT_SIZE      (3835392)
#define BOOT_SIZE       (3835044)
#define EBOOT_OFFSET    (32 * 0x800)
#define BOOT_OFFSET     (130480 * 0x800)

int FFTD_Decrypt(FFTD_Decryptor* decryptor)
{
    char zero;
    char* buffer;

    zero = 0x00;
    buffer = malloc(BOOT_SIZE);
    fseek(decryptor->file, BOOT_OFFSET, SEEK_SET);
    fread(buffer, BOOT_SIZE, 1, decryptor->file);
    fseek(decryptor->file, EBOOT_OFFSET, SEEK_SET);
    fwrite(buffer, BOOT_SIZE, 1, decryptor->file);
    for (size_t i = 0; i < (EBOOT_SIZE - BOOT_SIZE); ++i)
    {
        fwrite(&zero, 1, 1, decryptor->file);
    }
    free(buffer);
    return 1;
}
