#! /usr/bin/bash 

Black='\033[0;30m'
Red='\033[0;31m'
Green='\033[0;32m'
Brown='\033[0;33m'
Blue='\033[0;34m'
Purple='\033[0;35m'
Cyan='\033[0;36m'
LightGray='\033[0;37m'
DarkGray='\033[1;30m'
LightRed='\033[1;31m'
LightGreen='\033[1;32m'
Yellow='\033[1;33m'
LightBlue='\033[1;34m'
LightPurple='\033[1;35m'
LightCyan='\033[1;36m'
White='\033[1;37m'
NC='\033[0m'

clear
printf "${LightPurple}Do you want to run cmake?${NC}\n" 
printf "Enter [${Green}d${NC}] to not run cmake with debug (${Yellow}default${NC})\n"
printf "Enter [${Green}r${NC}] to not run cmake with released\n"
printf "Enter [${Green}n${NC}] to not run cmake\n"
read -p "Enter your choice: " choice

clear 
cmake_status=0
if [ "$choice" = "d" ] || [ "$choice" = "D" ];
then
    cmake -S src/ -B build/ -DCMAKE_BUILD_TYPE=Debug
    cmake_status=$?
elif [ "$choice" = "r" ] || [ "$choice" = "R" ];
then
    cmake -S src/ -B build/ -DCMAKE_BUILD_TYPE=Released
    cmake_status=$?
elif [ "$choice" = "n" ] || [ "$choice" = "N" ];
then
    printf ""
else
    cmake -S src/ -B build/ -DCMAKE_BUILD_TYPE=Debug
    cmake_status=$?
fi 

if [ "$cmake_status" -eq 0 ] && [ "$choice" != "n" ] && [ "$choice" != "N" ];
then
  printf "${Green}Successfully cmake\n${NC}"
else
  printf "${Red}Cmake fail${NC}\n" 
  printf "Cmake return value: ${Red}$cmake_status${NC}"
  exit 1
fi

printf "${Yellow}Press enter to continue\n${NC}"
read -p ""
clear

make -C build
make_status=$?

if [ "$make_status" -eq 0 ];
then 
    printf "${Green}Successfully make\n${NC}"
else
    printf "${Red}Make fail${NC}\n" 
    printf "Make return value: ${Red}$make_status${NC}"
    exit 1
fi 

printf "${Yellow}Press enter to continue\n${NC}"
read -p ""
clear

konsole -e "zsh -c \"gdb build/CLM && local_pause\""
