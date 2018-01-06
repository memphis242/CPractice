  /*
This is the code that runs on the arduino(s) that read the encoders directly.
For information about the encoders please see the encoder pdf on the google drive: https://drive.google.com/open?id=0BxlsGkfBNU4WXzI0QmpOMTduUVk 
for arduino syntax and documentation see: https://www.arduino.cc/en/Reference/HomePage

Brought to you by Brady Goehner, Zack O'brian, and Andrew Vetter 
*/
int16_t pulseCountLeft;
int16_t pulseCountRight;  

byte buf[8];

int x =0;

byte generateChecksum(byte* buf, int n) {
  byte result = 0;
  
  for(int i = 0; i < n; i++){
    result = result ^ buf[i];
  }
  return result;
}

void setup() {

  buf[1] = 'L';
  buf[4] = 'R';
  
  Serial.begin(57600);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  //pinMode(13, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), pulse1, RISING); //when a rising edge is detected on pin 2/3 run the function pulse1/2. phase A
  attachInterrupt(digitalPinToInterrupt(6), pulse2, RISING);
  
}

void loop() {
  // put your main code here, to run repeatedly:
 if (Serial.available() > 0){ // if data is sent to the serial from computer then print the readings from the encoders. 
      
      byte echo = Serial.read();
//      digitalWrite(13, HIGH);
      buf[0] = echo;
      buf[1] = (byte)76;
      buf[2] = (pulseCountLeft & 0xff);
      buf[3] = ((pulseCountLeft >> 8) & 0xFF);
      buf[4] = (byte)82;
      buf[5] = (pulseCountRight & 0xff);
      buf[6] = ((pulseCountRight >> 8) & 0xFF);

      // add checksum to buffer
      buf[7] = generateChecksum(buf, 7);
        
      Serial.write(buf, 8);//write data to the serial from pin 2/4
      pulseCountLeft = 0;
      pulseCountRight = 0;
      
  }
//digitalWrite(13, LOW);
  
}

void pulse1(){
  if (digitalRead(4)==0) // if encode rotates clockwise increase count. phase B 
    pulseCountLeft++;
  else			// else decrease count. i.e. rotate CCW 
    pulseCountLeft--;
}


void pulse2(){
  if (digitalRead(8)==0)
    pulseCountRight--;
  else
    pulseCountRight++;
}

