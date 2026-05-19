#!/bin/bash

if ! [ -f ~/.espressif/python_env/idf6.0_py*_env/bin/python ]; then
    ~/.espressif/v6.0.1/esp-idf/install.sh
fi

source ~/.espressif/v6.0.1/esp-idf/export.sh

if [ "$1" == "--set-target" ]; then
    idf.py set-target $2

    shift; shift
fi

idf.py -B build/esp32 build -DSPHINX_TARGET=esp32

if [ "$1" == "--upload" ]; then
    idf.py -B build/esp32 flash

    shift
fi