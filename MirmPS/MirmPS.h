#include "MirmPS_assemf.h"

#ifndef Mirm_PS_h
#define Mirm_PS_h

typedef volatile union Spt			//Определяем тип для хранения 
{int i;								//StackPointer; Определение
char c[2];							//на основе union позволит
} SPstore_t;						//обращаться со значением
                                    //и как с int и как с char[2]

extern SPstore_t SPstore[3];    //Определение массива на два стека

//прямая установка StackPointer.
#define setStackPointer(x,y) {SPH=x;SPL=y;}   

//макросы для работы с SPstore. Запись и Чтение.
#define copyStackPointer(x) {x.c[1]=SPH;x.c[0]=SPL;}  
#define loadStackPointer(x) {SPH=x.c[1];SPL=x.c[0];} 

#define saveContext() \
asm volatile ( "\n\t" \
"push r0 \n\t" \
"in r0, __SREG__ \n\t" \
"push r0 \n\t" \
"push r1 \n\t" \
"clr r1 \n\t" \
"push r2 \n\t"  \
"push r3 \n\t" \
"push r4 \n\t" \
"push r5 \n\t" \
"push r6 \n\t" \
"push r7 \n\t" \
"push r8 \n\t" \
"push r9 \n\t" \
"push r10 \n\t" \
"push r11 \n\t" \
"push r12 \n\t" \
"push r13 \n\t" \
"push r14 \n\t" \
"push r15 \n\t" \
"push r16 \n\t" \
"push r17 \n\t" \
"push r18 \n\t" \
"push r19 \n\t"\
"push r20 \n\t" \
"push r21 \n\t" \
"push r22 \n\t" \
"push r23 \n\t"\
"push r24 \n\t" \
"push r25 \n\t" \
"push r26 \n\t" \
"push r27 \n\t" \
"push r28 \n\t" \
"push r29 \n\t"\
"push r30 \n\t" \
"push r31 \n\t");

#define loadContext() \
asm volatile ("\n\t" \
"pop r31 \n\t" \
"pop r30 \n\t" \
"pop r29 \n\t" \
"pop r28 \n\t" \
"pop r27 \n\t" \
"pop r26 \n\t" \
"pop r25 \n\t" \
"pop r24 \n\t"\
"pop r23 \n\t" \
"pop r22 \n\t" \
"pop r21 \n\t" \
"pop r20 \n\t" \
"pop r19 \n\t" \
"pop r18 \n\t" \
"pop r17 \n\t" \
"pop r16 \n\t" \
"pop r15 \n\t" \
"pop r14 \n\t"\
"pop r13 \n\t" \
"pop r12 \n\t" \
"pop r11 \n\t" \
"pop r10 \n\t" \
"pop r9 \n\t" \
"pop r8 \n\t" \
"pop r7 \n\t" \
"pop r6 \n\t" \
"pop r5 \n\t" \
"pop r4 \n\t"\
"pop r3 \n\t" \
"pop r2 \n\t" \
"pop r1 \n\t" \
"pop r0 \n\t" \
"out __SREG__, r0 \n\t" \
"pop r0 \n\t");

#endif


