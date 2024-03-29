//Arduino PWM Speed Control：
int E1 = 5;
int M1 = 4;
int E2 = 6;
int M2 = 7;
int left = 18;
int right = 19;
int bottom = 3;
int top =2;

int x = 0;
int y = 0;
bool L, R, B, T = 0;



volatile int countL = 0;
volatile int countR = 0;
volatile bool dir;

volatile bool SetLeft = true;
volatile bool SetBottom = true;
volatile bool SetRight = true;
volatile bool SetUp = true;
void setup()
{
Serial.begin(9600);
pinMode(M1, OUTPUT);
pinMode(M2, OUTPUT);
pinMode(18, INPUT_PULLUP);
pinMode(19, INPUT_PULLUP);
pinMode(21, INPUT_PULLUP);
pinMode(20, INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(21), countA, RISING);
attachInterrupt(digitalPinToInterrupt(20), countB, RISING);
attachInterrupt(digitalPinToInterrupt(left), safeL, HIGH);
attachInterrupt(digitalPinToInterrupt(right), safeR, HIGH);
attachInterrupt(digitalPinToInterrupt(bottom), safeB, HIGH);
attachInterrupt(digitalPinToInterrupt(top), safeT, HIGH);

homie();
countL = 0;
countR = 0;
//goRight();
//goUp();
//PIDtest();
//SetRight = 1;
}
void loop()
{
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  analogWrite(E1, 0); //PWM Speed Control
  analogWrite(E2, 0);
}

// void Rectangle(Width,Height){

//   W =  Width* 6050
//   H = Height* 9557

// }

// void circle(float radius, float xIn, float yIn){





// PIDtest

// }

void goRight(){
while(SetRight){
     x = (countL + countR)/2;
     y = (countL - countR)/2;
    digitalWrite(M1, LOW);
    digitalWrite(M2, LOW);
    analogWrite(E1, 255); //PWM Speed Control
    analogWrite(E2, 255);
    Serial.print(x);
      Serial.print(", x");
      Serial.println();
  }
     x = (countL + countR)/2;
     y = (countL - countR)/2;
      Serial.print(x);
      Serial.print(", x");
      Serial.println();
}

void goUp(){
while(SetUp){
     x = (countL + countR)/2;
     y = (countL - countR)/2;
    digitalWrite(M1,LOW);
    digitalWrite(M2, HIGH);
    analogWrite(E1, 255); //PWM Speed Control
    analogWrite(E2, 255);
      Serial.print(y);
      Serial.print(", y");
      Serial.println();
  }
     x = (countL + countR)/2;
     y = (countL - countR)/2;
      Serial.print(y);
      Serial.print(", y");
      Serial.println();

}

void PIDtest(float xIn, float yIn){
  float error, integral, lastE, der = 0, effort;
  //float xIn = 6000.0;
  //float yIn = 2000.0;
  float kp = 2, ki = 1, kd = 0.3;

  while(error > (xIn * .02)){
    Serial.print(error);
    Serial.print(",  ");
    Serial.print(effort);
    Serial.print(",  ");
    Serial.println(x);
      x = (countL + countR)/2;
      error = xIn - x;
      integral = integral + error;
      der = error - lastE;
      lastE = error;
      if(error > 0){ //move right
      digitalWrite(M1, LOW);
      digitalWrite(M2, LOW);
      }else if(error < 0){ //move left
      digitalWrite(M1,HIGH);
      digitalWrite(M2,HIGH);

  }
  effort = 255 * ((kp * error) + (ki * integral));
  if(effort > 255){
    effort = 255;
  }
      analogWrite(E1, effort);
      analogWrite(E2, effort);
    
    delay(100);
  }

  // while(error > (yIn * .02)){
  //   Serial.print(error);
  //   Serial.print(",  ");
  //   Serial.print(effort);
  //   Serial.print(",  ");
  //   Serial.println(y);
  //     y = (countL - countR)/2;
  //     error = yIn - y;
  //     integral = integral + error;
  //     der = error - lastE;
  //     lastE = error;
  //     if(error > 0){ //move right
  //     digitalWrite(M1,LOW);
  //     digitalWrite(M2, HIGH);
  //     }else if(error < 0){ //move left
  //     digitalWrite(M1,HIGH);
  //     digitalWrite(M2, LOW);

  // }
  // effort = 255 * ((kp * error) + (ki * integral));
  // if(effort > 255){
  //   effort = 255;
  // }
  //     analogWrite(E1, effort);
  //     analogWrite(E2, effort);
    
  //   delay(100);
  // }
      Serial.print(error);
      Serial.print(",  ");
      Serial.print(effort);
      Serial.print(",  ");
      Serial.println(x);
      analogWrite(E1, 0);
      analogWrite(E2, 0);
      Serial.print(error);
      Serial.print(",  ");
      Serial.println(x);
      

}

void homie(){
while(SetLeft){
  digitalWrite(M1,HIGH);
  digitalWrite(M2,HIGH);
  analogWrite(E1, 100); //PWM Speed Control
  analogWrite(E2, 100); //PWM Speed Control
  Serial.println("going left");
}

while(SetBottom){
  digitalWrite(M1,HIGH);
  digitalWrite(M2, LOW);
  analogWrite(E1, 100); //PWM Speed Control
  analogWrite(E2, 100); //PWM Speed Control
  Serial.println("going butt");
}
}


void safeR(){
  while(digitalRead(right)){
    digitalWrite(M1, HIGH);
    digitalWrite(M2, HIGH);
    analogWrite(E1, 255); //PWM Speed Control
    analogWrite(E2, 255); 
  }
  analogWrite(E1, 0); //PWM Speed Control
  analogWrite(E2, 0); 
  SetRight = false;
  //Serial.println(count); 
}

void safeL(){
  while(digitalRead(left)){
    digitalWrite(M1, LOW);
    digitalWrite(M2, LOW);
    analogWrite(E1, 255); //PWM Speed Control
    analogWrite(E2, 255);
    
  }
  analogWrite(E1, 0); //PWM Speed Control
  analogWrite(E2, 0); 
 
  SetLeft = false;
  //Serial.println(count); 
}
void safeB(){
  while(digitalRead(bottom)){
    digitalWrite(M1,LOW);
    digitalWrite(M2, HIGH);
    analogWrite(E1, 255); //PWM Speed Control
    analogWrite(E2, 255); 
  }
  analogWrite(E1, 0); //PWM Speed Control
  analogWrite(E2, 0); 
  
  SetBottom = false;
}
void safeT(){
  while(digitalRead(top)){
    digitalWrite(M1,HIGH);
    digitalWrite(M2, LOW);
    analogWrite(E1, 255); //PWM Speed Control
    analogWrite(E2, 255); 
  }
  analogWrite(E1, 0); //PWM Speed Control
  analogWrite(E2, 0); 
  SetUp = false;
}





void countA(){
if(digitalRead(M1)){
  countL--;}
else{
countL++;}

}

void countB(){
if(digitalRead(M2)){
  countR--;}
else{
countR++;}

}


