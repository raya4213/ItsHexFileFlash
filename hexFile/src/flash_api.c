
#include "flash_api.h"

/*! \brief Function to erase one page in the Application Table Section.
 *
 *  \note The maximum pageAddress must not be exceeded. The maximum number of 
 *        pages can be found in the datasheet. For the ATxmega128A1, the maximum
 *        number of pages in the application table is 16.
 *
 *  \param pageAddress Page address to the page to erase.
 */

//Original Code commented by Bhallaji @ 3/2/2017 @ 12:28 AM
// void EraseAppTablePage(uint8_t pageAddress)
// {
// 	 Calculate actual start address of the page.
// 	uint32_t tableAddress = (pageAddress * FLASH_PAGE_SIZE);
// 	
// 	 Perform page erase. 
// 	SP_EraseApplicationPage(APP_SECTION_START + tableAddress);
// 
// 	 Wait for NVM to finish. 
// 	SP_WaitForSPM();
// 	NVM.CMD = NVM_CMD_NO_OPERATION_gc;
// }

// Modifying for test purposes by Bhallaji @ 3/2/2017 @ 12:28 AM

void EraseAppTablePage(uint32_t pageAddress)
{
	/* Calculate actual start address of the page.*/
	uint32_t tableAddress = (pageAddress * FLASH_PAGE_SIZE);
	
	/* Perform page erase. */
	SP_EraseApplicationPage(APP_SECTION_START + tableAddress);

	/* Wait for NVM to finish. */
	SP_WaitForSPM();
	NVM.CMD = NVM_CMD_NO_OPERATION_gc;
}



/*! \brief Function to do an atomic erase-write on one page in the Application Table Section.
 *
 *  \note The maximum pageAddress must not be exceeded. The maximum number of 
 *        pages can be found in the datasheet. For the ATxmega128A1, the maximum
 *        number of pages in the application table is 16.
 

 *  \param pageAddress Page address to the page to erase/write.
 */

//Original Code commented by Bhallaji @ 3/2/2017
// void EraseWriteAppTablePage(uint8_t pageAddress)
// {
// 	 Calculate actual start address of the page.
// 	uint32_t tableAddress = (pageAddress * FLASH_PAGE_SIZE);
// 	
// 	Perform page erase. 
// 	SP_EraseWriteApplicationPage(APP_SECTION_START + tableAddress);
// 
// 	Wait for NVM to finish. 
// 	SP_WaitForSPM();
// 	NVM.CMD = NVM_CMD_NO_OPERATION_gc;
// }

// Modifying for test purposes by Bhallaji @ 3/2/2017 @ 12:20 AM
void EraseWriteAppTablePage(uint32_t pageAddress)
{
	/* Calculate actual start address of the page.*/
	uint32_t tableAddress = (pageAddress * FLASH_PAGE_SIZE);

	/* Perform page erase. */
	SP_EraseWriteApplicationPage(APP_SECTION_START + tableAddress);

	/* Wait for NVM to finish. */
	SP_WaitForSPM();
	NVM.CMD = NVM_CMD_NO_OPERATION_gc;
}


/*! \brief Function to program one page in the Application Table Section.
 *
 *  \note The maximum pageAddress must not be exceeded. The maximum number of 
 *        pages can be found in the datasheet. For the ATxmega128A1, the maximum
 *        number of pages in the application table is 16.
 *
 *  \param pageAddress Page address to the page to write.
 */

//Original Code commented by Bhallaji @ 3/2/2017 @ 12:29 AM
// void WriteAppTablePage(uint8_t pageAddress)
// {
// 	 Calculate actual start address of the page.
// 	uint32_t tableAddress = (pageAddress * FLASH_PAGE_SIZE);
// 	
// 	 Perform page write. 
// 	SP_WriteApplicationPage(APP_SECTION_START + tableAddress);
// 
// 	 Wait for NVM to finish. 
// 	SP_WaitForSPM();
// 	NVM.CMD = NVM_CMD_NO_OPERATION_gc;
// }

// Modifying for test purposes by Bhallaji @ 3/2/2017 @ 12:29 AM
void WriteAppTablePage(uint32_t pageAddress)
{
	/* Calculate actual start address of the page.*/
	uint32_t tableAddress = (pageAddress * FLASH_PAGE_SIZE);
	
	/* Perform page write. */
	SP_WriteApplicationPage(APP_SECTION_START + tableAddress);

	/* Wait for NVM to finish. */
	SP_WaitForSPM();
	NVM.CMD = NVM_CMD_NO_OPERATION_gc;
}


/*! \brief Function to load one word into page buffer.
 *
 *  \param tableAddress Address in buffer to write the word.
 *  \param lowByte      The low byte of the word to load.
 *  \param highByte     The high byte of the word to load.
 */
void LoadAppTableWord(uint16_t tableAddress, uint8_t lowByte, uint8_t highByte)
{
	/* Perform word load. */
	SP_LoadFlashWord(tableAddress, ((uint16_t) highByte << 8) | lowByte);

	/* Wait for NVM to finish. */
	SP_WaitForSPM();
	NVM.CMD = NVM_CMD_NO_OPERATION_gc;
}


/*! \brief Function to read a flash page.
 *
 *  \note The maximum pageAddress must not be exceeded. The maximum number of 
 *        pages can be found in the datasheet. For the ATxmega128A1, the maximum
 *        number of pages in the application table is 16.
 *
 *  \param data         Pointer to a data buffer to store the data.
 *  \param pageAddress  Page address to read from. 
 */
void ReadFlashPage(const uint8_t * data, uint8_t pageAddress)
{
	/* Calculate actual start address of the page.*/
	uint32_t tableAddress = (pageAddress * FLASH_PAGE_SIZE);
	
	/* Read the flash page into the buffer. */
	SP_ReadFlashPage(data, APP_SECTION_START + tableAddress);
	NVM.CMD = NVM_CMD_NO_OPERATION_gc;
}


static inline void NVM_EXEC_WRAPPER_FLASH(void)
{
	// Save the Sleep register
	uint8_t sleepCtr = SLEEP.CTRL;
	// Set sleep mode to IDLE
	SLEEP.CTRL = (SLEEP.CTRL & ~SLEEP.CTRL) | SLEEP_SMODE_IDLE_gc;
	// Save the PMIC Status and control registers
	uint8_t statusStore = PMIC.STATUS;
	uint8_t pmicStore = PMIC.CTRL;
	
	// Enable only the highest level of interrupts
	PMIC.CTRL = (PMIC.CTRL & ~(PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm)) | PMIC_HILVLEN_bm;
	// Save SREG for later use
	uint8_t globalInt = SREG;
	// Enable global interrupts
	sei();
	// Set sleep enabled
	SLEEP.CTRL |= SLEEP_SEN_bm;
	// Save eeprom interrupt settings for later
	uint8_t spmintStore = NVM.INTCTRL;
	NVM_EXEC();
	// Enable EEPROM interrupt
	NVM.INTCTRL =  NVM_SPMLVL0_bm | NVM_SPMLVL1_bm;
	// Sleep before 2.5uS has passed
	sleep_cpu();
	// Restore sleep settings
	SLEEP.CTRL = sleepCtr;
	// Restore PMIC status and control registers
	PMIC.STATUS = statusStore;
	PMIC.CTRL = pmicStore;
	// Restore EEPROM interruptsettings
	NVM.INTCTRL = spmintStore;
	// Restore global interrupt settings
	SREG = globalInt;
}

/*! \brief Example to show how to read and write to the flash.
 */

void writeRead(uint8_t* WriteBuffer, uint32_t pageNumber) 
{
	
	
	//ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		//PMIC.CTRL &= ~(PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm);
		//NONATOMIC_BLOCK(NONATOMIC_RESTORESTATE){
			
		//}
		//uint8_t success = 1;
		///* Load the flashbuffer with the test buffer. */
		/* Calculate actual start address of the page.*/
		uint32_t tableAddress = (pageNumber * FLASH_PAGE_SIZE);
		
		SP_LoadFlashPage(WriteBuffer);
		SP_WaitForSPM();
		
		SP_EraseWriteApplicationPage(tableAddress);
		NVM.CMD = NVM_CMD_ERASE_WRITE_APP_PAGE_gc;
		NVM_EXEC();
		NVM.CMD = NVM_CMD_NO_OPERATION_gc;
//
	///* Calculate actual start address of the page.*/
	//uint32_t tableAddress = (pageAddress * FLASH_PAGE_SIZE);
//
	///* Perform page erase. */
	//SP_EraseWriteApplicationPage(APP_SECTION_START + tableAddress);
//
	///* Wait for NVM to finish. */
	//SP_WaitForSPM();
	//NVM.CMD = NVM_CMD_NO_OPERATION_gc;

		
		//NVM_EXEC_WRAPPER_FLASH();

		/* Read a flashpage into the read buffer. */
		//ReadFlashPage(ReadBuffer,pageTowrite);

		/* Verify Flash contents. */
		//for (uint16_t i = 0; i < FLASH_PAGE_SIZE; i++) {
			////printf("%d ",ReadBuffer[i] );
			//if (ReadBuffer[i] != WriteBuffer[i]){
				//success = 0;
				//break;
			//}
		//}
		
		//printf("\n\rsuccess 2nd attempt %hu\n\r", success);
		//success = 1;
		
	//}
}


//void writeRead(void) 
//{
	///* Assume success until proven otherwise. */
	//int success = 1;	
	//
	///*  If success, try with another method using load/read flash page function
	 //*  and an erase-write of the page.
	 //*/
	//if (success) {
//
		///* Fill up a test buffer with 512 bytes with other values. */
		//for (uint16_t i = 0; i < FLASH_PAGE_SIZE; i++) {
			//WriteBuffer[i] = (uint8_t) i;
		//}
//
		///* Load the flashbuffer with the test buffer. */
		//SP_LoadFlashPage(WriteBuffer);
		//NVM.CMD = NVM_CMD_NO_OPERATION_gc;
//
		///* Do a Erase-Write of the page. */
		//EraseWriteAppTablePage(16);
//
		///* Read a flashpage into the read buffer. */
		//ReadFlashPage(ReadBuffer, 16);
//
		///* Verify Flash contents. */
		//for (uint16_t i = 0; i < FLASH_PAGE_SIZE; i++) {
			//printf(" ReadBuffer %d\n\r",ReadBuffer[i] );
			//if (ReadBuffer[i] != WriteBuffer[i]){
				//success = 0;
				//break;
			//}
		//}
		//
		//printf("\n\rsuccess 2nd attempt %d\n\r", success);
		//success = 1;
	//}
	//
	//
//}

