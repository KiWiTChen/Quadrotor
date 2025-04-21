 ; myScatterLoad.s （独立的数据初始化文件）
    AREA    |.text|, CODE, READONLY
    EXPORT  myScatterLoad
    IMPORT  |Image$$RW_IRAM1$$Base|
    IMPORT  |Image$$RW_IRAM1$$Length|
    IMPORT  |Load$$RW_IRAM1$$Base|
    IMPORT  |Image$$RW_IRAM1$$ZI$$Base|
    IMPORT  |Image$$RW_IRAM1$$ZI$$Length|

myScatterLoad    PROC
    ; 数据段拷贝
    LDR     R0, =|Load$$RW_IRAM1$$Base|
    LDR     R1, =|Image$$RW_IRAM1$$Base|
    LDR     R2, =|Image$$RW_IRAM1$$Length|
    CMP     R2, #0
    BEQ     SkipDataCopy
CopyLoop
    LDMIA   R0!, {R3}        ; 从加载地址批量加载
    STMIA   R1!, {R3}        ; 存储到链接地址
    SUBS    R2, R2, #4       ; 递减计数器
    BGT     CopyLoop         ; 循环直到完成
SkipDataCopy

    ; BSS段清零（优化后的正向清零）
    LDR     R0, =|Image$$RW_IRAM1$$ZI$$Base|
    LDR     R1, =|Image$$RW_IRAM1$$ZI$$Length|
    CMP     R1, #0
    BEQ     SkipBSSInit
    ADD     R2, R0, R1       ; 计算结束地址
    MOVS    R3, #0
ZeroLoop
    STR     R3, [R0], #4     ; 存储0并递增地址
    CMP     R0, R2           ; 检查是否到达结束地址
    BLT     ZeroLoop          ; 继续直到覆盖全部区域
SkipBSSInit

    BX      LR               ; 返回调用者
    ENDP

    ALIGN
    END