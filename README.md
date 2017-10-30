Multitasking on Arduino became simple! Do not belive me? Take a look:
 
```c++
#include <MirmPS.h>
#include <MirmPS_assemf.h>

void setup() {
	// MANAGE TASK PRIORITIES
	byte _vp[] = {75,25,0}; // think about this numbers as percents of the MCU load per task   
	set_tasks_priorities(_vp);
}

void loop1() {
	// DO WHATEVER YOU WANT
}

void loop2() {  
	// DO WHATEVER YOU WANT
}

void loop3() {
	// DO WHATEVER YOU WANT
}
```

How to use:

 1) Copy "MirmPS" library to the Arduino IDE libraries location
 
 3) Build and run [Multitask](https://github.com/pi-null-mezon/Arduinomultitask/blob/master/Multitask/Multitask.ino) example

The original idea is not mine, and can be found here: [Вытесняющая многозадачность для Arduino](http://robocraft.ru/blog/985.html), - thanks a lot Mirmik! But the original code has been published in 2012 and does not compile by the modern Arduino IDE versions.
I've found it very interesting to make this library work on new IDE versions and add support of more than two loops.



 
