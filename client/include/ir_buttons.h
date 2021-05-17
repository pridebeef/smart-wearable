/*
 * hex values for IR remote buttons. 
 * unless you have the same remote and read values as i do, 
 * you should change these.
 */

#define IR_BUTTON1 0xFD00FF
#define IR_BUTTON2 0xFD807F
#define IR_BUTTON3 0xFD40BF

#define IR_BUTTON4 0xFD20DF
#define IR_BUTTON5 0xFDA05F
#define IR_BUTTON6 0xFD609F

#define IR_BUTTON7 0xFD10EF
#define IR_BUTTON8 0xFD906F
#define IR_BUTTON9 0xFD50AF

#define IR_BUTTON10 0xFD30CF
#define IR_BUTTON11 0xFDB04F
#define IR_BUTTON12 0xFD708F

#define IR_BUTTON13 0xFD08F7 // 1
#define IR_BUTTON14 0xFD8877 // 2
#define IR_BUTTON15 0xFD48B7 // 3

#define IR_BUTTON16 0xFD28D7 // ...
#define IR_BUTTON17 0xFDA857
#define IR_BUTTON18 0xFD6897

#define IR_BUTTON19 0xFD18E7
#define IR_BUTTON20 0xFD9867
#define IR_BUTTON21 0xFD58A7 // 9

#define IR_NO_INPUT 0x000000

/*
 * how to find your own:

 * spin this up and record the values
 * note: you could totally use Serial.println() for this
 *       my board randomly stopped working over serial?
 *       so i just drew to the screen. copy and pasting would have
 *       been nice but it's worth not even trying to troubleshoot that

#include <IRrecv.h>
#include <IRutils.h>

TFT_eSPI tft = TFT_eSPI();
IRrecv irrecv(4);               // whatever pin you're using for IR

void setup(void) {
	tft.begin();
	tft.setRotation(1);
	tft.fillScreen(TFT_BLACK);
	irrecv.enableIRIn();
	tft.setTextColor(TFT_WHITE, TFT_BLUE);
}

void loop() 
{	
	decode_results results;
	if (irrecv.decode(&results)) {
		if ((uint32_t)results.value != 0xFFFFFFFF) {
			// really hasty i promise i don't actually write code like this
			char buffer[9];
			sprintf(buffer, "%X", (uint32_t)results.value);
			tft.drawString(buffer, 50, 50);
		}
    	irrecv.resume();
    }
}

  */

