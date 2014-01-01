RCHome

Suite for lighting control and monitoring of the main parameters in the rooms

Hardware:
SensorBoard sensor module based on the Arduino Leonardo and nRF24l01+
Goals:
	Control switches
	Sensor readings
	Receiving commands via radio to ControlBorad
	Transmission of the sensors via radio to ControlBorad

ControlBoard control module based on Raspberry Pi and nRF24l01+
Goals:
	Periodic collection of sensor readings from all SensorBoard
	Transmitting control commands to all SensorBoard
	Keeping all the readings the database
	Providing API to display readings and control switches
	Providing Web-based interface to display readings and control switches