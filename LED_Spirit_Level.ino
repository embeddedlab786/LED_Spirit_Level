/*
Connections:
MPU6050_____UNO
VCC_________5v
GND_________GND
SCL_________PinA5
SDA_________PinA4
*/

#include <Wire.h> // I2C communication library
const int MPU = 0x68; // I2C address of the MPU6050 accelerometer

int16_t AcX, AcY, AcZ;

#define Com1 2 // com1 Pin Out
#define Com2 3 // com2 Pin Out
#define Com3 4 // com3 Pin Out
#define Com4 5 // com4 Pin Out


#define B_led 9  // Blue   Led Pin Out
#define G_led 10 // Green  Led Pin Out
#define Y_led 11 // Yellow Led Pin Out
#define R_led 12 // Red    Led Pin Out

#define Buzzer 13 // Buzzer Pin Out

int DTime = 4; // Delay time

int L1, L2, L3, L4, flag=0;

void setup() {
Serial.begin(9600);

pinMode(Com1, OUTPUT);
pinMode(Com2, OUTPUT);
pinMode(Com3, OUTPUT);
pinMode(Com4, OUTPUT);

pinMode(B_led, OUTPUT);
pinMode(G_led, OUTPUT);
pinMode(Y_led, OUTPUT);
pinMode(R_led, OUTPUT);

pinMode(Buzzer, OUTPUT);
  
  // Initialize interface to the MPU6050
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
 
  delay(1000); 
}
void loop() {

Read_accelerometer(); 


  leds(L1);
  digitalWrite(Com1, 0);   
  delay(DTime);
  digitalWrite(Com1, 1);
  
  leds(L2);
  digitalWrite(Com2, 0); 
  delay(DTime);
  digitalWrite(Com2, 1);

  leds(L3);
  digitalWrite(Com3, 0);   
  delay(DTime);
  digitalWrite(Com3, 1);

  leds(L4);
  digitalWrite(Com4, 0);   
  delay(DTime);
  digitalWrite(Com4, 1);
}

void Read_accelerometer(){
      // Read the accelerometer data
Wire.beginTransmission(MPU);
Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
Wire.endTransmission(false);
Wire.requestFrom(MPU, 6, true); // Read 6 registers total, each axis value is stored in 2 registers

AcX = Wire.read() << 8 | Wire.read(); // X-axis value
AcY = Wire.read() << 8 | Wire.read(); // Y-axis value
AcZ = Wire.read() << 8 | Wire.read(); // Z-axis value

AcX = map(AcX, -17000, 17000, 0, 18);
AcY = map(AcY, -17000, 17000, 0, 18);
AcZ = map(AcZ, -17000, 17000, 0, 18);

//Serial.print(AcX);  Serial.print(" \t ");Serial.print(AcY);  Serial.print(" \t ");Serial.println(AcZ); 

if((AcX>8 && AcX<10)&&(AcY>8 && AcY<10)){ 
digitalWrite(B_led, 1); // Blue  Led is ON 
if(flag>0){ flag = flag-1;
digitalWrite(Buzzer, 1); // Buzzer is ON   
 }else{
digitalWrite(Buzzer, 0); // Buzzer is OFF 
 }
}
else{ flag = 20;
digitalWrite(B_led, 0); // Blue  Led is OFF 
digitalWrite(Buzzer, 0); // Buzzer is OFF 
}

if(AcX<=8){L1=AcX;
if(L1<6)L1=6;
}
else{L1=0;}

if(AcX>=10){L2=AcX;
if(L2>12)L2=12;
}
else{L2=0;}

if(AcY<=8){L3=AcY;
if(L3<6)L3=6;
}
else{L3=0;}

if(AcY>=10){L4=AcY;
if(L4>12)L4=12;
}
else{L4=0;}



//Serial.print(L1);  Serial.print(" \t ");Serial.print(L2);  Serial.print(" \t ");Serial.print(L3);  Serial.print(" \t ");Serial.println(L4);

}

void leds(int x){
   switch(x){
     case 0: zero();  break;
     case 10: one();   break;
     case 11: two();   break;
     case 12: three(); break;
     case 8: one();   break;
     case 7: two();   break;
     case 6: three(); break;
   }
}

void zero(){
  digitalWrite(G_led, 0); // Green  Led is OFF
  digitalWrite(Y_led, 0); // Yellow Led is OFF
  digitalWrite(R_led, 0); // Red    Led is OFF
}

void one(){
  digitalWrite(G_led, 1); // Green  Led is ON
  digitalWrite(Y_led, 0); // Yellow Led is OFF
  digitalWrite(R_led, 0); // Red    Led is OFF
}

void two(){
  digitalWrite(G_led, 1); // Green  Led is ON
  digitalWrite(Y_led, 1); // Yellow Led is ON
  digitalWrite(R_led, 0); // Red    Led is OFF
}

void three(){
  digitalWrite(G_led, 1); // Green  Led is ON
  digitalWrite(Y_led, 1); // Yellow Led is ON
  digitalWrite(R_led, 1); // Red    Led is ON
}
