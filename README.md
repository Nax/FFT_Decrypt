# FFT Decrypt

![Mac Screenshot](/data/misc/mac_screenshot.png?raw=true)

Decrypt FFT WotL's EBOOT.BIN in-place within the ISO.

FFT Decrypt is compatible with the E and U versions of the game.

## Usage

Command line:

    fftdecrypt [-f|--force] <file.iso>

Decrypt the WotL iso. the `-f` flag can be used to force re-encryption of EBOOT.BIN from BOOT.BIN.

## Building

With an UNIX environment:

    mkdir build
    cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release
    make
    sudo make install

## License

FFT Decrypt is available under the terms of the MIT license.

## Credits

FFT Decrypt was created by [Nax](https://github.com/Nax).
