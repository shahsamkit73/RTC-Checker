#include <Wire.h>
#include "RTClib.h"
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define DS1307_CTRL_ID 0x68
#define OLED_RESET     4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
RTC_DS1307 RTC;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
char monthOfTheYear[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
String tz;
long hours;

const unsigned char myBitmap [] PROGMEM = 
{
  0x00, 0x00, 0xfc, 0x03, 0x00, 0x00, 0x00, 0xc0, 0xff, 0x3f, 0x00, 0x00,
 0x00, 0xf8, 0xff, 0xff, 0x01, 0x00, 0x00, 0x86, 0xff, 0x1f, 0x06, 0x00,
 0x80, 0x81, 0xff, 0x1f, 0x18, 0x00, 0xc0, 0x80, 0xff, 0x1f, 0x30, 0x00,
 0x20, 0x80, 0xff, 0x1f, 0xc0, 0x00, 0x10, 0x00, 0xff, 0x0f, 0x80, 0x01,
 0x08, 0x00, 0xff, 0x0f, 0x00, 0x01, 0x08, 0x00, 0xff, 0x0f, 0x00, 0x02,
 0x08, 0x00, 0xff, 0x0f, 0x00, 0x02, 0x08, 0x00, 0xfe, 0x07, 0x00, 0x02,
 0x08, 0x00, 0xfe, 0x07, 0x00, 0x02, 0x08, 0x00, 0xfe, 0x07, 0x00, 0x02,
 0x08, 0x00, 0x00, 0x00, 0x00, 0x06, 0x08, 0x00, 0x00, 0x00, 0x00, 0x06,
 0x08, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x06,
 0x0c, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x06,
 0x0c, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x06,
 0x0c, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x06,
 0x06, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x06,
 0x06, 0x00, 0x00, 0x00, 0x00, 0x0e, 0xc6, 0x07, 0x00, 0x00, 0x7c, 0x0e,
 0xe6, 0xff, 0xff, 0xff, 0xff, 0x0e, 0xe6, 0xff, 0x03, 0xf8, 0xff, 0x0c,
 0x02, 0x3f, 0x00, 0x80, 0x1f, 0x0c, 0x02, 0x00, 0x00, 0x00, 0x00, 0x0c,
 0x03, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x0c,
 0x03, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x0c,
 0x03, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00, 0x06,
 0x07, 0x00, 0x00, 0x00, 0x00, 0x06, 0x16, 0x00, 0x00, 0x00, 0x00, 0x06,
 0x2e, 0x00, 0x00, 0x00, 0x80, 0x07, 0x6e, 0x00, 0x00, 0x00, 0x40, 0x07,
 0x6e, 0x00, 0x00, 0x00, 0x60, 0x07, 0xde, 0x00, 0x00, 0x00, 0xb0, 0x07,
 0xde, 0x00, 0x00, 0x00, 0xb0, 0x07, 0x9c, 0x01, 0x00, 0x00, 0xd8, 0x03,
 0xbc, 0x01, 0x00, 0x00, 0xf8, 0x03, 0x3c, 0x01, 0x00, 0x00, 0xe8, 0x03,
 0x7c, 0x03, 0x00, 0x00, 0xf4, 0x03, 0xfc, 0x02, 0x00, 0x00, 0xf4, 0x03,
 0xfc, 0xc2, 0xff, 0x1f, 0xfa, 0x03, 0xf8, 0x25, 0xff, 0x27, 0xfa, 0x01,
 0xf8, 0x38, 0x00, 0x60, 0xf9, 0x01, 0xf8, 0x10, 0x00, 0xc0, 0xf8, 0x01,
 0xf0, 0x00, 0x00, 0x00, 0xf8, 0x01, 0xf0, 0x00, 0x00, 0x00, 0xf8, 0x01,
 0xf0, 0x00, 0xf8, 0x00, 0xf8, 0x00, 0xe0, 0xc1, 0xff, 0x0f, 0xf8, 0x00,
 0xc0, 0xe3, 0xff, 0x1f, 0x7c, 0x00, 0x80, 0xff, 0xff, 0x7f, 0x3e, 0x00,
 0x00, 0xff, 0xff, 0x7f, 0x0f, 0x00, 0x00, 0xf6, 0x00, 0xfe, 0x07, 0x00,
 0x00, 0x3c, 0x00, 0xb0, 0x01, 0x00, 0x00, 0x08, 0x00, 0x40, 0x00, 0x00
};

void setSQW(uint8_t value)
{
  Wire.beginTransmission(DS1307_CTRL_ID);
  Wire.write(7);
  Wire.write(value);
  Wire.endTransmission();
}

void setup()
{
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.drawBitmap(0, 0, myBitmap, 128, 64, WHITE);
  display.display();
  delay(1000);
  Wire.begin();
  RTC.begin();
  Wire.beginTransmission(0x68);
  Wire.write(1);
  if(Wire.endTransmission()!=0)
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(34,33);
    display.print("FAULTY RTC");
    display.display();
    delay(2000);
  }
  else
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(38,33);
    display.print("RTC FINE!");
    display.display();
    delay(2000);
  }
  if (!RTC.isrunning())
  {
    Serial.println("RTC is not running");
    RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  setSQW(0x10);
}

void loop()
{
  DateTime now = RTC.now();
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(33,7);
  display.print("RTC CHECKER");
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 25);
  if (now.hour() >= 12)
  {
    hours = now.hour() - 12;
    if (hours == 0)
    {
      hours = 12;
    }
  }
  else
  {
    hours = now.hour();
  }
  if (hours <= 9)
  {
    display.print("0");
  }
  display.print(hours, DEC);
  display.print(":");
  if (now.minute() <= 9)
  {
    display.print("0");
  }
  display.print(now.minute(), DEC);
  display.setTextSize(1);
  display.print(":");
  if (now.second() <= 9)
  {
    display.print("0");
  }
  display.print(now.second(), DEC);
  display.setTextSize(1);
  display.setCursor(66, 33);
  if(now.hour()<12 ? tz = "AM" : tz = "PM")
  display.print(tz);
  display.setTextSize(2);
  display.setCursor(85, 23);
  display.print(daysOfTheWeek[now.dayOfTheWeek()]);
  display.setTextSize(2);
  display.setCursor(1, 46);
  display.print(monthOfTheYear[now.month()-1]);
  display.print(" ");
  display.print(now.day(),DEC);
  display.print(",");
  display.setTextSize(1);
  display.setCursor(90,52);
  display.print(now.year(),DEC);
  display.display();

// -----------------------------------------------------------------------------------------------------------------------

  Serial.print(now.day(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.year(), DEC);
  Serial.print(" - ");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.print(" ");
  Serial.print(tz);
  Serial.print('\t');
  Serial.print( F("Compiled: "));
  Serial.print( F(__DATE__));
  Serial.print( F(", "));
  Serial.print( F(__TIME__));
  Serial.print( F(", "));
  Serial.println( F(__VERSION__));
  Serial.println();
  delay(1000);
}
