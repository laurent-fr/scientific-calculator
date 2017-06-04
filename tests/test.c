/** Test suite
*
*
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "display.h"
#include "number.h"

extern unsigned char display_mem[];

int exit_code=0;

void printf_test(char *t) {
	printf("\n***\n* %s\n*\n",t);
}

void printf_display_mem(char *answer) {
	int i;
	char s[100];

	sprintf(s,"%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",
		display_mem[0],display_mem[1],display_mem[2],display_mem[3],
		display_mem[4],display_mem[5],display_mem[6],display_mem[7],
		display_mem[8],display_mem[9],display_mem[10],display_mem[11]);
	
	printf("Display mem : %s ",s);

	if (!strcmp(s,answer))
		printf(" - OK");
	else {
		printf(" - ERROR should be %s",answer);
		exit_code=-1;
	}
	printf("\n");

}

void printf_number(t_number *n, char *answer) {
	int i;
	char s[100];

	sprintf(s,"%02x %02x %02x %02x %02x %02x / %02x %02x",
		n->m[0],n->m[1],n->m[2],n->m[3],n->m[4],n->m[5],
		n->e[0],n->e[1]);

	printf("Number : %s ",s);
	if (!strcmp(s,answer))
		printf(" - OK");
	else {
		printf(" - ERROR should be %s",answer);
		exit_code=-1;
	}
	printf("\n");	
}

void test_disp_add_digit() {

	int i;

	char *number_answers[] = {
"0b 0b 0b 0b 0b 0b 0b 0b 10 0b 0b 0b",
"0b 0b 0b 0b 0b 0b 0b 00 11 0b 0b 0b",
"0b 0b 0b 0b 0b 0b 00 01 12 0b 0b 0b",
"0b 0b 0b 0b 0b 00 01 02 13 0b 0b 0b",
"0b 0b 0b 0b 00 01 02 03 14 0b 0b 0b",
"0b 0b 0b 00 01 02 03 14 05 0b 0b 0b",
"0b 0b 00 01 02 03 14 05 06 0b 0b 0b",
"0b 00 01 02 03 14 05 06 07 0b 0b 0b",
"0b 01 02 03 14 05 06 07 08 0b 0b 0b",
"0b 01 02 03 14 05 06 07 08 0b 0b 0b",
"0a 01 02 03 14 05 06 07 08 0b 0b 0b",
"0b 01 02 03 14 05 06 07 08 0b 0b 0b",
"0b 01 02 03 14 05 06 07 08 0b 00 01",
"0b 01 02 03 14 05 06 07 08 0b 01 02",
"0b 01 02 03 14 05 06 07 08 0b 01 02",
"0b 01 02 03 14 05 06 07 08 0a 01 02",
"0b 01 02 03 14 05 06 07 08 0b 01 02"
	};

	printf_test("disp_add_digit");

	// 0.
	disp_init();	
	printf_display_mem(number_answers[0]);	

	// 1. , 12. , 123. ... , 12345678.
	for(i=1;i<=8;i++) {
		disp_add_digit(i);
		printf_display_mem(number_answers[i]);	
		if (i==4) disp_move_dot();
	}

	// 9th number -> does nothing
	disp_add_digit(1);
	printf_display_mem(number_answers[9]);

	// -12345678.
	disp_change_sign();
	printf_display_mem(number_answers[10]);	

	// 12345678.
	disp_change_sign();
	printf_display_mem(number_answers[11]);	

	// 12345678.E12
	disp_mod_exponent();
	disp_add_digit(1);
	printf_display_mem(number_answers[12]);
	disp_add_digit(2);
	printf_display_mem(number_answers[13]);	

	// 3rd number -> does nothing
	disp_add_digit(1);
	printf_display_mem(number_answers[14]);

	// 12345678.E-12
	disp_change_sign();
	printf_display_mem(number_answers[15]);	

	// 12345678.E12
	disp_change_sign();
	printf_display_mem(number_answers[16]);


}

void test_disp_to_number() {

	int i;
	t_number n;

	printf_test("disp_to_number");

	// 0.
	disp_init();	
	printf_display_mem("0b 0b 0b 0b 0b 0b 0b 0b 10 0b 0b 0b");	
	disp_to_number(&n);
	printf_number(&n,"00 00 00 00 00 00 / 00 00");
	
	// 321.
	disp_init();
	display_mem[8]=0x11;
	display_mem[7]=0x02;
	display_mem[6]=0x03;
	printf_display_mem("0b 0b 0b 0b 0b 0b 03 02 11 0b 0b 0b");	
	disp_to_number(&n);
	printf_number(&n,"00 00 00 01 23 00 / 02 00");

	// -1.
	disp_init();
	display_mem[8]=0x11;
	disp_change_sign();
	printf_display_mem("0a 0b 0b 0b 0b 0b 0b 0b 11 0b 0b 0b");	
	disp_to_number(&n);
	printf_number(&n,"00 00 00 01 23 00 / 02 00");

	// 1E-3
	disp_init();
	display_mem[8]=0x11;
	display_mem[10]=0x00;
	disp_mod_exponent();
	display_mem[11]=0x03;
	disp_change_sign();
	printf_display_mem("0b 0b 0b 0b 0b 0b 0b 0b 11 0a 00 03");	
	disp_to_number(&n);
	printf_number(&n,"00 00 00 00 01 00 / 97 99");


}


void main() {

	test_disp_add_digit();
	test_disp_to_number();

	if (exit_code==0) 
		printf("\nSUCCESS !\n");
	else
		printf("\nFAILURE !\n");

	exit(exit_code);
}



