#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned int result;

volatile unsigned long duration;
int pulseInPin = 2;

//---------------------------------
// Analogue port read
// Lecture dde l'ADC 2 sur la pin 4
//---------------------------------
void analogRead() {
  duration = pulseIn(pulseInPin, HIGH);
  //result from XBee PWM is 0-65
  result = map(duration, 0, 64, 0, 2000);
}

//-----------------------------
// interruption mode CTC a 50hz
//-----------------------------
ISR(TIM0_COMPA_vect) {
  PORTB |= (1 << PB0);          // Pin 0 high
  _delay_loop_2(result + 2000);     // Waiting
  PORTB &= ~(1 << PB0);         // Pin 0 Low
}

//--------------------
// Programme principal
//--------------------
int main (void) {
  sei();                      // Enable global interrupts
  DDRB |= (1 << PB0);         // PB0 as output
  TCCR0A |= (1 << WGM01);           // Configure timer 0 for CTC mode
  TIMSK |= (1 << OCIE0A);             // Enable CTC interrupt
  TCCR0B |= (1 << CS02) | (1 << CS00) ;     // Prescaler clk/1024
  OCR0A = 156;                  // Set CTC pour execution 50hz
  pinMode(pulseInPin, INPUT);
  
  while (1) {
    analogRead();               // read pot value and refresh ValPot
  }
}
