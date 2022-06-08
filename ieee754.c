#include <stdio.h>

#define FLOAT_BIT_SIZE sizeof(float)*8

void print_int_binary(void* x, int size) {
    //Using a char pointer
    char* super = (char*) x;

    for (int i = size/sizeof(char) - 1; i >= 0; --i) {
        for (int m = 8*sizeof(char) - 1; m >= 0; --m)
            putchar((super[i]>>m) & 0x01 ? '1' : '0');
        putchar(' ');
    }

    /*printf("\nUsing an int: ");
    for (int i = FLOAT_BIT_SIZE - 1; i >=0 ; --i) {
            putchar((sucker>>i) & 0x01 ? '1' : '0');
    }*/
}

int main(int argc, char const *argv[]) {    
    unsigned int cheat_f = 0;
    unsigned long cheat_d = 0;

    float f_val;       //0.000000000000000000000000000000000000000000001401298464329F
    double d_val;
       
    do {
        printf("Integer: %ld \n%23s "
            "\t\t\t %32s\n",cheat_d,
            "====FLOAT====",
            "====DOUBLE===="); 
        f_val = *((float *) &cheat_f);
        d_val = *((double *) &cheat_d);

        print_int_binary(&f_val, sizeof(f_val));
        printf(" \t ");
        print_int_binary(&d_val, sizeof(d_val));

        if (cheat_f + 1) {
            printf("\n%.17e", f_val);
            cheat_f++;
        }
        else {
            printf("\n%*c",35,'-');
        }
        printf("                  %.20le\n\n", d_val);
    } while (++cheat_d);

    return 0;
}