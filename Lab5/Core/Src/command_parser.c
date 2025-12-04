/*
 * command_parser.c
 *
 *  Created on: Dec 4, 2025
 *      Author: Admin
 */

#include "global.h"
#include <string.h>
uint8_t state = INIT_PARSE;

  void command_parser_fsm(void) {
	  switch (state){
	   case INIT_PARSE:
		   if (temp == '!'){
			   idx_data = 0;
			   memset(command_data, 0, MAX_BUFFER_SIZE );
			   state = WAIT_PARSE;

		   }
		   break;
	   case WAIT_PARSE:
		   if (temp == '#'){
			   command_flag = 1;
			   command_data[idx_data] = '\0';
			   state = INIT_PARSE;
		   }else if(temp == '!'){
			   idx_data = 0;
			   memset(command_data, 0, MAX_BUFFER_SIZE );
		   }else{
			   command_data[idx_data++] = temp;
			   if (idx_data >= MAX_BUFFER_SIZE){
				   idx_data = 0;
			   }
		   }
		   break;
	   default:
		   state = INIT_PARSE;
	  }
}
