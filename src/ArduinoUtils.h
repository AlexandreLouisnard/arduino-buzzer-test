/**
Some useful Arduino functions.

@author Alexandre Louisnard
2018

*/
#ifndef ARDUINO_UTILS
#define ARDUINO_UTILS

/**
* Emulation of the C printf() function.
*
* Usage:
* 		int l=2;
*  		char *j = "test";
*  		long k = 123456789;
*  		char s = 'g';
*  		float f = 2.3;
* 		ardprintf("test %d %l %c %s %f", l, k, s, j, f);
*
* Arduino setup() must call the usual Serial.begin(xxx).
*/
int ardprintf(char *str, ...);

#endif
