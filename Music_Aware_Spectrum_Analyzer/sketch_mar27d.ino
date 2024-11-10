volatile byte a=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
a=0;
int b=4;
a+=b;
Serial.println(a);
delay(2000);
}
