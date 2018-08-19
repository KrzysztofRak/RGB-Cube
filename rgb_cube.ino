#include <Adafruit_NeoPixel.h>
#define LEDS_NUM 512
#define DATA_PIN 3
#define CS 8

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(LEDS_NUM, DATA_PIN, NEO_GRB + NEO_KHZ800);

class RGB {
  private:
    byte predefinedColors[14][3] = {
      {255, 204, 0}, // YELLOW
      {0, 255, 0}, // GREEN
      {255, 0, 0}, // RED
      {0, 255, 0}, // BLUE
      {204, 0, 153}, // PINK
      {51, 204, 255}, // LIGHT BLUE
      {255, 204, 102}, // LIGHT YELLOW
      {102, 0, 102}, // DARK PURPLE
      {153, 51, 255}, // PURPLE
      {204, 0, 102}, // DARK PINK
      {0, 153, 51}, // DARK GREEN
      {153, 51, 0}, // BROWN
      {255, 102, 0}, // ORANGE
      {255, 255, 255} // WHITE
    };

    byte lastColorIndex = -1;
    
  public:
    byte r = 0, g = 0, b = 0;

   void randColor(byte withoutWhite = 0)
   {
      
      byte index = random(14-withoutWhite);
      while(index == lastColorIndex)
        index = random(14);
      lastColorIndex = index;
      r=predefinedColors[index][0];
      g=predefinedColors[index][1];
      b=predefinedColors[index][2];
   }

   void set(byte r, byte g, byte b)
   {
      this->r = r;
      this->g = g;
      this->b = b;
   }
};

String getParam(String paramName);
void checkData();
bool checkForNewData();
void displayText(String text, int timeDelay, RGB color);
void displayChar(bool SELECTED_CHAR[CS][CS], int timeDelay, RGB color);
void selectAndDisplayChar(char selectedChar, int timeDelay, RGB color);
void setDiode(int x, int y, int z, RGB color);
void setColumnX(int y, int z, RGB color);
void setColumnY(int x, int y, RGB color);
void setColumnZ(int x, int y, RGB color);
void setLayer(short axis, short layer, RGB color);
RGB ColorWheel(byte WheelPos);

String data = "";
bool newDataAvailable = false;
   
void setup() {
    Serial.begin(57600);

    Serial.setTimeout(2);

    pixels.begin();
    pixels.show();
    
    randomSeed(analogRead(0));

    RGB c;
    c.r = 255;
    displayText("R", 150, c);
    c.r = 0;
    c.g = 255;
    displayText("G", 150, c);
    c.g = 0;
    c.b = 255;
    displayText("B", 150, c);
    c.r = 255;
    c.g = 255;
    c.b = 0;
    displayText(" CUBE", 150, c);
}

void loop() {
  checkForNewData();
  if(newDataAvailable)
    checkData();
  delay(100);
}


