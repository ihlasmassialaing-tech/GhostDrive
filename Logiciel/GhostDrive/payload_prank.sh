#!/bin/bash

clear
printf '\033[?25l'   # cache le curseur

echo -e "\e[40m"
echo -e "\e[1;31m=========================================\e[0m"
echo -e "\e[1;31m        CRITICAL SYSTEM FAILURE         \e[0m"
echo -e "\e[1;31m=========================================\e[0m"

sleep 1

echo
echo "[ OK ] Boot sequence initialized"
sleep 0.7
echo "[ OK ] Loading kernel modules"
sleep 0.7
echo "[ OK ] Checking system memory"
sleep 0.7

echo
echo -e "\e[1;33mStarting deep memory scan...\e[0m"
sleep 1

for i in {1..100}
do
    printf "\rScanning sectors: %d%%" "$i"
    sleep 0.03
done

echo
sleep 1

echo
echo -e "\e[1;31m[ WARNING ] Unauthorized activity detected\e[0m"
sleep 1

notify-send -u critical "SYSTEM ALERT" "Suspicious activity detected"

sleep 1

echo
echo "Attempting automatic recovery..."
sleep 1

for i in {1..100}
do
    printf "\rRestoring corrupted files: %d%%" "$i"
    sleep 0.025
done

echo
sleep 1

echo
echo -e "\e[1;31mRecovery failed.\e[0m"
sleep 1

notify-send -u critical "KERNEL PANIC" "Memory corruption detected"

sleep 1

echo
echo "Disconnecting suspicious processes..."
sleep 2

clear

echo
echo -e "\e[1;32mSYSTEM STABILIZED\e[0m"
echo -e "\e[1;32mNo permanent damage detected\e[0m"

printf '\033[?25h'   # remet le curseur
