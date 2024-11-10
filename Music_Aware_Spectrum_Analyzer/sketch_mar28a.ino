int strobe   =   4;       //controls the data readout from spectrum shield
int reset    =   5;       //resets the spectrum shield
int left_ip  =   A0;
//int f1       =   A1;      // 160Hz
//int f2       =   A2;      // 400Hz
//int f3       =   A3;      // 1kHz
//int f4       =   A4;      // 2.5kHz
//int f5       =   A5;      // 6.25kHz
//int f6       =   5;       // 16kHz
int left[7];              // store band values in these arrays
//int right[7]; 
int band = 0;
void setup()
{
 Serial.begin(9600);
 pinMode(reset, OUTPUT);           // reset
 pinMode(strobe, INPUT);   // strobe
 pinMode(A2,OUTPUT);
/* pinMode(f1,OUTPUT);
 pinMode(f2,OUTPUT);
 pinMode(f3,OUTPUT);
 pinMode(f4,OUTPUT);
 pinMode(f5,OUTPUT);
 pinMode(f6,OUTPUT); */
 digitalWrite(reset,LOW);          // reset low
 digitalWrite(strobe,HIGH);        //pin 5 is RESET on the shield
}
void readMSGEQ7()
// Function to read 7 band equalizers
{
  digitalWrite(reset, HIGH);                  // pulling reset high and then low activates the strobe pin and the amplitude values corresponding to the frequencies is read out through amp_read pin serially
  digitalWrite(reset, LOW);
  for(band=0; band <7; band++)
  {
    digitalWrite(strobe,LOW);                 // strobe pin on the shield - kicks the IC up to the next band. Data is read while the strobe pin is low
    delayMicroseconds(300);                    // settling time for the the above pull
    left[band] = analogRead(left_ip);         // store left band reading
    Serial.print(left[band]);
    Serial.print(" ");
    //right[band] = analogRead(right_ip); // ... and the right
    digitalWrite(strobe,HIGH); 
  }
  Serial.println(' ');
}
void loop()
{
 // readMSGEQ7();
  //if(digitalRead(strobe) == 0){
  left[band]=analogRead(A1);
   Serial.print(left[band]);
    Serial.print(" ");
  band++;
  if(band == 8) { band = 0;}
  Serial.println(' ');
 /* analogWrite(f2,left[2]/4);
  analogWrite(f3,left[3]/4);
  analogWrite(f4,left[4]/4);
  analogWrite(f5,left[5]/4);
  analogWrite(f6,left[6]/4); */
  delay(1000);
}
}
