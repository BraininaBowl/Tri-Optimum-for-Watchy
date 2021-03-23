#include <Watchy.h> //include the Watchy library
#include "BarlowCondensed_Bold36pt7b.h"
#include "BarlowCondensed_Bold10pt7b.h"
#include "images.h"
				

class WatchFace : public Watchy { //inherit and extend Watchy class
  public:
    void drawWatchFace() { //override this method to customize how the watch face looks
      
      int16_t  x1, y1, lasty;
      uint16_t w, h,h2;
      String textstring;
      
      //drawbg
      display.fillScreen(GxEPD_WHITE);
      display.drawBitmap(0, 0, bg, 200, 200, GxEPD_BLACK);

      //draw time
      display.setFont(&BarlowCondensed_Bold36pt7b);
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
      display.setFont(&BarlowCondensed_Bold10pt7b);
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
    }
};

WatchFace m; //instantiate your watchface

void setup() {
  m.init(); //call init in setup
}

void loop() {
  // this should never run, Watchy deep sleeps after init();
}
 
