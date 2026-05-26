/*
             LUFA Library
     Copyright (C) Dean Camera, 2021.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2021  Dean Camera (dean [at] fourwalledcubicle [dot] com)
  Copyright 2010  Matthias Hullin (lufa [at] matthias [dot] hullin [dot] net)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Main source file for the MassStorageKeyboard demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */

#include "MassStorageKeyboard.h"
#include "Dictionnaire.h"
#include "payload_amour.h"
#include "payload_prank.h"
#include "payload_insta.h"
#include <avr/pgmspace.h>

/** LUFA Mass Storage Class driver interface configuration and state information. This structure is
 *  passed to all Mass Storage Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */

USB_ClassInfo_MS_Device_t Disk_MS_Interface =
	{
		.Config =
			{
				.InterfaceNumber           = INTERFACE_ID_MassStorage,
				.DataINEndpoint            =
					{
						.Address           = MASS_STORAGE_IN_EPADDR,
						.Size              = MASS_STORAGE_IO_EPSIZE,
						.Banks             = 1,
					},
				.DataOUTEndpoint            =
					{
						.Address           = MASS_STORAGE_OUT_EPADDR,
						.Size              = MASS_STORAGE_IO_EPSIZE,
						.Banks             = 1,
					},
				.TotalLUNs                 = TOTAL_LUNS,
			},
	};

/** Buffer to hold the previously generated Keyboard HID report, for comparison purposes inside the HID class driver. */
static uint8_t PrevKeyboardHIDReportBuffer[sizeof(USB_KeyboardReport_Data_t)];

/** LUFA HID Class driver interface configuration and state information. This structure is
 *  passed to all HID Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_HID_Device_t Keyboard_HID_Interface =
 	{
		.Config =
			{
				.InterfaceNumber              = INTERFACE_ID_Keyboard,
				.ReportINEndpoint             =
					{
						.Address              = KEYBOARD_EPADDR,
						.Size                 = KEYBOARD_EPSIZE,
						.Banks                = 1,
					},
				.PrevReportINBuffer           = PrevKeyboardHIDReportBuffer,
				.PrevReportINBufferSize       = sizeof(PrevKeyboardHIDReportBuffer),
			},
    };

// Fonction pour configurer les broches au démarrage
void Init_Dip_Switch(void) {
    // 1. Configurer PB4 et PB5 en ENTRÉES (on met les bits à 0 dans le registre DDRB)
    DDRB &= ~((1 << PB4) | (1 << PB5));
    
    // 2. Activer les résistances de PULL-UP sur PB4 et PB5 (on met les bits à 1 dans PORTB)
    PORTB |= ((1 << PB4) | (1 << PB5));
}

// Fonction pour lire l'état du switch et renvoyer un chiffre de 0 à 3
uint8_t Lire_Programme(void) {
    uint8_t programme = 0;

    // On lit le registre PINB.
    // Attention : la logique est inversée ! Un switch fermé (ON) donne 0V.
    // On inverse donc la lecture avec '!' pour que Switch ON = 1.

    if (!(PINB & (1 << PB4))) { // Si PROG1 est à la masse
        programme |= 1;         // On met le bit 0 à 1 (Valeur +1)
    }

    if (!(PINB & (1 << PB5))) { // Si PROG2 est à la masse
        programme |= 2;         // On met le bit 1 à 1 (Valeur +2)
    }

    return programme; // Renvoie 0, 1, 2 ou 3 selon les switchs
}

/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();
    Init_Dip_Switch();
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	GlobalInterruptEnable();

	for (;;)
	{
		MS_Device_USBTask(&Disk_MS_Interface);
		HID_Device_USBTask(&Keyboard_HID_Interface);
		USB_USBTask();
	}
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
#if (ARCH == ARCH_AVR8)
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);
#elif (ARCH == ARCH_XMEGA)
	/* Start the PLL to multiply the 2MHz RC oscillator to 32MHz and switch the CPU core to run from it */
	XMEGACLK_StartPLL(CLOCK_SRC_INT_RC2MHZ, 2000000, F_CPU);
	XMEGACLK_SetCPUClockSource(CLOCK_SRC_PLL);

	/* Start the 32MHz internal RC oscillator and start the DFLL to increase it to 48MHz using the USB SOF as a reference */
	XMEGACLK_StartInternalOscillator(CLOCK_SRC_INT_RC32MHZ);
	XMEGACLK_StartDFLL(CLOCK_SRC_INT_RC32MHZ, DFLL_REF_INT_USBSOF, F_USB);

	PMIC.CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;
#endif

	/* Hardware Initialization */
	LEDs_Init();
	Joystick_Init();
	Buttons_Init();
	//Dataflash_Init();
	USB_Init();

	/* Check if the Dataflash is working, abort if not */
	/*if (!(DataflashManager_CheckDataflashOperation()))
	{
		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
		for(;;);
	}
    */
	/* Clear Dataflash sector protections, if enabled */
	//DataflashManager_ResetDataflashProtections();
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	ConfigSuccess &= HID_Device_ConfigureEndpoints(&Keyboard_HID_Interface);
	ConfigSuccess &= MS_Device_ConfigureEndpoints(&Disk_MS_Interface);

	USB_Device_EnableSOFEvents();

	LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
	MS_Device_ProcessControlRequest(&Disk_MS_Interface);
	HID_Device_ProcessControlRequest(&Keyboard_HID_Interface);
}

/** Mass Storage class driver callback function the reception of SCSI commands from the host, which must be processed.
 *
 *  \param[in] MSInterfaceInfo  Pointer to the Mass Storage class interface configuration structure being referenced
 */
/*bool CALLBACK_MS_Device_SCSICommandReceived(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo)
{
	bool CommandSuccess;

	LEDs_SetAllLEDs(LEDMASK_USB_BUSY);
	CommandSuccess = SCSI_DecodeSCSICommand(MSInterfaceInfo);
	LEDs_SetAllLEDs(LEDMASK_USB_READY);

	return CommandSuccess;
}*/

/** Event handler for the USB device Start Of Frame event. */
void EVENT_USB_Device_StartOfFrame(void)
{
    HID_Device_MillisecondElapsed(&Keyboard_HID_Interface);
}

/** HID class driver callback function for the creation of HID reports to the host.
 *
 *  \param[in]     HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in,out] ReportID    Report ID requested by the host if non-zero, otherwise callback should set to the generated report ID
 *  \param[in]     ReportType  Type of the report to create, either HID_REPORT_ITEM_In or HID_REPORT_ITEM_Feature
 *  \param[out]    ReportData  Pointer to a buffer where the created report should be stored
 *  \param[out]    ReportSize  Number of bytes written in the report (or zero if no report is to be sent)
 *
 *  \return Boolean \c true to force the sending of the report, \c false to let the library determine if it needs to be sent
 */
bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                         uint8_t* const ReportID,
                                         const uint8_t ReportType,
                                         void* ReportData,
                                         uint16_t* const ReportSize)
{
	USB_KeyboardReport_Data_t* KeyboardReport = (USB_KeyboardReport_Data_t*)ReportData;

    static uint8_t etat = 0;
    static uint16_t delai = 0;
    static uint8_t programme_choisi = 0; 
    // Pour savoir où on en est dans notre tableau
    static uint16_t index_payload = 0;


    // Délai initial de sécurité pour laisser l'OS reconnaître la clé
    if (delai < 1000 && etat == 0) {
        programme_choisi = Lire_Programme(); // On lit les switchs pendant la pause
        delai++;
        *ReportSize = sizeof(USB_KeyboardReport_Data_t);
        return false;
    }
    switch(programme_choisi){
        /* ============================
                  PROGRAMME 00
           ============================ */
        case 0:
            switch(etat) {
                case 0:
                    // Raccourci d'ouverture du terminal : Ctrl + Alt + T
                    KeyboardReport->Modifier = (HID_KEYBOARD_MODIFIER_LEFTCTRL | HID_KEYBOARD_MODIFIER_LEFTALT);
                    KeyboardReport->KeyCode[0] = FR_T;
                    etat++;
                    delai = 0; // Réinitialisation du délai pour la prochaine pause
                    break;

                case 1:
                    // Relâchement obligatoire des touches
                    KeyboardReport->Modifier = 0;
                    KeyboardReport->KeyCode[0] = 0;
                    etat++;
                    break;

                case 2:
                    // Pause pour laisser le temps au terminal de s'ouvrir à l'écran
                    if (delai < 500) {
                        delai++;
                    } else {
                        etat++;
                    }
                    break;

                case 3:
                    // Appui sur 'P'
                    KeyboardReport->KeyCode[0] = FR_P;
                    etat++;
                    break;

                case 4:
                    // Relâchement (bonne pratique entre chaque lettre)
                    KeyboardReport->KeyCode[0] = 0;
                    etat++;
                    break;

                case 5:
                    // Appui sur 'W' (La macro se charge de la conversion AZERTY matérielle)
                    KeyboardReport->KeyCode[0] = FR_W; 
                    etat++;
                    break;

                case 6:
                    // Relâchement
                    KeyboardReport->KeyCode[0] = 0;
                    etat++;
                    break;

                case 7:
                    // Appui sur 'D'
                    KeyboardReport->KeyCode[0] = FR_D;
                    etat++;
                    break;
                    
                case 8:
                    // Relâchement
                    KeyboardReport->KeyCode[0] = 0;
                    etat++;
                    break;

                case 9:
                    // Validation de la commande (Entrée)
                    KeyboardReport->KeyCode[0] = FR_ENTREE;
                    etat++;
                    break;

                case 10:
                    // Relâchement final et fin de séquence
                    KeyboardReport->KeyCode[0] = 0;
                    etat++;
                    break;

                default:
                    // L'automate reste ici indéfiniment une fois la séquence terminée
                    break;
            }
            break;
        /* ============================
                  PROGRAMME 01
           ============================ */
        case 1:
            switch(etat) {
                case 0:
                    // Raccourci d'ouverture du terminal : Ctrl + Alt + T
                    KeyboardReport->Modifier = (HID_KEYBOARD_MODIFIER_LEFTCTRL | HID_KEYBOARD_MODIFIER_LEFTALT);
                    KeyboardReport->KeyCode[0] = FR_T;
                    etat++;
                    delai = 0; // Réinitialisation du délai pour la prochaine pause
                    break;

                case 1:
                    // Relâchement obligatoire des touches
                    KeyboardReport->Modifier = 0;
                    KeyboardReport->KeyCode[0] = 0;
                    etat++;
                    break;

                case 2:
                    // Pause pour laisser le temps au terminal de s'ouvrir à l'écran
                    if (delai < 1000) {
                        delai++;
                    } else {
                        etat++;
                    }
                    break;

                case 3:
                    // ETAT D'APPUI : On lit le tableau généré
                    if (index_payload < payload_prank_len) {
                        // On charge la touche et le modificateur depuis le fichier .h
                        KeyboardReport->Modifier = pgm_read_byte(&payload_prank[index_payload].modifier);
                        KeyboardReport->KeyCode[0] = pgm_read_byte(&payload_prank[index_payload].keycode);
                        etat++; // On passe à l'état de relâchement
                    } else {
                        // Si l'index a atteint la taille max, on a fini !
                        etat = 5; // On saute à l'état final
                    }
                    break;

                case 4:
                    // ETAT DE RELÂCHEMENT : Obligatoire pour simuler la frappe
                    KeyboardReport->Modifier = 0;
                    KeyboardReport->KeyCode[0] = 0;
                    
                    index_payload++; // On avance à la lettre suivante pour le prochain tour
                    etat = 3;        // On retourne à l'état 3 pour créer une boucle !
                    break;

                default:
                    // L'automate reste ici indéfiniment une fois la séquence terminée
                    break;
            }
            break;
        /* ============================
                  PROGRAMME 10
           ============================ */
        case 2:
            switch(etat) {
                case 0:
                    // Raccourci d'ouverture du terminal : Ctrl + Alt + T
                    KeyboardReport->Modifier = (HID_KEYBOARD_MODIFIER_LEFTCTRL | HID_KEYBOARD_MODIFIER_LEFTALT);
                    KeyboardReport->KeyCode[0] = FR_T;
                    etat++;
                    delai = 0; // Réinitialisation du délai pour la prochaine pause
                    break;

                case 1:
                    // Relâchement obligatoire des touches
                    KeyboardReport->Modifier = 0;
                    KeyboardReport->KeyCode[0] = 0;
                    etat++;
                    break;

                case 2:
                    // Pause pour laisser le temps au terminal de s'ouvrir à l'écran
                    if (delai < 1000) {
                        delai++;
                    } else {
                        delai = 0;
                        etat++;
                    }
                    break;

                case 3:
                    // ETAT D'APPUI : On lit le tableau généré
                    if (index_payload < payload_amour_len) {
                        // On charge la touche et le modificateur depuis le fichier .h
                        KeyboardReport->Modifier = pgm_read_byte(&payload_amour[index_payload].modifier);
                        KeyboardReport->KeyCode[0] = pgm_read_byte(&payload_amour[index_payload].keycode);
                        etat++; // On passe à l'état de relâchement
                    } else {
                        // Si l'index a atteint la taille max, on a fini !
                        etat = 5; // On saute à l'état final
                    }
                    break;

                case 4:
                    // ETAT DE RELÂCHEMENT : Obligatoire pour simuler la frappe
                    KeyboardReport->Modifier = 0;
                    KeyboardReport->KeyCode[0] = 0;
                    
                    index_payload++; // On avance à la lettre suivante pour le prochain tour
                    etat = 3;        // On retourne à l'état 3 pour créer une boucle !
                    break;

                case 5:
                    // Pause 
                    if (delai < 20000) {
                        delai++;
                    } else {
                        delai = 0;
                        etat++;
                    }
                    break;

                case 6:
                    // Ctrl + C 
                    KeyboardReport->Modifier = HID_KEYBOARD_MODIFIER_LEFTCTRL; 
                    KeyboardReport->KeyCode[0] = FR_C;
                    etat++;
                    break;

                case 7:
                    // Relâchement obligatoire des touches
                    KeyboardReport->Modifier = 0;
                    KeyboardReport->KeyCode[0] = 0;
                    index_payload = 0; // on remet l'indice à 0 pour lire le prochain payload
                    etat++;
                    break;

                case 8:
                    // ETAT D'APPUI : On lit le tableau généré
                    if (index_payload < payload_insta_len) {
                        // On charge la touche et le modificateur depuis le fichier .h
                        KeyboardReport->Modifier = pgm_read_byte(&payload_insta[index_payload].modifier);
                        KeyboardReport->KeyCode[0] = pgm_read_byte(&payload_insta[index_payload].keycode);
                        etat++; // On passe à l'état de relâchement
                    } else {
                        // Si l'index a atteint la taille max, on a fini !
                        etat = 10; // On saute à l'état final
                    }
                    break;

                case 9:
                    // ETAT DE RELÂCHEMENT : Obligatoire pour simuler la frappe
                    KeyboardReport->Modifier = 0;
                    KeyboardReport->KeyCode[0] = 0;
                    
                    index_payload++; // On avance à la lettre suivante pour le prochain tour
                    etat = 8;        // On retourne à l'état 3 pour créer une boucle !
                    break;
          
                case 10:
                    // Pause 
                    if (delai < 5000) {
                        delai++;
                    } else {
                        delai = 0;
                        etat++;
                    }
                    break;

                case 11:
                    KeyboardReport->Modifier = 0;
                    KeyboardReport->KeyCode[0] = FR_ECHAP;
                    etat++;
                    break;
                default:
                    // L'automate reste ici indéfiniment une fois la séquence terminée
                    break;
            }
            break;
        
        /* ============================
                  PROGRAMME 11
           ============================ */
        case 3:
            KeyboardReport->Modifier = 0;
            KeyboardReport->KeyCode[0] = 0;
            break;

            /* ============================
             SÉCURITÉ : CAS IMPOSSIBLE
           ============================ */
        default:
            // Si la variable est corrompue ou vaut 4, 5, etc.
            // On relâche tout par sécurité.
            KeyboardReport->Modifier = 0;
            KeyboardReport->KeyCode[0] = 0;
            break;
    }


	*ReportSize = sizeof(USB_KeyboardReport_Data_t);
	return false;
}

/** HID class driver callback function for the processing of HID reports from the host.
 *
 *  \param[in] HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in] ReportID    Report ID of the received report from the host
 *  \param[in] ReportType  The type of report that the host has sent, either HID_REPORT_ITEM_Out or HID_REPORT_ITEM_Feature
 *  \param[in] ReportData  Pointer to a buffer where the received report has been stored
 *  \param[in] ReportSize  Size in bytes of the received HID report
 */
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                          const uint8_t ReportID,
                                          const uint8_t ReportType,
                                          const void* ReportData,
                                          const uint16_t ReportSize)
{
	uint8_t  LEDMask   = LEDS_NO_LEDS;
	uint8_t* LEDReport = (uint8_t*)ReportData;

	if (*LEDReport & HID_KEYBOARD_LED_NUMLOCK)
	  LEDMask |= LEDS_LED1;

	if (*LEDReport & HID_KEYBOARD_LED_CAPSLOCK)
	  LEDMask |= LEDS_LED3;

	if (*LEDReport & HID_KEYBOARD_LED_SCROLLLOCK)
	  LEDMask |= LEDS_LED4;

	LEDs_SetAllLEDs(LEDMask);
}




// Ce callback remplace toute la logique matérielle complexe.
// Il dit simplement "Non" à toutes les requêtes de l'ordinateur.
bool CALLBACK_MS_Device_SCSICommandReceived(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo)
{
    // On indique à LUFA et à l'ordinateur que la commande ne peut pas aboutir.
    // L'ordinateur comprendra que le lecteur est vide.
    return false;
}
