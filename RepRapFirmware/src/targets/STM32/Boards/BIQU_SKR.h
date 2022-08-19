#ifndef BIQU_SKR_H
#define BIQU_SKR_H

#include "../Pins_STM32.h"

// List of assignable pins and their mapping from names to MPU ports. This is indexed by logical pin number.
// The names must match user input that has been converted to lowercase and had _ and - characters stripped out.
// Aliases are separate by the , character.
// If a pin name is prefixed by ! then this means the pin is hardware inverted. The same pin may have names for both the inverted and non-inverted cases,
// for example the inverted heater pins on the expansion connector are available as non-inverted servo pins on a DFueX.
constexpr PinEntry PinTable_BTT_OCTOPUS[] =
{
    //Thermistors
    {PF_3, "bedtemp,tb"},
    {PF_4, "e0temp,th0"},
    {PF_5, "e1temp,th1"},
    {PF_6, "e2temp,th2"},
    {PF_7, "e3temp,th3"},

    //Endstops
    {PG_6, "xstop"},
    {PG_9, "ystop"},
    {PG_10, "zstop"},
    {PG_11, "e0stop,e0det"},
    {PG_12, "e1stop,e1det"},
    {PG_13, "e2stop,e2det"},
    {PG_14, "e3stop,e3det"},
    {PG_15, "e4stop,e4det"},

    //Servos
    {PB_6,  "servo0" },

    //Probe
    {PB_7, "probe"},

    //Heaters and Fans (Big and Small Mosfets}
    {PA_1,  "bed,hbed" },
    {PA_2,  "e0heat,heat0" },
    {PA_3,  "e1heat,heat1" },
    {PB_10, "e2heat,heat2" },
    {PB_11, "e3heat,heat3" },
    {PA_8,  "fan0,fan" },
    {PE_5,  "fan1" },
    {PD_12, "fan2" },
    {PD_13, "fan3" },
    {PD_14, "fan4" },
    {PD_15, "fan5" },

    //EXP1
    {PE_15, "LCDD7"},
    {PE_13, "LCDD5"},
    {PE_10, "LCDRS"},
    {PE_7, "BTNENC"},
    {PE_8, "BEEP"},
    {PE_9, "LCDEN"},
    {PE_12, "LCDD4"},
    {PE_14, "LCDD6"},

    //EXP2
    {PC_15, "LCDCD"},
    {PB_2, "BTNEN2"},
    {PB_1, "BTNEN1"},
    {PA_6, "LCDMISO"},
    {PA_5, "LCDSCK"},
    {PA_4, "LCDSS"},
    {PA_7, "LCDMOSI"},

    //Neopixel
    {PB_0, "Neopixel"},

    //TFT
    {PA_9, "TX1,tfttx"},
    {PA_10, "RX1,tftrx"},

    //SPI
    {PC_4, "XCS"},
    {PD_11, "YCS"},
    {PC_6, "ZCS"},
    {PC_7, "E0CS"},
    {PF_2, "E1CS"},
    {PE_4, "E2CS"},
    {PE_1, "E3CS"},
    {PD_3, "E4CS"},
    {PA_6, "MISO"},
    {PA_7, "MOSI"},
    {PA_5, "SCK"},

    //I2C
    {PB_8, "SCL1"},
    {PB_9, "SDA1"},

    //PSON
    {PE_11, "PSON"},

    //PWRDET
    {PC_0, "PWRDET"},

    //Status LED
    {PA_13, "LED"},
};

constexpr BoardDefaults btt_octopus_Defaults = {
    {0x5e29d842},                               // Signatures
    SD_SDIO,                                    // SD Card access
    {   //CLK, MISO, MOSI
        {PA_5, PA_6, PA_7},                     //SPI0
        {PB_13, PC_2, PC_3},                    //SPI1
        {PB_3,  PB_4,  PB_5},                   //SPI2
        {NoPin, NoPin, NoPin},                  //SPI3
        {NoPin, NoPin, NoPin},                  //SPI4
        {NoPin, NoPin, NoPin},                  //SPI5
    },
    8,                                          // Number of drivers
    {PF_14, PF_15, PG_5, PA_0, PG_2, PF_1, PD_4, PE_0}, // enablePins
    {PF_13, PG_0, PF_11, PG_4, PF_9, PC_13, PE_2, PE_6},// stepPins
    {PF_12, PG_1, PG_3, PC_1, PF_10, PF_0, PE_3,
#if STARTUP_DELAY
    NoPin
#else
    PA_14
#endif 
    },	// dirPins
#if TMC_SOFT_UART
    {PC_4, PD_11, PC_6, PC_7, PF_2, PE_4, PE_1, PD_3},  // uartpins
    8,                                          // Smart drivers
#endif
    0,                                          // digiPot Factor
#if HAS_VOLTAGE_MONITOR
    NoPin,
#endif
    NoPin,
#if HAS_SBC_INTERFACE
    PD_10, PB_12, SSP2,
#endif
};
#endif