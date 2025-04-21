 AREA    |.text|, CODE, READONLY
myScatterLoad   PROC
        EXPORT  myScatterLoad
        IMPORT  |Image$$RW_IRAM1$$Base|      ; 数据段链接地址（RAM）
        IMPORT  |Image$$RW_IRAM1$$Length|    ; 数据段长度
        IMPORT  |Load$$RW_IRAM1$$Base|       ; 数据段加载地址（Flash）
        IMPORT  |Image$$RW_IRAM1$$ZI$$Base|  ; ZI段（BSS）链接地址
        IMPORT  |Image$$RW_IRAM1$$ZI$$Length|; ZI段长度

;------------------------------
; 1. 复制数据段（从Flash到RAM）
;------------------------------
CopyData
    LDR     R0, =|Load$$RW_IRAM1$$Base|     ; R0 = 数据段加载地址（Flash）
    LDR     R1, =|Image$$RW_IRAM1$$Base|    ; R1 = 数据段链接地址（RAM）
    LDR     R2, =|Image$$RW_IRAM1$$Length|  ; R2 = 数据段长度
    MOV     R3, #0                          ; 初始化偏移为0

CopyLoop
    CMP     R3, R2                          ; 检查是否复制完毕
    BGE     CopyDone                         ; 若 R3 >= R2，跳转到 CopyDone
    LDR     R4, [R0, R3]                     ; 从Flash加载4字节数据到R4
    STR     R4, [R1, R3]                     ; 将R4中的数据写入RAM
    ADD     R3, R3, #4                       ; 偏移增加4字节
    B       CopyLoop                         ; 继续循环

CopyDone

;------------------------------
; 2. 清零BSS段（初始化未初始化数据）
;------------------------------
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

CleanDone

    ALIGN                                   ; 确保地址对齐
    BX      LR                              ; 返回调用者
    ENDP

;------------------------------
; 结束
;------------------------------
	ALIGN
	END