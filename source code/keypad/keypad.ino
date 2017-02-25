#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const byte numRows= 4; //number of rows on the keypad
const byte numCols= 4; //number of columns on the keypad

//keymap defines the key pressed according to the row and columns just as appears on the keypad
char keymap[numRows][numCols]= 
{
{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'}, 
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};
int x=0,password_attempt=0;
const int green = 8;
int piezoStatus = LOW;
char password[6] = {'1', '2', '3', '4', '5', '6'};

//Code that shows the the keypad connections to the arduino terminals
byte rowPins[numRows] = {A3,A2,A1,A0}; //Rows 0 to 3
byte colPins[numCols]= {A5,A4,7,6}; //Columns 0 to 3

//initializes an instance of the Keypad class
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

void setup()
{
Serial.begin(9600);
 pinMode(A0, INPUT_PULLUP);
digitalWrite(A0, HIGH);

pinMode(A1, INPUT_PULLUP);
digitalWrite(A1, HIGH);

pinMode(A2, INPUT_PULLUP);
digitalWrite(A2, HIGH);

pinMode(A3, INPUT_PULLUP);
digitalWrite(A3, HIGH);

pinMode(A4, INPUT_PULLUP);
digitalWrite(A4, HIGH);

pinMode(A5, INPUT_PULLUP);
digitalWrite(A5, HIGH);

pinMode(green, OUTPUT);

lcd.begin(16, 2);
lcd.setCursor(0, 0);
lcd.print("A-Enter password.");
lcd.setCursor(0, 1);
  // Print a message to the LCD.
lcd.print("B-Change password.");
  
}

//If key is pressed, this key is stored in 'keypressed' variable
//If key is not equal to 'NO_KEY', then this key is printed out
//if count=17, then count is reset back to 0 (this means no key is pressed during the whole keypad scan process
void loop()
{
  
char keypressed = myKeypad.getKey();
if (keypressed == 'A'){
 boolean pw_correct = enter_password();
 if(pw_correct){
  digitalWrite(green, HIGH);
  delay(1000);
  digitalWrite(green, LOW);
  menu(1000);}
  }
else if (keypressed == 'B'){
  boolean change_pw = change_password();
  }

}


void clear_display(int time){ //clear display with delay time
  delay(time);
  lcd.clear();
}

void menu(int time){     //go to menu with delay time and clear display
  password_attempt=0; //set password attemted to 0
  clear_display(time);
  lcd.setCursor(0, 0);
lcd.print("A-Enter password.");
lcd.setCursor(0, 1);
  // Print a message to the LCD.
lcd.print("B-Change password.");
  }

boolean enter_password(){
  password_attempt++;
  if(password_attempt>3){
    wrong_password();
    return false;
    }
   else{ 
   boolean pw_correct = true;
  clear_display(0);
  lcd.setCursor(0, 0);
  lcd.print("Enter Password : ");
  char pw[6];
  int y=0;
  
  while(1&&y!=6){
  pw[y] = myKeypad.getKey();
  if(pw[y]!=NO_KEY){
  lcd.setCursor(y, 1);
  lcd.print(pw[y]);
  y++;
  }
  }
  for(int x=0;x<6;x++){
    if(pw[x]!=password[x]){
      pw_correct = false;
      break;
      }
    }

  if(pw_correct){
    //digitalWrite(green, HIGH);    
  clear_display(500);
  lcd.setCursor(0, 0);
  lcd.print("Password valid");
  //digitalWrite(green, LOW);    
    }
  if(!pw_correct){
  //digitalWrite(red, HIGH);    
  clear_display(500);
  lcd.setCursor(0, 0);
  lcd.print("Password invalid");
  clear_display(1000);
 // digitalWrite(red, LOW);    
  pw_correct = enter_password();
    }  
  return pw_correct;
  }
}

void wrong_password(){
  clear_display(500);
  lcd.setCursor(0, 0);
  lcd.print("Yoy entered password 3 times incorrectly!");
  delay(500);
  for (int positionCounter = 0; positionCounter < 25; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(300);}
menu(1000);
  }

boolean change_password(){
  boolean pw_correct = enter_password();
  boolean change_pw = true;
  if(pw_correct){
    
  clear_display(0);
  lcd.setCursor(0, 0);
  lcd.print("New Password : ");
  int y=0;
    

  while(1&&y!=6){
  password[y] = myKeypad.getKey();
  if(password[y]!=NO_KEY){
  lcd.setCursor(y, 1);
  lcd.print(password[y]);
  y++;
  }
  }
  }
  clear_display(500);
  lcd.setCursor(0, 0);
  lcd.print("New PassWord is :");  
  lcd.setCursor(0, 1);
  for (int positionCounter = 0; positionCounter < 6; positionCounter++) {
    lcd.setCursor(positionCounter, 1);
    lcd.print(password[positionCounter]); 
    }
   delay(1000);
   menu(0);
  }  
