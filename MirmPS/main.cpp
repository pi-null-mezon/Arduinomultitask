#include <Arduino.h>
#include "MirmPS.h"

volatile byte taskNum = 0; 

ISR(TIMER2_OVF_vect,ISR_NAKED)
{
saveContext();				// ��������� ��������.

copyStackPointer(SPstore[taskNum]);	
taskNum = (taskNum+1) % 3;	
loadStackPointer(SPstore[taskNum]);
					// ��������� ���� SP
loadContext();				//��������� ����� ��������.

asm("reti");				//������� �� ����������.
}

volatile void programm1 (void);
volatile void programm2 (void);
volatile void programm3 (void);

volatile SPstore_t SPstore[3];		// ����� ��������� ��������� �����
					// ����������� �������.
volatile int Taskcount=0;		// ��� ������� ������� �� ���������. 

void branching(void)__attribute__((always_inline));
void branching_2 (void)__attribute__((naked,noinline));

void branching(void)
{	setStackPointer(0x04,0xFF);	// ��������� SP � RAMEND
	branching_2();			// ����� ������ ��������� 
					// �����������.

//� ��� ����� ������������ ����� ������. 

//������� ������ ������� �� ���������:
	
	if (Taskcount==0) {Taskcount++;programm1();}
	if (Taskcount==1) {Taskcount++;programm2();}
	if (Taskcount==2) {Taskcount++;programm3();}
}

void branching_2 (void)
{	saveContext();				//���������
	SPstore[1].i=copyContext(0x0484);
	SPstore[2].i=copyContext(0x040A);	//��������
	loadContext();				//���������
		
//�.�. ������� naked, ����� ���� �������� �������
	asm("ret");				//������������.		
}

void loop1(void);
void loop2(void);          //������� ����������� � ������.              
void loop3(void); 

 int main (void)__attribute__((__noreturn__));

int main(void)                      //����� ����� ���������.
{
	init();     //��������� ���� �������. � �������� �������.
	cli();      //init() ��������� ����������. �� 
                    //��� ��� ���� �� �����
	branching();   
        return 0;   //���� ��������� �� ������.
}

volatile void programm1(void){	//� ��� ��� ����� ������.
sei(); 	setup();     //������ ����� �������� ����� c�������      
	for (;;) {loop1();  //������� setup.� ��������� ����������.
	}
}                                       //�� �� ����� ������������

volatile void programm2 (void){
for (;;) {loop2();}                      //������� branching()
}

volatile void programm3 (void){
for (;;) {loop3();}                      //������� branching()
}
