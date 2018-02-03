#include <stdio.h>
#include <string.h>
#include <fft/decrypt.h>

static void usage(const char* progpath)
{
    printf("usage: %s [-f|--force] <file.iso>\n", progpath);
}

int main(int argc, char** argv)
{
    FFTD_Decryptor* decryptor;
    int force;
    const char* path;

    force = 0;
    path = NULL;

    puts("FFT Decrypt version " FFT_DECRYPT_VERSION);
    puts(" by Nax");
    puts("");

    for (size_t i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--force") == 0)
            force = 1;
        else
        {
            if (path == NULL)
                path = argv[i];
            else
            {
                usage(argv[0]);
                return 1;
            }
        }
    }

    if (path == NULL)
    {
        usage(argv[0]);
        return 0;
    }

    decryptor = FFTD_Open(path);
    if (!decryptor)
    {
        printf("error: could not open \"%s\"\n", path);
        return 2;
    }

    if (!FFTD_IsTactics(decryptor))
    {
        puts("error: the supplied file does not seems to be a WotL iso");
        return 3;
    }

    if (FFTD_IsDecrypted(decryptor))
    {
        if (!force)
        {
            puts("The ISO is already decrypted, no action needed");
            puts("Use -f to force re-decryption");
            return 0;
        }
        else
        {
            puts("The ISO is already decrypted, forcing re-decryption");
        }
    }
    puts("Decrypting...");
    FFTD_Decrypt(decryptor);
    FFTD_Close(decryptor);
    puts("Done!");
    return 0;
}
