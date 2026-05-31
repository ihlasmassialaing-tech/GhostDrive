#ifndef __BOARD_DATAFLASH_H__
#define __BOARD_DATAFLASH_H__

#include <avr/io.h>

#define DATAFLASH_TOTALCHIPS   1
#define DATAFLASH_NO_CHIP      0
#define DATAFLASH_CHIP1        (1 << 0) // PB0
#define DATAFLASH_PAGE_SIZE    512 
#define DATAFLASH_PAGES        4096

/* Commandes standards Atmel Dataflash */
#define DF_CMD_GETSTATUS                         0xD7
#define DF_CMD_MAINMEMTOBUFF1                    0x53
#define DF_CMD_MAINMEMTOBUFF2                    0x55
#define DF_CMD_BUFF1READ                         0xD4
#define DF_CMD_BUFF2READ                         0xD6
#define DF_CMD_BUFF1WRITE                        0x84
#define DF_CMD_BUFF2WRITE                        0x87
#define DF_CMD_BUFF1TOMAINMEMWITHERASE           0x83
#define DF_CMD_BUFF2TOMAINMEMWITHERASE           0x86
#define DF_CMD_MAINMEMPAGEREAD                   0xD2
#define DF_CMD_MAINMEMPAGEPROGTHROUGHBUFF1       0x82
#define DF_CMD_MAINMEMPAGEPROGTHROUGHBUFF2       0x85
#define DF_CMD_PAGEERASE                         0x81
#define DF_CMD_BLOCKERASE                        0x50
#define DF_CMD_READMANUFACTURERDEVICEINFO        0x9F

#define DF_MANUFACTURER_ATMEL                    0x1F
#define DF_STATUS_SECTORPROTECTION_ON            (1 << 1)

static const uint8_t DF_CMD_SECTORPROTECTIONOFF[4] = {0x3D, 0x2A, 0x7F, 0x9A};

/* 1. Initialisation manuelle pure (sans LUFA) */
static inline void Dataflash_Init(void)
{
    // PB0 (CS), PB1 (SCK), PB2 (MOSI) en sortie
    DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2);
    // PB3 (MISO) en entrée
    DDRB &= ~(1 << PB3);
    
    // CS à l'état HAUT (inactif) et Pull-up sur MISO
    PORTB |= (1 << PB0) | (1 << PB3);

    // Configuration SPI pure : Master, Mode 0, Vitesse très lente (F_CPU/16)
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
    SPSR = 0;
}

/* 2. Transfert SPI manuel */
static inline uint8_t Dataflash_TransferByte(const uint8_t Byte)
{
    SPDR = Byte;
    while (!(SPSR & (1 << SPIF))); // Attend la fin de l'envoi
    return SPDR;
}

static inline void Dataflash_SendByte(const uint8_t Byte) {
    Dataflash_TransferByte(Byte);
}

static inline uint8_t Dataflash_ReceiveByte(void) {
    return Dataflash_TransferByte(0x00); // Horloge artificielle pour lire
}

/* 3. Gestion du Chip Select */
static inline uint8_t Dataflash_GetSelectedChip(void) {
    return (!(PINB & DATAFLASH_CHIP1)) ? DATAFLASH_CHIP1 : DATAFLASH_NO_CHIP;
}

static inline void Dataflash_SelectChip(const uint8_t ChipMask) {
    PORTB &= ~ChipMask; 
}

static inline void Dataflash_DeselectChip(void) {
    PORTB |= DATAFLASH_CHIP1; 
}

static inline void Dataflash_SelectChipFromPage(const uint16_t PageAddress) {
    Dataflash_DeselectChip();
    Dataflash_SelectChip(DATAFLASH_CHIP1);
}

static inline void Dataflash_ToggleSelectedChipCS(void) {
    Dataflash_DeselectChip();
    Dataflash_SelectChip(DATAFLASH_CHIP1);
}

/* 4. Sécurité anti-plantage avec Timeout */
static inline void Dataflash_WaitWhileBusy(void)
{
    Dataflash_ToggleSelectedChipCS();
    Dataflash_SendByte(0xD7); 
    uint16_t timeout = 50000;
    while (!(Dataflash_ReceiveByte() & (1 << 7)) && timeout > 0) {
        timeout--;
    }
    Dataflash_ToggleSelectedChipCS();
}

static inline void Dataflash_SendAddressBytes(uint16_t PageAddress, const uint16_t BufferByte)
{
    Dataflash_SendByte((PageAddress >> 6));
    Dataflash_SendByte((PageAddress << 2) | (BufferByte >> 8));
    Dataflash_SendByte(BufferByte);
}

#endif
