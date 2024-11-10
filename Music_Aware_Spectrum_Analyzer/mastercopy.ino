//SPI MASTER (ARDUINO)
//SPI COMMUNICATION BETWEEN TWO ARDUINO 
//CIRCUIT DIGEST

#include<SPI.h>                             //Library for SPI 

int strobe   =   4;       //controls the data readout from spectrum shield
int reset    =   5;       //resets the spectrum shield
int left_ip  =   A0;
int left[7];              // store band values in these arrays
//int right[7]; 
int band;
volatile byte value1=0;
int SS1=10;
//int SS2=7;// CS FOR SLAVE1 And SLAVE2
void setup()
{
 Serial.begin(9600);
 pinMode(reset, OUTPUT);           // reset
 pinMode(strobe, OUTPUT);          // strobe
/* pinMode(f1,OUTPUT);
 pinMode(f2,OUTPUT);
 pinMode(f3,OUTPUT);
 pinMode(f4,OUTPUT);
 pinMode(f5,OUTPUT);
 pinMode(f6,OUTPUT); */
 digitalWrite(reset,LOW);          // reset low
 digitalWrite(strobe,HIGH);        //pin 5 is RESET on the shield

 //SPI
  SPI.begin();                            //Begins the SPI commnuication
  SPI.setClockDivider(SPI_CLOCK_DIV8);    //Sets clock for SPI communication at 8 (16/8=2Mhz)
  digitalWrite(SS1,HIGH);
  //digitalWrite(SS2,HIGH);
   
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
    //right[band] = analogRead(right_ip); // ... and the right
    digitalWrite(strobe,HIGH);    
  }
}

/*void calc()
{
  left[1]/=205;//5
  left[2]/=342;//3
  left[3]/=342;//3
  left[4]/=205;//5
  left[5]/=205;//5
  left[6]/=342;//3
  int i;
  for( i=2;i>=0;i--)
  {value1*=10;
    value1+=left[i];
  }
  for( i=5;i>=3;i--)
  {value2*=10;
    value2+=left[i];
  }
}*/
  
void loop()
{
  digitalWrite (SS1,HIGH);
  readMSGEQ7();
  Serial.println(' ');
  delay(1000);
 // calc();

 // digitalWrite(SS2, HIGH);
  digitalWrite(SS1, LOW);                  //Starts communication with Slave connected to master
                           
  SPI.transfer(left,6); //Send the mastersend value to slave also receives value from slave
  
  digitalWrite(SS1, HIGH);
 // digitalWrite(SS2, LOW);                  //Starts communication with Slave connected to master
                           
  //SPI.transfer(value2); //Send the mastersend value to slave also receives value from slave
 
}

