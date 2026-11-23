# GhostDrive — Hardware Security-Audit Device (BadUSB)

> A from-scratch embedded hardware project: a custom USB device (own PCB + firmware)
> designed for authorized security-awareness demonstrations. Built for a supervised
> engineering course.

**Author:** Ihlas Massiala — engineering student, IoT & Cybersecurity, Polytech Lille.
**Stack:** ATmega32U4 · AT45DB161E (external SPI flash) · KiCad (PCB) · C / LUFA (USB firmware) · Python

### ⚠️ Disclaimer — educational use only
This is an **academic project** built to learn embedded systems and hardware-security
concepts. It must only be used on hardware you **own** or have **explicit written
authorization** to test. The author takes no responsibility for any misuse.

### Overview (English)
GhostDrive is a small **USB device of the BadUSB family**. It presents itself to a host as a
standard USB mass-storage key (a 2 MB drive) while also acting as a USB keyboard (HID),
illustrating why untrusted USB peripherals are a real security risk. The behaviour is selected
**offline** with a mechanical DIP switch — no battery required.

The project was designed end to end:
- **Hardware:** a custom PCB in **KiCad** around an **ATmega32U4** MCU with an external
  **AT45DB161E** SPI flash, in a USB-key form factor (schematic, routing, production files).
- **Firmware:** written in **C** on top of the **LUFA** USB stack — USB composite-device
  enumeration, SPI communication with the flash (FAT12 geometry) and reading the hardware
  configuration switches.
- **Tooling:** a small **Python** generator and low-level test firmware (status-LED board bring-up).

### What this project demonstrates
Embedded C, USB device programming (LUFA), SPI/flash handling, PCB design (KiCad), hardware
bring-up and debugging, and a practical understanding of a well-known physical-access attack
class — the kind of hands-on background useful for offensive security / penetration testing.

> 🇫🇷 **Version française complète ci-dessous.**

---

# GhostDrive - Plateforme d'Audit de Sécurité Furtive & Autonome

## Description Générale
GhostDrive est un outil d'audit de sécurité matériel de type BadUSB. Il a été conçu pour exécuter des injections de commandes automatisées tout en se camouflant derrière l'apparence d'un périphérique USB de stockage standard (clé USB de 2 Mo). 

L'architecture matérielle repose sur un microcontrôleur ATmega32U4 couplé à une mémoire flash SPI externe (AT45DB161E). La sélection du vecteur d'attaque en mode "Hors-Ligne" est gérée par un DIP Switch mécanique, permettant de calibrer le dispositif sans nécessiter de batterie embarquée. Une fois branché, le périphérique est reconnu comme un périphérique USB Composite (Mass Storage + Clavier HID).

## Architecture du Dépôt

Le projet est divisé en trois dossiers principaux :

* **`Documentation/`** : Contient les fiches techniques (datasheets) des composants critiques utilisés pour la conception.
    * `atmega32U4_datasheet.pdf` : Microcontrôleur principal.
    * `AT45DB161E.pdf` : Puce mémoire Flash SPI (2 Mo) pour le stockage de masse.
    * `MAX1811.pdf` : Contrôleur de charge LiPo (intégré au schéma pour une alimentation hybride optionnelle).

* **`Hardware/`** : Contient les fichiers de conception électronique réalisés sous KiCad.
    * `ghost_drive.kicad_sch` : Schéma de principe.
    * `ghost_drive.kicad_pcb` : Routage de la carte mère au format clé USB.
    * `production/` : Fichiers de fabrication (Gerbers, BOM, Pick&Place).

* **`Logiciel/`** : Contient les différents firmwares développés (basés sur la bibliothèque LUFA).
    * `test_led/` : Programme de test unitaire bas niveau permettant de valider l'alimentation, le fonctionnement de l'horloge interne et les soudures de la carte via le clignotement d'une LED de statut.
    * `GhostDrive/` : Firmware principal complet gérant l'énumération USB Composite, la communication SPI avec la mémoire flash (géométrie FAT12), la lecture matérielle des DIP Switchs et l'exécution automatisée des payloads HID.

## Fonctionnalités Principales

1.  **Configuration Matérielle Hors-Ligne :** Sélection du payload via DIP Switch physique avant connexion.
2.  **Camouflage (Leurre) :** Montage automatique d'un volume de stockage FAT12 vierge et fonctionnel de 2 Mo pour lever les soupçons de l'utilisateur cible.
3.  **Exécution Furtive :** Frappe automatisée de séquences de touches programmées (clavier virtuel) en arrière-plan pendant la consultation du volume de stockage.

## Compilation et Flashage

Pour compiler et flasher les firmwares sur l'ATmega32U4, les outils suivants sont requis sous Linux : `avr-gcc`, `avr-libc`, `make` et `dfu-programmer`.

1.  Ouvrir un terminal dans le dossier du firmware souhaité (`Logiciel/GhostDrive/` ou `Logiciel/test_led/`).
2.  Passer la carte en mode Bootloader (Maintenir le bouton HWB, appuyer sur RESET, relâcher HWB).
3.  Lancer la compilation et le flashage :
    ```bash
    make clean
    make
    make dfu
    ```
