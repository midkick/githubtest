
void into_array(char x[] ,char y){
    for(int i = 0; i<8;i++){
        x[i] = (y & (0b10000000 >> i))>>(7-i);
    }
}
void into_array_key(char x[] ,int y){
    int j = 0;
    for(int i = 0; i<15;i++){
        if(i % 4 == 3){
            x[i] = ' ';
            j++;
        }
        else if((y & (0x0001 << (i-j))) == 0){
            x[i] = '0';
        }
        else{
            x[i] = '1';
        }
    }
    x[15] = '\0';
}

char degital(char num1)
{
    static char num2;
    switch(num1)
    {
        case 0:
            num2 = 0b11111100;
            break;
        case 1:
            num2 = 0b01100000;
            break;
        case 2:
            num2 = 0b11011010;
            break;
        case 3:
            num2 = 0b11110010;
             break;
        case 4:
            num2 = 0b01100110;
             break;
        case 5:
            num2 = 0b10110110;
             break;
        case 6:
            num2 = 0b10111110;
             break;
        case 7:
            num2 = 0b11100100;
             break;
        case 8:
            num2 = 0b11111110;
             break;
        case 9:
            num2 = 0b11110110;
             break;
        default:
            num2 = 0b10011110;
    }
    return num2;
}

char alphabet(char char1)
{
    static char char2;
    
    switch(char1)
    {
        case 'a':
        case 'A':
            char2 = 0b10001000;
            break;
        case 'b':
        case 'B':
            char2 = 0b10000011;
            break;
        case 'c':
        case 'C':
            char2 = 0b11000110;
            break;
        case 'd':
        case 'D':
            char2 = 0b10100001;
            break;
        case 'e':
        case 'E':
            char2 = 0b10000110;
            break;
        case 'f':
        case 'F':
            char2 = 0b10001110;
            break;
        case 'g':
        case 'G':
            char2 = 0b11000010;
            break;
        case 'h':
        case 'H':
            char2 = 0b10001011;
            break;
        case 'i':
        case 'I':
            char2 = 0b11001111;
            break;
        case 'j':
        case 'J':
            char2 = 0b11100001;
            break;
        case 'k':
        case 'K':
            char2 = 0b10001010;
            break;
        case 'l':
        case 'L':
            char2 = 0b11000111;
            break;
        case 'm':
        case 'M':
            char2 = 0b11001000;
            break;
        case 'n':
        case 'N':
            char2 = 0b10101011;
            break;
        case 'o':
        case 'O':
            char2 = 0b10100011;
            break;
        case 'p':
        case 'P':
            char2 = 0b10001100;
            break;
        case 'q':
        case 'Q':
            char2 = 0b10011000;
            break;
        case 'r':
        case 'R':
            char2 = 0b10101111;
            break;
        case 's':
        case 'S':
            char2 = 0b10010011;
            break;
        case 't':
        case 'T':
            char2 = 0b10000111;
            break;
        case 'u':
        case 'U':
            char2 = 0b11100011;
            break;
        case 'v':
        case 'V':
            char2 = 0b11000001;
            break;
        case 'w':
        case 'W':
            char2 = 0b11010101;
            break;
        case 'x':
        case 'X':
            char2 = 0b10001001;
            break;
        case 'y':
        case 'Y':
            char2 = 0b10010001;
            break;
        case 'z':
        case 'Z':
            char2 = 0b11100100;
            break;
    }
    return char2;
}