//SPI SLAVE (ARDUINO)
//SPI COMMUNICATION BETWEEN TWO ARDUINO 
//CIRCUIT DIGEST
//Pramoth.T

#include<SPI.h>

volatile boolean received;
volatile byte Slavereceived;
byte a;
int SS1 = 10;

void setup()

{
  pinMode(MOSI,INPUT);
  SPCR |= _BV(SPE);                       //Turn on SPI in Slave Mode
  

  SPI.attachInterrupt();                  //Interuupt ON is set for SPI commnucation
  
}

ISR (SPI_STC_vect)                        //Inerrrput routine function 
{
  Slavereceived = SPDR;         // Value received from master if store in variable slavereceived
  a = Slavereceived;
                        
}
void loop() {
  // put your main code here, to run repeatedly:
  if(a>100) {
    digitalWrite(2,LOW);
  }
  else {
    digitalWrite(2,HIGH);
  }
  delay(1000);
  Serial.print(a);
  Serial.print(" ");
/*for(int i=0;i<3;i++)
  {a[i]=Slavereceived%10;
    Slavereceived/=10;
  }
for(int i=0;i<=a[0];i++)
  {digitalWrite(i,LOW);
  Serial.print(i);
  Serial.print(" ");
  }
for(int i=0;i<a[1];i++)
  {int k=i+5;
    digitalWrite(k,LOW);
      Serial.print(k);
  Serial.print(" ");
  }  
for(int i=0;i<a[2];i++)
  {int k=i+8;
    digitalWrite(k,HIGH); 
      Serial.print(k);
  Serial.print(" "); 
} */
}


