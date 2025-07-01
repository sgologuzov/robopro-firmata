/*
  PixelFirmata.h - Firmata library
  Copyright (C) 2025 RoboPRO.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.

  Last updated by Sergey Gologuzov: 2025.07.01
*/

#ifndef PixelFirmata_h
#define PixelFirmata_h

#include <ConfigurableFirmata.h>
#include <FirmataFeature.h>
#include <ws2812.h>

// define the firmata commands needed
#define PIXEL_COMMAND 0x52 // firmata command used for a pixel

class PixelFirmata : public FirmataFeature
{
public:
    PixelFirmata();
    boolean handlePinMode(byte pin, int mode);
    void handleCapability(byte pin);
    boolean handleSysex(byte command, byte argc, byte *argv);
    void reset();
};

PixelFirmata::PixelFirmata()
{
}

boolean PixelFirmata::handlePinMode(byte pin, int mode)
{
    return true;
}

void PixelFirmata::handleCapability(byte pin)
{
}

boolean PixelFirmata::handleSysex(byte command, byte argc, byte *argv)
{
    switch (command)
    {
    case PIXEL_COMMAND:
        if (argc < 2)
        {
            Firmata.sendString(F("Error in Pixel command: Not enough parameters"));
            return false;
        }
        process_command(argc, argv);
        Firmata.startSysex();
        Firmata.write(0x00);
        Firmata.write(0x00);
        Firmata.endSysex();
        return true;
    }
    return false;
}

void PixelFirmata::reset()
{
}

#endif
