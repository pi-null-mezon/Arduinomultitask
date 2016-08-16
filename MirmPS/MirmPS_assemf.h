

#ifndef _Mirm_Assembler_     //Защита от 
#define _Mirm_Assembler_     //двойного подключения 

//Общие определения 

#ifdef __ASSEMBLER__

//Определения для ассемблера
.equ UDR0, 0xc6    // Эти определения в программе
.equ UCSR0A, 0xc0  // не используются. Приведены,
.equ TXC0, 6       // как пример.

#endif    //#ifdef __ASSEMBLER__

#ifndef __ASSEMBLER__

//Определения не для ассемблера.

#ifdef __cplusplus   
extern "C"{         //extern "C" декларирует, что  
					//передача параметров 
					//в функцию и возвращение результата
	                //должны вестись по соглашениям
	                //языка Си, а не C++.
#endif    //#ifdef __cplusplus

int volatile copyContext(int)__attribute__((naked));
// copyContext:
// Определена, как naked. В данном случае это не обязательно.
// Определена, как volatile. На всякий случай.
// принимает и возвращает int по соглашениям языка Си. 

#ifdef __cplusplus
} // extern "C"
#endif    //#ifdef __cplusplus
	
#endif    //#if not def __ASSEMBLER__

#endif    //#ifndef _Mirm_Assembler_

