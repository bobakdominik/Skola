#define ROW_1 10 // pin matice 9
#define ROW_2 A1 // pin 14
#define ROW_3 2 // pin 8
#define ROW_4 13 // pin 12
#define ROW_5 9 // pin 1
#define ROW_6 3 // pin 7
#define ROW_7 8 // pin 2
#define ROW_8 5 // pin 5

#define COL_1 A0 // pin 13
#define COL_2 7 // pin 3
#define COL_3 6 // pin 4
#define COL_4 11 // pin 10
#define COL_5 4 // pin 6
#define COL_6 12 // pin 11
#define COL_7 A2 // pin 15
#define COL_8 A3 // pin 16

#define BUTTON A4
#define POTPIN A5
const byte rows[] = {
  ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8
};
  byte background[] = {0,0,0,0,0,0,0,0};
  byte player = 0b00011000;
  byte heart[] = {
B00000000,
B01100110,
B10011001,
B10000001,
B01000010,
B00100100,
B00011000,
B00000000};

byte five[] = {
B00000000,
B01111110,
B01100000,
B01111100,
B00000110,
B01100110,
B00111100,
B00000000};

byte four[] = {
B00000000,
B00011110,
B00110110,
B01100110,
B01111110,
B00000110,
B00000110,
B00000000};

byte three[] = {
B00000000,
B00111100,
B01100110,
B00001100,
B00001100,
B01100110,
B00111100,
B00000000};

byte two[] = {
B00000000,
B00111100,
B01100110,
B00001100,
B00011000,
B00110010,
B01111110,
B00000000};

byte one[] = {
B00000000,
B00011000,
B01111000,
B00011000,
B00011000,
B00011000,
B00011000,
B00000000};

byte* numbers[] = {five, four, three, two, one};


void setup() {
  randomSeed(analogRead(0));
  for (byte i = 2; i <= 13; i++)
    pinMode(i, OUTPUT);
    
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
}

void menu(){
  while(digitalRead(BUTTON) == LOW){
    drawToMatrix(five);
  }
  for(byte i = 0; i < 4; i++){
    drawScreen(numbers[i+1], 50);
  }
 }

void loop() {
  menu();
  bool startChecking = false;
  int row = 0;
  byte lastRow;
  do{
    lastRow = background[6];
    shiftPlayer();
    shiftRows();
    drawScreen(background, 30);
    if(++row == 8)
      startChecking = true;
  }while (!startChecking || !checkPlayer());
  background[7] = lastRow;
  finish();
  reset();
}

void finish(){
  for(byte i = 0; i < 3; i++){
    drawScreen(background, 50);
    setColumns(player);
    digitalWrite(ROW_8, HIGH);
    delay(700);
    digitalWrite(ROW_8, LOW);
    }
  }

bool checkPlayer(){
  byte posCount = 0;
  for(byte i = 0; i < 8; i++){
    if(((background[7] >> i) & 0x01) == 1){
      posCount++;
      }
    }
   if(posCount < 3)
    return true;
   return false;
}
void shiftPlayer(){
  int input = analogRead(POTPIN);
  if ((input < 412) && (player > 0b00000011))
    player = player >> 0x01;
  else if((input > 612) && (player < 0b11000000))
    player = player << 0x01;
  
}

void shiftRows(){
  for(byte i = 7; i > 0; i--){
    background[i] = background[i-1];
    }
  background[0] = 1 << random(7);
  background[7] = background[7] | player;
 }

void drawScreen(byte buf[], float timeCountMax){
  float timeCount = 0;
  while(timeCount < timeCountMax){
    drawToMatrix(buf);
    timeCount += 1;
  }
}

void reset(){
  for(byte i = 0; i < 8; i++){
    background[i] = 0;
  }
  player = 0b00011000; 
}

void drawToMatrix(byte buf[]){
    for (byte i = 0; i < 8; i++) {
      setColumns(buf[i]); // nastavenie stlpca pre konkretny riadok
      digitalWrite(rows[i], HIGH);
      delay(2);
      digitalWrite(rows[i], LOW);
    }
}

void setColumns(byte b) {
  digitalWrite(COL_8, ((b >> 0) & 0x01) == 0); 
  digitalWrite(COL_7, ((b >> 1) & 0x01) == 0); 
  digitalWrite(COL_6, ((b >> 2) & 0x01) == 0); 
  digitalWrite(COL_5, ((b >> 3) & 0x01) == 0); 
  digitalWrite(COL_4, ((b >> 4) & 0x01) == 0); 
  digitalWrite(COL_3, ((b >> 5) & 0x01) == 0); 
  digitalWrite(COL_2, ((b >> 6) & 0x01) == 0); 
  digitalWrite(COL_1, ((b >> 7) & 0x01) == 0); 
}
