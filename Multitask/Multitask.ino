#include <MirmPS.h>
#include <MirmPS_assemf.h>

/** 
 *  Функции ядра Ардуино рассчитаны на работу в режиме постоянных прерываний от системного таймера.
 *  Это значит, что они не критичны к остановам и не разрушаются в многопоточном режиме.
 *  Если есть какие-то сомнения, функцию всегда можно сделать атомарной, выполнив перед ней макрос cli(), а после нее макрос sei().
 *  В этом случае на время работы такой функции прерывания будут запрещены.
 *  Если есть переменные, с которыми работает больше одного процесса, их следует описывать как volatile, а обращения к ним делать атомарными.
 *  
 *  Также нужно помнить что переключение задач происходит по прерыванию системного таймера №2, поэтому нельзя запрещать прерывания от него
 */

void setup() {
  Serial.begin(9600);   // initialize Serial port
}

void loop1() {
   cli();
   Serial.println("First"); 
   sei();
}

void loop2() { 
  cli();                                        // loop2 and loop3 both will use shared resource - Serial port, so we should use "cli() ... sei()" rule to prevent data corruption    
  Serial.println("Second");
  /*int sensorValue = analogRead(A0);             // read the input on analog pin 0  
  float voltage = sensorValue * (5.0 / 1023.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)  
  Serial.print("<loop2> - voltage at pin A0: ");
  Serial.println(voltage);                      // print out the value you read                                    
  delay(10);*/
  sei();
}

void loop3() {
  cli(); 
  Serial.println("Third");
  /*int state = digitalRead(5);
  Serial.print("<loop3> - state of pin 5: ");
  Serial.println(state);  // print out the state of the button
  delay(10);*/
  sei();  
}

