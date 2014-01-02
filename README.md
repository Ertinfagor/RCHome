RCHome

Suite for lighting control and monitoring of the main parameters in the rooms

Hardware:
SensorBoard sensor module based on the Arduino Leonardo and nRF24l01+
Version 1 goals:
	* Control switches(in progress...)
	* Sensor readings(in progress...)
	* Receiving commands via radio to ControlBorad(in progress...)
	* Transmission of the sensors via radio to ControlBorad(in progress...)

ControlBoard control module based on Raspberry Pi and nRF24l01+
Version 1 goals:
	* Periodic collection of sensor readings from all SensorBoard(in progress...)
	* Transmitting control commands to all SensorBoard(in progress...)
	* Keeping all the readings the database(in progress...)
	* Providing API to display readings and control switches(in progress...)
	* Providing Web-based interface to display readings and control switches(in progress...)