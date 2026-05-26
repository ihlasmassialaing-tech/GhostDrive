// ==========================================
//      MAPPAGE COMPLET CLAVIER AZERTY (FR)
// ==========================================

// ------------------------------------------
// 1. L'ALPHABET (Minuscules / Majuscules avec Shift)
// ------------------------------------------
#define FR_A  HID_KEYBOARD_SC_Q
#define FR_B  HID_KEYBOARD_SC_B
#define FR_C  HID_KEYBOARD_SC_C
#define FR_D  HID_KEYBOARD_SC_D
#define FR_E  HID_KEYBOARD_SC_E
#define FR_F  HID_KEYBOARD_SC_F
#define FR_G  HID_KEYBOARD_SC_G
#define FR_H  HID_KEYBOARD_SC_H
#define FR_I  HID_KEYBOARD_SC_I
#define FR_J  HID_KEYBOARD_SC_J
#define FR_K  HID_KEYBOARD_SC_K
#define FR_L  HID_KEYBOARD_SC_L
#define FR_M  HID_KEYBOARD_SC_SEMICOLON_AND_COLON
#define FR_N  HID_KEYBOARD_SC_N
#define FR_O  HID_KEYBOARD_SC_O
#define FR_P  HID_KEYBOARD_SC_P
#define FR_Q  HID_KEYBOARD_SC_A
#define FR_R  HID_KEYBOARD_SC_R
#define FR_S  HID_KEYBOARD_SC_S
#define FR_T  HID_KEYBOARD_SC_T
#define FR_U  HID_KEYBOARD_SC_U
#define FR_V  HID_KEYBOARD_SC_V
#define FR_W  HID_KEYBOARD_SC_Z
#define FR_X  HID_KEYBOARD_SC_X
#define FR_Y  HID_KEYBOARD_SC_Y
#define FR_Z  HID_KEYBOARD_SC_W

// ------------------------------------------
// 2. RANGÉE DES CHIFFRES (Haut du clavier)
// (⚠️ Chiffres = Shift actif / Symboles = Sans Shift)
// ------------------------------------------
#define FR_ESPERLUETTE      HID_KEYBOARD_SC_1_AND_EXCLAMATION // & (1 avec Shift)
#define FR_E_ACCENT_AIGU    HID_KEYBOARD_SC_2_AND_AT          // é (2 avec Shift, ~ avec AltGr)
#define FR_GUILLEMET        HID_KEYBOARD_SC_3_AND_HASHMARK    // " (3 avec Shift, # avec AltGr)
#define FR_APOSTROPHE       HID_KEYBOARD_SC_4_AND_DOLLAR      // ' (4 avec Shift, { avec AltGr)
#define FR_PARENTHESE_G     HID_KEYBOARD_SC_5_AND_PERCENTAGE  // ( (5 avec Shift, [ avec AltGr)
#define FR_TIRET            HID_KEYBOARD_SC_6_AND_CARET       // - (6 avec Shift, | avec AltGr)
#define FR_E_ACCENT_GRAVE   HID_KEYBOARD_SC_7_AND_AMPERSAND// è (7 avec Shift, ` avec AltGr)
#define FR_UNDERSCORE       HID_KEYBOARD_SC_8_AND_ASTERISK    // _ (8 avec Shift, \ avec AltGr)
#define FR_C_CEDILLE        HID_KEYBOARD_SC_9_AND_OPENING_PARENTHESIS // ç (9 avec Shift, ^ avec AltGr)
#define FR_A_ACCENT_GRAVE   HID_KEYBOARD_SC_0_AND_CLOSING_PARENTHESIS // à (0 avec Shift, @ avec AltGr)
#define FR_PARENTHESE_D     HID_KEYBOARD_SC_MINUS_AND_UNDERSCORE      // ) (° avec Shift, ] avec AltGr)
#define FR_EGAL             HID_KEYBOARD_SC_EQUAL_AND_PLUS            // = (+ avec Shift, } avec AltGr)

// ------------------------------------------
// 3. PONCTUATION ET SYMBOLES SPÉCIAUX (AZERTY)
// ------------------------------------------
#define FR_CARRE            HID_KEYBOARD_SC_GRAVE_ACCENT_AND_TILDE    // ² (Touche tout en haut à gauche)
#define FR_CHEVRON_G        HID_KEYBOARD_SC_NON_US_BACKSLASH_AND_PIPE // < (> avec Shift)
#define FR_VIRGULE          HID_KEYBOARD_SC_M                         // , (? avec Shift)
#define FR_POINT_VIRGULE    HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN  // ; (. avec Shift)
#define FR_DEUX_POINTS      HID_KEYBOARD_SC_DOT_AND_GREATER_THAN_SIGN // : (/ avec Shift)
#define FR_POINT_EXCLAMATION HID_KEYBOARD_SC_SLASH_AND_QUESTION_MARK  // ! (§ avec Shift)
#define FR_CIRCONFLEXE      HID_KEYBOARD_SC_LEFT_BRACKET_AND_LEFT_BRACE // ^ (¨ avec Shift)
#define FR_DOLLAR           HID_KEYBOARD_SC_RIGHT_BRACKET_AND_RIGHT_BRACE // $ (£ avec Shift, ¤ avec AltGr)
#define FR_U_ACCENT_GRAVE   HID_KEYBOARD_SC_APOSTROPHE_AND_QUOTE      // ù (% avec Shift)
#define FR_ASTERISQUE       HID_KEYBOARD_SC_BACKSLASH_AND_PIPE        // * (µ avec Shift)

// ------------------------------------------
// 4. TOUCHES DE CONTRÔLE ET NAVIGATION
// ------------------------------------------
#define FR_ESPACE           HID_KEYBOARD_SC_SPACE
#define FR_ENTREE           HID_KEYBOARD_SC_ENTER
#define FR_ECHAP            HID_KEYBOARD_SC_ESCAPE
#define FR_EFFACER          HID_KEYBOARD_SC_BACKSPACE
#define FR_TAB              HID_KEYBOARD_SC_TAB
#define FR_VERR_MAJ         HID_KEYBOARD_SC_CAPS_LOCK

#define FR_INSERER          HID_KEYBOARD_SC_INSERT
#define FR_SUPPRIMER        HID_KEYBOARD_SC_DELETE
#define FR_DEBUT            HID_KEYBOARD_SC_HOME
#define FR_FIN              HID_KEYBOARD_SC_END
#define FR_PAGE_PREC        HID_KEYBOARD_SC_PAGE_UP
#define FR_PAGE_SUIV        HID_KEYBOARD_SC_PAGE_DOWN

#define FR_FLECHE_D         HID_KEYBOARD_SC_RIGHT_ARROW
#define FR_FLECHE_G         HID_KEYBOARD_SC_LEFT_ARROW
#define FR_FLECHE_B         HID_KEYBOARD_SC_DOWN_ARROW
#define FR_FLECHE_H         HID_KEYBOARD_SC_UP_ARROW

// ------------------------------------------
// 5. PAVÉ NUMÉRIQUE (Numpad)
// ------------------------------------------
#define FR_NUM_VERR         HID_KEYBOARD_SC_NUM_LOCK
#define FR_NUM_DIVISER      HID_KEYBOARD_SC_KEYPAD_SLASH
#define FR_NUM_MULTIPLIER   HID_KEYBOARD_SC_KEYPAD_ASTERISK
#define FR_NUM_MOINS        HID_KEYBOARD_SC_KEYPAD_MINUS
#define FR_NUM_PLUS         HID_KEYBOARD_SC_KEYPAD_PLUS
#define FR_NUM_ENTREE       HID_KEYBOARD_SC_KEYPAD_ENTER
#define FR_NUM_POINT        HID_KEYBOARD_SC_KEYPAD_DOT_AND_DELETE
#define FR_NUM_1            HID_KEYBOARD_SC_KEYPAD_1_AND_END
#define FR_NUM_2            HID_KEYBOARD_SC_KEYPAD_2_AND_DOWN_ARROW
#define FR_NUM_3            HID_KEYBOARD_SC_KEYPAD_3_AND_PAGE_DOWN
#define FR_NUM_4            HID_KEYBOARD_SC_KEYPAD_4_AND_LEFT_ARROW
#define FR_NUM_5            HID_KEYBOARD_SC_KEYPAD_5
#define FR_NUM_6            HID_KEYBOARD_SC_KEYPAD_6_AND_RIGHT_ARROW
#define FR_NUM_7            HID_KEYBOARD_SC_KEYPAD_7_AND_HOME
#define FR_NUM_8            HID_KEYBOARD_SC_KEYPAD_8_AND_UP_ARROW
#define FR_NUM_9            HID_KEYBOARD_SC_KEYPAD_9_AND_PAGE_UP
#define FR_NUM_0            HID_KEYBOARD_SC_KEYPAD_0_AND_INSERT

// ------------------------------------------
// 6. TOUCHES F1 à F12
// ------------------------------------------
#define FR_F1               HID_KEYBOARD_SC_F1
#define FR_F2               HID_KEYBOARD_SC_F2
#define FR_F3               HID_KEYBOARD_SC_F3
#define FR_F4               HID_KEYBOARD_SC_F4
#define FR_F5               HID_KEYBOARD_SC_F5
#define FR_F6               HID_KEYBOARD_SC_F6
#define FR_F7               HID_KEYBOARD_SC_F7
#define FR_F8               HID_KEYBOARD_SC_F8
#define FR_F9               HID_KEYBOARD_SC_F9
#define FR_F10              HID_KEYBOARD_SC_F10
#define FR_F11              HID_KEYBOARD_SC_F11
#define FR_F12              HID_KEYBOARD_SC_F12

