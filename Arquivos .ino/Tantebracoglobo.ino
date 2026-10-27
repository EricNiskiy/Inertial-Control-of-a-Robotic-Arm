


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
const byte endereco = 0xB3B4B5B6A3;





int msg[8];




int vangZ;
int vangY;
int vangX;
int GyroZ; // que merda é essa??? aclração do eixo Y

float angZ;
float angY;
float angX;

void setup() {
  radio.begin();
  radio.openWritingPipe(endereco);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
  radio.setChannel(100);
  
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);


  
  
}

void loop() {

  
  mpu6050.update();
  GyroZ = (mpu6050.getGyroZ());
  
       // angulo Z = base //

   //         
     
  angZ = mpu6050.getAngleZ();
  vangZ = map(angZ, -200, 200, -80, 100);
  
  Serial.print("tangZ : ");
  Serial.print(vangZ);
  
  


      // angulo Y = elevação e profundidade // 
      

    
  angY = mpu6050.getAccAngleY();
  vangY = map(angY, -150, 180, -150, 180);
  Serial.print("\tangY : ");
  Serial.print(vangY);
  
   
     // angulo X = rotacao punho //

  angX = mpu6050.getAccAngleX();
  vangX = map(angX, -200, 200, -100, 100);
  Serial.print("\tangX : ");
  Serial.print(vangX);


  
  Serial.print("\tang da garra : ");
  Serial.print(msg[4]);

  Serial.print("\tGyroZ : ");
  Serial.println(GyroZ);
  
    // pacote de transmissão //
  msg[5] = GyroZ;
  msg[2] = vangY;
  msg[1] = vangZ;
  msg[0] = 101;
  radio.write(&msg, sizeof(msg));
  
}
