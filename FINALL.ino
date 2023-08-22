//Arduino PWM Speed Control：
int E1 = 5;
int M1 = 4;
int E2 = 6;
int M2 = 7;
int left = 18;
int right = 19;
int bottom = 3;
int top = 2;
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

void setup() {
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


  float Xarray[] = {
    // 120.0000,
    // 120.0361,
    // 120.1445,
    // 120.3247,
    // 120.5764,
    // 120.8991,
    // 121.2918,
    // 121.7537,
    // 122.2836,
    // 122.8803,
    // 123.5424,
    // 124.2681,
    // 125.0559,
    // 125.9038,
    // 126.8097,
    // 127.7715,
    // 128.7868,
    // 129.8532,
    // 130.9682,
    // 132.1290,
    // 133.3329,
    // 134.5769,
    // 135.8581,
    // 137.1733,
    // 138.5195,
    // 139.8933,
    // 141.2915,
    // 142.7106,
    // 144.1473,
    // 145.5981,
    // 147.0595,
    // 148.5280,
    // 150.0000,
    // 151.4720,
    // 152.9405,
    // 154.4019,
    // 155.8527,
    // 157.2894,
    // 158.7085,
    // 160.1067,
    // 161.4805,
    // 162.8267,
    // 164.1419,
    // 165.4231,
    // 166.6671,
    // 167.8710,
    // 169.0318,
    // 170.1468,
    // 171.2132,
    // 172.2285,
    // 173.1903,
    // 174.0962,
    // 174.9441,
    // 175.7319,
    // 176.4576,
    // 177.1197,
    // 177.7164,
    // 178.2463,
    // 178.7082,
    // 179.1009,
    // 179.4236,
    // 179.6753,
    // 179.8555,
    // 179.9639,
    // 180.0000,
    // 179.9639,
    // 179.8555,
    // 179.6753,
    // 179.4236,
    // 179.1009,
    // 178.7082,
    // 178.2463,
    // 177.7164,
    // 177.1197,
    // 176.4576,
    // 175.7319,
    // 174.9441,
    // 174.0962,
    // 173.1903,
    // 172.2285,
    // 171.2132,
    // 170.1468,
    // 169.0318,
    // 167.8710,
    // 166.6671,
    // 165.4231,
    // 164.1419,
    // 162.8267,
    // 161.4805,
    // 160.1067,
    // 158.7085,
    // 157.2894,
    // 155.8527,
    // 154.4019,
    // 152.9405,
    // 151.4720,
    // 150.0000,
    // 148.5280,
    // 147.0595,
    // 145.5981,
    // 144.1473,
    // 142.7106,
    // 141.2915,
    // 139.8933,
    // 138.5195,
    // 137.1733,
    // 135.8581,
    // 134.5769,
    // 133.3329,
    // 132.1290,
    // 130.9682,
    // 129.8532,
    // 128.7868,
    // 127.7715,
    // 126.8097,
    // 125.9038,
    // 125.0559,
    // 124.2681,
    // 123.5424,
    // 122.8803,
    // 122.2836,
    // 121.7537,
    // 121.2918,
    // 120.8991,
    // 120.5764,
    // 120.3247,
    // 120.1445,
    // 120.0361,
    // 120.0000,
    // 12.00000


120,
120.1444582,
120.5764416,
121.2917899,
122.283614,
123.5423621,
125.0559116,
126.8096864,
128.7867966,
130.9682015,
133.332893,
135.8580979,
138.519497,
141.2914597,
144.1472903,
147.0594858,
150,
152.9405142,
155.8527097,
158.7085403,
161.480503,
164.1419021,
166.667107,
169.0317985,
171.2132034,
173.1903136,
174.9440884,
176.4576379,
177.716386,
178.7082101,
179.4235584,
179.8555418,
180,
179.8555418,
179.4235584,
178.7082101,
177.716386,
176.4576379,
174.9440884,
173.1903136,
171.2132034,
169.0317985,
166.667107,
164.1419021,
161.480503,
158.7085403,
155.8527097,
152.9405142,
150,
147.0594858,
144.1472903,
141.2914597,
138.519497,
135.8580979,
133.332893,
130.9682015,
128.7867966,
126.8096864,
125.0559116,
123.5423621,
122.283614,
121.2917899,
120.5764416,
120.1444582,
120,
120


  };

  float Yarray[] = {
    // 70.0000,
    // 68.5280,
    // 67.0595,
    // 65.5981,
    // 64.1473,
    // 62.7106,
    // 61.2915,
    // 59.8933,
    // 58.5195,
    // 57.1733,
    // 55.8581,
    // 54.5769,
    // 53.3329,
    // 52.1290,
    // 50.9682,
    // 49.8532,
    // 48.7868,
    // 47.7715,
    // 46.8097,
    // 45.9038,
    // 45.0559,
    // 44.2681,
    // 43.5424,
    // 42.8803,
    // 42.2836,
    // 41.7537,
    // 41.2918,
    // 40.8991,
    // 40.5764,
    // 40.3247,
    // 40.1445,
    // 40.0361,
    // 40.0000,
    // 40.0361,
    // 40.1445,
    // 40.3247,
    // 40.5764,
    // 40.8991,
    // 41.2918,
    // 41.7537,
    // 42.2836,
    // 42.8803,
    // 43.5424,
    // 44.2681,
    // 45.0559,
    // 45.9038,
    // 46.8097,
    // 47.7715,
    // 48.7868,
    // 49.8532,
    // 50.9682,
    // 52.1290,
    // 53.3329,
    // 54.5769,
    // 55.8581,
    // 57.1733,
    // 58.5195,
    // 59.8933,
    // 61.2915,
    // 62.7106,
    // 64.1473,
    // 65.5981,
    // 67.0595,
    // 68.5280,
    // 70.0000,
    // 71.4720,
    // 72.9405,
    // 74.4019,
    // 75.8527,
    // 77.2894,
    // 78.7085,
    // 80.1067,
    // 81.4805,
    // 82.8267,
    // 84.1419,
    // 85.4231,
    // 86.6671,
    // 87.8710,
    // 89.0318,
    // 90.1468,
    // 91.2132,
    // 92.2285,
    // 93.1903,
    // 94.0962,
    // 94.9441,
    // 95.7319,
    // 96.4576,
    // 97.1197,
    // 97.7164,
    // 98.2463,
    // 98.7082,
    // 99.1009,
    // 99.4236,
    // 99.6753,
    // 99.8555,
    // 99.9639,
    // 100.0000,
    // 99.9639,
    // 99.8555,
    // 99.6753,
    // 99.4236,
    // 99.1009,
    // 98.7082,
    // 98.2463,
    // 97.7164,
    // 97.1197,
    // 96.4576,
    // 95.7319,
    // 94.9441,
    // 94.0962,
    // 93.1903,
    // 92.2285,
    // 91.2132,
    // 90.1468,
    // 89.0318,
    // 87.8710,
    // 86.6671,
    // 85.4231,
    // 84.1419,
    // 82.8267,
    // 81.4805,
    // 80.1067,
    // 78.7085,
    // 77.2894,
    // 75.8527,
    // 74.4019,
    // 72.9405,
    // 71.4720,
    // 68.5


70,
67.05948579,
64.14729034,
61.29145968,
58.51949703,
55.8580979,
53.33289301,
50.96820148,
48.78679656,
46.8096864,
45.05591163,
43.54236207,
42.28361402,
41.29178993,
40.57644159,
40.1444582,
40,
40.1444582,
40.57644159,
41.29178993,
42.28361402,
43.54236207,
45.05591163,
46.8096864,
48.78679656,
50.96820148,
53.33289301,
55.8580979,
58.51949703,
61.29145968,
64.14729034,
67.05948579,
70,
72.94051421,
75.85270966,
78.70854032,
81.48050297,
84.1419021,
86.66710699,
89.03179852,
91.21320344,
93.1903136,
94.94408837,
96.45763793,
97.71638598,
98.70821007,
99.42355841,
99.8555418,
100,
99.8555418,
99.42355841,
98.70821007,
97.71638598,
96.45763793,
94.94408837,
93.1903136,
91.21320344,
89.03179852,
86.66710699,
84.1419021,
81.48050297,
78.70854032,
75.85270966,
72.94051421,
70,
67.05948579
  };

  //test no delay adn higher kp
  // PIDtest(40, 41);
  // //delay(2000);
  // PIDtest(90, 40);
  // //delay(500);
  // PIDtest(90, 100);
  // //delay(500);
  // PIDtest(40, 100);
  // //delay(500);
  // PIDtest(41, 40);

  PIDtest(150,70);
  for(int i = 0; i < 66; i++){
    PIDcircle(Xarray[i], Yarray[i]);
  }
}


void loop() {
   analogWrite(E1, 0);
    analogWrite(E2, 0);
}






void PIDtest(float xIn, float yIn) {
  float error, integral, lastE, der = 0, effort;
  float kp = 400, ki = 0.002, kd = 0.05;

  xIn = xIn * 46;
  yIn = yIn * 46;
  x = (countL + countR) / 2;
  y = (countL - countR) / 2;
  error = xIn - x;
  while (abs(error) > 5) {
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

  while (abs(error) > 5) {

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

void PIDcircle(float xxIn, float yyIn) {

int  xIn = xxIn * 44;
int  yIn = yyIn * 42;
  int errorX = 0;
  int errorY = 0;
  float integralX = 0;
  float integralY = 0;
  float kp = 1.5;
  float ki = 0.0005;
  int effortA = 0;
  int effortB = 0;
  x = (countL + countR) / 2;
  y = (countL - countR) / 2;
  errorX = xIn - x;
  errorY = yIn - y;
  while ((abs(errorX) > 10) || (abs(errorY) > 10)) {
    x = (countL + countR) / 2;
    y = (countL - countR) / 2;

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
    if (abs(integralX) > 1500) {
      if (integralX > 0) {
        integralX = 1500;
      } else {
        integralX = -1500;
      }
    }

    if (abs(integralY) > 1500) {
      if (integralY > 0) {
        integralY = 1500;
      } else {
        integralY = -1500;
      }
    }
    effortA = (kp * (errorX + errorY)) + (ki * (integralX + integralY));
    effortB = (kp * (errorX - errorY)) + (ki * (integralX - integralY));


    if (effortA >= 0) {
      digitalWrite(M1, LOW);
    } else {
      digitalWrite(M1, HIGH);
    }

    if (effortB >= 0) {
      digitalWrite(M2, LOW);
    } else {
      digitalWrite(M2, HIGH);
    }
    if (abs(effortA) > 255) {
      effortA = 255;
    }
    if (abs(effortB) > 255) {
      effortB = 255;
    }

    if (abs(effortA) < 100) {
      effortA = 100;
    }
    if (abs(effortB) < 100) {
      effortB = 100;
    }
    analogWrite(E1, abs(effortA));
    analogWrite(E2, abs(effortB));
    delay(50);
  }
  analogWrite(E1, 0);
  analogWrite(E2, 0);
}


void homie() {
  while (SetLeft) {
    digitalWrite(M1, HIGH);
    digitalWrite(M2, HIGH);
    analogWrite(E1, 200);  //PWM Speed Control
    analogWrite(E2, 200);  //PWM Speed Control
    Serial.println("going left");
  }

  while (SetBottom) {
    digitalWrite(M1, HIGH);
    digitalWrite(M2, LOW);
    analogWrite(E1, 200);  //PWM Speed Control
    analogWrite(E2, 200);  //PWM Speed Control
    Serial.println("going butt");
  }
}


void safeR() {
  while (digitalRead(right)) {
    digitalWrite(M1, HIGH);
    digitalWrite(M2, HIGH);
    analogWrite(E1, 250);  //PWM Speed Control
    analogWrite(E2, 250);
  }
  analogWrite(E1, 0);  //PWM Speed Control
  analogWrite(E2, 0);
  SetRight = false;
  //Serial.println(count);
}

void safeL() {
  while (digitalRead(left)) {
    digitalWrite(M1, LOW);
    digitalWrite(M2, LOW);
    analogWrite(E1, 250);  //PWM Speed Control
    analogWrite(E2, 250);
  }
  analogWrite(E1, 0);  //PWM Speed Control
  analogWrite(E2, 0);

  SetLeft = false;
  //Serial.println(count);
}
void safeB() {
  while (digitalRead(bottom)) {
    digitalWrite(M1, LOW);
    digitalWrite(M2, HIGH);
    analogWrite(E1, 250);  //PWM Speed Control
    analogWrite(E2, 250);
  }
  analogWrite(E1, 0);  //PWM Speed Control
  analogWrite(E2, 0);

  SetBottom = false;
}
void safeT() {
  while (digitalRead(top)) {
    digitalWrite(M1, HIGH);
    digitalWrite(M2, LOW);
    analogWrite(E1, 250);  //PWM Speed Control
    analogWrite(E2, 250);
  }
  analogWrite(E1, 0);  //PWM Speed Control
  analogWrite(E2, 0);
  SetUp = false;
}





void countA() {
  if (digitalRead(M1)) {
    countL--;
  } else {
    countL++;
  }
}

void countB() {
  if (digitalRead(M2)) {
    countR--;
  } else {
    countR++;
  }
}