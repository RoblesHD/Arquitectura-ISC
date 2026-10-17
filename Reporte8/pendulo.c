#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdint.h>


#define LEDS 0x07  // PD0, PD1, PD2

const uint16_t vel[] PROGMEM = {500, 400, 300, 250, 200, 150, 100, 50};

void retardo(uint16_t t){
    while (t--) _delay_ms(1);
}

int main(void){
    uint8_t sw;
    uint16_t t;

    // Leds como salidas
    DDRD |= LEDS;

    // PB1-PB5 como entradas con pull-up
    DDRB  &= ~0x3E;
    PORTB |=  0x3E;

    // PC0-PC2 como entradas con pull-up
    DDRC  &= ~0x07;
    PORTC |=  0x07;

    while (1)
    {
        // Leer switches
        sw = ((~PINB & 0x3E) >> 1) |
             (((~PINC & 0x07)) << 5);

        // Elegir velocidad
        uint8_t i = 8;
        while (i > 0 && !(sw & (1 << (i - 1)))) i--;

        t = (i > 0) ? pgm_read_word(&vel[i - 1]) : 300;

        // Péndulo
        PORTD = (PORTD & ~LEDS) | 0x01;
        retardo(t);

        PORTD = (PORTD & ~LEDS) | 0x02;
        retardo(t);

        PORTD = (PORTD & ~LEDS) | 0x04;
        retardo(t);

        PORTD = (PORTD & ~LEDS) | 0x02;
        retardo(t);
    }
}
