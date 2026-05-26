#define F_CPU 8000000UL 
#include <avr/io.h>
#include <util/delay.h>

#define LED_DDR  DDRB
#define LED_PORT PORTB
#define LED_PIN  6

void initHorloge(void){
    CLKSEL0 = 0b00010101;   // sélection de l'horloge externe
    CLKSEL1 = 0b00001111;   // minimum de 8Mhz
    CLKPR = 0b10000000;     // modification du diviseur d'horloge (CLKPCE=1)
    CLKPR = 0;              // 0 pour pas de diviseur (diviseur de 1)
}

int main(void) {
    initHorloge();
    // 1. Initialisation : On configure la broche de la LED comme une SORTIE
    LED_DDR |= (1 << LED_PIN);

    while (1) {
        // Allumer la LED 
        LED_PORT |= (1 << LED_PIN);
        
        // Attendre 500 millisecondes
        _delay_ms(500);

        // Éteindre la LED 
        LED_PORT &= ~(1 << LED_PIN);
        
        // Attendre 500 millisecondes
        _delay_ms(500);
    }
    
    return 0; 
}
