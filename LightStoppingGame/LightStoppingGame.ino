#include <avr/io.h> // contains uint8_t and register definitions
#include <avr/delay.h>  // contains the delay function


int rest = 1000;//The Delay method needs a constant variable


//Rest Decrement
void setRest(int decrement){
  //int decrement will set the decrement factor
  
  if(rest<=20){
    rest=20;
  }
  else{
    rest-=20;
  }
}

/*
 * Lights are controlled by the following pins
 * PD[2-7] and PB[0]
 * The Green Light is controlled by PB[4]
 * 
 * The Start Game button is controlled by PB[5]
 * 
 * Skill Stop is controlled by PB[4]
 * 
 * Full Stop is controlled by PB[3]
 */





//TODO: Make a method that cycles through the lights. 
int cycle(int cycles){
  //We will set all the necessary pins to output
  DDRD=0b11111111;//Setting the lights to output
  DDRB=0b00000000;

  //This allow us to loop through the lights one by one in the forward direction from 0 to 1
for(int a=0;a<=cycle;a++){
  for(int i=2;i<8;i++){
    //This will go from 0 to 7
    PORTD=1<<i;
    int decision=skillStop();
    if(decision==0){
      continue;
    }
    else if(decision==1){
      //If the correct button was pressed we want to show that, decrement the rest time, and continue
      setRest(200);
      _delay_ms(2000);
      continue;
    }
    else if (decision==2){
      _delay_ms(2000);//If the wrong light was chosen, then we want to stop the 
      return;
    }
    else if(cycles<=0){
      return 3;
    }
  }

  //This will loop in the reverse direction
  for(int i=7;i>=2;i--){
    // this will go from 7 to 0

    PORTD=1<<i;
     int decision=skillStop();
    if(decision==0){
      continue;
    }
    else if(decision==1){
      //If the correct button was pressed we want to show that, decrement the rest time, and continue
      setRest(80);
      _delay_ms(2000);
      continue;
    }
    else if (decision==2){
      _delay_ms(2000);//If the wrong light was chosen, then we want to stop the 
      return;
    }
    else if(cycles<=0){
      return 3;
    }
  }
  
}
}








//TODO:Slow STOP method. This will choose a random number of lights to go down till it stops





//TODO skill stop stops the light right at the place
int skillStop(){
  //This method will stop the light in its spot
  //we want to have a while loop here to make sure the board registers inputs at any point
  bool pressed=false;//this will see if the button is pressed
  int x=0;
  while(!pressed && x<=rest){
    _delay_ms(1);
    pressed=PINB & 0b00010000;
    x++;
  }
  //This loop will break after the button has been pressed or if the rest period has expired
  if(x==0){
    //We will handle if the rest period has expired first
    //In this case we want to break
    return 0;
  }
  else if(pressed &&(PORTD & 0b00010000)){
    //Here we want to handle if the button has been pressed on the correct spot
    return 1;//We will handle this in the cycle method
  }
  else if(pressed &&!(PORTD & 0b00010000)){
    //If the button was pressed, but it was the wrong light
    return 2;
  }
//  else if((PINB & 0b0001000)){
//    //If the slow stop button is pressed, then we will slowly stop at a position
//    int numStop=10;//Try to make this random if possible, but I have it relate to the current rest
//    for(int i=0;i>=numStop;i++){
//      PORTD=1<<i;
//      _delay_ms(1000);
//    }
//    if(PORTB & 0b00010000){
//      //If you land on the correct spot
//      return 1;
//    }
//    else{
//      //Did not land on the correct spot
//      return 2;
//    }
  
  else{
    return 0;
  }
}







int main(){
//This is the main method
init(); 
bool startGame; 
while(true){
  //Here we want to see if the start game button is pressed
 startGame=PINB& 0b00100000;
  if(startGame){
    cycle(100);
  }
}

cycle(100000);
  return 0;
}

 
