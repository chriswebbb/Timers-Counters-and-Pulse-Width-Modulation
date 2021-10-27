#include <avr/io.h>
#include <util/delay.h>
#include "et_scale.h"

#define FREQ 262

unsigned long toneClock = 8;   /* set at timer initialisation and used to calculate TOP when setting frequency */

void init_tone(void);
void tone(uint16_t frequency);

int main(void) {

    init_tone();
	
    int direction = 0;	//0 means its counting up and 1 means down
	int i = 0;
	
    for (;;){
		if (i<0){
			direction = 0;
		}
		if(i>ET_SCALE_TOP){
			direction = 1;
		}
		if (direction == 0){
			i++;
		}else{
			i--;
		}
		_delay_ms(2000);
		tone(et_scale[i]);
	}
}

/* init_tone ---
   Setup timer as a tone frequency oscillator.
*/
void init_tone(void)
{
    DDRD |= _BV(PD5);
	TCCR1A = _BV(COM1A0) | _BV(WGM10);
	TCCR1B = _BV(WGM13) | _BV(CS11);
}

/* tone ---
   Set oscillator output to desired frequency
*/
void tone(uint16_t frequency)
{
	OCR1A = (uint16_t)(F_CPU/(2*2*toneClock*frequency));
}


