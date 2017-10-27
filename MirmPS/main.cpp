#include <Arduino.h>
#include "MirmPS.h"

volatile unsigned int _sppos;

ISR(TIMER2_OVF_vect,ISR_NAKED)
{
	saveContext();				// Сохраняем контекст.

	_sppos = SPH*0x0100+SPL; 

	if(_sppos >= 0x0400) {
		copyStackPointer(SPstore[0]);		
		loadStackPointer(SPstore[1]);
	} else if(_sppos >= 0x0301) {					// И загружаем другой.
		copyStackPointer(SPstore[1]);
		loadStackPointer(SPstore[2]);
	} else {
		copyStackPointer(SPstore[2]);
		loadStackPointer(SPstore[0]);
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
void branching_3 (void)__attribute__((naked,noinline));

void branching(void)
{	
	setStackPointer(0x04,0xFF);	// установка SP в RAMEND Atmega328P (для Atmega 168 это будет 0x04FF)
	branching_2();			// точка вызова процедуры копирования
	if (Taskcount==0) 	
		branching_3();		 
				
	//В эту точку возвращаются новые потоки. 

	//векторы выхода потоков из ветвителя:	
	if (Taskcount==0) {Taskcount++; programm1();}
	if (Taskcount==1) {Taskcount++; programm2();}
	if (Taskcount==2) {Taskcount++; programm3();}
}

void branching_2 (void)
{	
	saveContext();				
	SPstore[1].i=copyContext(0x0400); // Разбиваем кучу на куски и отдаём куски нашим потокам		
	loadContext();			  //Загружаем		
//т.к. функция naked, нужно явно объявить возврат
	asm("ret");				//Возвращаемся.		
}

void branching_3 (void)
{
	saveContext();					
	SPstore[2].i=copyContext(0x0301);	
	loadContext();				//Загружаем		
//т.к. функция naked, нужно явно объявить возврат
	asm("ret");
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

volatile void programm1(void)
{	
	sei();
	TIMSK2 = 1;
	setup();     //Первый поток вызывает функцию setup и разрешает прерывания      
	for (;;) {loop1();}  	
}                                       

volatile void programm2 (void)
{
	for (;;) {loop2();}                      
}

volatile void programm3 (void)
{
	for (;;) {loop3();}                      
}
