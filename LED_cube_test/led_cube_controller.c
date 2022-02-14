 /*
 * File:   led_cube.c
 * Author: kumi106
 *
 * Created on 2022/01/24, 13:02
 */


#include "P18F23K20.h"
#include "LED_cube.h"

void __interrupt() isr(void){
    //�}�X�^�[����̃��Z�b�g����
    if(INTCONbits.INT0IF == 1){
        INTCONbits.INT0IF = 0;
        PORTA = 0x80;
        PORTC = 0x80;
    }
    
    //�N���b�N�̗����オ�茟�m�ŗ�ƒi�𓮂���
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
    OSCCONbits.IRCF = 7;            //���C���N���b�N16MHz
    TRISA = 0x00;		    //�i�o��
    TRISB = 0x03;                   //�O�������݂��g�p���邽��PB0�APB1�����
    TRISC = 0x00;		�@�@//��o��
    ANSEL = 0;                      //PORTA�̓A�i���O�ϊ��g�p���Ȃ�
    PORTA = 0x80;
    PORTB = 0x00;
    PORTC = 0x80;
    
    //�����ݐݒ�
    INTCONbits.INT0IF = 0;
    INTCON3bits.INT1IF = 0;
    INTCON2bits.INTEDG1 = 1;        //�����オ��G�b�W�Ŋ�����
    INTCONbits.INT0IE = 1;
    INTCON3bits.INT1E = 1;
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    
    while(1){
        
    }
    
}
