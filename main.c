/**
 * @file    PushButton.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "DataTypeDefinitions.h"
#include "MK64F12.h"
#define NUM_COLORES 5

void choose_color(int);
void delay(uint16 delay);
/*
 * @brief   Application entry point.
 */
int main(void) {
	/**Variable to capture the input value*/
	uint32 inputValueS2 = 0;
	uint32 inputValueS3 = 0;
	uint8 color_c = 0;

	/**Activating the GPIOB, GPIOC and GPIOE clock gating*/
	SIM->SCGC5 = 0x2E00;
	/**Pin control configuration of GPIOB pin22 and pin21 as GPIO*/
	PORTB->PCR[21] = 0x00000100;
	PORTB->PCR[22] = 0x00000100;
	/**Pin control configuration of GPIOC pin6 as GPIO with is pull-up resistor enabled*/
	PORTC->PCR[6] = 0x00000103;
	PORTA->PCR[4] = 0x00000103;
	/**Pin control configuration of GPIOE pin26 as GPIO*/
	PORTE->PCR[26] = 0x00000100;
	/**Assigns a safe value to the output pin21 of the GPIOB*/
	GPIOB->PDOR = 0x00200000;
	/**Assigns a safe value to the output pin22 of the GPIOB*/
	GPIOB->PDOR |= 0x00400000;
	/**Assigns a safe value to the output pin26 of the GPIOE*/
	GPIOE->PDOR |= 0x04000000;

	GPIOC->PDDR &=~(0x40);
	GPIOA->PDDR &=~(0x10);
	/**Configures GPIOB pin21 as output*/
	GPIOB->PDDR = 0x00200000;
	/**Configures GPIOB pin22 as output*/
	GPIOB->PDDR |= 0x00400000;
	/**Configures GPIOE pin26 as output*/
	GPIOE->PDDR |= 0x04000000;

    while(1)
    {
    	//copia valor en sw2 Y sw3
		inputValueS2 = GPIOC->PDIR;
		inputValueS3 = GPIOA->PDIR;
		/**Masks the GPIOC in the bit of interest*/
		inputValueS2 &= 0x40;
		inputValueS3 &= 0x10;
		/**Note that the comparison is not inputValur == False, because it is safer if we switch the arguments*/

		if(FALSE == inputValueS2)
		{
			color_c++;

			choose_color(color_c%NUM_COLORES);

			while(FALSE == inputValueS2)
			{
				inputValueS2 = GPIOC->PDIR;
				inputValueS3 = GPIOA->PDIR;
				/**Masks the GPIOC in the bit of interest*/
				inputValueS2 &= 0x40;
				inputValueS3 &= 0x10;
				if((FALSE == inputValueS2) && (FALSE == inputValueS3))
				{
					color_c--;
					GPIOB->PDOR &= ~(0x00400000);/**Read led on*/
					GPIOB->PDOR &= ~(0x00200000);/**Blue led on*/
					GPIOE->PDOR &= ~(0x4000000);/**Green led on*/

					while((FALSE == inputValueS3))
					{
						inputValueS3 = GPIOA->PDIR;
						inputValueS3 &= 0x10;
					}
				}
			}
		}

		else if(FALSE == inputValueS3)
		{
			color_c--;

			choose_color(color_c%NUM_COLORES);

			while(FALSE == inputValueS3)
			{
				inputValueS2 = GPIOC->PDIR;
				inputValueS3 = GPIOA->PDIR;
				/**Masks the GPIOC in the bit of interest*/
				inputValueS2 &= 0x40;
				inputValueS3 &= 0x10;
				if((FALSE == inputValueS2) && (FALSE == inputValueS3))
				{
					color_c++;
					GPIOB->PDOR &= ~(0x00400000);/**Read led on*/
					GPIOB->PDOR &= ~(0x00200000);/**Blue led on*/
					GPIOE->PDOR &= ~(0x4000000);/**Green led on*/

					while((FALSE == inputValueS2))
					{

						inputValueS2 = GPIOC->PDIR;
						inputValueS2 &= 0x40;
					}
				}
			}
		}
    }
    return 0 ;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
void delay(uint16 delay)
{
	volatile uint16 counter;

	for(counter=delay; counter > 0; counter--)
	{
	}
}

void choose_color(int color){
	switch(color)
				{
				case 0:
					GPIOB->PDOR |= 0x00200000;/**Blue led off*/
					GPIOB->PDOR |= 0x00400000;/**Read led off*/
					GPIOE->PDOR &= ~(0x4000000);
				break;
				case 1:
					GPIOB->PDOR |= 0x00400000;/**Read led off*/
					GPIOE->PDOR |= 0x4000000;/**Green led off*/
					GPIOB->PDOR &= ~(0x00200000);/**Blue led on*/
				break;
				case 2:
					GPIOE->PDOR |= 0x4000000;/**Green led off*/
					GPIOB->PDOR &= ~(0x00400000);/**Read led on*/
					GPIOB->PDOR &= ~(0x00200000);/**Blue led on*/
				break;
				case 3:
					GPIOB->PDOR &= ~(0x00400000);/**Read led on*/
					GPIOB->PDOR |= 0x00200000;/**Blue led off*/
					GPIOE->PDOR |= 0x4000000;/**Green led off*/
				break;
				case 4:
					GPIOB->PDOR &= ~(0x00400000);/**Read led on*/
					GPIOE->PDOR &= ~(0x4000000);/**Green led on*/
					GPIOB->PDOR |= 0x00200000;/**Blue led off*/
				break;
				}
}
