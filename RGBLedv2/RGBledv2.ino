#include <MirmPS.h>
#include <MirmPS_assemf.h>

#define RED_PIN 5
#define GREEN_PIN 6
#define BLUE_PIN 9

// Global variables --------------------------
byte _vpin[] = {RED_PIN, GREEN_PIN, BLUE_PIN};
enum Color {Red, Green, Blue};
//--------------------------------------------

// Function declarations ---------------------
void randomColorFade(Color _color, int timedev);
//--------------------------------------------

void setup() {
  TIMSK2 = 1; // Устанавливаем маску разрешения прерывания по переполнению для таймера 2
  initRGBpins();    
}

void loop1() {
    randomColorFade(Red,7); 
}

void loop2() {
    randomColorFade(Green,7); 
}

void loop3() {
    randomColorFade(Blue,7);
}

void randomColorFade(Color _color, int timedev) {
  if(random(13) == 1) {
    for(byte t = 0; t < 255; t++) {
        analogWrite(_vpin[_color], t);
        delay(timedev);  
    }     
    for(byte t = 0; t < 255; t++) {   
        analogWrite(_vpin[_color], 255-t);
        delay(timedev);  
    }
    digitalWrite(_vpin[_color], LOW);       
  } else 
    delay(timedev*55); 
    
}

void initRGBpins() {   
  for(byte i = 0; i < 3; i++) {
     pinMode(_vpin[i], OUTPUT);
     digitalWrite(_vpin[i], LOW);  
  }
 
}

