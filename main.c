#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include <stdio.h>

#include <LUFA/Drivers/Board/LEDs.h>

#include "usb.h"

int
main(void)
{
	/* Disable watchdog */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);

	LEDs_Init();
	usb_init();

	sei();

	char c;
	for (;;) {
		c = getchar();

		switch (c) {
		case '1':
			printf("ok\r\n");
			LEDs_TurnOnLEDs(LEDS_LED1);
			break;

		case '0':
			printf("ok\r\n");
			LEDs_TurnOffLEDs(LEDS_LED1);
			break;

		default:
			printf("error\r\n");
		}
	}
}
