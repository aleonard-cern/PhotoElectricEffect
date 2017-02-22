# GUI for the Photoelectric Effect Experiment

## Introduction
This application provides a graphical user interface to the electrometer Keithley 6517A device. This device allows the user to scan different output voltage while measuring the current at the same time. The Keithley is connect to a computer via RS-232 serial line.


## Requirements:
The GUI is based on the Qt framework.

1. Ubuntu 14.04 or later 
2. Qt5.7 or later (type "qmake -v" to see if the right Qt is installed)

## Installation:
1. git clone https://github.com/aleonard-cern/PhotoElectricEffect.git
2. cd PhotoElectricEffect
3. qmake
4. make
5. sudo make install


