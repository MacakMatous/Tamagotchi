#include <LiquidCrystal.h>

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int red_led = 7; 
const int green_led = 6;
const int blue_led = 5;
const int yellow_led = 4;

const int sound = 2;
long i = 0;
long j = 0;
long k = 0;
byte score = 0;
int money = 0;
byte turn = 0;

byte thinking[6];
byte displayed[6];

const int BACK = A0; 
const int ENTER = A1; 
const int UP = A2; 
const int DOWN = A3;

bool is_alive = true;			//stats
bool is_ill = false;
bool is_playing_game = false;
bool is_sleeping = false;
bool is_hungry = false;
								
byte hunger = 0;	
byte happiness = 0;
byte poop_counter = 0;
										
enum states {
  	HOME, HOME_SEL_CARE, HOME_SEL_SHOP, HOME_SEL_GAME, HOME_SEL_STATS, CARE, CARE_HUNGER, CARE_HAPPINESS,CARE_LIGHT,
     CARE_POOP,CARE_DRUGS, SHOP, GAME, STATS
	};
enum states STATE, NEXT_STATE;


byte buttonFlag = 0;

void setup() {
  Serial.begin(9600);			//For testing purpose 
  pinMode(BACK,INPUT);
  pinMode(ENTER,INPUT);
  pinMode(UP,INPUT);
  pinMode(DOWN,INPUT);
  create_egg();
  lcd.begin(16,2);
  display_pet();
  STATE = HOME;
  
  tone(sound,261,100);			//Tone
  delay(200);
  tone(sound,220,200);
  delay(200);
  tone(sound,294,300);
  delay(300);

}

void display_pet(){
  lcd.write(byte(0));
  lcd.write(byte(1));
  lcd.setCursor(0,1);
  lcd.write(byte(2));
  lcd.write(byte(3));
}

void create_egg() { 
  
byte egg_top_left[] = {		
  0x00,
  0x00,
  0x00,
  0x00,
  0x01,
  0x02,
  0x04,
  0x08
};

byte egg_top_right[] = {
  0x00,
  0x00,
  0x00,
  0x00,
  0x10,
  0x08,
  0x14,
  0x0A
};

byte egg_down_left[] = {
  0x12,
  0x15,
  0x12,
  0x15,
  0x10,
  0x08,
  0x04,
  0x03
};

byte egg_down_right[] = {
  0x01,
  0x01,
  0x01,
  0x01,
  0x03,
  0x06,
  0x0C,
  0x18
};
  lcd.createChar(0, egg_top_left);  
  lcd.createChar(1, egg_top_right); 
  lcd.createChar(2, egg_down_left); 
  lcd.createChar(3, egg_down_right); 
}

void create_baby() { 
  
  byte baby_top_left[] = {		
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00
};

byte baby_top_right[] = {
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00
};
	 
byte baby_down_left[] = {	
  0x04,
  0x0F,
  0x0D,
  0x0F,
  0x0C,
  0x1F,
  0x1F,
  0x00
};

byte baby_down_right[] = {
  0x08,
  0x1E,
  0x16,
  0x1E,
  0x06,
  0x1F,
  0x1F,
  0x00
};

  lcd.createChar(0, baby_top_left);  
  lcd.createChar(1, baby_top_right); 
  lcd.createChar(2, baby_down_left); 
  lcd.createChar(3, baby_down_right); 
}

void create_child() { 
  
  byte child_top_left[] = {		
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x02,
  0x07
};

byte child_top_right[] = {
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x08,
  0x1C
};
	 
byte child_down_left[] = {	
  0x08,
  0x0B,
  0x0B,
  0x08,
  0x08,
  0x08,
  0x07,
  0x00
};

byte child_down_right[] = {
  0x02,
  0x1A,
  0x1A,
  0x02,
  0x1A,
  0x02,
  0x1C,
  0x00
};

  lcd.createChar(0, child_top_left);  
  lcd.createChar(1, child_top_right); 
  lcd.createChar(2, child_down_left); 
  lcd.createChar(3, child_down_right); 
}

void create_Billy() { 
  
  byte Billy_top_left[] = {		
  0x00,
  0x00,
  0x00,
  0x00,
  0x02,
  0x02,
  0x05,
  0x04
};

byte Billy_top_right[] = {
  0x00,
  0x00,
  0x10,
  0x10,
  0x12,
  0x0A,
  0x05,
  0x01
};
	 
byte Billy_down_left[] = {	
  0x04,
  0x0D,
  0x10,
  0x1C,
  0x10,
  0x0C,
  0x03,
  0x00
};

byte Billy_down_right[] = {
   0x01,
  0x01,
  0x09,
  0x01,
  0x02,
  0x04,
  0x18,
  0x00
};

  lcd.createChar(0, Billy_top_left);  
  lcd.createChar(1, Billy_top_right); 
  lcd.createChar(2, Billy_down_left); 
  lcd.createChar(3, Billy_down_right); 
}

void create_Rabbit() { 
  
  byte Rabbit_top_left[] = {		
  0x00,
  0x00,
  0x04,
  0x04,
  0x04,
  0x07,
  0x0F,
  0x0C
};

byte Rabbit_top_right[] = {
  0x00,
  0x08,
  0x08,
  0x08,
  0x1C,
  0x1E,
  0x1E,
  0x06
};
	 
byte Rabbit_down_left[] = {	
  0x08,
  0x12,
  0x08,
  0x08,
  0x04,
  0x05,
  0x02,
  0x00
};

byte Rabbit_down_right[] = {
  0x12,
  0x01,
  0x09,
  0x11,
  0x02,
  0x12,
  0x0A,
  0x04
};

  lcd.createChar(0, Rabbit_top_left);  
  lcd.createChar(1, Rabbit_top_right); 
  lcd.createChar(2, Rabbit_down_left); 
  lcd.createChar(3, Rabbit_down_right); 
}

void create_Bill() { 
  
  byte Bill_top_left[] = {		
  0x00,
  0x00,
  0x00,
  0x03,
  0x07,
  0x0F,
  0x0E,
  0x04
};

byte Bill_top_right[] = {
  0x00,
  0x00,
  0x00,
  0x1C,
  0x1E,
  0x1F,
  0x03,
  0x01
};
	 
byte Bill_down_left[] = {	
   0x0D,
  0x10,
  0x1C,
  0x04,
  0x06,
  0x06,
  0x03,
  0x00
};

byte Bill_down_right[] = {
  0x09,
  0x01,
  0x01,
  0x19,
  0x01,
  0x06,
  0x1C,
  0x00
};

  lcd.createChar(0, Bill_top_left);  
  lcd.createChar(1, Bill_top_right); 
  lcd.createChar(2, Bill_down_left); 
  lcd.createChar(3, Bill_down_right); 
}

void create_Clown() { 
  
  byte Clown_top_left[] = {		
  0x00,
  0x0C,
  0x1E,
  0x1E,
  0x0E,
  0x0F,
  0x0F,
  0x0F
};

byte Clown_top_right[] = {
 0x00,
  0x06,
  0x0F,
  0x0F,
  0x0E,
  0x1E,
  0x1E,
  0x1E
};
	 
byte Clown_down_left[] = {	
    0x08,
  0x09,
  0x1C,
  0x1C,
  0x08,
  0x04,
  0x03,
  0x0E
};

byte Clown_down_right[] = {
  0x02,
  0x12,
  0x03,
  0x0B,
  0x12,
  0x04,
  0x1C,
  0x04
};

  lcd.createChar(0, Clown_top_left);  
  lcd.createChar(1, Clown_top_right); 
  lcd.createChar(2, Clown_down_left); 
  lcd.createChar(3, Clown_down_right); 
}

void create_Cat() { 
  
  byte Cat_top_left[] = {		
  0x02,
  0x06,
  0x06,
  0x06,
  0x07,
  0x0F,
  0x0F,
  0x10
};

byte Cat_top_right[] = {
  0x08,
  0x0C,
  0x0C,
  0x0C,
  0x1C,
  0x1E,
  0x1E,
  0x01
};
	 
byte Cat_down_left[] = {	
  0x08,
  0x08,
  0x0A,
  0x10,
  0x08,
  0x08,
  0x05,
  0x06
};

byte Cat_down_right[] = {
  0x12,
  0x02,
  0x02,
  0x09,
  0x12,
  0x02,
  0x14,
  0x0C
};

  lcd.createChar(0, Cat_top_left);  
  lcd.createChar(1, Cat_top_right); 
  lcd.createChar(2, Cat_down_left); 
  lcd.createChar(3, Cat_down_right); 
}

void display_care(){
  lcd.setCursor(0,0);
  lcd.print("> Care          ");
  lcd.setCursor(0,1);
  lcd.print("  Shop       1/2");
} 

void display_shop(){
  lcd.setCursor(0,0);
  lcd.print("  Care          ");
  lcd.setCursor(0,1);
  lcd.print("> Shop       1/2");
}

void display_game(){
  lcd.setCursor(0,0);
  lcd.print("> Game          ");
  lcd.setCursor(0,1);
  lcd.print("  Stats      2/2");
} 


void display_stats(){
} 


void care_hunger(){
  lcd.setCursor(0,0);
  lcd.print("Hunger:         ");
  lcd.setCursor(0,1);
  lcd.print(hunger);
  lcd.print("               ");
}

void care_food(){				//krmí zvíře - snižuje hodnotu hladu
hunger--;
}

void care_light(){				// zhasne/rozsvítí - vytiskne znak měsíce na display
  lcd.setCursor(0,0);
  lcd.print("Light switch    ");
  lcd.setCursor(0,1);
  lcd.print("                ");

}

void switch_light(){  
}

void care_drugs(){
  lcd.setCursor(0,0);
  lcd.print("Take medication ");
  lcd.setCursor(0,1);
  lcd.print("                ");
}

void take_drugs(){					// vyléčí zvíře - odebere znak srdce
}

void care_clean(){					// zobrazuje aktuální hodnotu poops
  lcd.setCursor(0,0);
  lcd.print("Poop counter:   ");
  lcd.setCursor(0,1);
  lcd.print(poop_counter);
  lcd.print("               ");
}

void clean_after(){					// uklidí po zvířeti - odebere znak poop
Serial.println("clean");}

void care_happiness()				// zobrazuje akutální hodnotu štěstí
{
  lcd.setCursor(0,0);
  lcd.print("Happiness:      ");
  lcd.setCursor(0,1);
  lcd.print(happiness);
  lcd.print("               ");
}

void sub_shop(){
  lcd.clear();
  lcd.print("SHOP sub");
  lcd.clear();
}

void sub_game(){
initialize_game();
  if (i >= 1){ 
  lcd.setCursor(0,0);
  lcd.print("higher or lower");
  lcd.setCursor(0,1);
  lcd.print("then  ");
  lcd.print(displayed[turn]);
  lcd.print("      ");
  lcd.print(score);
  lcd.print("/");
  lcd.print(turn);
  
  if(button_event(DOWN))
  {
  check_button(DOWN);
  turn++;
  }
  
  if(button_event(UP))
  { 
  check_button(UP);
  turn++;
  }
  
  if(turn == 5){
    if(score >= 3){
    money++;
    }
  	i=0;
    turn=0;
    display_game();
    STATE = HOME_SEL_GAME;
  }
 }
}

void initialize_game(){
  i++;
  if (i == 1){ 
    score=0;
    thinking[0] = random(0,10);
    thinking[1] = random(0,10);
    thinking[2] = random(0,10);
    thinking[3] = random(0,10);
    thinking[4] = random(0,10);
    
    displayed[0] = random(1,9);
    displayed[1] = random(1,9);
    displayed[2] = random(1,9);
    displayed[3] = random(1,9);
    displayed[4] = random(1,9);
  }
  
  	if(thinking[turn] == displayed[turn]){
  	thinking[turn] = random(1,9);
  }
}

void check_button(int button_pressed){
  bool is_correct;
  if(displayed[turn] > thinking[turn] && button_pressed == UP){
  is_correct = 1;
  }
  
  if(displayed[turn] < thinking[turn] && button_pressed == DOWN){
    is_correct = 1;
  }
  
  if(is_correct == 1){
    score++;
  }
}
         

bool button_event(int button){
  switch(button)
  {
    case UP:
     if (digitalRead(UP) == LOW)
     {
       buttonFlag |= 1;
       Serial.println("A");
     } else if (buttonFlag & 1)
     {
       Serial.println("B");
       buttonFlag ^= 1;
       return true;
     }
     break;

    case DOWN:
     if (digitalRead(DOWN) == LOW)
     {
       buttonFlag |= 2;
       Serial.println("C");
     } else if (buttonFlag & 2)
     {
       buttonFlag ^= 2;
       Serial.println("D");
       return true;
     }
     break;

    case BACK:
     if (digitalRead(BACK) == LOW)
     {
       buttonFlag |= 4;
     } else if (buttonFlag & 4)
     {
       buttonFlag ^= 4;
       return true;
     }
     break;

    case ENTER:
     if (digitalRead(ENTER) == LOW)
     {
       buttonFlag |= 8;
     } else if (buttonFlag & 8)
     {
       buttonFlag ^= 8;
       return true;
     }
  }
   return false;
}

void menu(){

  switch (STATE){
   
  case HOME:
    	if(button_event(ENTER))                // je stisknuto tlačítko 'pohyb dolu'?
          {
    		display_care();
            NEXT_STATE = HOME_SEL_CARE;
          }
   		 break;
   
  case HOME_SEL_CARE:                      	   // MENU - TEMPERATURE
         if(button_event(DOWN))                // je stisknuto tlačítko 'pohyb dolu'?
          {
            display_shop();                    // změna domovské obrazovky
            NEXT_STATE = HOME_SEL_SHOP;
          }
    
         else if (button_event(ENTER))         // je stisknuto tlačítko 'vybrat senzor'?
          {
            NEXT_STATE = CARE;
          }
          
   		 else if (button_event(BACK))          // je stisknuto tlačítko 'vybrat senzor'?
          {
            NEXT_STATE = HOME;
           	lcd.clear();
           	display_pet();
          }
          break;

	case HOME_SEL_SHOP:                     	// MENU - MICROPHONE
          if (button_event(DOWN))               // je stisknuto tlačítko 'pohyb dolu'?
          {
            display_game();                     // změna domovské obrazovky
            NEXT_STATE = HOME_SEL_GAME;
          }
          else if (button_event(UP))            // je stisknuto tlačítko 'pohyb nahoru'?
          {
            display_care();                     // změna domovské obrazovky
            NEXT_STATE = HOME_SEL_CARE;
          }
          else if (button_event(ENTER))         // je stisknuto tlačítko 'vybrat senzor'?
          {
            NEXT_STATE = SHOP;
          }
      	  else if (button_event(BACK))          // je stisknuto tlačítko 'vybrat senzor'?
          {
            NEXT_STATE = HOME;
           	lcd.clear();
           	display_pet();
          }
          break;

	case HOME_SEL_GAME:
												// MENU - ACCELEROMETER
          if (button_event(UP))           	 	// je stisknuto tlačítko 'pohyb nahoru'?
          {
            display_shop();                     // změna domovské obrazovky
            NEXT_STATE = HOME_SEL_SHOP;
          }
          else if (button_event(ENTER))         // je stisknuto tlačítko 'vybrat senzor'?
          {
            NEXT_STATE = GAME;
          }
      	  else if (button_event(BACK))          // je stisknuto tlačítko 'vybrat senzor'?
          {
            NEXT_STATE = HOME;
           	lcd.clear();
           	display_pet();
          }
          break;
    
     case CARE:
    	care_happiness();
     	if(button_event(BACK)){                 // je stisknuto tlačítko 'zpět do menu'?
            display_care();                     // zobrazení domovské obrazovky
            NEXT_STATE = HOME_SEL_CARE;
          }
    	else if (button_event(DOWN)){
          care_hunger();
          NEXT_STATE = CARE_HUNGER;
          }
          break;

     case CARE_HUNGER:
          if(button_event(BACK))                // je stisknuto tlačítko 'zpět do menu'?
          {
            display_care();                     // zobrazení domovské obrazovky
            NEXT_STATE = HOME_SEL_CARE;
          }
  		  else if(button_event(DOWN))
  		  {
            care_light();
            NEXT_STATE = CARE_LIGHT;
          }
  
 		  else if(button_event(UP))
  		  { 
            care_happiness();  
            NEXT_STATE = CARE;
  		  }
    
    	  else if(button_event(ENTER))
          { 
            care_food();  
  		  }
          break;
    
     case CARE_LIGHT:
    	 
          if(button_event(BACK))                // je stisknuto tlačítko 'zpět do menu'?
          {
            display_care();                     // zobrazení domovské obrazovky
            NEXT_STATE = HOME_SEL_CARE;
          }
  		  else if(button_event(DOWN))
  		  {
            care_clean();
            NEXT_STATE = CARE_POOP;
          }
  
 		  else if(button_event(UP))
  		  {
            care_hunger();
            NEXT_STATE = CARE_HUNGER;
  		  }
    
    	  else if(button_event(ENTER))
  		  { 
            care_light();  
  		  }
          break;
        
    case CARE_POOP:
    
          if(button_event(BACK))                // je stisknuto tlačítko 'zpět do menu'?
          {
            display_care();                     // zobrazení domovské obrazovky
            NEXT_STATE = HOME_SEL_CARE;
          } 
 		  else if(button_event(UP))
  		  { 
            care_light();
            NEXT_STATE = CARE_LIGHT;
  		  }
    
      	  else if(button_event(DOWN))
  		  {
            care_drugs();
            NEXT_STATE = CARE_DRUGS;
          }
    
    	  else if(button_event(ENTER))
  		  { 
            clean_after();  
  		  }
          break;
    
     case CARE_DRUGS:
    	 
          if(button_event(BACK))                // je stisknuto tlačítko 'zpět do menu'?
          {
            display_care();                     // zobrazení domovské obrazovky
            NEXT_STATE = HOME_SEL_CARE;
          }
    
 		  else if(button_event(UP))
  		  {
            care_clean();
            NEXT_STATE = CARE_POOP;
  		  }
    
    	  else if(button_event(ENTER))
  		  { 
            take_drugs();  
  		  }
          break;

     case GAME:	
   		 
          if(button_event(BACK))                // je stisknuto tlačítko 'zpět do menu'?
          {
            display_game();                     // zobrazení domovské obrazovky
            NEXT_STATE = HOME_SEL_GAME;
          }
          else { 
          sub_game();
          }
          break;
  }
  STATE = NEXT_STATE;
}
void evolution(){
   if(millis()/1000/60 >=7 && millis()/1000/60 < 60){create_baby();}
   if(millis()/1000/60 >=60 && millis()/1000/60 < 120){create_child();}
  
   if((random(100)>=50)&&(j==0)){
   if(millis()/1000/60 >=120 && millis()/1000/60 < 240){create_Billy();
                                                j++;}
   if(millis()/1000/60 >=240 && millis()/1000 < 300){create_Bill();
                                                j++;}
   }
  else if (random(100) < 50 && (j==0))
  {
    if(millis()/1000/60 >=120 && millis()/1000/60 < 240){create_Rabbit();
                                                j++;}
    if(millis()/1000/60 >=240 && millis()/1000/60 < 300){create_Cat();
                                                j++;}
   }
}

void life(){
  if((millis()/1000/60)>=20){
  is_hungry = millis();
  hunger++;
  }
  if(hunger > 10){death();}
  
  if((millis()/1000/60)>=20){
  is_hungry = millis();
  hunger++;
  }
  if(hunger > 8){digitalWrite(blue_led,HIGH);}
  if(hunger > 10){death();}
}

void death()
{
  is_alive = false;
}

void loop() {
  if(is_alive ==  true){
  life();
  menu();
  evolution();
  if(STATE == HOME){display_pet;}
  }
}