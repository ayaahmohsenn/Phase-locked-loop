#include <stdio.h>
#include <stdlib.h>
float Va=0;
float Vb=0;
float Vc=0;
float Valpha=0;
float Vbeta=0;
float Vq=0;
float frequency=0;
long int current_Time=0;
long int prev_Time=0;
int Vq_ref=0;
double Accumlative_error=0;
double error=0;
double delta=0;
long int Kp=320;
long int Ki=400;

int main()
{

void setup() {
pinMode(A0, INPUT);
pinMode(A1, INPUT);
pinMode(A2, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  //abc frame
  Va=analogRead(A0);
  Vb=analogRead(A1);
  Vb=analogRead(A2);
  Vc= -Va-Vb;

  //alpha beta frame
  Valpha=(2/3)*(cos(0)*Va+cos(2*3.14159265/3)*Vb+cos(4*3.14159265/3)*Vc);
  Vbeta=(2/3)*(sin(0)*Va+sin(2*3.14159265/3)*Vb+sin(4*3.14159265/3)*Vc);

  //dq frame
  Vq= Valpha*sin(-delta)+Vbeta*cos(-delta);
  current_Time=micros();

  //PI controller
  error=Vq_ref-Vq;
  Accumlative_error=(Accumlative_error + error * (current_Time - prev_Time));
  frequency=Kp*error+Ki*Accumlative_error;

  //saturation
   if (frequency < 40*2*3.14159265){
      frequency = 40*2*3.14159265;
      }
   if (frequency > 60*2*3.14159265){
      frequency = 60*2*3.14159265;
   }

   //integrate
     delta= delta+ frequency*(current_Time - prev_Time);
     prev_Time = current_Time;

}
}
