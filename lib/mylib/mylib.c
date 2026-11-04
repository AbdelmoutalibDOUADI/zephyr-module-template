#include <stdio.h>
#include <zephyr/kernel.h>
#include <lib/mylib.h>

void get_lib(char* output,int input){
	if(input==CONFIG_MYLIB_ANSWER){
		strcpy(output,"All rghit Abdeel !!!");
	}
	else sprintf(output,"%d",input);
}
