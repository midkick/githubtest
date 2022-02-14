/*
 * File:   LED_cube_master.c
 * Author: kumi106
 *
 * Created on 2022/01/31, 15:15
 */


#include "P18F23K20.h"
#include "LED_cube.h"
#define _XTAL_FREQ 16000000

//グローバル変数
_cube_data test[4];		//テスト用表示パターン（４種類）
_cube_data out,buf;

//----------割り込み関数------------------
void __interrupt() isr(void){
    //割り込み内で使う変数
    static int x,y,z = 0;
    static int out_state = 0;
   
    //外部割込み　PIC2と同期して表示する配列の要素を変更
　　　　　　　　　
    if(INTCON3bits.INT1IF == 1 && INTCON3bits.INT1IE == 1){
        INTCON3bits.INT1IF = 0;
        
        PORTA = 0x00;
        PORTA = out.data[x][y];
        if(x>=7){
            x = 0;
            if(y>=7){
                y = 0;
            }
            else{
                y++;
            }
        }
        else{
            x++;
        }
    }
    
    
    /*タイマ割込み　（割り込み時に表示パターンを変更）
    動作	PWM停止→PIC2にリセット命令→PORTAの出力を止める
                     →表示位置初期化→文字変更→初期化命令解除→PWM再開*/

    if(INTCONbits.TMR0IF == 1){       
        INTCONbits.TMR0IF =0;        

        //リセット命令
        T2CONbits.TMR2ON = 0;
        PORTCbits.RC2 = 1;
        PORTA = 0;
        x = 0;
        y = 0;
        
        //LED文字変更
        switch(out_state){
            case 0:
                if(down_cube_data() == 0){}
                else{           
                    set_cube_data(&test[z]);
                    z++;
                    out_state++;
                }
                break;
            case 1:
                if(forward_cube_data() == 0){}
                else{           
                    set_cube_data(&test[z]);
                    z++;
                    out_state++;
                }
                break;
            case 2:
                if(up_cube_data() == 0){}
                else{           
                    set_cube_data(&test[z]);
                    z++;
                    out_state++;
                }
                break;
            case 3:
                if(backward_cube_data() == 0){}
                else{           
                    set_cube_data(&test[z]);
                    z++;
                    out_state = 0;
                }
                break;              
        }
        if(z>2){
            z = 0;
        }
        
        //PWM再開
        PORTCbits.RC2 = 0;
        T2CONbits.TMR2ON = 1;
    }
}

//---------------メイン関数---------------------
void main(void) {
    into_cube_data(test);
    set_point(&buf,&out);
    set_cube_data(&test[0]);
    
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    
    OSCCONbits.IRCF = 7;        //内部クロック16M
    TRISA = 0x00;               //LED表示パターン出力
    ANSEL = 0;                  //アナログ変換未使用
    TRISCbits.RC2 = 0;          //スレーブにリセット出力
    
    //PWM設定
    TRISCbits.RC1 = 1;          //CCP2を使用
    PR2 = 78;
    CCP2CONbits.CCP2M = 0xC;
    CCPR2L = (156>>2);
    CCP2CONbits.DC2B = (156&3);
    PIR1bits.TMR2IF = 0;
    T2CONbits.T2CKPS = 1;       //プリスケーラ4
    T2CONbits.TMR2ON = 1;
    __delay_ms(10);
    TRISCbits.RC1 = 0;
    
    //タイマ設定
    T0CONbits.T08BIT = 0;
    T0CONbits.T0CS = 0;
    T0CONbits.T0SE = 0;
    T0CONbits.PSA = 0;
    T0CONbits.T0PS = 0x5;
    T0CONbits.TMR0ON = 1;
    
    ///UART設定 （今後使用予定）ボーレート9615 非同期
    //ボーレート設定の初期化
    BAUDCONbits.BRG16 = 0;
    TXSTAbits.BRGH = 0;
    TXSTAbits.SYNC = 0;
    //ピン設定
    TRISCbits.RC6 = 1;
    TRISCbits.RC7 = 1;
    TXSTAbits.TXEN = 1;
    TXSTAbits.TX9 = 0;      //8bitモード
    BAUDCONbits.DTRXP = 0;  //反転無し
    RCSTAbits.CREN = 1;     //受信許可
    RCSTAbits.SPEN = 1;     //送信許可
    SPBRG = 25;
    
    //割込み設定
    INTCONbits.TMR0IF = 0;
    INTCONbits.INT0IF = 0;
    INTCON3bits.INT1IF = 0;
    INTCON2bits.INTEDG1 = 1;            //自己クロックの立ち上がりで割込み
    INTCONbits.INT0IE = 1;
    INTCON3bits.INT1IE = 1;
    INTCONbits.GIE = 1;
    INTCONbits.TMR0IE = 1;
    
    while(1){
        
    }
}
