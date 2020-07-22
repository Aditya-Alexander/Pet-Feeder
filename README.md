# Pet Feeder :dog:

![Project](https://img.shields.io/badge/Project-Pet%20Feeder-red?logo=github)
![Build](https://img.shields.io/badge/build-passing-brightgreen.svg)
![Made With Arduino](https://img.shields.io/badge/Made%20With-Arduino-yellow.svg)
[![GitHub stars](https://img.shields.io/github/stars/Aditya-Alexander/Pet-Feeder.svg?logo=github)](https://github.com/Aditya-Alexander/Pet-Feeder/stargazers)

<p align="center">
<img width=300px  src="https://graphicriver.img.customer.envatousercontent.com/files/270440720/CartoonDogPointer%20p.jpg?auto=compress%2Cformat&q=80&fit=crop&crop=top&max-h=8000&max-w=590&s=d7ccf47eef9f9a8f679c134cc70bffa5" alt="Image of a Dog">
</p>

---
> Automated Pet Feeder, Because They're not just pets, they're family.
---


## Features

The proposed system is about pet feeding when all people of nuclear family members are busy at work for the survival in the metro cities and other cities. The proposed system will be particularly useful for those people who have to worry about leaving their pets alone at home while going out. The system ensures the pets always remain fed and healthy even when the owner is not at home. The implementation is in 2 modes: `AUTOMATIC` and `MANUAL`. Automatic mode consists of `PIR sensor` and `SERVO motor`. As the pet travels towards the food bowl, `PIR sensor` detects its motion, the `SERVO motor` gets activated immediately and it serves the food. In manually operated mode, an app called `Blynk` has been installed in cell phones. Basically, `Blynk` is a digital dashboard where a graphic interface can be built by simply dragging and dropping widgets. Here there is a use of a button. As the button is clicked, data is sent through the cloud, goes on to the `ESP8266` which is connected to the model and then it serves the food. `RTC widget` is a clock used to retrieve real time from server. The time input is used to take the time from the user. Here, user enters the time, it goes to the server, then through `ESP8266` it goes to the model, it compares the real time data obtained from the server to the time entered by the user. It is a `24-hour format`. If the time matches then it serves the food. Food level is known through `Ultrasonic sensor` and the level is shown on the app.

## Circuit Diagram

### Components:
- Arduino MEGA
- ESP8266 WIFI Module
- Voltage Regulator
- PIR Sensor
- Servo Motor
- Ultrasonic Sensor
- 5V Adapter x 2
- Jumper cables


<p align="center">
<img width=300px  src="https://drive.google.com/file/d/1glCzeAlCt9fQNT6oWf9WfuqXAx04ISPG/view?usp=sharing" alt="Image of a Circuit">
</p>

---
## Download

**Blynk App: 
[<img src="https://cdn.rawgit.com/simple-icons/simple-icons/develop/icons/googleplay.svg" width="18" height="18" /> Google Play](https://play.google.com/store/apps/details?id=cc.blynk) | 
[<img src="https://cdn.rawgit.com/simple-icons/simple-icons/develop/icons/apple.svg" width="18" height="18" /> App Store](https://apps.apple.com/us/app/blynk-iot-for-arduino-esp32/id808760481)**

**Software: [<img src="https://simpleicons.org/icons/arduino.svg" width="20" height="20" /> Arduino IDE](https://www.arduino.cc/en/main/software)**

**Library: [Blynk Library](http://help.blynk.cc/en/articles/512105-how-to-install-blynk-library-for-arduino-ide)**

## Installation Setup
1. Clone this repository on your System.
2. Make the connections as per the circuit diagram.
1. Install the Blynk App on your [Android](https://play.google.com/store/apps/details?id=cc.blynk) or [IOS](https://apps.apple.com/us/app/blynk-iot-for-arduino-esp32/id808760481) mobile device.
2. Create a new account on the app.
3. Create a new project on the app and match the [GUI]() of this project or just scan this [QR Code]() and get the GUI on your app.
4. Once the project is created you will get an `Auth code` on your email id through you created your account.
5. Add the auth code and Wifi name and password in the [code]().
6. Install the [Arduino IDE](https://www.arduino.cc/en/main/software) on your system.
7. Install the [Blynk Library](http://help.blynk.cc/en/articles/512105-how-to-install-blynk-library-for-arduino-ide) for Arduino IDE.
8. Compile and Upload the [code]() onto your Arduino.
9. If on your Serial Monitor the ouput is similar to this then your system is up and running and it will show online on your Blynk app.

<p align="center">
<img width=300px  src="https://drive.google.com/file/d/1glCzeAlCt9fQNT6oWf9WfuqXAx04ISPG/view?usp=sharing" alt="Serial Monitor Output">
</p>

10. Now everything is set to go, you can test it using the Blynk app or manually.

---
Here is the [`Detailed Report`]() of the above project with some proposed modification to the system and here are the some of the name of the [webpages]() for reference for the project.

