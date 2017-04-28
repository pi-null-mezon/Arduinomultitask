#define MIN_MEASURE_DELAY 100
/*
//Sensor---------------------------------------------------
#include <OneWire.h>
#define ONE_WIRE_PIN A0
 // it is not a milliseconds, just a cycles number
#define MEASURE_RESOLUTION 0.0625
OneWire ds(ONE_WIRE_PIN);*/

//Indicator------------------------------------------------
#define DOT_FLAG        0x01 // indicate a dot with symbol
#define MINUS_FLAG      0x02 // indicate G segment only
#define BLANKZERO_FLAG  0x04 // do not indicate zero symbol
#define SEGMENT_A A4
#define SEGMENT_B 9
#define SEGMENT_C 6
#define SEGMENT_D 4
#define SEGMENT_E 3
#define SEGMENT_F 12
#define SEGMENT_G 7
#define SEGMENT_H 5
#define CATHODE_FIRST   8
#define CATHODE_SECOND  10
#define CATHODE_THIRD   11 
#define CATHODE_FOURTH  A5

const byte v_segments[]   = {SEGMENT_A, SEGMENT_B, SEGMENT_C, SEGMENT_D, SEGMENT_E, SEGMENT_F, SEGMENT_G, SEGMENT_H};
const byte v_digits[]     = {CATHODE_FIRST, CATHODE_SECOND, CATHODE_THIRD, CATHODE_FOURTH}; 
const byte v_symbolCode[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; // a logic here is like in string H G F E D C B A, so A is a first bit, B is a second bit and so on

//Miscellaneous--------------------------------------------------
#define MEASUREMENTS_REGIME 0x01
#define ANALOGREAD_REGIME 0x02
#define SERIALREAD_REGIME 0x03
#define ANALOG_PIN A1
#define BUTTON_PIN 2
#define MAX_SENSORS_COUNT 8
uint16_t  measureDelay = MIN_MEASURE_DELAY; 
byte      v_symbols[4];
/*float     measure;
byte      v_addr[8 * MAX_SENSORS_COUNT];
byte      addr[8];
byte      m_sensors;*/
volatile int analogvalue;
byte      regime = SERIALREAD_REGIME; 
//-------------------------------------------------------------------------

void setup() {
  // Initialize custom board facilities
  initIndicator();
  initSensors();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(0, buttonPressed, FALLING); // 0 interrupt for Arduino Uno linked with 2 GIO 
  Serial.begin(115200);
}

//-------------------------------------------------------------------------
void loop() {
  switch(regime) {    
    case ANALOGREAD_REGIME:
      analogvalue = analogRead(ANALOG_PIN);
      v_symbols[0] = (byte)(analogvalue % 10);
      v_symbols[1] = (byte)((analogvalue/10) % 10);
      v_symbols[2] = (byte)((analogvalue/100) % 10);
      v_symbols[3] = (byte)((analogvalue/1000) % 10);     
      break;
    case SERIALREAD_REGIME: 
      if(Serial.available()) {  
        analogvalue = Serial.parseInt();    
        v_symbols[0] = (byte)(analogvalue % 10);
        v_symbols[1] = (byte)((analogvalue/10) % 10);
        v_symbols[2] = (byte)((analogvalue/100) % 10);
        v_symbols[3] = (byte)((analogvalue/1000) % 10);        
      }
      break;
  }  

  for(byte j = 0; j < 4; ++j)
    setSymbol(j, 0, BLANKZERO_FLAG);  
  for(uint16_t i = 0; i < (MIN_MEASURE_DELAY >> 2); ++i) {
    setSymbol(0, v_symbols[0], 0);
    setSymbol(1, v_symbols[1], 0);
    setSymbol(2, v_symbols[2], 0);
    setSymbol(3, v_symbols[3], 0);
  }
  for(byte j = 0; j < 4; ++j)
    setSymbol(j, 0, BLANKZERO_FLAG);
}

//-------------------------------------------------------------------------

void initIndicator()
{
  pinMode(SEGMENT_A, OUTPUT);
    digitalWrite(SEGMENT_A, HIGH);
  pinMode(SEGMENT_B, OUTPUT);
    digitalWrite(SEGMENT_B, HIGH);
  pinMode(SEGMENT_C, OUTPUT);
    digitalWrite(SEGMENT_C, HIGH);
  pinMode(SEGMENT_D, OUTPUT);
    digitalWrite(SEGMENT_D, HIGH);
  pinMode(SEGMENT_E, OUTPUT);
    digitalWrite(SEGMENT_E, HIGH);
  pinMode(SEGMENT_F, OUTPUT);
    digitalWrite(SEGMENT_F, HIGH);
  pinMode(SEGMENT_G, OUTPUT);
    digitalWrite(SEGMENT_G, HIGH);
  pinMode(SEGMENT_H, OUTPUT);
    digitalWrite(SEGMENT_H, HIGH);

  pinMode(CATHODE_FIRST, OUTPUT);
    digitalWrite(CATHODE_FIRST, HIGH);
  pinMode(CATHODE_SECOND, OUTPUT);
    digitalWrite(CATHODE_SECOND, HIGH);
  pinMode(CATHODE_THIRD, OUTPUT);
    digitalWrite(CATHODE_THIRD, HIGH);
  pinMode(CATHODE_FOURTH, OUTPUT);
    digitalWrite(CATHODE_FOURTH, HIGH);   
}

//-------------------------------------------------------------------------

void setSymbol(byte digit, byte value, byte flags) // use v_symbolCode vector for valueCode
{
  // turn all digits off
  for(byte i = 0; i < 4; i++)
    digitalWrite(v_digits[i], HIGH);

  byte valueCode = v_symbolCode[value];  
  if((flags & DOT_FLAG) == DOT_FLAG)
    valueCode |= 0x80;
  if((flags & MINUS_FLAG) == MINUS_FLAG) {  
    for(byte i = 0; i < 8 ; i++)
      digitalWrite(v_segments[i], (0x40 >> i) & 0x01);  
  } else if ((value == 0)  && ((flags & BLANKZERO_FLAG) == BLANKZERO_FLAG)) {
    for(byte i = 0; i < 8 ; i++)
      digitalWrite(v_segments[i], LOW); 
  } else { 
    for(byte i = 0; i < 8 ; i++)
      digitalWrite(v_segments[i], (valueCode >> i) & 0x01);  
  }
 
  // turn specified digit on (followed optimization digitalWrite(v_digits[digit], LOW), becomes to unsaturated lights, so leave this peace of code as is) 
  for(byte i = 0; i < 4; i++)
    digitalWrite(v_digits[i], i == digit ? LOW : HIGH);
}

//-------------------------------------------------------------------------

void initSensors()
{
  /*m_sensors = 0;
  byte addr[8];
  while(ds.search(addr)) {
    for(byte i = 0; i < 8; i++)
      v_addr[i + 8 * m_sensors] = addr[i];
    m_sensors++;     
  }*/
}

//-------------------------------------------------------------------------

void startConversion(byte *addres)
{
  /*noInterrupts();
  ds.reset();
  ds.select(addres);
  ds.write(0x44, 1); // start conversion, with parasite power on at the end
  interrupts();  */
}

//-------------------------------------------------------------------------

float readSensor(byte *addres)
{
  /*noInterrupts();
  ds.reset();
  ds.select(addres);    
  ds.write(0xBE); // start read scratchpad  
  byte lsb = ds.read();  
  byte msb = ds.read();
  byte sign = msb & 0xF0;
  interrupts();
  if(sign == 0xF0)
    return -((int)((byte)~lsb) | ((int)((byte)~msb) << 8)) * MEASURE_RESOLUTION;
  else
    return ((int)lsb | ((int)msb << 8)) * MEASURE_RESOLUTION;*/
  return 0.0f;
}

//----------------------------------------------------------------------

void buttonPressed()
{
  delayMicroseconds(1000);
  if(digitalRead(BUTTON_PIN) == LOW) {
    delayMicroseconds(1000);
    if(digitalRead(BUTTON_PIN) == LOW) {
      measureDelay = 0;
      switch(regime)  {
        case MEASUREMENTS_REGIME:
          regime = ANALOGREAD_REGIME;
          break;
        case ANALOGREAD_REGIME:
          regime = MEASUREMENTS_REGIME;
          break;    
      }
    }
  }
}
//----------------------------------------------------------------------
