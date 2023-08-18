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
attachInterrupt(digitalPinToInterrupt(21), countB, RISING);
attachInterrupt(digitalPinToInterrupt(20), countA, RISING);
attachInterrupt(digitalPinToInterrupt(left), safeL, HIGH);
attachInterrupt(digitalPinToInterrupt(right), safeR, HIGH);
attachInterrupt(digitalPinToInterrupt(bottom), safeB, HIGH);
attachInterrupt(digitalPinToInterrupt(top), safeT, HIGH);
homie();
countL = 0;
countR = 0;


PIDcircle(3000,	4500);
PIDcircle(3293,	4471);
PIDcircle(3574,	4386);
PIDcircle(3833,	4247);
PIDcircle(4061,	4061);
PIDcircle(4247,	3833);
PIDcircle(4386,	3574);
PIDcircle(4471,	3293);
PIDcircle(4500,	3000);
PIDcircle(4471,	2707);
PIDcircle(4386,	2426);
PIDcircle(4247,	2167);
PIDcircle(4061,	1939);
PIDcircle(3833,	1753);
PIDcircle(3574,	1614);
PIDcircle(3293,	1529);
PIDcircle(3000,	1500);
PIDcircle(2707,	1529);
PIDcircle(2426,	1614);
PIDcircle(2167,	1753);
PIDcircle(1939,	1939);
PIDcircle(1753,	2167);
PIDcircle(1614,	2426);
PIDcircle(1529,	2707);
PIDcircle(1500,	3000);
PIDcircle(1529,	3293);
PIDcircle(1614,	3574);
PIDcircle(1753,	3833);
PIDcircle(1939,	4061);
PIDcircle(2167,	4247);
PIDcircle(2426,	4386);
PIDcircle(2707,	4471);
PIDcircle(3000,	4500);

 //PIDtest(3000,	4500);
// PIDtest(3293,	4471);
// PIDtest(3574,	4386);
// PIDtest(3833,	4247);
// PIDtest(4061,	4061);
// PIDtest(4247,	3833);
// PIDtest(4386,	3574);
// PIDtest(4471,	3293);
// PIDtest(4500,	3000);
// PIDtest(4471,	2707);
// PIDtest(4386,	2426);
// PIDtest(4247,	2167);
// PIDtest(4061,	1939);
// PIDtest(3833,	1753);
// PIDtest(3574,	1614);
// PIDtest(3293,	1529);
// PIDtest(3000,	1500);
// PIDtest(2707,	1529);
// PIDtest(2426,	1614);
// PIDtest(2167,	1753);
// PIDtest(1939,	1939);
// PIDtest(1753,	2167);
// PIDtest(1614,	2426);
// PIDtest(1529,	2707);
// PIDtest(1500,	3000);
// PIDtest(1529,	3293);
// PIDtest(1614,	3574);
// PIDtest(1753,	3833);
// PIDtest(1939,	4061);
// PIDtest(2167,	4247);
// PIDtest(2426,	4386);
// PIDtest(2707,	4471);
// PIDtest(3000,	4500);



//circle(2000,3000,3000.0);
//PIDtest();
//SetRight = 1;
}
void loop()
{
  // float res = 8;
  // float r = 1500;
  // float x1;
  // for (int i=0;i<=res;i++){
  // x1 = r * cos(1.62 * (i / res));
  // Serial.println(x1);
  // delay(100);
  // }
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  analogWrite(E1, 0); //PWM Speed Control
  analogWrite(E2, 0);
  x = (countL + countR)/2;
  y = (countL - countR)/2;
  Serial.print(x);
  Serial.print(", ");
  Serial.print(y);
  Serial.println();

}

// void Rectangle(Width,Height){

//   W =  Width* 6050
//   H = Height* 9557

// }

void circle(float diameter, float xIn, float yIn){

float yO = yIn;
float xO = xIn;

float x1;
float y1;

float r = diameter/2.0;
float res = 8;
float i; // does this need to be an int

PIDcircle(xIn,yIn);
PIDcircle(xIn,yIn + r);

// PIDtest(xIn,yIn);
// PIDtest(xIn,yIn + r);
x = 0;
y = 0;

Serial.println(r);
for (i=0;i<=res;i++){

x1 = r * sin(1.62 * (i / res));
//Serial.print
// y1 = sin((1.62*i)/res);
// x1 = cos((1.62*i)/res);


//PIDcircle((x1 + xIn),(y1+yIn));         

}


for (i=1;i<res;i++){
x1 = r - r * sin(i*1.571/res);
y1 = sqrt(r*r - x1*x1);
PIDcircle(xIn+x1,yIn - y1);



}

// for (i=1;i<res;i++){
// x1 =  r * sin(i*1.571/res);
// y1 = sqrt(r*r - x1*x1); 
// PIDtest(xIn-x1,yIn - r + y1);
// while(PID)
// {

// }
// PID = true;

// }
// for (i=1;i<res;i++){

// x1 = r - r * sin(i*1.571/res);
// y1 = sqrt(r*r - x1*x1);
// PIDtest(xIn - x1,yIn - r + y1);
// while(PID)
// {

// }
// PID = true;
// }

}

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
void PIDcircle(int xIn, int yIn){
  int errorX = 0;
  int errorY = 0;
  float integralX = 0;
  float integralY = 0;
  float kp = 69;
  float ki = 0.420;
  int effortA = 0;
  int effortB = 0;
       x = (countL + countR)/2;
       y = (countL - countR)/2;
  errorX = xIn - x;
  errorY = yIn - y;
  while((abs(errorX) > 10)&&(abs(errorY) > 10)){
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
    analogWrite(E1, abs(effortA));
    analogWrite(E2, abs(effortB));
    delay(50);
  }
    analogWrite(E1, 0);
    analogWrite(E2, 0);
}
// should we have 1 or 2 PID controllers
void PIDtest(int xIn, int yIn){
  float error, integral, lastE, der = 0, effort;
  float kp = .05, ki = .03, kd = 0.3;
      x = (countL + countR)/2;
       y = (countL - countR)/2;
      error = xIn - x;
  while(abs(error) > 10){
       x = (countL + countR)/2;
       y = (countL - countR)/2;
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
  effort = ((kp * error) + (ki * integral));
  if(abs(effort) > 255){
    if(effort > 0) {effort = 255;}
    else{effort = -255;}
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
    Serial.println();
    delay(50); //does this fuck with interupts
  }
  
      x = (countL + countR)/2;
      y = (countL - countR)/2;
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
      error = yIn - y;

  while(abs(error) > 10){

       x = (countL + countR)/2;
       y = (countL - countR)/2;
      error = yIn - y;
      integral = integral + error;
      der = error - lastE;
      lastE = error;
      if(error > 0){ //move up
      digitalWrite(M1,LOW);
      digitalWrite(M2, HIGH);
      }else if(error < 0){ //move down
      digitalWrite(M1,HIGH);
      digitalWrite(M2, LOW);

  }
  effort = ((kp * error) + (ki * integral));
 if(abs(effort) > 255){
    if(effort > 0) {effort = 255;}
    else{effort = -255;}
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
    Serial.println();
    delay(50); //does this fuck with interupts
  }
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

