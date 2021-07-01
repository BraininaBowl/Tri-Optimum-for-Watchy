#include <Watchy.h> //include the Watchy library
#include "Teko_Medium36pt7b.h"
#include "Teko_Medium10pt7b.h"
#include "images.h"


class WatchFace : public Watchy { //inherit and extend Watchy class
  public:
 
 		void drawGlitch() {
 				int x, y, w ,f;
 				bool light = false;
 				for (int i = 0;random(1,6);1) {
 					// set dist width, position
 					w = random(4,40);
 					x = random(0,200-w);
 					y = random(0,200);
 					if (random(0,2) > 0) {
 						light = true;
 					}
 					display.fillRect(x,y,w,1,light ? GxEPD_WHITE : GxEPD_BLACK);
 				}
 		}
  
    void drawWatchFace() { //override this method to customize how the watch face looks
      
      int16_t  x1, y1, lasty;
      uint16_t w, h,h2;
      String textstring;

      // ** UPDATE **
      //at midnight everyday
      if(currentTime.Hour == 0 && currentTime.Minute == 0) {
        //resets step counter 
        sensor.resetStepCounter();
        //set time
        // setNetworkTime(); <= broken
      }

      // ** DRAW **
      
      //drawbg
      display.fillScreen(GxEPD_WHITE);
      display.drawBitmap(0, 0, bg, 200, 200, GxEPD_BLACK);

      //draw time
      display.setFont(&Teko_Medium36pt7b);
      display.setTextColor(GxEPD_BLACK);
      display.setTextWrap(false);
      textstring = currentTime.Hour;
			if (currentTime.Minute < 10) {
        textstring += ":0";
      } else {
        textstring += ":";
      }
      textstring += currentTime.Minute;
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
			display.fillRoundRect(100-w/2-10,126-h/2-8,w+20,h+18,6,GxEPD_BLACK);
			display.fillRoundRect(100-w/2-8,126-h/2-6,w+16,h+14,4,GxEPD_WHITE);
      display.setCursor(100-w/2, 126+h/2);
      display.print(textstring);

      //draw date and steps
      display.setFont(&Teko_Medium10pt7b);
      textstring = monthShortStr(currentTime.Month);
      textstring += " ";
      textstring += currentTime.Day;
      if (currentTime.Day%10 == 1 ) {
        textstring += "st";
      } else if (currentTime.Day%10 == 2 ) {
        textstring += "nd";
      } else if (currentTime.Day%10 == 3 ) {
        textstring += "rd";
      } else {
        textstring += "th";
      }
      textstring += "  |  ";
      textstring += sensor.getCounter();
      textstring += " stp";
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h2);
      display.setCursor(100-w/2, 126+h/2+12+h2);
      display.print(textstring);

      // draw battery
      float batt = (getBatteryVoltage()-3.3)/0.9;
      for (int i = 0; i <= batt*10; i++) {
        display.drawBitmap(100-(batt*40)+(i*8), 190, health, 8, 10, GxEPD_BLACK);
      }
      
      //drawGlitch();
    }
};

WatchFace m; //instantiate your watchface

void setup() {
  m.init(); //call init in setup
}

void loop() {
  // this should never run, Watchy deep sleeps after init();
}
 
