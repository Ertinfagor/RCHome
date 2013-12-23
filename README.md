SensorBoard
===========

Arduino Sensor Board with nRF24l01 Control

The board based on AVR microcontroller with Arduino bootloader.

SensorBoard will transmit/recieve data from/to SmartHome Controller with nRF24l01 (Repo will be added)

Goals:
Send temperature
Send humidity
Send luminosity
Send lampN status
Recieve lampN status from nRF24l01 (switch on/off)
Recieve lampN status from Switch (switch on/off)

Packet definition:
Packet size - 32byte
0 - address of sender 
1 - command 
2 - command parameters 
3 - Temperature
4 - Humidity
5 - Luminosity
6 - Lamp status (Lamp N where N is nmber of lamp - max 8 lamp)
7 - Switch status (Switch N where N is nmber of switch - max 8 switch)
8-32 - reserved fo future use (Values 0xFF)

Commands:
0 - send status:
      send all parameters e.g. Temperature,Humidity,Luminosity,Lamp status,Switch status 
      Command status 0xFF
1 - Switch ON Lamp N
      where N is 1 - bit position in command parameters
      Send byte 5,6 status other bytes is 0xFF
2 - Switch OFF Lamp N
      where N is 1 - bit position in command parameters
      Send byte 5,6 status other bytes is 0xFF
      
      
