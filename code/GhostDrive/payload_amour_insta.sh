#!/bin/bash

# Capture le signal Ctrl+C pour réafficher le curseur et quitter proprement
trap 'tput cnorm; echo -e "\n\033[0mFin de la séquence."; exit 0' SIGINT

# Définition des couleurs
RED='\033[38;5;196m'
PINK='\033[38;5;213m'
WHITE='\033[1;37m'

# Cache le curseur de la console et efface l'écran
tput civis
clear

# 1. Séquence de démarrage (effet machine à écrire)
echo -e "${PINK}"
texte="[INFO] Initialisation du protocole romantique..."
for ((i=0; i<${#texte}; i++)); do echo -n "${texte:$i:1}"; sleep 0.03; done
echo ""
sleep 0.5

texte="[INFO] Contournement des pare-feux émotionnels... OK."
for ((i=0; i<${#texte}; i++)); do echo -n "${texte:$i:1}"; sleep 0.03; done
echo ""
sleep 0.5

texte="[INFO] Cible verrouillée. Exécution du payload..."
for ((i=0; i<${#texte}; i++)); do
    echo -n "${texte:$i:1}"
    sleep 0.05
done
sleep 1

clear

# 2. Boucle d'animation du cœur qui bat (pendant 12 secondes)
# 12 secondes avec des pauses de 0.5s par état = 12 cycles complets (24 battements)
for ((cycle=1; cycle<=10; cycle++)); do

    # État 1 : Grand Cœur (Rouge)
    tput cup 2 0
    echo -e "${RED}"
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
    sleep 0.5

    # État 2 : Petit Cœur (Rose)
    tput cup 2 0
    echo -e "${PINK}"
    echo -e "                                  \033[K"
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
    sleep 0.5
done

# 3. Fin de l'animation et transition vers le navigateur
tput cnorm # Réaffiche le curseur
clear
echo -e "${WHITE}[INFO] Redirection en cours... Enjoy ! ${PINK}❤️"
sleep 1.5

# Ouvre Firefox en tâche de fond (le & permet de libérer le terminal)
# REMPLACE PAR TON PROPRE LIEN INSTAGRAM ICI :
firefox "https://www.instagram.com/ihlas_374/" &

exit 0
