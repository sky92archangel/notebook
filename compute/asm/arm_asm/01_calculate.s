.global _start
_start:
	
	MOV R0,#5
	MOV R1,#7
	MOV R2,#0xFFFFFFFF
	ADD R3,R0,R1	//R2=R0+R1
	SUB R3,R0,R1	//R2=R0-R1
	MUL R3,R0,R1	//R4=R0*R1
	
	SUBS R4,R0,R1	//R2=R0-R1   SUBS计算同时会操作CPSR标记结果是否为负数 N
	
	ADDS R4,R2,R0
	ADC R4,R2,R0	//ADC  加法 带有进位  R4=R2+R0+CARRY
	 

//结束代码
_ends:	
	MOV R0,#30
	
	MOV R7,#1
	SWI 0
	
//数据
.data
list:
	.word 3,6,9,1,-5,10