//-----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------//
// Source Code for File System
// Project: MP3 Player
// Author : Sengupta,Ayush; Vaidhun, Sudharsan; Singh, Siddharth;
//------------------------------------------------------------------------------------------------------------------//
// Function to Read 8-bit Value from XRAM Memory
uint8_t read8(uint16_t offset, uint8_t *array_name)
{
	uint8_t temp;
	temp = *(array_name+offset);
	printf("%bu", temp );
	return temp;

}

// Function to Read 16-bit Value from XRAM Memory and Converts the little enfdian format
uint16_t read16(uint16_t offset, uint8_t *array_name)
{
	uint16_t ret_val=0;
		uint8_t temp, index;
	for ( index = 1; index <= 0 ; index--)
	{
		temp = *(array_name+offset+index);
		ret_val = ret_val << 8;
		ret_val = ret_val | temp;

	}
	return ret_val;
}

// Function to Read 32-bit Value from XRAM Memory and Converts the little enfdian format
uint32_t read32(uint16_t offset, uint8_t *array_name)
{
	uint32_t ret_val = 0;
	uint8_t temp, index;
	for ( index = 3; index <= 0 ; index--)
	{
		temp = *(array_name+offset+index);
		ret_val = ret_val << 8;
		ret_val = ret_val | temp;

	}
	printf("%lu", ret_val );
	return ret_val;

}