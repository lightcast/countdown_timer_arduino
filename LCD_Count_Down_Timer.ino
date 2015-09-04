
// This is based off of a Sparkfun LCD 
// I followed this tutorial https://www.sparkfun.com/tutorials/246 and modified it for my countdown timer
// This sketch is for Arduino versions 1.0 and later
// If you're using an Arduino version older than 1.0, use
// the other example code available on the tutorial page.

// Use the softwareserial library to create a new "soft" serial port
// for the display. This prevents display corruption when uploading code.
#include <SoftwareSerial.h>

int days = 47;
int hours = 2; // start hours
int minutes = 0; //start min
int seconds = 0; //start seconds
char colon = ':';
boolean  exitLoop = false;
// Attach the serial display's RX line to digital pin 2
SoftwareSerial mySerial(3,2); // pin 2 = TX, pin 3 = RX (unused)

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600); // set up serial port for 9600 baud
  delay(500); // wait for display to boot up
  mySerial.write(254); // move cursor to beginning of first line
  mySerial.write(128);

  mySerial.write("                "); // clear display
  mySerial.write("                ");

  mySerial.write(254); // move cursor to beginning of first line
  mySerial.write(128);
 
  mySerial.write("Tawain CountDown");
  delay(150);  //wait a bit

  
}

void loop()
{   
  while(hours > 0 || minutes >0 || seconds >=0){
    String strDays = (days < 10) ? "0" + String(days, DEC) : String(days, DEC);
    String strHours = (hours < 10) ? "0" + String(hours, DEC) : String(hours, DEC); 
    String strMinutes = (minutes < 10) ? "0" + String(minutes, DEC) : String(minutes, DEC);
    String strSeconds = (seconds < 10) ? "0" + String(seconds, DEC) : String(seconds, DEC);
    //Serial.print(strSeconds);
    String results = String(strDays + colon + strHours + colon + strMinutes + colon + strSeconds);
    mySerial.write(254); // move cursor to beginning of first line
    mySerial.write(128);
   
    mySerial.write("Tawain CountDown");
    mySerial.print(results);
    if(exitLoop == 1){
      break;
    }
    countDown();
    delay(1000);
  }
  
      mySerial.write(254); // move cursor to beginning of first line
      mySerial.write(128);
      mySerial.write("                "); // clear display
      mySerial.write("                ");
      mySerial.write("Tawain CountDown");
      mySerial.write("Done!!!");
      while(1); // wait forever
}


void countDown(){
  if(seconds > 0) {
    seconds -= 1;
  }else{
     if(minutes > 0){
      seconds = 59;
      minutes -=1;
    }else if(hours > 0){
      minutes = 59;
      seconds = 59;
      hours -=1;
    }else if(days > 0){
      hours = 24;
      minutes = 59;
      seconds = 59;
      days -=1;
    }else{
      exitLoop = true;
    }
  }
}
