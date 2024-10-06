.global _start
_start:
	
	
	LDR R0,=list	//将定义的数据首地址放入R0
	LDR R1,[R0]		//将R0寄存的地址解引用取值 放入R1
	//LDR R2,[R0,#8]	//   	从R0偏移8位得到地址并取值 放入R2   但是不影响R0的值
	//LDR R3,[R0,#8]!	//   	从R0偏移8位得到地址并取值 放入R3   同时会改变R0的值
	LDR R4,[R0],#4		//		从R0偏移4位得到地址并取值 放入R4	  同时会改变R0的值
	


//结束代码
_ends:	
	MOV R0,#30
	
	MOV R7,#1
	SWI 0
	
//数据
.data
list:
	.word 3,6,9,1,-5,10