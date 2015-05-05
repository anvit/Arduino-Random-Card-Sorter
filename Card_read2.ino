#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

#define CLK 8
#define LAT 10
#define OE  9
#define A   A0
#define B   A1
#define C   A2
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

char a[7];
int numbers[7];
int c=0;
int size = 7;
char cards[] = {'2','3','4','5','6','7','8','9','P','J','Q','K','A'};

int r[] = { 7,6,3,2,0,0,0,0,7,6,6,5,7,6 };
int g[] = { 0,0,0,0,0,0,7,6,7,6,2,1,0,0 };
int b[] = { 4,3,7,6,7,6,0,0,0,0,0,0,0,0 };

void setup()
{
  Serial.begin(9600);
  matrix.begin();
  matrix_boot();
}

void matrix_boot()
{
  blank_t();
  //Box L
  matrix.fillRect(1, 1, 9, 14, matrix.Color333(1, 1, 1));
  matrix.drawPixel(1, 1, matrix.Color333(0, 0, 0));
  matrix.drawPixel(9, 1, matrix.Color333(0, 0, 0));
  matrix.drawPixel(1, 14, matrix.Color333(0, 0, 0));
  matrix.drawPixel(9, 14, matrix.Color333(0, 0, 0));  
  //Box R
  matrix.fillRect(22, 1, 9, 14, matrix.Color333(1, 1, 1));
  matrix.drawPixel(22, 1, matrix.Color333(0, 0, 0));
  matrix.drawPixel(30, 1, matrix.Color333(0, 0, 0));
  matrix.drawPixel(22, 14, matrix.Color333(0, 0, 0));
  matrix.drawPixel(30, 14, matrix.Color333(0, 0, 0));    
  
  //Intro Spade
  matrix.fillRect(3, 4, 5, 6, matrix.Color333(0, 0, 0));
  matrix.drawPixel(3,4, matrix.Color333(1, 1, 1));
  matrix.drawPixel(7,4, matrix.Color333(1, 1, 1));  
  matrix.drawPixel(5,3, matrix.Color333(0, 0, 0));   
  matrix.drawLine(2, 7, 2, 8, matrix.Color333(0, 0, 0));  
  matrix.drawLine(8, 7, 8, 8, matrix.Color333(0, 0, 0));    
  matrix.drawLine(4, 5, 4, 8, matrix.Color333(0, 0, 1));  
  matrix.drawLine(6, 5, 6, 8, matrix.Color333(0, 0, 1));  
  matrix.drawPixel(5,7, matrix.Color333(0, 0, 1));
  matrix.drawPixel(5,5, matrix.Color333(0, 0, 1));    
  matrix.drawPixel(5,10, matrix.Color333(0, 0, 0));      
  matrix.drawLine(3, 12, 7, 12, matrix.Color333(0, 0, 0));  
  matrix.drawLine(4, 11, 6, 11, matrix.Color333(0, 0, 0));

  //Intro Diamond
  matrix.drawLine(26, 3, 26, 13, matrix.Color333(0, 0, 0));  
  matrix.drawLine(22, 8, 30, 8, matrix.Color333(0, 0, 0));    
  matrix.drawLine(25, 4, 27, 4, matrix.Color333(0, 0, 0));  
  matrix.drawLine(25, 12, 27, 12, matrix.Color333(0, 0, 0));  
  matrix.drawLine(24, 5, 24, 11, matrix.Color333(0, 0, 0));  
  matrix.drawLine(28, 5, 28, 11, matrix.Color333(0, 0, 0));    
  matrix.drawLine(23, 7, 29, 7, matrix.Color333(0, 0, 0));  
  matrix.drawLine(23, 9, 29, 9, matrix.Color333(0, 0, 0));    
  matrix.fillRect(25, 5, 3, 7, matrix.Color333(3, 0, 0));
  matrix.fillRect(24, 7, 5, 3, matrix.Color333(3, 0, 0));  
  matrix.drawPixel(23,8, matrix.Color333(3, 0, 0));
  matrix.drawPixel(29,8, matrix.Color333(3, 0, 0));    
  matrix.drawPixel(26,4, matrix.Color333(3, 0, 0));
  matrix.drawPixel(26,12, matrix.Color333(3, 0, 0));    
  matrix.drawLine(25, 6, 25, 9, matrix.Color333(0, 1, 0));  
  matrix.drawPixel(26,8, matrix.Color333(0, 1, 0));    
  matrix.drawPixel(27,7, matrix.Color333(0, 1, 0));
  matrix.drawPixel(27,9, matrix.Color333(0, 1, 0));      

  
}
void isort(int *ar, int n)
{
 for (int i = 1; i < n; ++i)
 {
   int j = ar[i];
   int k;
   for (k = i - 1; (k >= 0) && (j < ar[k]); k--)
   {
     ar[k + 1] = ar[k];
   }
   ar[k + 1] = j;
   draw_arr(ar,i);
 }
}

void draw_arr(int *ar, int n)
{
  blank_l_r();
  for (int i = 0; i < n; ++i)
  {
    draw_bar(ar[i],i);
  }
  for (int i = 0; i < n; ++i)
  {
    chose_num(ar[i]);
    pixel(i);
    delay(2000);
  }
}

void chose_num(int n)
{
  int s =  n % 4;
  int c = n / 4;
  int col = 0;
  blank_l(); //Blank slate
  switch(s)
  {
    case 0: draw_club();
            col = 0;
            break;
    case 1: draw_diamond();
            col = 7;
            break;
    case 2: draw_heart();
            col = 7;
            break;
    case 3: draw_spade();
            col = 0;
            break;    
  }
  draw_letter(cards[c],col);
}

void draw_bar(int n, int ct)
{
  int crd = n / 4;
  matrix.drawLine(18+(2*ct) , 15, 18 + (2*ct) , (15-crd-1) , matrix.Color333(r[crd], g[crd], b[crd]));
}

void pixel(int n)
{
  if(n!=0)
  {
      matrix.drawPixel(18+(2*(n-1)), 0, matrix.Color333(0, 0, 0));
  }
  matrix.drawPixel(18+(2*n), 0, matrix.Color333(1, 1, 1));
}

void draw_spade()
{
  matrix.drawLine(9, 14, 13, 14, matrix.Color333(0, 0, 0));
  matrix.drawLine(10, 13, 12, 13, matrix.Color333(0, 0, 0));
  matrix.drawLine(11, 6, 11, 12, matrix.Color333(0, 0, 0));
  matrix.drawLine(8, 10, 14, 10, matrix.Color333(0, 0, 0));  
  matrix.drawLine(8, 9, 14, 9, matrix.Color333(0, 0, 0));  
  matrix.drawLine(9, 8, 13, 8, matrix.Color333(0, 0, 0));
  matrix.drawLine(9, 11, 13, 11, matrix.Color333(0, 0, 0));
  matrix.drawLine(10, 7, 12, 7, matrix.Color333(0, 0, 0));
}

void draw_heart()
{
  matrix.drawLine(9, 7, 10, 7, matrix.Color333(7, 0, 0));
  matrix.drawLine(12, 7, 13, 7, matrix.Color333(7, 0, 0));
  matrix.drawPixel(12, 7, matrix.Color333(7, 0, 0));
  matrix.drawPixel(13, 7, matrix.Color333(7, 0, 0));
  matrix.drawLine(8, 8, 14, 8, matrix.Color333(7, 0, 0));
  matrix.drawLine(8, 9, 14, 9, matrix.Color333(7, 0, 0));
  matrix.drawLine(8, 10, 14, 10, matrix.Color333(7, 0, 0));
  matrix.drawLine(9, 11, 13, 11, matrix.Color333(7, 0, 0));
  matrix.drawLine(10, 12, 12, 12, matrix.Color333(7, 0, 0));
  matrix.drawPixel(11, 13, matrix.Color333(7, 0, 0));  
}

void draw_club()
{
  matrix.drawLine(9, 14, 13, 14, matrix.Color333(0, 0, 0));
  matrix.drawLine(10, 13, 12, 13, matrix.Color333(0, 0, 0));
  matrix.drawLine(11, 6, 11, 12, matrix.Color333(0, 0, 0));
  matrix.drawLine(10, 7, 12, 7, matrix.Color333(0, 0, 0));
  matrix.drawLine(8, 10, 14, 10, matrix.Color333(0, 0, 0));
  matrix.drawLine(9, 9, 9, 11, matrix.Color333(0, 0, 0));
  matrix.drawLine(13, 9, 13, 11, matrix.Color333(0, 0, 0));  
}

void draw_diamond()
{
  matrix.drawLine(8, 10, 14, 10, matrix.Color333(7, 0, 0));
  matrix.drawLine(11, 6, 11, 14, matrix.Color333(7, 0, 0));
  matrix.drawLine(10, 7, 10, 13, matrix.Color333(7, 0, 0));
  matrix.drawLine(12, 7, 12, 13, matrix.Color333(7, 0, 0));
  matrix.drawLine(9, 9, 9, 11, matrix.Color333(7, 0, 0));  
  matrix.drawLine(13, 9, 13, 11, matrix.Color333(7, 0, 0));     
}

void draw_letter(char s,int col)
{
  matrix.setCursor(1, 1);   // next line
  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color333(col,0,0));
  if(s=='P')
  {
    matrix.setCursor(3, 1);   // next line
    matrix.print(String(0));
    matrix.drawLine(1, 1, 1, 7, matrix.Color333(col, 0, 0));
  }
  else
  {
    matrix.print(s);
  }
}

void draw_num_right(int x)
{
  matrix.setCursor(17, 1);   // next line
  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color333(1,1,1)); 
  matrix.print(String(x)); 
}

void blank_t()
{
  matrix.fillRect(0, 0, 16, 16, matrix.Color333(0, 0, 0));
  matrix.fillRect(16, 0, 16, 16, matrix.Color333(0, 0, 0));  
}

void blank_l_r()
{
  matrix.fillRect(0, 0, 16, 16, matrix.Color333(1, 1, 1));
  matrix.fillRect(16, 0, 16, 16, matrix.Color333(0, 0, 0));  
}

void blank_l()
{
  matrix.fillRect(0, 0, 16, 16, matrix.Color333(1, 1, 1));
}

void loop()
{
  if(Serial.available()&&c<=(size-1))
  {
    a[c] = Serial.read();
    c++;
  }
  if(c==size)
  {
    blank_l_r();
    for(int i=0;i<c;++i)
    {
      numbers[i] = int(a[i]);
    }
    for(int i=0;i<c;++i)
    {
      chose_num(numbers[i]);
      pixel(i);
      draw_bar(numbers[i],i);
      delay(2000);
    }
    isort(numbers, (sizeof(numbers)/sizeof(numbers[0])) );    
    draw_arr(numbers,c);
    c++;
  }
}
