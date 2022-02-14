
//LED点灯パターンの構造体

#ifndef HEADER_H
#define HEADER_H
typedef struct{
    char data[8][8];
}_cube_data;
#endif

//LED_cube_data.c
void set_point(_cube_data* a,_cube_data* b);
void into_cube_data(_cube_data cube[]);
void set_cube_data(_cube_data* cube);
char forward_cube_data(void);
char backward_cube_data(void);
char up_cube_data(void);
char down_cube_data(void);

//myfunction.c
char degital(char);
char alphabet(char char1);
void into_array(char x[] ,char y);