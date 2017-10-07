#include <LiquidCrystal.h>
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






void setup() { 

  Serial.begin(9600);

  lcd.begin(16,2);
  lcd.setCursor(0,0);
  timer = 3;
  int prvKey = btnNONE;
   

  

}

void loop() {



  
//switch wyswietlacza zmienne

 lcd_key = read_LCD_buttons();
 switch(stanLCD){
      
      case 1:{        
        lcd.setCursor(0,0);
        lcd.print("    BEND-001     ");
        if(timer == 0){
         stanLCD = 2; 
         lcd_key = 5;
        } 
         break;     
      }
      case 2:{
        
        lcd.setCursor(0,0);
        lcd.print("USTAW CZAS      ");
        lcd.setCursor(0,1);
        lcd.print("NAGRZEWANIA     ");
       if(lcd_key == btnSELECT){
          stanLCD = 3; 
          lcd_key = 5; 
          delay(300);    
        }
        
        break;
        }

       case 3:{
        lcd.setCursor(0,0);
        lcd.print("USTAW CZAS      ");
        lcd.setCursor(0,1);
        lcd.print("STUDZENIA       ");
        if(lcd_key == btnSELECT){
          stanLCD = 4; 
          lcd_key = 5; 
          delay(300);   
        }
        
        break;
        }

       case 4:{
        lcd.setCursor(0,0);
        lcd.print("USTAW POZYCJE   ");
        lcd.setCursor(0,1);
        lcd.print("SERWA1          ");
        if(lcd_key == btnSELECT){
          stanLCD = 5;
          lcd_key = 5; 
          delay(300);        
        }       
        break;           
       }

        case 5:{
        lcd.setCursor(0,0);
        lcd.print("USTAW POZYCJE   ");
        lcd.setCursor(0,1);
        lcd.print("SERWA2          ");
        if(lcd_key == btnSELECT){
          stanLCD = 6;
          lcd_key = 5; 
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
          lcd_key = 5; 
          delay(300);        
        }       
        break;           
       }
      
  
  
  
  
  
  }

  Serial.print(stanLCD);



////============

unsigned long cTime = millis();
if(cTime-pTime >= 1000){
    pTime = cTime;
    timer--;
    if(timer < 0) timer = 0;  
  }
 

}
