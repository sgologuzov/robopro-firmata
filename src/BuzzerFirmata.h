/*
  BuzzerFirmata.h - Firmata library
  Copyright (C) 2023 OpenBlock.cc.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.

  Last updated by ArthurZheng: 2023.07.21
*/

#ifndef BuzzerFirmata_h
#define BuzzerFirmata_h

#include <ConfigurableFirmata.h>
#include <FirmataFeature.h>

#define BUZZER_COMMAND 0x51

#define BUZZER_TONE 0x1
#define BUZZER_NOTONE 0x2

class BuzzerFirmata : public FirmataFeature
{
public:
    BuzzerFirmata();
    boolean handlePinMode(byte pin, int mode);
    void handleCapability(byte pin);
    boolean handleSysex(byte command, byte argc, byte *argv);
    void reset();
};

BuzzerFirmata::BuzzerFirmata()
{
}

boolean BuzzerFirmata::handlePinMode(byte pin, int mode)
{
    return true;
}

void BuzzerFirmata::handleCapability(byte pin)
{
}

boolean BuzzerFirmata::handleSysex(byte command, byte argc, byte *argv)
{
    switch (command)
    {
    case BUZZER_COMMAND:
        if (argc < 2)
        {
            Firmata.sendString(F("Error in Buzzer command: Not enough parameters"));
            return false;
        }

        byte pin = argv[1];

        if (argv[0] == BUZZER_TONE)
        {
            if (argc < 6)
            {
                Firmata.sendString(F("Error in BUzzer command: Not enough parameters for buzzer tone"));
                return false;
            }
            int frequency = Firmata.decodePackedUInt32(argv + 2);
            tone(pin, frequency);
        }
        else
        {
            noTone(pin);
        }

        Firmata.startSysex();
        Firmata.write(0x00);
        Firmata.write(0x00);
        Firmata.endSysex();
        return true;
    }
    return false;
}

void BuzzerFirmata::reset()
{
}

#endif
