#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"
LiquidCrystal_I2C lcd(0x3F,16,2);
RTC_DS1307 RTC;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
int Mode =2;
int Up=9;
int Down=10;
int Led=11;
int tg=0;
int Hour=0;
int Minute=0;
int Second=0;
int Year=2021;
int Month=1;
int Day=1;
void nhapgiovao();
void nhapgiora();
void caichuong();
int giovao[12];
int phutvao[12];
int giora[12];
int phutra[12];
int giayvao[12];
int giayra[12];
void chuongra();

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
 Wire.begin();
 RTC.begin();
 pinMode(Up, INPUT);
 pinMode(Down, INPUT);
 pinMode(Mode, INPUT);
 pinMode(Led, OUTPUT);
pinMode(2, INPUT_PULLUP); 
pinMode(9, INPUT_PULLUP); 
 pinMode(10, INPUT_PULLUP); 
// attachInterrupt(0, ngatMode, LOW);
  if(!RTC.isrunning())
 {
//  RTC.adjust(DateTime(__DATE__,__TIME__));
 }
  lcd.begin();                    
  lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:

  if(digitalRead(2)==LOW)
  {tg++;
  if(tg==2)tg=0;
 
    }
   if(tg==1)//che do cai dat
   {lcd.clear();
    lcd.setCursor(0,0);
   lcd.print("UP:time setup ");
   lcd.setCursor(0,1);
   lcd.print("DOWN: bell setup");
    while(digitalRead(Up)!=LOW &&digitalRead(Down)!=LOW )
    {delay(100);
    }// doi bam nut
    if(digitalRead(Up)==LOW )
    {
      delay(500);
      Hour =chinhgio(Hour);
        Serial.println(Hour);
    delay(500);
Minute= chinhphut(Minute);
  delay(500);
Second= chinhgiay(Second);
  delay(500);
chinhnam();
  delay(500);
chinhthang();
  delay(500);
chinhngay();
  delay(500);
  RTC.adjust(DateTime(Year, Month, Day, Hour, Minute, Second));
  lcd.clear();
  tg=0;
    }
    if(digitalRead(Down)==LOW )
    {
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Up:via COM");
   lcd.setCursor(0,1);
   lcd.print("Down:via Button");
   delay(500);
  while(digitalRead(Up)!=LOW &&digitalRead(Down)!=LOW )
    {delay(100);
    }// doi chon che do
if(digitalRead(Up)==LOW )
{delay(500);
     caichuong();
     tg=0;
     lcd.clear();

}
if(digitalRead(Down)==LOW)
{      lcd.clear();
   lcd.setCursor(0,0);
   lcd.print(" nhap 12 thoi ");
   lcd.setCursor(0,1);
   lcd.print("  diem vao lop !");
      
   delay(500);
 while(digitalRead(Mode)!=LOW )
 {delay(100);}
   delay(500);
   for(int i=0; i<1;i++)
   {
      lcd.clear();
   lcd.setCursor(0,1);
   lcd.print(i);
   delay(500);
    while(digitalRead(Mode)!=LOW )
    {giovao[i]= chinhgio(giovao[i]);
      }
      delay(500);
      while(digitalRead(Mode)!=LOW )
    {phutvao[i]= chinhphut(phutvao[i]);
      }
            delay(500);
        while(digitalRead(Mode)!=LOW )
    {giayvao[i]= chinhgiay(giayvao[i]);
      }
            delay(500);
      
    }
         lcd.clear();
   lcd.setCursor(0,0);
   lcd.print(" nhap 12 thoi ");
    lcd.setCursor(0,1);
   lcd.print(" diem ra choi !");
   delay(100);
 while(digitalRead(Mode)!=LOW )
 {delay(100);}
   delay(500);
   for(int j=0; j<1;j++)
   {
      lcd.clear();
   lcd.setCursor(0,1);
   lcd.print(j);
   delay(500);
    while(digitalRead(Mode)!=LOW )
    {giora[j]= chinhgio(giora[j]);
      }
      delay(500);
      while(digitalRead(Mode)!=LOW )
    {phutra[j]= chinhphut(phutra[j]);
      }
            delay(500);
        while(digitalRead(Mode)!=LOW )
    {giayra[j] = chinhgiay(giayra[j]);
      }
            delay(500);
        
      
    }
   lcd.clear();
   lcd.setCursor(0,1);
   lcd.print("Hoan tat!");
   delay(1000);
    
}
 
}
    
tg=0;
lcd.clear();
}
  if(tg==0){
 DateTime now = RTC.now();
  Year=now.year();
  Month=now.month();
  Day=now.day();
  Hour=now.hour();
  Minute=now.minute();
  Second=now.second();


  int i;
  int j;
 
//-------------------
 for(i=0;i<12;i++)
 {
  if(giovao[i]==Hour && phutvao[i]==Minute&& giayvao[i]==Second)
  {digitalWrite(Led,HIGH);
  delay(3000);
  digitalWrite(Led,LOW);
    }
  }
   for(j=0;j<12;j++)
 {
  if(giora[j]==Hour && phutra[j]==Minute&& giayra[i]==Second)
  {chuongra();
    }
  }
//------------------
   if(now.hour()<=9)
   {

      lcd.setCursor(0,0);
      lcd.print(0);
     lcd.setCursor(1,0);
     lcd.print(now.hour());
   }
   else {
     lcd.setCursor(0,0);
     lcd.print(now.hour());
   }
     lcd.setCursor(2,0);
     lcd.print(":");
     //--------------------
   if(now.minute()<=9)
   {
    
      lcd.setCursor(3,0);
     lcd.print("0");;
     
      lcd.setCursor(4,0);
     lcd.print(now.minute());
   }
   else {
    
     lcd.setCursor(3,0);
  lcd.print(now.minute());
   }
   lcd.setCursor(5,0);
     lcd.print(":");
   //-------------------------
   if(now.second()<=9)
   {
      lcd.setCursor(6,0);
     lcd.print("0");;  
      lcd.setCursor(7,0);
     lcd.print(now.second());
   }
   else {
   lcd.setCursor(6,0);
   lcd.print(now.second());
   }
 
     lcd.setCursor(0,1);
     lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
    lcd.setCursor(3,1);
     lcd.print(",");
   if(now.day()<=9)
   {
     lcd.setCursor(4,1);
     lcd.print("0");;
      lcd.setCursor(5,1);
     lcd.print(now.day());
   }
   else {
  
          lcd.setCursor(4,1);
     lcd.print(now.day());
   }
     lcd.setCursor(6,1);
     lcd.print("/");
   if(now.month()<=9)
   {
     lcd.setCursor(7,1);
     lcd.print("0");;
      lcd.setCursor(8,1);
     lcd.print(now.month());
   }
   else {
     lcd.setCursor(7,1);
     lcd.print(now.month());
   }
 
     lcd.setCursor(9,1);
     lcd.print("/");
     lcd.setCursor(10,1);
     lcd.print(now.year());
  
   
  }
}
//--------- end loop---------

int chinhgio(int gio)
{lcd.clear();
  while(digitalRead(2)!=LOW){
lcd.setCursor(7,0);
lcd.print("Hour");

if(digitalRead(Up)!=HIGH)
 { gio++;
  delay(200);
  }
  if(digitalRead(Down)!=HIGH)
 { gio=gio-1;
  delay(200);
  }
 if(gio>23)gio=23;
if(gio<0)gio=0;
if(gio<=9){
lcd.setCursor(0,0);
lcd.print("0");
lcd.setCursor(1,0);
lcd.print(gio);}else
{
lcd.setCursor(0,0);
lcd.print(gio);

  }

  }
  return gio;
}
// -----------------------------
  int chinhgiay(int giay)
{lcd.clear();
  while(digitalRead(2)!=LOW){
lcd.setCursor(7,0);
lcd.print("Second");

if(digitalRead(Up)!=HIGH)
 { giay++;
  delay(200);
  }
  if(digitalRead(Down)!=HIGH)
 { giay--;
  delay(200);
  }
 if(giay<0)giay=59;
if(giay>59)giay=0;
if(giay<=9){
lcd.setCursor(0,0);
lcd.print("0");
lcd.setCursor(1,0);
lcd.print(giay);}else
{
lcd.setCursor(0,0);
lcd.print(giay);
  }
  }
  return giay;
  }
//--------------------
 int chinhphut(int phut)
{lcd.clear();
  while(digitalRead(2)!=LOW){
lcd.setCursor(7,0);
lcd.print("Minute");

if(digitalRead(Up)!=HIGH)
 { phut++;
  delay(200);
  }
  if(digitalRead(Down)!=HIGH)
 { phut--;
  delay(200);
  }
  if(phut<0)phut=59;
  if(phut>590)phut=0;
if(phut<=9){
lcd.setCursor(0,0);
lcd.print("0");
lcd.setCursor(1,0);
lcd.print(phut);}else
{
lcd.setCursor(0,0);
lcd.print(phut);
  }
  }
  return phut;
  }
//  ----------------------
 void chinhnam()
{ lcd.clear();
  while(digitalRead(2)!=LOW){

lcd.setCursor(7,0);
lcd.print("Year");
  if(Year<2000)Year=2100;
  if(Year>2100)Year=2000;
if(digitalRead(Up)!=HIGH)
 { Year++;
  delay(200);
  }
  if(digitalRead(Down)!=HIGH)
 { Year--;
  delay(200);
  }
lcd.setCursor(0,0);
lcd.print(Year);
  }
  }
  //-------------------
   void chinhthang()
{ lcd.clear();
  while(digitalRead(2)!=LOW){
lcd.setCursor(7,0);
lcd.print("Month");

if(digitalRead(Up)!=HIGH)
 { Month++;
  delay(200);
  }
  if(digitalRead(Down)!=HIGH)
 { Month--;
  delay(200);
  }
 if(Month<1)Month=12;
 if(Month>12)Month=1;
if(Month<=9){
lcd.setCursor(0,0);
lcd.print("0");
lcd.setCursor(1,0);
lcd.print(Month);}else
{
lcd.setCursor(0,0);
lcd.print(Month);
  }
  }
  }
  //-------------------
   void chinhngay(){
 lcd.clear();
while(digitalRead(2)!=LOW){
lcd.setCursor(7,0);
lcd.print("Day");

if(digitalRead(Up)!=HIGH)
 { Day++;
  delay(200);
  }
  if(digitalRead(Down)!=HIGH)
 { Day--;
  delay(200);
  }
  if(Month==1||Month==3||Month==5||Month==7||Month==8||Month==10||Month==12){
  if(Day<1)Day=31;
  if(Day>31)Day=1;}
else if(Month==2 && Year%4==0){
  if(Day<1)Day=29;
  if(Day>29)Day=1;
  }
else if(Month==2){
if(Day<1)Day=28;
if(Day>28)Day=1;
    }else{
 if(Day<1)Day=30;
if(Day>30)Day=1;
      }
if(Day<=9){
lcd.setCursor(0,0);
lcd.print("0");
lcd.setCursor(1,0);
lcd.print(Day);}else
{
lcd.setCursor(0,0);
lcd.print(Day);
  }
  }
  }
void caichuong(){
 
     lcd.setCursor(0,0);
     lcd.print("set the bell");
     lcd.setCursor(0,1);
     lcd.print("via COM");
   int n;
Serial.println("Nhap so luong gio ra choi, vao lop (max=12):");


  do{
      while(Serial.available()==0)
   {
   delay(100);
    }
n=Serial.readStringUntil('\n').toInt();
        if(n <0 || n > 12){
            Serial.println("\nNhap lai so luong : ");
        }
    }while(n < 0 || n > 12);

thoidiemvao(n);
thoidiemra(n);
Serial.println(" Hoan tat ! ");
tg=0;
  }
  //-----------
   void thoidiemvao(int n)
{
  Serial.println("Nhap  moc  thoi gian vao lop:");
 for(int i=0; i<n;i++)
 {  
  Serial.print("nhap thơi gian thư ");
  Serial.print(i);
  Serial.print(":");
  Serial.println();
  Serial.print("Nhap gio:");
   while(Serial.available()==0)
   {
   delay(100);
    }
  giovao[i] = Serial.readStringUntil('\n').toInt();
 
if(giovao[i]<=0||giovao[i]>23)
  { Serial.println();
      Serial.println("nhap lai gio:");
       while(Serial.available()==0)
   {
   delay(100);
    }
  giovao[i] = Serial.readStringUntil('\n').toInt();
    }
  Serial.println(giovao[i]);;
  Serial.print("Nhap phut:");
     while(Serial.available()==0)
   {
   delay(100);
    }
   phutvao[i] = Serial.readStringUntil('\n').toInt();
    if(phutvao[i]<=0||phutvao[i]>59)
  { Serial.println();
      Serial.println("nhap lai phut:");
       while(Serial.available()==0)
   {
   delay(100);
    }
  phutvao[i] = Serial.readStringUntil('\n').toInt();
    }
  Serial.println(phutvao[i]);
  //----------------------
      Serial.print("Nhap giay:");
     while(Serial.available()==0)
   {
   delay(100);
    }
   giayvao[i] = Serial.readStringUntil('\n').toInt();
    if(giayvao[i]<=0||giayvao[i]>59)
  { Serial.println();
      Serial.println("nhap lai giay:");
       while(Serial.available()==0)
   {
   delay(100);
    }
  giayvao[i] = Serial.readStringUntil('\n').toInt();
    }
  Serial.println(giayvao[i]);  
  
  }
}
//--------------
void thoidiemra(int n){
Serial.println("Nhap  moc  thoi gian ra choi:");
 for(int i=0; i<n;i++)
 {  
  Serial.print("nhap thơi gian thư ");
  Serial.print(i);
  Serial.print(":");
  Serial.println();
  Serial.print("Nhap gio:");
   while(Serial.available()==0)
   {
   delay(100);
    }
  giora[i] = Serial.readStringUntil('\n').toInt();
 
if(giora[i]<=0||giora[i]>23)
  { Serial.println();
      Serial.println("nhap lai gio:");
       while(Serial.available()==0)
   {
   delay(100);
    }
  giora[i] = Serial.readStringUntil('\n').toInt();
    }
  Serial.println(giora[i]);;
  //----------
  Serial.print("Nhap phut:");
     while(Serial.available()==0)
   {
   delay(100);
    }
   phutra[i] = Serial.readStringUntil('\n').toInt();
    if(phutra[i]<0||phutra[i]>59)
  { Serial.println();
      Serial.println("nhap lai phut:");
       while(Serial.available()==0)
   {
   delay(100);
    }
  phutra[i] = Serial.readStringUntil('\n').toInt();
    }
  Serial.println(phutra[i]);  
  //------------------
    Serial.print("Nhap giay:");
     while(Serial.available()==0)
   {
   delay(100);
    }
   giayra[i] = Serial.readStringUntil('\n').toInt();
    if(giayra[i]<0||giayra[i]>59)
  { Serial.println();
      Serial.println("nhap lai giay:");
       while(Serial.available()==0)
   {
   delay(100);
    }
  giayra[i] = Serial.readStringUntil('\n').toInt();
    }
  Serial.println(giayra[i]);  
  
  }
}
 void chuongra()
 {int i=0;
 while(i<4 )
 {i++;
  digitalWrite(Led,HIGH);
  delay(500);
  digitalWrite(Led,LOW);
    delay(500);
 }
  }
