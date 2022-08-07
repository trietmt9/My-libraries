/*
 * Servo.c
 *
 * Created: 8/7/2022 9:08:01 PM
 *  Author: pc
 */ 
#include <avr/io.h>
#include <Servo.h>
void Servo_init()
{
	//inverting mode
	TCCR1A = (1<<COM1A1) | (1<<COM1A0) | (1<<WGM11);
	TCCR1B = (1<< WGM13) | (1<< WGM12) | (1<<CS11); //using 1024 bit prescaler
	//0-39999 equal to 20ms 20000
	ICR1 = 39999;
}

void Servo_write(int a)
{
	OCR1A = ICR1 - ((10*a) + 700);
}
