//Sabrina Bagley
//CRT 360, Zane Cochran
//3/11/2022
//Pop Art PCB
//Aquatiq 


/* The PopArt PCB
 * This particular project is centered around a custom-made, custom-
 * shaped PCB board, inlaid with 30 NeoPixel LEDs and controlled via
 * ATTiny85. The board I created is shaped like a fish, so I decided
 * to create a series of underwater-themed switch cases. 
 * The first case is an animation that uses stripes of darker blue
 * LEDs to make the fish look as though it's swimming. It has two
 * frames; the first frame is the "rest" frame, and the second frame
 * moves the stripes from the center of the fish's body
 * towards the tail. Together, they make the stripes move back and 
 * forth every second. 
 * The second case turns the board completely blue, meant to act as
 * some nice aquatic mood-lighting.
 * The final case turns the lights off! 
 */
//Button Stuff
#include <Bounce2.h> //debouncing library
int buttonPin = 1; //there's just one button here
Bounce button = Bounce();

//Include neopixel library
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip (64, 0, NEO_GRB + NEO_KHZ800);

int whichFrame = 1;

//Switch case value
int switchVal = 0;

//Animation Values
int numGrid = 30;
int numFrames = 2;

//Timing vars
const long timeInterval = 1000; //interval at which the animation will blink
unsigned long previousMillis = 0;


char index [30]{
  //Animations for the fishe
  //A layout of the PCB's LEDs and their assignments
  
  30, 24, 18, 12,
  29, 23, 17, 11, 6,
  28, 22, 16, 10, 5, 1,
  27, 21, 15,  9, 4, 2,
  26, 20, 14,  8, 3,
  25, 19, 13,  7,
};

char colors [3][3]{ //[how many lists] [how many colors]
  {51, 255, 255}, //0 - Aqua
  // this is the main body color
  
  {0 , 0, 179}, //1 - Zaffre
  //this is the color of the first stripe

  {0, 0, 77}, //2 - Electric Ultramarine
  // this is the color of the second stripe
};

char frames [2] [30]{
  //create the three animation frames 
  //frame 1
  {
  0, 0, 2, 1,
  0, 0, 2, 1, 0,
  0, 0, 2, 1, 0, 0,
  0, 0, 2, 1, 0, 0,
  0, 0, 2, 1, 0,
  0, 0, 2, 1,
},
{
  0, 2, 1, 0,
  0, 2, 1, 0, 0,
  0, 2, 1, 0, 0, 0,
  0, 2, 1, 0, 0, 0,
  0, 2, 1, 0, 0,
  0, 2, 1, 0,
},
//{
//Unnecessary 3rd frame -- removed for memory conservation
//  2, 1, 0, 0,
//  2, 1, 0, 0, 0,
//  2, 1, 0, 0, 0, 0,
//  2, 1, 0, 0, 0, 0,
//  2, 1, 0, 0, 0,
//  2, 1, 0, 0,
//  
//},
}; 
/*  While I initially had borrowed some Bounce2 code from another project,
 *  I switched to using a simpler method that was better for a single button
 *  rather than using code meant for multiple buttons. The previous
 *  button code also stopped working while I was working out the
 *  kinks on the animation case, and, while it may work now, I'm
 *  sticking with the new, shorter code out of an abundance of caution. 
 * 
 */
void setup() {
  // put your setup code here, to run once:
  button.attach(buttonPin, INPUT);
  button.interval(25);
  
  strip.begin();
  strip.clear();
  strip.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  button.update();
  if (button.rose() == true){
    switchVal = switchVal + 1;
  }
  if (switchVal > 2){
    switchVal = 0;
  }
  unsigned long currentMillis = millis();
  

  
  switch (switchVal){
    case 0:
      
 //   for (int j=0; j < numFrames; j++){
 
 //The timer
     if(currentMillis - previousMillis >= timeInterval){
        
      whichFrame = whichFrame+1;
      previousMillis = millis();
      
     if(whichFrame >= numFrames){
      whichFrame = 0;
     }
    }  
      
    for (int i=0; i < numGrid; i++){
      int whichLED = i;
      int whichIndex = index[whichLED];
      int whichColor = frames [whichFrame] [whichLED];

      int a = colors[whichColor][0]; //aqua
      int z = colors[whichColor][1]; //zaffre
      int e = colors[whichColor][2]; //electric ultramarine
    

      strip.setPixelColor(whichIndex, a, z, e);
    }

     strip.show();

  break;
  
    case 1:
    //I'm Blue
    //Turn the whole fish blue 
    for (int i = 0; i < 30; i++){ //run through every LED
      strip.setPixelColor(i, 0, 0, 255); //set color to blue
      
    }
    strip.show(); //show it
    
    break;
  

    case 2:

   //Turn it off

   for (int i = 0; i < 30; i++){
    strip.setPixelColor(i, 0, 0, 0);
   }
   strip.show();
    break;
  }

}
