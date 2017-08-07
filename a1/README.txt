
CS221 Project 1

Student1: n3l0b; Hyung Ro Lee; 49806102
Student2: l3k0b; Jimin Jeon  ; 24832140

List of files:
LQueue_driver.C
LQueue.C
LQueue.h
Makefile
README.txt
runway.C
runway1.C (this is a only one runway version - simply switch the file name to run)
sample_outputfile_part1.txt 
sample_outputfile_part2_runway.txt   (sample output file of the file using two runways)

NOTE: ‘make’ will create both runway / LQueue_driver (runnable files) by default

NOTES about each part:

1. LQueue_driver

- LQueue_driver will first ask which number to move to front and if the number is not in the queue, it will do nothing.
- Subsequently, it will merge q1 with q3 where the queue is hardcoded.
(ASSUMPTION: each queue is sorted before merged)


2. runway 

- extra added functions: merge_two_queues and move_to_front
- runway is consist of two parts, 1) using 2 runways, 2) using 1 runway
- The program will ask to choose how many runways to manage, 
if pressed 1, program will run within switch case 1
if pressed 2, program will run within switch case 2
NOTE: in the main function, case 2 is before case 1

- the closed runway will automatically open after the duration of timeToReopen
- When the simulation time is done, it will not generate planes any more but program will continue to run until the queues are empty


3. runway1

- extra added function: move_to_front
- using 1 runway
- if there is plane in emergency to land, that plane will be moved to the front of the landing queue.
- When the simulation time is done, it will not generate planes any more but program will continue to run until the queues are empty 

