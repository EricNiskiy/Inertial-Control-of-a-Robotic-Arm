


//contole da luva//
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
#include <MPU6050_tockn.h>
#include <Wire.h>


MPU6050 mpu6050(Wire);

RF24 radio(9, 10);// CE CSN
const byte endereco = 0xB3B4B5B6F1;

int botao = 8;

int msg[12];
int lerbotao = 0;

int garra;

int vangZ;
int vangY;
int vangX;
int AccY; // que merda é essa??? aclração do eixo Y

float angZ;
float angY;
float angX;

void setup() {
  radio.begin();
  radio.openWritingPipe(endereco);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
  radio.setChannel(80);
  
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

 pinMode(botao,INPUT_PULLUP); // oq é?
  
  
}

void loop() {

  mpu6050.update();
  
 


      // angulo Y = elevação e profundidade // 
 
    
  angY = mpu6050.getAccAngleY();
  vangY = map(angY, -150, 180, -150, 180);
  Serial.print("\tangY : ");
  Serial.print(vangY);
  

     // angulo X = rotacao punho //

  angX = mpu6050.getAccAngleX();
  vangX = map(angX, -200, 200, -200, 200);
  Serial.print("\tangX : ");
  Serial.print(vangX);
 
    // fecha e abre garra //  
 
 lerbotao = digitalRead(botao);
  if(lerbotao == HIGH){
    garra = 0;    
  }
  else{
    garra = 75; 
  }

  
  Serial.print("\tang da garra : ");
  Serial.print(lerbotao);

  Serial.print("\tAccY : ");
  Serial.println(AccY);
  
    // pacote de transmissão //

  msg[4] = garra;
  msg[3] = vangX;
  msg[2] = vangY;
  msg[0] = 99;
  radio.write(&msg, sizeof(msg));
  
}
