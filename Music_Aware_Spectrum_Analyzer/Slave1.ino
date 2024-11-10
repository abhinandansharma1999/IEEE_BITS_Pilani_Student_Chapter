//SPI SLAVE (ARDUINO)
//SPI COMMUNICATION BETWEEN TWO ARDUINO 
//CIRCUIT DIGEST
//Pramoth.T

#include<SPI.h>

volatile boolean received;
volatile byte Slavereceived;
int ar[3];

void setup()

{
  
  SPCR |= _BV(SPE);                       //Turn on SPI in Slave Mode
  received = false;

  SPI.attachInterrupt();                  //Interuupt ON is set for SPI commnucation
  
}

ISR (SPI_STC_vect)                        //Inerrrput routine function 
{
  Slavereceived = SPDR;         // Value received from master if store in variable slavereceived
  received = true;                        //Sets received as True 
}
void loop() {
  // put your main code here, to run repeatedly:
for(int i=0;i<3;i++)
  {a[i]=Slavereceived%10;
    Slavereceived/=10;
  }
for(int i=0;i<=a[0];i++)
  {digitalWrite(i,HIGH);
  }
for(int i=0;i<a[1];i++)
  {int k=i+5;
    digitalWrite(k,HIGH);
  }  
for(int i=0;i<a[2];i++)
  {int k=i+8;
    digitalWrite(k,HIGH);  
}


