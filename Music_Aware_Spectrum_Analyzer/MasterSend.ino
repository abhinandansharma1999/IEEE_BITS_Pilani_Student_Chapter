/SPI MASTER (ARDUINO)
//SPI COMMUNICATION BETWEEN TWO ARDUINO 
//CIRCUIT DIGEST

#include<SPI.h>                             //Library for SPI 

int strobe   =   4;       //controls the data readout from spectrum shield
int reset    =   3;       //resets the spectrum shield
int left_ip  =   A0;
int f1       =   A1;      // 160Hz
int f2       =   A2;      // 400Hz
int f3       =   A3;      // 1kHz
int f4       =   A4;      // 2.5kHz
int f5       =   A5;      // 6.25kHz
int f6       =   5;       // 16kHz
int left[7];              // store band values in these arrays
//int right[7]; 
int band;
volatile byte value1=0,value2=0;
int SS1=6,SS2=7;// CS FOR SLAVE1 And SLAVE2
void setup()
{

 pinMode(reset, OUTPUT);           // reset
 pinMode(strobe, OUTPUT);          // strobe
 pinMode(f1,OUTPUT);
 pinMode(f2,OUTPUT);
 pinMode(f3,OUTPUT);
 pinMode(f4,OUTPUT);
 pinMode(f5,OUTPUT);
 pinMode(f6,OUTPUT);
 digitalWrite(reset,LOW);          // reset low
 digitalWrite(strobe,HIGH);        //pin 5 is RESET on the shield

 //SPI
  SPI.begin();                            //Begins the SPI commnuication
  SPI.setClockDivider(SPI_CLOCK_DIV8);    //Sets clock for SPI communication at 8 (16/8=2Mhz)
  SPI.setBitOrder(MSBFIRST);
  digitalWrite(SS1,HIGH);
  digitalWrite(SS2,HIGH);
   
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
    //right[band] = analogRead(right_ip); // ... and the right
    digitalWrite(strobe,HIGH);    
  }
}
void loop()
{
  readMGSEQ7();
  calc();

  digitalWrite(SS2, HIGH);
  digitalWrite(SS1, LOW);                  //Starts communication with Slave connected to master
                           
  SPI.transfer(value1); //Send the mastersend value to slave also receives value from slave
  
  digitalWrite(SS1, HIGH);
  digitalWrite(SS2, LOW);                  //Starts communication with Slave connected to master
                           
  SPI.transfer(value2); //Send the mastersend value to slave also receives value from slave
 
}

void calc()
{
  band[1]/=205;//5
  band[2]/=342;//3
  band[3]/=342;//3
  band[4]/=205;//5
  band[5]/=205;//5
  band[6]/=342;//3
  for(int i=3;i>0;i--)
  {value1*=10;
    value1+=band[i];
  }
  for(int i=6;i>3;i--)
  {value2*=10;
    value2+=band[i];
  }
  
}

