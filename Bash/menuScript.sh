#!/bin/sh
clear
echo "Please pick from one of the following option:"
echo "1: Display info about the CPU"
echo "2: Display the loadavg of the sytem"
echo "3: Get a process PID running on the system and its status"
echo "4: Exit"

read userAnswer

if [userAnswer = 1]; then
        cat /proc/cpuinfo
if [userAnswer = 2]; then
        cat /proc/loadavg
if [userAnswer = 3]; then
        echo "not finished
if [userAnswer = 4]; then
        exit
else
        echo "Not a valid Command"
        goExit

