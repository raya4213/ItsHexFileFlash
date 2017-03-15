#include "user_template.h"

/*
 * Any code in this function will be run once, when the robot starts.
 */


void init()
{
	set_rgb(255,0,0);
}

/*
 * The code in this function will be called repeatedly, as fast as it can execute.
 */

void loop()
{

}

/*
 * After each pass through loop(), the robot checks for all messages it has 
 * received, and calls this function once for each message.
 */
 void handle_msg(ir_msg* msg_struct)
 {		
	 
 }


///*
 //*	The function below is optional - commenting it in can be useful for debugging if you want to query
 //*	user variables over a serial connection.
 //*/
 
// TODO: data_pointer has possible currency issues. Add Semaphore.
// int16_t counterForTransmit = -1; 
 
//  void send_code_packet(){
// 	set_rgb(255,0,0);
// 	uint8_t length = strlen(data_pointer);
// 
// 	ir_send(ALL_DIRS,data_pointer,length);
// 					//if (counterForTransmit%32 == 0 && counterForTransmit > 0)
// 					//{
// 					//set_rgb(0,255,0);
// 					//delay_ms(2000);
// 					//}
// 	waitForTransmission(ALL_DIRS);
// 	printf("Done\r\n");
// 	set_rgb(0,0,0);
//  }
 
 //send multiple data and receive

uint8_t user_handle_command(char* command_word, char* command_args)
{
	
// 	if (command_word[0]=='!' && command_word[1]==0)
// 	{		
// 		//TODO: data_pointer has possible currency issues. Add Semaphore.
// 		strcpy(data_pointer, command_args);
// 		schedule_task(20, send_code_packet, NULL); 
// 				
// 		return 1;
// 	}
	return 0;	
}

///*
 //*	The function below is optional - if it is commented in, and the leg interrupts have been turned on
 //*	with enable_leg_status_interrupt(), this function will get called when that interrupt triggers.
 //*/	
//void	user_leg_status_interrupt()
//{
	//
//}