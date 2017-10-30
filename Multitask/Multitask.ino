#include <MirmPS.h>
#include <MirmPS_assemf.h>

/** 
 *  [ENG]
 *  What to remember when working with the MirmPS library:
 *  1.  Arduino kernel functions are designed to work in the mode of permanent interrupts from the system timer.
 *      This means that they are not critical to the breakpoints and do not collapse in a multitask mode.
 *      If there are any doubts, the function can always be made atomic by executing the cli() macro before it, and after it the macro sei().
 *      In this case, for the duration of this function, interrupts will be disabled.
 * 2.   If there are variables with which more than one task works, they should be described as volatile, and calls to them are made atomic.
 * 3.   It is necessary to understand and remember that switching between tasks occurs by interrupting the system timer No. 2, so you can not prevent interrupts from it.
 * 4.   The distribution of time for the execution of tasks should be performed using the void function set_tasks_priorities (byte _vp [])
 *  
 *  [RUS]
 *  Что следует помнить при работе с библиотекой MirmPS:
 *  1.  Функции ядра Ардуино рассчитаны на работу в режиме постоянных прерываний от системного таймера.
 *      Это значит, что они не критичны к остановам и не разрушаются в многозадачном режиме.
 *      Если есть какие-то сомнения, функцию всегда можно сделать атомарной, выполнив перед ней макрос cli(), а после нее макрос sei().
 *      В этом случае на время работы такой функции прерывания будут запрещены.
 *  2.  Если есть переменные, с которыми работает больше одного процесса, их следует описывать как volatile, а обращения к ним делать атомарными.
 *  3.  Нужно понимать и помнить, что переключение между задачами происходит по прерыванию системного таймера №2, поэтому нельзя запрещать прерывания от него.
 *  4.  Распределение времени на выполненеие задач следует выполнять при помощи функции void set_tasks_priorities(byte _vp[]) 
 */

void setup() {
  Serial.begin(9600);
  
  // You can manage priorities of the tasks 
  // Try to select mutually divisible numbers, for the instance: {50,25,25} or {75,20,5} or {10,0,90}
  // 0 is also valid priority, in such a case task will not be performed at all, but will still consume part of the MCU's SRAM
  byte _vp[] = {50,25,25}; // think about this numbers as percents of the MCU load per task   
  set_tasks_priorities(_vp);
}

void loop1() {
   cli(); // disable interrupts, it is essential for the Serial output 
   Serial.println("[First]"); 
   sei(); // enable interrupts
}

void loop2() {  
  cli();                                             
  Serial.println("[Second]");  
  sei();
}

void loop3() {
  cli(); 
  Serial.println("[Third]");
  sei();  
}

