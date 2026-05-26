#!/bin/bash

# Capture le signal Ctrl+C pour réafficher le curseur et quitter proprement
trap 'tput cnorm; echo -e "\n\033[0mArrêt du protocole. À bientôt !"; exit 0' SIGINT

# Définition des couleurs
RED='\033[38;5;196m'
PINK='\033[38;5;213m'
WHITE='\033[1;37m'

# Cache le curseur de la console et efface l'écran
tput civis
clear

# 1. Séquence de démarrage stylée (effet machine à écrire)
echo -e "${PINK}"
texte="[INFO] Initialisation du protocole romantique..."
for ((i=0; i<${#texte}; i++)); do
    echo -n "${texte:$i:1}"
    sleep 0.04
done
echo ""

texte="[INFO] Contournement des pare-feux émotionnels... OK."
for ((i=0; i<${#texte}; i++)); do
    echo -n "${texte:$i:1}"
    sleep 0.03
done
echo ""

texte="[INFO] Cible verrouillée. Exécution du payload..."
for ((i=0; i<${#texte}; i++)); do
    echo -n "${texte:$i:1}"
    sleep 0.05
done
sleep 1

clear

# 2. Boucle d'animation du cœur qui bat
while true; do
    # Positionne le curseur en haut (ligne 2, colonne 0)
    tput cup 2 0

    # État 1 : Grand Cœur (Rouge)
    echo -e "${RED}"
    # Le \033[K à la fin de chaque ligne permet d'effacer les restes de l'ancienne image
    echo -e "           ███████    ███████\033[K"
    echo -e "        ███████████  ███████████\033[K"
    echo -e "      ████████████████████████████\033[K"
    echo -e "      ████████████████████████████\033[K"
    echo -e "      ████████${WHITE} I LOVE YOU ${RED}████████\033[K"
    echo -e "      ████████████████████████████\033[K"
    echo -e "        ████████████████████████\033[K"
    echo -e "          ████████████████████\033[K"
    echo -e "            ████████████████\033[K"
    echo -e "              ████████████\033[K"
    echo -e "                ████████\033[K"
    echo -e "                  ████\033[K"
    echo -e "                   ██\033[K"
    echo -e "\n  ${WHITE}(Appuyez sur Ctrl+C pour quitter)\033[K"

    sleep 0.5

    # Positionne à nouveau le curseur au même endroit
    tput cup 2 0

    # État 2 : Petit Cœur (Rose)
    echo -e "${PINK}"
    echo -e "                                  \033[K" # Ligne vide pour la contraction
    echo -e "            █████      █████\033[K"
    echo -e "         █████████    █████████\033[K"
    echo -e "       ██████████████████████████\033[K"
    echo -e "       ██████████████████████████\033[K"
    echo -e "       ███████${WHITE} I LOVE YOU ${PINK}███████\033[K"
    echo -e "        ████████████████████████\033[K"
    echo -e "          ████████████████████\033[K"
    echo -e "            ████████████████\033[K"
    echo -e "              ████████████\033[K"
    echo -e "                ████████\033[K"
    echo -e "                  ████\033[K"
    echo -e "                   ██\033[K"
    echo -e "\n  ${WHITE}(Appuyez sur Ctrl+C pour quitter)\033[K"

    sleep 0.5
done
