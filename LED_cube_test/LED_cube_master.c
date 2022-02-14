/*
 * File:   LED_cube_master.c
 * Author: kumi106
 *
 * Created on 2022/01/31, 15:15
 */


#include "P18F23K20.h"
#include "LED_cube.h"
#define _XTAL_FREQ 16000000

//�O���[�o���ϐ�
_cube_data test[4];		//�e�X�g�p�\���p�^�[���i�S��ށj
_cube_data out,buf;

//----------���荞�݊֐�------------------
void __interrupt() isr(void){
    //���荞�ݓ��Ŏg���ϐ�
    static int x,y,z = 0;
    static int out_state = 0;
   
    //�O�������݁@PIC2�Ɠ������ĕ\������z��̗v�f��ύX
�@�@�@�@�@�@�@�@�@
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
    
    
    /*�^�C�}�����݁@�i���荞�ݎ��ɕ\���p�^�[����ύX�j
    ����	PWM��~��PIC2�Ƀ��Z�b�g���߁�PORTA�̏o�͂��~�߂�
                     ���\���ʒu�������������ύX�����������߉�����PWM�ĊJ*/

    if(INTCONbits.TMR0IF == 1){       
        INTCONbits.TMR0IF =0;        

        //���Z�b�g����
        T2CONbits.TMR2ON = 0;
        PORTCbits.RC2 = 1;
        PORTA = 0;
        x = 0;
        y = 0;
        
        //LED�����ύX
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
        
        //PWM�ĊJ
        PORTCbits.RC2 = 0;
        T2CONbits.TMR2ON = 1;
    }
}

//---------------���C���֐�---------------------
void main(void) {
    into_cube_data(test);
    set_point(&buf,&out);
    set_cube_data(&test[0]);
    
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    
    OSCCONbits.IRCF = 7;        //�����N���b�N16M
    TRISA = 0x00;               //LED�\���p�^�[���o��
    ANSEL = 0;                  //�A�i���O�ϊ����g�p
    TRISCbits.RC2 = 0;          //�X���[�u�Ƀ��Z�b�g�o��
    
    //PWM�ݒ�
    TRISCbits.RC1 = 1;          //CCP2���g�p
    PR2 = 78;
    CCP2CONbits.CCP2M = 0xC;
    CCPR2L = (156>>2);
    CCP2CONbits.DC2B = (156&3);
    PIR1bits.TMR2IF = 0;
    T2CONbits.T2CKPS = 1;       //�v���X�P�[��4
    T2CONbits.TMR2ON = 1;
    __delay_ms(10);
    TRISCbits.RC1 = 0;
    
    //�^�C�}�ݒ�
    T0CONbits.T08BIT = 0;
    T0CONbits.T0CS = 0;
    T0CONbits.T0SE = 0;
    T0CONbits.PSA = 0;
    T0CONbits.T0PS = 0x5;
    T0CONbits.TMR0ON = 1;
    
    ///UART�ݒ� �i����g�p�\��j�{�[���[�g9615 �񓯊�
    //�{�[���[�g�ݒ�̏�����
    BAUDCONbits.BRG16 = 0;
    TXSTAbits.BRGH = 0;
    TXSTAbits.SYNC = 0;
    //�s���ݒ�
    TRISCbits.RC6 = 1;
    TRISCbits.RC7 = 1;
    TXSTAbits.TXEN = 1;
    TXSTAbits.TX9 = 0;      //8bit���[�h
    BAUDCONbits.DTRXP = 0;  //���]����
    RCSTAbits.CREN = 1;     //��M����
    RCSTAbits.SPEN = 1;     //���M����
    SPBRG = 25;
    
    //�����ݐݒ�
    INTCONbits.TMR0IF = 0;
    INTCONbits.INT0IF = 0;
    INTCON3bits.INT1IF = 0;
    INTCON2bits.INTEDG1 = 1;            //���ȃN���b�N�̗����オ��Ŋ�����
    INTCONbits.INT0IE = 1;
    INTCON3bits.INT1IE = 1;
    INTCONbits.GIE = 1;
    INTCONbits.TMR0IE = 1;
    
    while(1){
        
    }
}
