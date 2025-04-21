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
    
; 保存中断状态并关中断
OS_CPU_SR_Save PROC              ; 标签后不需要冒号
    MRS R0, PRIMASK             ; 读取PRIMASK到R0
    CPSID I                     ; 关闭中断
    BX LR                       ; 返回
    ENDP
    
; 恢复中断状态
OS_CPU_SR_Restore PROC
    MSR PRIMASK, R0             ; 从R0恢复PRIMASK
    BX LR
    ENDP
    
; 其他函数保持相同结构...
	
; 任务上下?切换，此处为空实现，仅供通过编译。以后需要实现任务上下?切换代码。
OSCtxSw PROC
	BX LR
	ENDP
	
; 中断级任务切换，空实现
OSIntCtxSw PROC
	BX LR
	ENDP
	
; 启动最?优先级任务，空实现，实际需要初始化任务堆栈并启动第?个任务
OSStartHighRdy PROC
	BX LR
	ENDP
	
; PendSV 中断处理，空实现，实际应实现PendSV中断处理以完成任务切换
OS_CPU_PendSVHandler PROC
	BX LR
	ENDP
	END