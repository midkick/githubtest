/*
 * File:   LED_data.c
 * Author: kumi106
 *
 * Created on 2022/02/07, 12:16
 */


#include "P18F23K20.h"
#include "LED_cube.h"

static _cube_data* buf;
static _cube_data* out;

//ポインタの関連付け
void set_point(_cube_data* a,_cube_data* b){
    buf = a;
    out = b;
}

//文字データ格納
void into_cube_data(_cube_data cube[]){
    char x, y;
    for(x = 0;x<8;x++){
        for(y = 0;y<8;y++){
            cube[0].data[x][y] = degital(x);
        }
    }
    for(x = 0;x<8;x++){
        for(y = 0;y<8;y++){
            cube[1].data[x][y] = degital(y);
        }
    }
    for(x = 0;x<8;x++){
        for(y = 0;y<8;y++){
            cube[2].data[x][y] = 0xFF;
        }
    }
    for(x = 0;x<8;x++){
        for(y = 0;y<8;y++){
            cube[3].data[x][y] = 0x00;
        }
    }
}

void set_cube_data(_cube_data* cube){
    *buf = *cube;
    *out = *cube;
}

/*-------------文字の動作------------------------
    動作中は戻り値0、終わったら1 動作中は点灯時間1/4 */

char forward_cube_data(void){
    static char state_mov = 0;
    char x,y;
    if(state_mov == 0){
        T0CONbits.T0PS = 0x3;
    }
    for(y = 0;y<8;y++){
        out->data[0][y] = 0;
    }
    for(x = 0;x<7;x++){
        for(y = 0;y<8;y++){
            out->data[x+1][y] = buf->data[x][y];
        }
    }
    *buf = *out;
    state_mov++;
    if(state_mov>7){
        state_mov = 0;
        T0CONbits.T0PS = 0x5;
        return 1;
    }
    else{
        return 0;
    }
}

char backward_cube_data(void){
    static char state_mov = 0;
    char x,y;
    if(state_mov == 0){
        T0CONbits.T0PS = 0x3;
    }
    for(y = 0;y<8;y++){
        out->data[7][y] = 0;
    }
    for(x = 7;x>0;x--){
        for(y = 0;y<8;y++){
            out->data[x-1][y] = buf->data[x][y];
        }
    }
    *buf = *out;
    state_mov++;
    if(state_mov>7){
        state_mov = 0;
        T0CONbits.T0PS = 0x5;
        return 1;
    }
    else{
        return 0;
    }
}

char down_cube_data(void){
    static char state_mov = 0;
    char x,y;
    if(state_mov == 0){
        T0CONbits.T0PS = 0x3;
    }
    for(x = 0;x<8;x++){
        out->data[x][0] = 0;
    }
    for(x = 0;x<8;x++){
        for(y = 0;y<7;y++){
            out->data[x][y+1] = buf->data[x][y];
        }
    }
    *buf = *out;
    state_mov++;
    if(state_mov>7){
        state_mov = 0;
        T0CONbits.T0PS = 0x5;
        return 1;
    }
    else{
        return 0;
    }
}

char up_cube_data(void){
    static char state_mov = 0;
    char x,y;
    if(state_mov == 0){
        T0CONbits.T0PS = 0x3;
    }
    for(x = 0;x<8;x++){
        out->data[x][7] = 0;
    }
    for(x = 0;x<8;x++){
        for(y = 7;y>0;y--){
            out->data[x][y-1] = buf->data[x][y];
        }
    }
    *buf = *out;
    state_mov++;
    if(state_mov>7){
        state_mov = 0;
        T0CONbits.T0PS = 0x5;
        return 1;
    }
    else{
        return 0;
    }
}

