#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_SPIFlash.h"

Adafruit_SPIFlash Flashdev = Adafruit_SPIFlash( new Adafruit_FlashTransport_SPI( SS1, &SPI1 ) );

SPIFlash_Device_t SerpenteFlash = {
    .total_size = (1 << 22), /* 4 MiB */                                       \
        .start_up_time_us = 5000, .manufacturer_id = 0xc8,                     \
    .memory_type = 0x40, .capacity = 0x16,                                     \
    .max_clock_speed_mhz =                                                     \
        104, /* if we need 120 then we can turn on high performance mode */    \
        .quad_enable_bit_mask = 0x02, .has_sector_protection = false,          \
    .supports_fast_read = true, .supports_qspi = true,                         \
    .supports_qspi_writes = true, .write_status_register_split = false,        \
    .single_status_byte = false,     
};

void setup( void ) {
    bool Printable = false;
    char c = 0;
    int i = 0;

    Serial.begin( 115200 );

    // Wait for someone to open the serial port
    while ( ! Serial )
    ;

    if ( Flashdev.begin( &SerpenteFlash, 1 ) ) {
        do {
            c = Flashdev.read8( i++ );
            Printable = isprint( c );

            Serial.write( Printable ? c : 0 );
        }
        while ( Printable );
    } else {
        Serial.println( "Flash not found?" );
        Serial.println( "Something weird must be up" );
    }
}

void loop( void ) {
    while ( true )
    ;
}
