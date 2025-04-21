        AREA MyCode ,CODE,READONLY
        ENTRY
        EXPORT __main ;���� LED_INIT Ϊ�ɵ������ţ���ʾ������ڵ�
                
__main
        BL LED_INIT
                
LED_INIT
                
        ;RCC
        LDR R0,=0x40023800+0x30
        LDR R1,[R0]
        ORR R1,R1,#(0x01);��λ����1��Ϊ1
        STR R1,[R0];R1���ص�R0
        
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
        MOV R3,#(0X00100000);�趨�ض���ʱ����֤�۲�õ����
mm
        CMP R3,#0
        SUBNE R3,R3,#1
        BNE mm
        BX LR
        
        END


