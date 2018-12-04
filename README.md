QBoat voice control relay and get temperature,humidity value
=======

This project is use QBoat Sunny connect microphone and speaker integrate QIoT Suite Lite and Dialogflow(api.ai) to control Linkit 7697 + Relay and get temperature, humidity value of DHT11.

## Create Ubuntu LXC container in QBoat Sunny

-   Install the latest Container Station on your QBoat Sunny by following the instructions in the ["How to use Container Station?"](https://www.qnap.com/en/how-to/tutorial/article/how-to-use-container-station).

-   Create "Ubuntu 14.04.1 LTS" LXC container in Container Station and start it.
-   Into Terminal two options :
    -   Open a PuTTY session and connect to the device use SSH. Then key in command : 
        
            lxc-console -n <your container name>

    -   Or find nearby "Console" on container station website and click icon to enter terminal

## Mount sound device to container

Reference : https://www.qnap.com/go/how-to/tutorial/article/how-to-use-speakers-when-using-qboat-sunny-an-lxc-example

## Install Python to Container

    apt update
    apt install python python-pip 

## Dependencies in Container

Need to install this list:

1. [SpeechRecognition](https://github.com/Uberi/speech_recognition)
2. [eSpeak](http://espeak.sourceforge.net/)
3. [PyAudio](https://people.csail.mit.edu/hubert/pyaudio/)
4. paho-mqtt of python

## Install Module to QIoT Suite Lite Node-Red

Install [node-red-contrib-apiai](https://flows.nodered.org/node/node-red-contrib-apiai) in QIoT Suite Lite Node-Red

Reference : [How to install other modules in QIoT Suite Lite NodeRED?](https://www.qnap.com/en/how-to/tutorial/article/how-to-install-other-modules-in-qiot-suite-lite-nodered)

## Start

 1. Copy "speak" floder to container
 2. Import IoT Application "QIoT_export/MQTTHome.json" to QIoT Suite Lite, Reference : [How to Backup QIoT Suite Lite](https://www.qnap.com/en/how-to/tutorial/article/how-to-backup-qiot-suite-lite)
 3. Generate MQTT connect information and edit "resourceinfo.json" change IP to "10.0.3.1" then copy to container in "speak/res/" folder. Generate "resourceinfo.json" reference : [How to connect to QIoT Suite Lite using MQTT?
](https://www.qnap.com/en/how-to/tutorial/article/how-to-connect-to-qiot-suite-lite-using-mqtt)
 4. Edit api.ai and key in Dialogflow api key and save in QIoT Suite Lite Rule
 5. Upload "speak" folder to container and change folder to "speak". 
 6. Run `python mqtt.py` in container
 6. Then click `Start` in speak flow of QIoT Suite Lite rule, then you can speak to control.

## Authors

It was created by [QNAP Systems, Inc.](https://www.qnap.com/en/index.php)

 - Linkit 7697 code : Laisan 
 - Python code & QIoT Suite Lite Flow : Tim Hsu

Thanks to the authors of each libraries.
