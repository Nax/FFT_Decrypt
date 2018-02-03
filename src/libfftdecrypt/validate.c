#include <string.h>
#include <fft/decrypt.h>

static int has_sig(FFTD_Decryptor* decryptor, size_t offset, const char* sig)
{
    char buf[1024];
    size_t len;

    len = strlen(sig);
    memset(buf, 0, len + 1);
    fseek(decryptor->file, offset, SEEK_SET);
    fread(buf, len, 1, decryptor->file);
    return (strcmp(buf, sig) == 0);
}

int FFTD_IsTactics(FFTD_Decryptor* decryptor)
{
    int good_gameid;

    good_gameid = 0;

    if (has_sig(decryptor, 0x8373, "ULUS-10297"))
        good_gameid = 1;
    else if (has_sig(decryptor, 0x8373, "ULES-00850"))
        good_gameid = 1;

    if (good_gameid == 0)
        return 0;

    /* EBOOT.BIN */
    if (!has_sig(decryptor, 32 * 0x800, "~PSP") && !has_sig(decryptor, 32 * 0x800, "\x7F" "ELF"))
        return 0;

    /* BOOT.BIN */
    if (!has_sig(decryptor, 130480 * 0x800, "\x7F" "ELF"))
        return 0;

    return 1;
}

int FFTD_IsDecrypted(FFTD_Decryptor* decryptor)
{
    return has_sig(decryptor, 32 * 0x800, "\x7F" "ELF");
}
