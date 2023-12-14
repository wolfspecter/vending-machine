#include <Wire.h> //I2C lib
#include <Adafruit_GFX.h> //OLED lib
#include <Adafruit_SSD1306.h> //OLED lib
#include <Keypad.h> //KEYPAD lib

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); //create oled object to control oled

#define ROW_NUM  4 //four rows
#define COLUMN_NUM  4 //four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
}; //set up matrix keypad button

byte pin_rows[ROW_NUM] = {25, 33, 32,}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {12, 14, 27, 26}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM ); //create keypad object to control keypad

#define returnmn 18 //monney return pin connect

class product{
  public:
    String name; //product name
    int price; //product price
    int tag; //product tag
    int pull; //pinout to control pull out product
    int amount; //number of product left
}; //create class product to store product data

product defa; //defa data is NULL
product no1; //no1 is product 1
product no2; //no2 is product 2
product no3; //no3 is product 3

static int count; //use to store monney put in data
static product choose; //use to store choosen product data. If did not choose, choose=defa
static String mess; //use to store message to display

void setup(){
  choose=defa; //set choose=defa
  count=0; //set monney put in = 0

  pinMode(returnmn,OUTPUT);

  //test with
  //product 1: "hang1", 4 product left
  //product 2: "hang2", 5 product left
  //product 3: "hang3", no product left
  //product no1, 
  no1.name="hang1";
  no1.price=10000;
  no1.tag=1;
  no1.pull=15;
  no1.amount=4;
  pinMode(no1.pull,OUTPUT);

  //product no2;
  no2.name="hang2";
  no2.price=20000;
  no2.tag=2;
  no2.pull=2;
  no2.amount=5;
  pinMode(no2.pull,OUTPUT);

  //product no3;
  no3.name="hang3";
  no3.price=30000;
  no3.tag=3;
  no3.pull=4;
  no3.amount=0;
  pinMode(no3.pull,OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize the oled with I2c address 0x3C
  delay(2000); //wait 2s to initilize the oled
  display.clearDisplay(); //clear the display
  display.setTextSize(1); //set oled text size to 1
  display.setTextColor(WHITE); //set text color to white
}

void loop(){
  display.setCursor(0, 10); //set cursor at (0,10)

  display.print("Danh muc san pham:");

//display tag, name and price of each product
  display.println("");
  display.print(no1.tag);
  display.print(" ");
  display.print(no1.name);
  display.print(": ");
  display.print(no1.price);
  display.print("dong");

  display.println("");
  display.print(no2.tag);
  display.print(" ");
  display.print(no2.name);
  display.print(": ");
  display.print(no2.price);
  display.print("dong");

  display.println("");
  display.print(no3.tag);
  display.print(" ");
  display.print(no3.name);
  display.print(": ");
  display.print(no3.price);
  display.print("dong");

  //display monney put in
  display.println("");
  display.print("da bo vao: ");
  display.print(count);

  //display message if has
  display.println("");
  display.print(mess);

  char key=keypad.getKey(); //get the button push in keypad

  //case for each button push
  /*
    1 for choosing product 1
    2 for choosing product 2
    3 for choosing product 3
    4 for put in 10000dong
    5 for put in 20000dong
    6 for put in 50000dong
    A for take out choosen product
    B for take out monney put in
  */
  switch (key){
    case '1':
      if(no1.amount>0){
      mess="da chon: 1";
        choose=no1;
      }
      else{
      mess="het hang";
      choose=defa;
      }
      break;

    case '2':
      if(no2.amount>0){
      mess="da chon: 2";
        choose=no2;
      }
      else{
      mess="het hang";
      choose=defa;
      }
      break;

    case '3':
      if(no3.amount>0){
      mess="da chon: 3";
        choose=no3;
      }
      else{
      mess="het hang";
      choose=defa;
      }
      break;

    case '4':
      count=count+10000;
      break;

    case '5':
      count=count+20000;
      break;

    case '6':
      count=count+50000;
      break;

    case 'A':
      if(choose.price<=count&&choose.amount>0){
        digitalWrite(choose.pull,HIGH);
        delay(1000);
        digitalWrite(choose.pull,LOW);
        count=count-choose.price;
        choose.amount=choose.amount-1;
        switch (choose.tag){
          case '1':
            no1.amount=choose.amount;
            break;
          case '2':
            no2.amount=choose.amount;
            break;
          case '3':
            no3.amount=choose.amount;
            break;
        }
      }
      else{
      mess="moi chon lai";
      choose=defa;
      }
      break;

    case 'B':
      if(count>0){
        for(int i=0;i<count/10000;i++){
          digitalWrite(returnmn,HIGH);
          delay(500);
          digitalWrite(returnmn,LOW);
          delay(500);
        //  count=count-10000;
        }
        count=0;
        mess="";
      }
      break;
  }
  display.display();

  display.clearDisplay();
}