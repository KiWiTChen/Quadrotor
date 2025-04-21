 AREA    |.text|, CODE, READONLY
myScatterLoad   PROC
        EXPORT  myScatterLoad
        IMPORT  |Image$$RW_IRAM1$$Base|      ; ���ݶ����ӵ�ַ��RAM��
        IMPORT  |Image$$RW_IRAM1$$Length|    ; ���ݶγ���
        IMPORT  |Load$$RW_IRAM1$$Base|       ; ���ݶμ��ص�ַ��Flash��
        IMPORT  |Image$$RW_IRAM1$$ZI$$Base|  ; ZI�Σ�BSS�����ӵ�ַ
        IMPORT  |Image$$RW_IRAM1$$ZI$$Length|; ZI�γ���

;------------------------------
; 1. �������ݶΣ���Flash��RAM��
;------------------------------
CopyData
    LDR     R0, =|Load$$RW_IRAM1$$Base|     ; R0 = ���ݶμ��ص�ַ��Flash��
    LDR     R1, =|Image$$RW_IRAM1$$Base|    ; R1 = ���ݶ����ӵ�ַ��RAM��
    LDR     R2, =|Image$$RW_IRAM1$$Length|  ; R2 = ���ݶγ���
    MOV     R3, #0                          ; ��ʼ��ƫ��Ϊ0

CopyLoop
    CMP     R3, R2                          ; ����Ƿ������
    BGE     CopyDone                         ; �� R3 >= R2����ת�� CopyDone
    LDR     R4, [R0, R3]                     ; ��Flash����4�ֽ����ݵ�R4
    STR     R4, [R1, R3]                     ; ��R4�е�����д��RAM
    ADD     R3, R3, #4                       ; ƫ������4�ֽ�
    B       CopyLoop                         ; ����ѭ��

CopyDone

;------------------------------
; 2. ����BSS�Σ���ʼ��δ��ʼ�����ݣ�
;------------------------------
; BSS�����㣨�Ż�����������㣩
    LDR     R0, =|Image$$RW_IRAM1$$ZI$$Base|
    LDR     R1, =|Image$$RW_IRAM1$$ZI$$Length|
    CMP     R1, #0
    BEQ     SkipBSSInit
    ADD     R2, R0, R1       ; ���������ַ
    MOVS    R3, #0
ZeroLoop
    STR     R3, [R0], #4     ; �洢0��������ַ
    CMP     R0, R2           ; ����Ƿ񵽴������ַ
    BLT     ZeroLoop          ; ����ֱ������ȫ������
SkipBSSInit

CleanDone

    ALIGN                                   ; ȷ����ַ����
    BX      LR                              ; ���ص�����
    ENDP

;------------------------------
; ����
;------------------------------
	ALIGN
	END