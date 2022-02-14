 /*
 * File:   led_cube.c
 * Author: kumi106
 *
 * Created on 2022/01/24, 13:02
 */


#include "P18F23K20.h"
#include "LED_cube.h"

void __interrupt() isr(void){
    //マスターからのリセット命令
    if(INTCONbits.INT0IF == 1){
        INTCONbits.INT0IF = 0;
        PORTA = 0x80;
        PORTC = 0x80;
    }
    
    //クロックの立ち上がり検知で列と段を動かす
    if(INTCON3bits.INT1IF == 1){
        INTCON3bits.INT1IF = 0;
        if(PORTA >= 0x80){
            PORTA = 0x01;
            
            if(PORTC >= 0x80){
                PORTC= 0x01;
            }
            else{
                PORTC = (PORTC<<1);
            }
        }
        else{
            PORTA = (PORTA<<1);
        }
    }
}


void main(void) {
    OSCCONbits.IRCF = 7;            //メインクロック16MHz
    TRISA = 0x00;		    //段出力
    TRISB = 0x03;                   //外部割込みを使用するためPB0、PB1を入力
    TRISC = 0x00;		　　//列出力
    ANSEL = 0;                      //PORTAはアナログ変換使用しない
    PORTA = 0x80;
    PORTB = 0x00;
    PORTC = 0x80;
    
    //割込み設定
    INTCONbits.INT0IF = 0;
    INTCON3bits.INT1IF = 0;
    INTCON2bits.INTEDG1 = 1;        //立ち上がりエッジで割込み
    INTCONbits.INT0IE = 1;
    INTCON3bits.INT1E = 1;
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    
    while(1){
        
    }
    
}
