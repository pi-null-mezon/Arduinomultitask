#include <Arduino.h>
#include "MirmPS.h"

volatile unsigned int _sppos;

ISR(TIMER2_OVF_vect,ISR_NAKED)
{
saveContext();				// Сохраняем контекст.

_sppos = SPH*0x0100+SPL; 

if(_sppos < 0x0501) 	// Очень глупый способ вычисления активного потока.
{
  copyStackPointer(SPstore[2]);		
  loadStackPointer(SPstore[1]);
}				// Сохраняем один SP
else if(_sppos < 0x0700)					
{				// И загружаем другой.
  copyStackPointer(SPstore[1]);
  loadStackPointer(SPstore[0]);
} else {
  copyStackPointer(SPstore[0]);
  loadStackPointer(SPstore[2]);
}

loadContext();				//Загружаем новый контекст.
asm("reti");				//Возврат из прерывания.
}

volatile void programm1 (void);
volatile void programm2 (void);
volatile void programm3 (void);

volatile SPstore_t SPstore[3];		// Здесь храняться указатели стека
					// сохраненных потоков.
volatile byte Taskcount=0;		// Это счетчик выходов из ветвителя. 

void branching(void)__attribute__((always_inline));
void branching_2 (void)__attribute__((naked,noinline));

void branching(void)
{	setStackPointer(0x08,0xFF);	// установка SP в RAMEND Atmega328P (для Atmega 168 это будет 0x04FF)
	branching_2();			// точка вызова процедуры 
					// копирования.

//В эту точку возвращаются новые потоки. 

//векторы выхода потоков из ветвителя:
	
	if (Taskcount==0) {Taskcount++; programm1();}
	if (Taskcount==1) {Taskcount++; programm2();}
	if (Taskcount==2) {programm3();}
}

void branching_2 (void)
{	saveContext();				//Сохраняем

	SPstore[1].i=copyContext(0x0700); // Разбиваем кучу SRAM Atmega328P на четыре куска и отдаём куски нашим потокам
	SPstore[2].i=copyContext(0x0501);	

	loadContext();				//Загружаем
		
//т.к. функция naked, нужно явно объявить возврат
	asm("ret");				//Возвращаемся.		
}

void loop1(void);
void loop2(void);          //Функции реализованы в скетче.              
void loop3(void); 

 int main (void)__attribute__((__noreturn__));

int main(void)                      //Точка входа программы.
{
	init();     //Настройка ядра Ардуино. В основном таймеры.
	cli();      //init() разрешает прерывания. но 
                    //нам они пока не нужны
	branching();   
        return 0;   //Сюда программа не попадёт.
}

volatile void programm1(void){	//А это два наших потока.
sei(); 	setup();     //Первый поток вызывает также cодержит      
	for (;;) {loop1();  //функцию setup.И разрешает прерывания.
	}
}                                       //За их вызов ответственна

volatile void programm2 (void){
for (;;) {loop2();}                      //функция branching()
}

volatile void programm3 (void){
for (;;) {loop3();}                      //функция branching()
}
