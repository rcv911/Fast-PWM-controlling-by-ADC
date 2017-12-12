#include <avr\io.h>
#include <avr\interrupt.h>
#include <avr\signal.h>

ISR(ADC_vect){
  	TIFR|=(1<<OCF1B); //"Output Compare 1 B"
	OCR1A = ADCH;  //8bit 0-255	
}

void adc_init(void) {
 	ADMUX=(1<<REFS0)|(1<<ADLAR); //ADC0 SE, VREF=AVCC, 8bit (<-left)
	SFIOR=(1<<ADTS2)|(1<<ADTS0);
	ADCSRA=(1<<ADEN)|(1<<ADATE)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADSC);
}

int main(void) {
	//led
	DDRC = 255;
	PORTC = 0;
	// t/c1
	// fast PWM 8bit, CLK/256, TOP(ICR1)=0x00ff
	TCCR1A=(1<<COM1A1)|(0<<WGM11)|(1<<WGM10);
	TCCR1B=(0<<WGM13)|(1<<WGM12)|(1<<CS12);

	OCR1A=0;
	TCNT1=0;
	
	adc_init();
	
	asm("sei");
	
	while(1) {
		asm("nop");	
	}

}
