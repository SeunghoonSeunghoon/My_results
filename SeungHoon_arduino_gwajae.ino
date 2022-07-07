//자물쇠 만들기-승훈 ver-피컴과제!
//LCD로 비번 보고 매트릭스 키패드로 입력받고, 서브모터 돌려서 잠궈보자! 

#include <Keypad.h>   //매트릭스 키패드
#include <Servo.h>
#include <Wire.h>     //I2C통신                                
#include <LiquidCrystal_I2C.h>                    
LiquidCrystal_I2C lcd(0x27, 16, 2);  //LCD  
int tru=0;                           //변수 초기화
int count=0;
char PW[4]={'0','3','2','8'};        //비밀번호(까먹지 말기!!!)
const byte ROWS = 4;                 //상수(배열 넣어야 돼서 절대 바뀌면 안돼)
const byte COLS = 4;


byte rowPins[ROWS] = {9,8,7,6};
byte colPins[COLS] = {5,4,3,2};      //키패드용 배열
char Keys[ROWS][COLS] = {
  {'A', '3', '2', '1'},              //키패드 키 배열
  {'B', '6', '5', '4'},
  {'C', '9', '8', '7'},
  {'D', '#', '0', '*'}
};

Servo myservo;//서브모터
Keypad customkeypad = Keypad(makeKeymap(Keys),rowPins,colPins,ROWS,COLS);//키패드에 배열대로 넣기


void setup() {
  Serial.begin(9600);
  myservo.attach(11);                //11번핀으로 servo 컨트롤
  lcd.init();           
  lcd.backlight();                  //LCD 기본설정                           
  lcd.setCursor(0, 0);     
}


void loop() {
  char Keys = customkeypad.getKey(); // 입력한 key 배열 넣어주기
 
  if (Keys)
  {
    
    Serial.println(Keys);
    
    lcd.print(Keys);                 // if 안쓰면 안돼겠다; if 배열 돌려서 일치하면 하나씩 올려서 정답에 도달시키자.
    if (Keys==PW[count])
    {
      count++;             
      tru++;                        //key가 맞으면 tru에 쁠쁠해주기
      
    }
    else if(Keys!=PW[count])        //아니면 카운트만 올려주기. 브레이크는 불안해
    {
      count++;
    }

    if (Keys=='#')            //# 누르면 re함수로 돌려서 초기화하기
      re();
   
    if (count==4)             //카운트가 4가되면 tru변수가 4(정답)인지 확인해주기
    {
      if (tru==4)   
        Su();                 // 4네? Su(정답)함수로 가랏
      else
        Fa();                 //아니네? Fa(실패)함수로 가랏

      tru=0;                  //초기화
      count=0;                //초기화
    }
    
  }//다시 되돌릴 생각 하지마 차피 loop자너
}

void Su() //성공함수
{
  myservo.write(180);                                    // 성공했으니까 서브모터 반대방향으로 돌려주기
  lcd.clear();                                           //켜져있는 문자열 없애버리기
  lcd.print("Right password!!"); 
  delay(2000);                                           //딜레이 주고
  lcd.clear();                                           //클리어 한담에
  lcd.print("enter the key                           "); // 다시 첨으로 돌려주기
}

void Fa()//실패함수
{
  myservo.write(0);                                      //실패네? 원점으로 돌아가
  lcd.clear();                                           //동일
  lcd.print("wrong password..");                         //실패!
  delay(2000);                                           //동일
  lcd.clear();                                           //동일
  lcd.print("enter the key                           "); //동일
  
}
 void re()//re함수
 {
    tru=0;                                               //제로
    count=0;                                             //제로
    lcd.clear();                                         //지우기
    lcd.print("reseted!");                               //리셋문자 출력
    delay(2000);                                         //딜레이
    lcd.clear();                                         //지우고 
    lcd.print("enter the key                           ");//다시 돌리기
 }
 

  
  
