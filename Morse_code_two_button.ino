#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(5,6);
long previousMillis = 0;
const int dotButton = 2;
const int dashButton = 3;
const int buzzerPin = 4;
const int ledDotPin = 7;
const int ledDashPin = 8;

int buttonDotState = 0;
int buttonDashState = 0;
int aWordMorse;



void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(dotButton, INPUT);
  pinMode(dashButton, INPUT);
  pinMode (ledDotPin, OUTPUT);
  pinMode(ledDashPin, OUTPUT);
  pinMode (buzzerPin, OUTPUT);
  Serial.println("Initializing...");
  delay(5000);
  Serial.println("Start typing Morse Code"); 
}
void loop() 
{
  unsigned long currentMillis =  millis();
  const int intervalchar = 1000;
  const int intervalword = 3000;
  int spacing = 0;
 for(int a = 0; a < 5 ; a++)
  {
    previousMillis = currentMillis;
    int k = 2; //Used to end loop
    while(k != 0)
    {
      currentMillis =  millis();//reset counter
      buttonDotState = digitalRead(dotButton);
      buttonDashState = digitalRead(dashButton);
  
      if(buttonDotState == HIGH && buttonDashState == LOW)
      {
        aWordMorse = 1 + aWordMorse*10;
        k=0;
        digitalWrite(ledDotPin,HIGH); 
        delay(100);
        digitalWrite(ledDotPin,LOW);
        previousMillis = currentMillis;//reset counter
      }
      else if(buttonDotState == LOW && buttonDashState == HIGH)
      {
        aWordMorse = 2 + aWordMorse*10;
        k = 0;
        digitalWrite(ledDashPin,HIGH);
        delay(100);
        digitalWrite(ledDashPin,LOW);
        previousMillis = currentMillis;//reset counter
      }
      else if(buttonDotState == LOW && buttonDashState == LOW)
      {
        currentMillis =  millis();
        if(currentMillis - previousMillis > intervalchar)
        {        
          k = 0;
          a = 4;
        }
      }
      else if(buttonDotState == HIGH && buttonDashState == HIGH)
      {
         k=0;
         spacing = 1;
         a = 4;
      }
      delay(150);
    }

    
   if(a == 4)
   { 
    morseCodeConverter(aWordMorse, spacing);
    aWordMorse = 0;
    spacing = 0;
   }
  }
}

void morseCodeConverter(int code, int spacing)
{
   if(spacing == 1)
   {
    Serial.print(" ");
   }
   else
   {
    switch(code)
    {
      case 1:
      Serial.print("E");
      break;
      
      case 2:
      Serial.print("T");
      break;
      
      case 11:
      Serial.print("I");
      break;
      
      case 12:
      Serial.print("A");
      break;

      case 21:
      Serial.print("N");
      break;

      case 22:
      Serial.print("M");
      break;

      case 111:
      Serial.print("s");
      break;


      case 112:
      Serial.print("U");
      break;

      case 121:
      Serial.print("R");
      break;

      case 122:
      Serial.print("W");
      break;

      case 211:
      Serial.print("D");
      break;
      
      case 212:
      Serial.print("K");
      break;
      
      case 221:
      Serial.print("G");
      break;

      case 222:
      Serial.print("O");
      break;

      case 1111:
      Serial.print("H");
      break;

      case 1112:
      Serial.print("V");
      break;

      case 1121:
      Serial.print("F");
      break;

      case 1211:
      Serial.print("L");
      break;

      case 1221:
      Serial.print("P");
      break;

      case 1222:
      Serial.print("J");
      break;

      case 2111:
      Serial.print("B");
      break;

      case 2112:
      Serial.print("X");
      break;

      case 2121:
      Serial.print("C");
      break;

      case 2122:
      Serial.print("Y");
      break;

      case 2211:
      Serial.print("Z");
      break;

      case 2212:
      Serial.print("Q");
      break;

      case 11111:
      Serial.print("5");
      break;

      case 11112:
      Serial.print("4");
      break;

      case 11122:
      Serial.print("3");
      break;
      
      case 11222:
      Serial.print("2");
      break;

      case 12121:
      Serial.print("+");
      break;

      case 12222:
      Serial.print("1");
      break;

      

      case 22222:
      Serial.print("0");
      break;

      case 22221:
      Serial.print("9");
      break;

      case 22211:
      Serial.print("8");
      break;

      case 22111:
      Serial.print("7");
      break;

      case 21111:
      Serial.print("6");
      break;

      case 21112:
      Serial.print("=");
      break;

      case 21121:
      Serial.print("/");
      break;  
    }
   }
    
   
void buzz(int targetPin, long frequency, long length) {
  digitalWrite(buzzerPin, HIGH);
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
  digitalWrite(13, LOW);
 
}










   

}
