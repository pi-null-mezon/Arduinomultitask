This repo contains an Arduino platform library and some examples of how to work with

How to use:

 1) Library catalogue "MirmPS" hould be copied to the Arduino IDE libraries location
 
 2) Try example [RGBLed](https://github.com/pi-null-mezon/Arduinomultitask/blob/master/RGBLed/RGBLed.ino), where each one of three light channels work in independent event loop 

 3) Try example [Multitask](https://github.com/pi-null-mezon/Arduinomultitask/blob/master/Multitask/Multitask.ino), where some Ardiono basic examples work in multitask regime 

The original idea is not mine, and can be found here: [Вытесняющая многозадачность для Arduino](http://robocraft.ru/blog/985.html), - thanks a lot Mirmik! But the original code has been published in 2012 and does not compile an modern Arduino IDE versions.
I've found it very interesting to make this library work on new IDE versions and add support of more than two loops.



 
