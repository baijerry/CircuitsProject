# CircuitsProject
Final Project for Circuits (SYDE 292) - Software component

Signal filtering circuit for transmission of data over human skin. Arduino programs responsible for sending and receiving the data, hardware circuit provides filtering and amplification to allow signal transmission. 

Setup:
-2 Arduino boards send data simutaneously to a metal wrist bracelet
-Signal is picked up by second wrist bracelet during handshake.
-Hardware circuit filters and amplifies signal
-Signal is read by receiving program

Tx program
-2 modes: Select either slave or master
-2 types of transmission: URL or channel (sends an "AB" or "BA").
-Master mode: sends signal to slave to coordinate sending of signal, then sends on channel 1
-Slave mode: recieves prompt from master, sends data according to what master selected on channel 2
    -If URL: master sends url, slave silent
    -If AB: master sends A, slave sends B
    -if BA: master sends B, slave sends A
-Channel 1 (Master) transmits at 600Hz
-Channel 2 (Slave) transmits at 6000Hz

Rx program
-2 modes: URL and channel
-URL mode: Read and displays from URL pin, ignores Channel pins
-Channel mode: Ignores URL pin, reads in from Channel Pins, displayes the data from each channel. 