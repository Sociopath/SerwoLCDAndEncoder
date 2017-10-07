#include <LiquidCrystal.h>
#include <Servo.h>
#include <EEPROM.h>


//wyswietlacz zmienne
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5 

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int lcd_key  = 0;
int adc_key_in  = 0;


//obsluga lcd klawiszy 

int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor 
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 // For V1.1 us this threshold
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 250)  return btnUP; 
 if (adc_key_in < 450)  return btnDOWN; 
 if (adc_key_in < 650)  return btnLEFT; 
 if (adc_key_in < 850)  return btnSELECT;  

 // For V1.0 comment the other threshold and use the one below:
/*
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 195)  return btnUP; 
 if (adc_key_in < 380)  return btnDOWN; 
 if (adc_key_in < 555)  return btnLEFT; 
 if (adc_key_in < 790)  return btnSELECT;   
*/

 return btnNONE;  // when all others fail, return this...
}

// ============= 

//switch wyswietlacza zmienne
int stanLCD = 1;
int timer = 0;
unsigned long pTime = 0;


////============

// zmienne dla switch counter
int stanE = 1;
int timer2 = 0;

#define A 12
#define B 13

 int counter = 0; 
 


//==++++

// zmienne informacyjne
int TimeN = 0;
int TimeS = 0;
int Q1 = 0;
int Q2 = 0;


// zmienne switch funkcyjny

Servo servo1;
Servo servo2;


int stan = 1;

//________________
void setup() { 

  Serial.begin(9600);
  pinMode (A,OUTPUT);
  pinMode (B,OUTPUT);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  timer = 3;
  int prvKey = btnNONE;

  servo1.attach(11);
  servo2.attach(3);

   

  

}

void loop() {  
  
  
  lcd_key = read_LCD_buttons();
  
 // counter switch
  switch(lcd_key){
    case btnUP:{
      counter++;
      delay(100);
      break;
     }
      case btnDOWN:{
      counter--;
      delay(100);
      break;
      }  
    
    }

 



  
//switch wyswietlacza zmienne

 
 switch(stanLCD){
      
      case 1:{        
        lcd.setCursor(0,0);
        lcd.print("    BEND-001     ");
        if(timer == 0){
         stanLCD = 2; 
         
        } 
         break;     
      }
      case 2:{
        
        lcd.setCursor(0,0);
        lcd.print("USTAW CZAS      ");
        lcd.setCursor(0,1);
        lcd.print("NAGRZEWANIA     ");
        lcd.setCursor(12,1);
        lcd.print(counter);
       if(lcd_key == btnSELECT){
          stanLCD = 3;
          TimeN = counter;
          counter = 0;        
          delay(300);    
        }
        
        break;
        }

       case 3:{
        lcd.setCursor(0,0);
        lcd.print("USTAW CZAS      ");
        lcd.setCursor(0,1);
        lcd.print("STUDZENIA       ");
        lcd.setCursor(12,1);
        lcd.print(counter);
        if(lcd_key == btnSELECT){
          TimeS = counter;
          counter = 0; 
          stanLCD = 4;          
          delay(300);   
        }
        
        break;
        }

       case 4:{
        lcd.setCursor(0,0);
        lcd.print("USTAW POZYCJE   ");
        lcd.setCursor(0,1);
        lcd.print("SERWA1          ");
        lcd.setCursor(12,1);
        lcd.print(counter);
        if(lcd_key == btnSELECT){
          Q1 = counter;
          counter = 0; 
          stanLCD = 5;           
          delay(300);        
        }       
        break;           
       }

        case 5:{
        lcd.setCursor(0,0);
        lcd.print("USTAW POZYCJE   ");
        lcd.setCursor(0,1);
        lcd.print("SERWA2          ");
        lcd.setCursor(12,1);
        lcd.print(counter);
        if(lcd_key == btnSELECT){
          Q2 = counter;
          counter = 0; 
          stanLCD = 6;           
          delay(300);        
        }       
        break;           
       }

        case 6:{
        lcd.setCursor(0,0);
        lcd.print("GIECIE          ");
        lcd.setCursor(0,1);
        lcd.print("SELECT TO END          ");
        if(lcd_key == btnSELECT){
          stanLCD = 2; 
          delay(300);        
        }       
        break;           
       }
      
  
  
  
  
  
  }


  // switch funkcyjny 

  switch(stan){
    case 1:{
      servo1.write(0);
      servo2.write(0);
      digitalWrite(A,LOW);
      digitalWrite(B,LOW);     
      if(lcd_key == btnRIGHT && stanLCD == 6) {
        stan = 2;
        timer2 = TimeN;
      }
      break;
      }
     case 2:{
      servo1.write(0);
      servo2.write(0);      
      if(Q1 > 0) digitalWrite(A,HIGH); else digitalWrite(A,LOW);
      if(Q2 > 0)digitalWrite(B,HIGH); else digitalWrite(B,LOW); 
      if(timer2 == 0){               
        stan = 3;
        timer2 = TimeS; 
      }               
 
     break; 
     }  
     case 3:{
      servo1.write(Q1);
      servo2.write(Q2);
      digitalWrite(A,LOW);
      digitalWrite(B,LOW);
       if(timer2 == 0){              
        stan = 1;
      }     
      }  
    
  }
  Serial.println(stan);  

 delay(10);



////============

unsigned long cTime = millis();
if(cTime-pTime >= 500){
    pTime = cTime;
    timer--;
    if(timer < 0) timer = 0;
    timer2--;
    if(timer2 < 0) timer2 = 0;  
  }
 

}
