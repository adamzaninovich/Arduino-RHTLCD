/*  rhtlcd.c
    
    This will loop every 2 seconds,
    read temp and rel humidity from a RHT03/DHT22 sensor,
    and display the values on an LCD
    
    RHT Setup:
    * RHT Data pin to digital pin 2
    
    LCD Setup:
    * LCD RS pin to digital pin 12
    * LCD Enable pin to digital pin 11
    * LCD D4 pin to digital pin 7
    * LCD D5 pin to digital pin 6
    * LCD D6 pin to digital pin 5
    * LCD D7 pin to digital pin 4
    * LCD R/W pin to ground
    * 10K potentiometer:
    * ends to +5V and ground
    * wiper to LCD VO pin (pin 3)
    
*/

// include LCD Library Code
#include <LiquidCrystal.h>

// include RHT Library Code
#include <DHT22.h>

// func prototypes
void printError(char *string);

// initialize the LCD with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

// initialize RHT with data pin (2)
DHT22 rht(2);

void setup() {
  // set the LCD's number of cols and lines
  lcd.begin(16, 2);
  
  // print a message
  lcd.print('RHTLCD Starting');
  delay(1000);
}

void loop() {
  DHT22_ERROR_t errorCode;
  lcd.setCursor(0, 0);
  delay(2000);
  lcd.print('Requesting Data');
  errorCode = rht.readData();
  lcd.clear();
  switch(errorCode) {
    case DHT_ERROR_NONE:
      lcd.print('T:  ' << rht.getTemperatureC() << 'C');
      lcd.setCursor(0, 1);
      lcd.print('RH: ' << rht.getHumidity() << '%');
      break;
    case DHT_ERROR_CHECKSUM:
      lcd.print('T:  ' << rht.getTemperatureC() << 'C *');
      lcd.setCursor(0, 1);
      lcd.print('RH: ' << rht.getHumidity() << '% *');
      break;
    case DHT_BUS_HUNG:
      printError('BUS Hung');
      break;
    case DHT_ERROR_NOT_PRESENT:
      printError('Not Present');
      break;
    case DHT_ERROR_ACK_TOO_LONG:
      printError('ACK timeout');
      break;
    case DHT_ERROR_SYNC_TIMEOUT:
      printError('Sync timeout');
      break;
    case DHT_ERROR_DATA_TIMEOUT:
      printError('Data timeout');
      break;
    case DHT_ERROR_TOOQUICK:
      printError('Poll too quickly');
      break;
  }
}

void printError(char *msg) {
  lcd.print('**** ERROR ****');
  lcd.setCursor(0, 1);
  lcd.print(msg);
}