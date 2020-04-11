#include <CapacitiveSensor.h>
//#include <SoftwareSerial.h>

#define AAA 80   //resolution
#define CCC 360 //Trigger


//SoftwareSerial mySerial(1, 0); // RX, TX

CapacitiveSensor   cs1 = CapacitiveSensor(5, 2);
CapacitiveSensor   cs2 = CapacitiveSensor(5, 3);
CapacitiveSensor   cs3 = CapacitiveSensor(5, 4);
CapacitiveSensor   cs4 = CapacitiveSensor(5, 6);

unsigned long csSum1;
unsigned long csSum2;
unsigned long csSum3;
unsigned long csSum4;

void setup()
{
  //  mySerial.begin(9600);
  pinMode(10, OUTPUT);
}
void loop() {
  sense(cs1, csSum1, 10, 70, 600);
  sense(cs2, csSum2, 9, 70, 600);
  sense(cs3, csSum3, 8, 70, 600);
  sense(cs4, csSum4, 7, 70, 600);
}

void sense(CapacitiveSensor &mycs, unsigned long &mysum, int pin, int sen, int trigp) {
  long cs = mycs.capacitiveSensor(AAA); //a: Sensor resolution is set to 80
  //  mySerial.println(cs);
  if (cs > sen) { //b: Arbitrary number
    mysum += cs;
    //    mySerial.println(mysum);
    if (mysum >= trigp) //c: This value is the threshold, a High value means it takes longer to trigger
    {
      //      mySerial.print("T");
      //      mySerial.println(mysum);
      if (mysum > 0) {
        mysum = 0;  //Reset
      }
      //      mycs.reset_CS_AutoCal(); //Stops readings
      digitalWrite(pin, HIGH);
    }
  } else {
    digitalWrite(pin, LOW);
    mysum = 0; //Timeout caused by bad readings
  }
}
