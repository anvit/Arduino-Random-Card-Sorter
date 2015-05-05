int c = 0;
int size = 7;
int ran;
int a[7] = { 0, 0, 0, 0, 0, 0, 0 };
bool flag;
void setup() {
  Serial.begin(9600);
  unsigned long seed=0, count=32;
  while (--count)
    seed = (seed<<1) | (analogRead(8)&1);
  randomSeed(seed);
  int i = 0;
  while (i< size)
  {
    ran = random(0,51);
    flag = true;
    for(int j = 0; j<size; ++j)
    {
      if(a[j]==ran)
      {
        flag = false;
      }
    }
    if(flag)
    {
      a[i] = ran;
      i++;
    }
  }
  //Serial.print(' ');
}

void loop() {
 if(c<size)
 {
   Serial.print(char(a[c]));
   delay(100);
   c++;
 }
}
