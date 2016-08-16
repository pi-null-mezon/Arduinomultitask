/** 
 *  Функции ядра Ардуино рассчитаны на работу в режиме постоянных прерываний от системного таймера.
 *  Это значит, что они не критичны к остановам и не разрушаются в многопоточном режиме.
 *  Если есть какие-то сомнения, функцию всегда можно сделать атомарной, выполнив перед ней макрос cli(), а после нее макрос sei().
 *  В этом случае на время работы такой функции прерывания будут запрещены.
 *  Если есть переменные, с которыми работает больше одного процесса, их следует описывать как volatile, а обращения к ним делать атомарными.
 */

#include <MirmPS.h>
#include <MirmPS_assemf.h>

void setup() {
  TIMSK2 = 1;           // enable Timer 2 to generate overflow interruptions for context switches
  Serial.begin(9600);   // initialize Serial port
  pinMode(5, INPUT);
  pinMode(13, OUTPUT);  // initialize digital pin 13 as an output.
}

void loop1() {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(5);                 // yes, delay still works! It is great, isn't it?
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(5);             // note however that MirmPS way of multitasking effects on delay and often makes delay longer   
}

void loop2() { 
  cli();                                        // loop2 and loop3 both will use shared resource - Serial port, so we should use "cli() ... sei()" rule to prevent data corruption    
  int sensorValue = analogRead(A0);             // read the input on analog pin 0  
  float voltage = sensorValue * (5.0 / 1023.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)  
  Serial.print("<loop2> voltage at pin A0: ");
  Serial.println(voltage);                      // print out the value you read                                    
  delay(10);
  sei();
}

void loop3() {
  cli(); 
  int state = digitalRead(5);
  Serial.print("<loop3> state of pin 5: ");
  Serial.println(state);  // print out the state of the button
  delay(10);
  sei();  
}

