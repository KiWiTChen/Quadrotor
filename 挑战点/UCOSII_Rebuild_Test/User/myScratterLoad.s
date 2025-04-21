 ; myScatterLoad.s �����������ݳ�ʼ���ļ���
    AREA    |.text|, CODE, READONLY
    EXPORT  myScatterLoad
    IMPORT  |Image$$RW_IRAM1$$Base|
    IMPORT  |Image$$RW_IRAM1$$Length|
    IMPORT  |Load$$RW_IRAM1$$Base|
    IMPORT  |Image$$RW_IRAM1$$ZI$$Base|
    IMPORT  |Image$$RW_IRAM1$$ZI$$Length|

myScatterLoad    PROC
    ; ���ݶο���
    LDR     R0, =|Load$$RW_IRAM1$$Base|
    LDR     R1, =|Image$$RW_IRAM1$$Base|
    LDR     R2, =|Image$$RW_IRAM1$$Length|
    CMP     R2, #0
    BEQ     SkipDataCopy
CopyLoop
    LDMIA   R0!, {R3}        ; �Ӽ��ص�ַ��������
    STMIA   R1!, {R3}        ; �洢�����ӵ�ַ
    SUBS    R2, R2, #4       ; �ݼ�������
    BGT     CopyLoop         ; ѭ��ֱ�����
SkipDataCopy

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

    BX      LR               ; ���ص�����
    ENDP

    ALIGN
    END