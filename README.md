# Crash-Report
Repo about my implementation of N-Modular Redundancy on Vehicle Accident Report System

Vehicles are one of the necessities needed by humans at this time, especially in Indonesia, 
where the number of vehicle accidents is quite large, especially in remote areas, and far from health facilities. 
For that we need a vehicle accident report system, which is reliable and accurate. The tool must be able to detect accidents accurately,
and be able to send messages to the victim's family. 

However, in an accident, the vehicle will be in a condition that can cause damage to components or modules as a whole. 
These problems can cause the device to be unable to detect accidents. 
Therefore, the system must be equipped with the N-Modular Redundancy method, as a method to disguise errors that occur in the module and allow the tool to continue to work, 
even if there is damage. 

N-Modular Redundancy or NMR is a method based on the principle of the Triple Modular Redundancy or TMR method, 
but this method uses "N" modules instead of three as in TMR. (Elena Dubrova, 2013). 
The system consists of 3 MPU-6050 sensors as vehicle tilt sensors, 1 TC9548A module as a hardware fault tolerant implementation, 1 Arduino Nano as a microcontroller, 
and 1 NodeMCU ESP8266 as a message sender. 

From the test results, the tool has a reliability value of 95%, and a failure rate value of 0.24%, 
and is able to run 50% more test cycles than identical tools that do not have a reliability function. The results of the tool process will be displayed in the e-mail. 

In the future, hopefully there will be a development on this system in threms of the tool be able to detect wheter the vehicle is on an accident or the vehicle just fall on it's own
in a safe situation, ex: Parking, Stopping. Also will be a development for the message delivery system that make the warning system more effectively,
and also be able to send a message to ambulance or hospital services, so first response can come more quickly, 
and a data storage system that can help the authorities to investigate the accident that occured.
