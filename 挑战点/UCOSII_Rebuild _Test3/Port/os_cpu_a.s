    EXPORT OS_CPU_SR_Save
    EXPORT OS_CPU_SR_Restore
    EXPORT OSCtxSw
    EXPORT OSIntCtxSw
    EXPORT OSStartHighRdy
    EXPORT OS_CPU_PendSVHandler
        
    AREA  |.text|, CODE, READONLY, ALIGN=2
    THUMB
    REQUIRE8
    PRESERVE8
    
; �����ж�״̬�����ж�
OS_CPU_SR_Save PROC              ; ��ǩ����Ҫð��
    MRS R0, PRIMASK             ; ��ȡPRIMASK��R0
    CPSID I                     ; �ر��ж�
    BX LR                       ; ����
    ENDP
    
; �ָ��ж�״̬
OS_CPU_SR_Restore PROC
    MSR PRIMASK, R0             ; ��R0�ָ�PRIMASK
    BX LR
    ENDP
    
; ��������������ͬ�ṹ...
	
; ��������?�л����˴�Ϊ��ʵ�֣�����ͨ�����롣�Ժ���Ҫʵ����������?�л����롣
OSCtxSw PROC
	BX LR
	ENDP
	
; �жϼ������л�����ʵ��
OSIntCtxSw PROC
	BX LR
	ENDP
	
; ������?���ȼ����񣬿�ʵ�֣�ʵ����Ҫ��ʼ�������ջ��������?������
OSStartHighRdy PROC
	BX LR
	ENDP
	
; PendSV �жϴ�����ʵ�֣�ʵ��Ӧʵ��PendSV�жϴ�������������л�
OS_CPU_PendSVHandler PROC
	BX LR
	ENDP
	END