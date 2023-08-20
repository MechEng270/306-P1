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
float XARRAY[] = {120.1539203,
120.6141018,
121.3758223,
122.4312657,
123.7696015,
125.3770968,
127.2372563,
129.3309924,
131.6368205,
134.1310797,
136.7881755,
139.5808424,
142.480424,
145.4571667,
148.4805249,
151.5194751,
154.5428333,
157.519576,
160.4191576,
163.2118245,
165.8689203,
168.3631795,
170.6690076,
172.7627437,
174.6229032,
176.2303985,
177.5687343,
178.6241777,
179.3858982,
179.8460797,
180,
179.8460797,
179.3858982,
178.6241777,
177.5687343,
176.2303985,
174.6229032,
172.7627437,
170.6690076,
168.3631795,
165.8689203,
163.2118245,
160.4191576,
157.519576,
154.5428333,
151.5194751,
148.4805249,
145.4571667,
142.480424,
139.5808424,
136.7881755,
134.1310797,
131.6368205,
129.3309924,
127.2372563,
125.3770968,
123.7696015,
122.4312657,
121.3758223,
120.6141018,
120.1539203,
120
};
float YARRAY[] = {70,
66.96495034,
63.9610444,
61.01910631,
58.16932435,
55.44094112,
52.86195355,
50.45882552,
48.25621638,
46.27672789,
44.54067228,
43.06586381,
41.86743604,
40.95768643,
40.34595027,
40.03850478,
40.03850478,
40.34595027,
40.95768643,
41.86743604,
43.06586381,
44.54067228,
46.27672789,
48.25621638,
50.45882552,
52.86195355,
55.44094112,
58.16932435,
61.01910631,
63.9610444,
66.96495034,
70,
73.03504966,
76.0389556,
78.98089369,
81.83067565,
84.55905888,
87.13804645,
89.54117448,
91.74378362,
93.72327211,
95.45932772,
96.93413619,
98.13256396,
99.04231357,
99.65404973,
99.96149522,
99.96149522,
99.65404973,
99.04231357,
98.13256396,
96.93413619,
95.45932772,
93.72327211,
91.74378362,
89.54117448,
87.13804645,
84.55905888,
81.83067565,
78.98089369,
76.0389556,
73.03504966,
70
};

 
for(int i = 0;i < 62; i++){
  Serial.print(i);
  Serial.println();
  PIDcircle(XARRAY[i],YARRAY[i]);

}




}
void loop()
{

  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  analogWrite(E1, 0); //PWM Speed Control
  analogWrite(E2, 0);
  x = (countL + countR)/2;
  y = (countL - countR)/2;
 // 

}

// void Rectangle(Width,Height){

//   W =  Width* 6050
//   H = Height* 9557

// }

void circle(){
 
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

