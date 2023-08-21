//Arduino PWM Speed Control：
int E1 = 5;
int M1 = 4;
int E2 = 6;
int M2 = 7;
int left = 18;
int right = 19;
int bottom = 3;
int top =2;
bool PID = true;
int x = 0;
int y = 0;
bool L, R, B, T = 0;




volatile int countL = 0;
volatile int countR = 0;


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
attachInterrupt(digitalPinToInterrupt(21), countB, RISING);
attachInterrupt(digitalPinToInterrupt(20), countA, RISING);
attachInterrupt(digitalPinToInterrupt(left), safeL, HIGH);
attachInterrupt(digitalPinToInterrupt(right), safeR, HIGH);
attachInterrupt(digitalPinToInterrupt(bottom), safeB, HIGH);
attachInterrupt(digitalPinToInterrupt(top), safeT, HIGH);
homie();
countL = 0;
countR = 0;
PIDtest(1000,1000);
delay(2000);
PIDtest(2000,1200);
delay(500);
PIDtest(1000,1400);
delay(500);
PIDtest(2000,1600);
delay(500);
PIDtest(1000,1800);

}

void loop()
{


}

void PIDtest(int xIn, int yIn) {
  float error, integral, lastE, der = 0, effort;
  float kp = 420, ki = .002, kd = 0.05;
  x = (countL + countR) / 2;
  y = (countL - countR) / 2;
  error = xIn - x;
  while (abs(error) > 10) {
    x = (countL + countR) / 2;
    y = (countL - countR) / 2;
    error = xIn - x;
    integral = integral + error;
    der = error - lastE;
    lastE = error;
    if (error > 0) {  //move right
      digitalWrite(M1, LOW);
      digitalWrite(M2, LOW);
    } else if (error < 0) {  //move left
      digitalWrite(M1, HIGH);
      digitalWrite(M2, HIGH);
    }
    if (abs((ki * integral)) > 255) {
      integral = 255 / ki;
    }
    effort = ((kp * error) + (ki * integral));
    if (abs(effort) > 255) {
      if (effort > 0) {
        effort = 255;
      } else {
        effort = -255;
      }
    }
    if (abs(error) < 500) {
      effort = 80;
    }
    analogWrite(E1, abs(effort));
    analogWrite(E2, abs(effort));
    Serial.print(x);
    Serial.print(", ");
    Serial.print(xIn);
    Serial.print(",");
    Serial.print(y);
    Serial.print(", ");
    Serial.print(yIn);
    Serial.print(", ");
    Serial.print(error);
    Serial.print(", ");
    Serial.print("Effort = ");
    Serial.print(effort);
    Serial.println();
    // delay(50);  //does this fuck with interupts
  }

  //x position has been reached
  analogWrite(E1, 0);
  analogWrite(E2, 0);
  delay(50);

  x = (countL + countR) / 2;
  y = (countL - countR) / 2;
  Serial.print(x);
  Serial.print(", ");
  Serial.print(xIn);
  Serial.print(",");
  Serial.print(y);
  Serial.print(", ");
  Serial.print(yIn);
  Serial.print(", ");
  Serial.print(error);
  Serial.print(", ");
  Serial.print("Effort = ");
  Serial.print(effort);
  Serial.println();
  error = yIn - y;

  while (abs(error) > 10) {

    x = (countL + countR) / 2;
    y = (countL - countR) / 2;
    error = yIn - y;
    integral = integral + error;
    der = error - lastE;
    lastE = error;
    if (error > 0) {  //move up
      digitalWrite(M1, LOW);
      digitalWrite(M2, HIGH);
    } else if (error < 0) {  //move down
      digitalWrite(M1, HIGH);
      digitalWrite(M2, LOW);
    }
    if (abs((ki * integral)) > 255) {
      integral = 255 / ki;
    }
    effort = ((kp * error) + (ki * integral));
    if (abs(effort) > 255) {
      if (effort > 0) {
        effort = 255;
      } else {
        effort = -255;
      }
    }
    if (abs(error) < 500) {
      effort = 80;
    }
    analogWrite(E1, abs(effort));
    analogWrite(E2, abs(effort));
    Serial.print(x);
    Serial.print(", ");
    Serial.print(xIn);
    Serial.print(",");
    Serial.print(y);
    Serial.print(", ");
    Serial.print(yIn);
    Serial.print(", ");
    Serial.print(error);
    Serial.print(", ");
    Serial.print("Effort = ");
    Serial.print(effort);
    Serial.println();
    Serial.println();
    // delay(50);  //does this fuck with interupts
  }
  analogWrite(E1, 0);  //PWM Speed Control
  analogWrite(E2, 0);
  Serial.print(x);
  Serial.print(", ");
  Serial.print(xIn);
  Serial.print(",");
  Serial.print(y);
  Serial.print(", ");
  Serial.print(yIn);
  Serial.print(", ");
  Serial.print(error);
  Serial.println();
}

void PIDcircle(int xIn, int yIn){

  xIn = xIn*45.545;
  yIn = yIn*44.;
  int errorX = 0;
  int errorY = 0;
  float integralX = 0;
  float integralY = 0;
  float kp = 1;
  float ki = 0.01;
  int effortA = 0;
  int effortB = 0;
       x = (countL + countR)/2;
       y = (countL - countR)/2;
  errorX = xIn - x;
  errorY = yIn - y;
  while((abs(errorX) > 10) || (abs(errorY) > 10)){
     x = (countL + countR)/2;
     y = (countL - countR)/2;
    
    errorX = xIn - x;
    errorY = yIn - y;
    Serial.print(x);
    Serial.print(", ");
    Serial.print(xIn);
    Serial.print(",");
    Serial.print(y);
    Serial.print(", ");
    Serial.print(yIn);
    Serial.print(", ");
    Serial.print(errorX);
    Serial.print(", ");
    Serial.print(errorY);
    Serial.print(", ");
    Serial.print(effortA);
    Serial.print(", ");
    Serial.print(effortB);
    Serial.println();
    integralX = errorX + integralX;
    integralY = errorY + integralY;
    if(abs(integralX) > 1500){
        if(integralX > 0) {integralX = 1500;
        }else{
          integralX = -1500;
        }
    }

     if(abs(integralY) > 1500){
        if(integralY > 0) {integralY = 1500;
        }else{
          integralY = -1500;
        }
    }
    effortA = (kp * (errorX + errorY)) + (ki * (integralX + integralY));
    effortB = (kp * (errorX - errorY)) +(ki * (integralX - integralY));

    
    if(effortA >= 0){
    digitalWrite(M1,LOW);
    }else{
      digitalWrite(M1,HIGH);
    }

    if(effortB >= 0){
      digitalWrite(M2,LOW);
    }else{
      digitalWrite(M2,HIGH);
    }
    if(abs(effortA) > 255){
      effortA = 255;
    }
    if(abs(effortB) > 255){
      effortB = 255;
    }

    if(abs(effortA) < 100 ){
      effortA = 100;
    }
    if(abs(effortB) < 100){
      effortB = 100;
    }
    analogWrite(E1, abs(effortA));
    analogWrite(E2, abs(effortB));
    delay(50);
  }
    analogWrite(E1, 0);
    analogWrite(E2, 0);
}


void homie(){
while(SetLeft){
  digitalWrite(M1,HIGH);
  digitalWrite(M2,HIGH);
  analogWrite(E1, 200); //PWM Speed Control
  analogWrite(E2, 200); //PWM Speed Control
  Serial.println("going left");
}

while(SetBottom){
  digitalWrite(M1,HIGH);
  digitalWrite(M2, LOW);
  analogWrite(E1, 200); //PWM Speed Control
  analogWrite(E2, 200); //PWM Speed Control
  Serial.println("going butt");
}
}


void safeR(){
  while(digitalRead(right)){
    digitalWrite(M1, HIGH);
    digitalWrite(M2, HIGH);
    analogWrite(E1, 250); //PWM Speed Control
    analogWrite(E2, 250); 
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
    analogWrite(E1, 250); //PWM Speed Control
    analogWrite(E2, 250);
    
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
    analogWrite(E1, 250); //PWM Speed Control
    analogWrite(E2, 250); 
  }
  analogWrite(E1, 0); //PWM Speed Control
  analogWrite(E2, 0); 
  
  SetBottom = false;
}
void safeT(){
  while(digitalRead(top)){
    digitalWrite(M1,HIGH);
    digitalWrite(M2, LOW);
    analogWrite(E1, 250); //PWM Speed Control
    analogWrite(E2, 250); 
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

