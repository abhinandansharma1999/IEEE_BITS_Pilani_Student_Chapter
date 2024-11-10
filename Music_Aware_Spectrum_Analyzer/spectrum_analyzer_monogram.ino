int strobe   =   4;       //controls the data readout from spectrum shield
int reset    =   5;       //resets the spectrum shield
int left_ip  =   A0;

int f11      =   0;       // 60Hz
int f12      =   2;

int f21      =   3;      // 400Hz
int f22      =   6;      // 1kHz

int f31      =   7;      // 2.5kHz
int f32      =   8;      // 6.25kHz

int f41      =   9;
int f42      =   10;
int f43      =   11;
int f44      =   12;

int f51      =   13;
int f52      =   A1;

int f61      =   A2;
int f62      =   A3;

int f71      =   A4;
int f72      =   A5;

                         // 16kHz
int left[7];              // store band values in these arrays
int band;
void setup()
{
 Serial.begin(9600);
 pinMode(reset, OUTPUT);           // reset
 pinMode(strobe, OUTPUT);   // strobe


 pinMode(f11,OUTPUT);
 pinMode(f12,OUTPUT);
 pinMode(f21,OUTPUT);
 pinMode(f22,OUTPUT);
 pinMode(f31,OUTPUT);
 pinMode(f32,OUTPUT);
 pinMode(f41,OUTPUT);
 pinMode(f42,OUTPUT);
 pinMode(f43,OUTPUT);
 pinMode(f44,OUTPUT);
 pinMode(f51,OUTPUT);
 pinMode(f52,OUTPUT); 
 pinMode(f61,OUTPUT);
 pinMode(f62,OUTPUT);
 pinMode(f71,OUTPUT);
 pinMode(f72,OUTPUT);
 digitalWrite(reset,LOW);          // reset low
 digitalWrite(strobe,HIGH);        //pin 5 is RESET on the shield
 digitalWrite(f11,HIGH);
 digitalWrite(f12,HIGH);
 digitalWrite(f21,HIGH);
 digitalWrite(f22,HIGH);
 digitalWrite(f31,HIGH);
 digitalWrite(f32,HIGH);
 digitalWrite(f41,HIGH);
 digitalWrite(f42,HIGH);
 digitalWrite(f43,HIGH);
 digitalWrite(f44,HIGH);
 digitalWrite(f51,HIGH);
 analogWrite(f52,255);
 analogWrite(f61,255);
 analogWrite(f62,255);
 analogWrite(f71,255);
 analogWrite(f72,255);
}
void readMSGEQ7()
// Function to read 7 band equalizers
{
  digitalWrite(reset, HIGH);                  // pulling reset high and then low activates the strobe pin and the amplitude values corresponding to the frequencies is read out through amp_read pin serially
  digitalWrite(reset, LOW);
  for(band=0; band <7; band++)
  {
    digitalWrite(strobe,LOW);                 // strobe pin on the shield - kicks the IC up to the next band. Data is read while the strobe pin is low
    delayMicroseconds(30);                    // settling time for the the above pull
    left[band] = analogRead(left_ip);         // store left band reading
    Serial.print(left[band]);
    Serial.print(" ");
    digitalWrite(strobe,HIGH); 
  }
  Serial.println(' ');
}
void loop()
{
  readMSGEQ7();
  
  if (left[0]>500)
  { digitalWrite(f11,LOW);
    digitalWrite(f12,LOW);
    delay(100);
    digitalWrite(f11,HIGH);
    digitalWrite(f12,HIGH);
  }
    
  if (left[1]>300)
  { digitalWrite(f21,LOW);
    digitalWrite(f22,LOW);
    delay(100);
    digitalWrite(f21,HIGH);
    digitalWrite(f22,HIGH);
  }

 //if (left[2]>200)
  { digitalWrite(f31,LOW);
    digitalWrite(f32,LOW);
    delay(100);
    digitalWrite(f31,HIGH);
    digitalWrite(f32,HIGH);
  }

  if (left[3]>150)
  { digitalWrite(f41,LOW);
    digitalWrite(f42,LOW);
    digitalWrite(f43,LOW);
    digitalWrite(f44,LOW);
    delay(100);
    digitalWrite(f41,HIGH);
    digitalWrite(f42,HIGH);
    digitalWrite(f43,HIGH);
    digitalWrite(f44,HIGH);
  }

  if (left[4]>150)
  { digitalWrite(f51,LOW);
    analogWrite(f52,0);
    delay(100);
    digitalWrite(f51,HIGH);
    analogWrite(f52,255);
  }

  if (left[5]>150)
  { analogWrite(f61,0);
    analogWrite(f62,0);
    delay(100);
    analogWrite(f61,255);
    analogWrite(f62,255);
  }

  if (left[6]>150)
  { analogWrite(f71,0);
    analogWrite(f72,0);
    delay(100);
    analogWrite(f71,255);
    analogWrite(f72,255);
  }
    
    
   
  delay(1000);
}
