/* $CSK: lesson1.c,v 1.2 2008/09/28 07:46:59 ckuethe Exp $ */
/*
 * Copyright (c) 2008 Chris Kuethe <chris.kuethe@gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#define F_CPU 8000000 
#include <avr/io.h>
#include <util/delay.h>

/*
 * Assumptions:
 * 	- LED connected to PORTB
 * 	- F_CPU is defined to be your cpu speed (preprocessor define)
 */

void sleep(double sec)
{
	double maxms, last;
	int sleeps;

	sec *= 1000.0; /* turn seconds into milliseconds */
	maxms = 262144000 / F_CPU;
	sleeps = sec / maxms;
	last = sec - (sleeps * maxms);

	while (sleeps--)
		_delay_ms(maxms);
	_delay_ms(last);
	return;
}

int main (void)
{
	/* set PORTB for output*/
	DDRB = 0xFF;

	while (1) {
		/* set PORTB high */
		PORTB = 0xFF;
		sleep(0.5);

		/* set PORTB low */
		PORTB = 0x00;
		sleep(0.5);
	}
	return 0;
}
