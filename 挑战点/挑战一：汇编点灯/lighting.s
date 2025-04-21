        AREA MyCode ,CODE,READONLY
        ENTRY
        EXPORT __main ;声明 LED_INIT 为可导出符号，表示程序入口点
                
__main
        BL LED_INIT
                
LED_INIT
                
        ;RCC
        LDR R0,=0x40023800+0x30
        LDR R1,[R0]
        ORR R1,R1,#(0x01);按位或，有1则为1
        STR R1,[R0];R1加载到R0
        
        ;MODER
        LDR R0,=0x40020000
        LDR R1,[R0]
        BIC R1,R1,#(3<<10)
        ORR R1,R1,#(1<<10)
        STR R1,[R0]
        
        ;OUTPUT TYPE
        LDR R0,=0x40020000+0x04
        LDR R1,[R0]
        BIC R1,R1,#(1<<5)
        STR R1,[R0]
        
        ;SPEED
        LDR R0,=0x40020000+0x08
        LDR R1,[R0]
        BIC R1,R1,#(3<<10)
        STR R1,[R0]
        
        BL LOOP
                
LOOP
        BL LED_ON
        BL DELAY
        BL LED_OFF
        BL DELAY
        B LOOP
                
                
LED_ON
        ;ODR
        LDR R0,=0x40020000+0x14
        LDR R1,[R0]
        ORR R1,R1,#(1<<5)
        STR R1,[R0]
        BX LR
        
LED_OFF
        LDR R0,=0x40020000+0x14
        LDR R1,[R0]
        BIC R1,R1,#(1<<5)
        STR R1,[R0]
        BX LR
        
DELAY
        MOV R3,#(0X00100000);设定特定延时，保证观察得到结果
mm
        CMP R3,#0
        SUBNE R3,R3,#1
        BNE mm
        BX LR
        
        END


