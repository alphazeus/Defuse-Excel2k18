#define duration 5000 

#define A 2
#define B 3
#define C 4
#define D 5
#define E 6
#define F 7
#define G 8
#define DP 9

#define disp1 10
#define disp2 11
#define disp3 12
#define disp4 13

#define fuse A0
#define bout A1
#define xtra A2

#define numbersegments { \
{1,1,1,1,1,1,0,0},\
{0,1,1,0,0,0,0,0},\
{1,1,0,1,1,0,1,0},\
{1,1,1,1,0,0,1,0},\
{0,1,1,0,0,1,1,0},\
{1,0,1,1,0,1,1,0},\
{1,0,1,1,1,1,1,0},\
{1,1,1,0,0,0,0,0},\
{1,1,1,1,1,1,1,0},\
{1,1,1,0,0,1,1,0},\
}

byte numbers[10][8] = numbersegments; 
const int segments[8] = {A, B, C, D, E, F, G, DP};
unsigned long int t=0;
int xmin=1;
void setup() 
{ 
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(DP, OUTPUT);
  pinMode(disp1, OUTPUT);
  pinMode(disp2, OUTPUT);  
  pinMode(disp3, OUTPUT);
  pinMode(disp4, OUTPUT);
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  digitalWrite(DP, LOW);
  digitalWrite(disp1, LOW);
  digitalWrite(disp2, LOW);
  digitalWrite(disp3, LOW);
  digitalWrite(disp4, LOW);
 } 

 void loop()
 { 
  int digit1=2,digit2=0,digit3=0,digit4=0;
  t=millis();
  while(digit1!=0&&digit2!=0&&digit3!=0&&digit4!=0)
  {
    setsegments(digit1, disp1, duration); 
    setsegments(digit2, disp2, duration);
    setsegments(digit3, disp3, duration);
    setsegments(digit4, disp4, duration);
    sec=(t-millis());
    if(sec%1000<20)
    {
      delay(20);
      digit4=9-(sec/1000)%10;
      digit3=5-(sec/60000)%6;
      digit2=9-(sec/(60000*60))%10;
      digit1=xmin-(sec/(60000*60*60))%6;
    }
    if(digitalRead(fuse)==HIGH)
      break;
    if(digitalRead(xtra)==HIGH)
      xmin++;
  }
  if(digitalRead(bout)==0)digitalWrite(9,HIGH);
  else digitalWrite(9,LOW);
 }        

  void setsegments(int number, int digit, int ontime)
  { 
    for (int seg=0; seg<8; seg++)
    { 
      if(numbers[number][seg]==1)
      { 
        digitalWrite(segments[seg], HIGH);
      }
      else 
      {
        digitalWrite(segments[seg], LOW);
      }
    }
    digitalWrite(digit, HIGH);
    delayMicroseconds(ontime);
    digitalWrite(digit, LOW);
  }
