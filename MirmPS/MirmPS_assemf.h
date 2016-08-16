

#ifndef _Mirm_Assembler_     //������ �� 
#define _Mirm_Assembler_     //�������� ����������� 

//����� ����������� 

#ifdef __ASSEMBLER__

//����������� ��� ����������
.equ UDR0, 0xc6    // ��� ����������� � ���������
.equ UCSR0A, 0xc0  // �� ������������. ���������,
.equ TXC0, 6       // ��� ������.

#endif    //#ifdef __ASSEMBLER__

#ifndef __ASSEMBLER__

//����������� �� ��� ����������.

#ifdef __cplusplus   
extern "C"{         //extern "C" �����������, ���  
					//�������� ���������� 
					//� ������� � ����������� ����������
	                //������ ������� �� �����������
	                //����� ��, � �� C++.
#endif    //#ifdef __cplusplus

int volatile copyContext(int)__attribute__((naked));
// copyContext:
// ����������, ��� naked. � ������ ������ ��� �� �����������.
// ����������, ��� volatile. �� ������ ������.
// ��������� � ���������� int �� ����������� ����� ��. 

#ifdef __cplusplus
} // extern "C"
#endif    //#ifdef __cplusplus
	
#endif    //#if not def __ASSEMBLER__

#endif    //#ifndef _Mirm_Assembler_

