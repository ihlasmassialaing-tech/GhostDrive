# Configuration du microcontrôleur
MCU = atmega32u4
F_CPU = 8000000

# Nom du fichier (sans le .c)
TARGET = test_led

# Outils de compilation
CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU)UL -Os

# Règle par défaut (quand on tape juste "make")
all: $(TARGET).hex

# Compilation du C en ELF
$(TARGET).elf: $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET).elf $(TARGET).c

# Conversion de l'ELF en HEX (le format lisible par la puce)
$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $(TARGET).elf $(TARGET).hex

# Règle pour téléverser en USB via le Bootloader DFU
dfu: $(TARGET).hex
	dfu-programmer $(MCU) erase --force
	dfu-programmer $(MCU) flash $(TARGET).hex
	dfu-programmer $(MCU) reset

# Nettoyage des fichiers générés
clean:
	rm -f *.elf *.hex
