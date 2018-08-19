bool brightening(int timeDelay)
{
     for(short i = 5; i<=255; i+=2)
     {
        if(checkForNewData())
          return true;
          
        pixels.setBrightness(i);
        delay(timeDelay);
        pixels.show();
     }
     return false;
}

bool blanking(int timeDelay)
{
     for(short j = 255; j>=5; j-=2)
     {
        if(checkForNewData())
          return true;
        pixels.setBrightness(j);
        delay(timeDelay);
        pixels.show();
     }
     return false;
}

RGB colorWheel(byte WheelPos) {
  RGB color;
  
  if(WheelPos < 85) {
    color.r = WheelPos * 3;
    color.g = 255 - WheelPos * 3;
    color.b = 0;
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    color.r = 255 - WheelPos * 3;
    color.g = 0;
    color.b = WheelPos * 3;
  } 
  else {
    WheelPos -= 170;
    color.r = WheelPos * 3;
    color.g = 0;
    color.b = 255 - WheelPos * 3;
  }

  return color;
}

void rainbow(int timeDelay) {
  pixels.setBrightness(100);

  while(true)
  {
    uint16_t i, j;
  
    for(j=0; j<255; j++) {
      if(checkForNewData())
      {
        pixels.setBrightness(255);
        return;
      }
      for(i=1; i<=8; i++) {
        setLayer(3, i, colorWheel((1+j+i*8) & 255));
      }
          pixels.show();
          delay(timeDelay);
    }
  }
}

void expandingCube(RGB color, bool randomColors, int timeDelay)
{
  int cs, start;
  byte xMax, yMax, zMax;
  byte currentSize = 2;
  while(true)
  {
    if(checkForNewData())
      break;
      
    xMax = 1, yMax = 1, zMax = 1;
    cs = 4, start = 4;

      if(randomColors)
        color.randColor();
      for(byte i = 1; i <= currentSize; i++)
      {
          setDiode(i, 1, 8, color);
          setDiode(i, currentSize, 8, color);  

          setDiode(1, i, 8, color);
          setDiode(currentSize, i, 8, color); 

          setDiode(i, 1, 9-currentSize, color);
          setDiode(i, currentSize, 9-currentSize, color);  

          setDiode(1, i, 9-currentSize, color);
          setDiode(currentSize, i, 9-currentSize, color); 

          setDiode(1, 1, 9-i, color);
          setDiode(1, currentSize, 9-i, color);
          setDiode(currentSize, 1, 9-i, color);
          setDiode(currentSize, currentSize, 9-i, color);
      }

      if(currentSize==8)
        currentSize=2;
      else
        currentSize++;
        
      pixels.show();
      pixels.clear();
      delay(timeDelay);
  }
}

void randomCubeColors(int timeDelay)
{
  RGB color;
  timeDelay /= 50;
  while(true)
  {
     if(checkForNewData())
      break;
      
     color.randColor();
     setCubeColor(color);
     
     if(brightening(timeDelay))
      break;
     if(blanking(timeDelay))
      break;
  }
} 

void waving(RGB color, bool randomColors, int timeDelay)
{
  byte z[8] = {8,8,8,8,8,8,8,8};
  bool upDirection[8] = {1,1,1,1,1,1,1,1};
  byte k = 1;
  
  while(true)
  {
    if(randomColors)
      color.randColor();
    for(byte x=1; x<=8; x++)
    {
      if(checkForNewData())
       return;
      
       setColumnX(x, z[x-1], color);
       if(z[x-1] == 1 && upDirection[x-1])
        upDirection[x-1] = 0;
       else if (z[x-1] == 8 && !upDirection[x-1])
        upDirection[x-1] = 1;
        
       if(x<=k && upDirection[x-1])
        z[x-1]--;
       else if(x<=k && !upDirection[x-1])
        z[x-1]++;
    }
      if(k<8)
        k++;
        
      pixels.show();
      pixels.clear();
      delay(timeDelay);
  }
}

void multiColors(int timeDelay)
{
  RGB color;
  while(true)
  { 
    for(short i = 0; i<150; i++)
    {
      if(checkForNewData())
       return;
      color.randColor();
      pixels.setPixelColor(random(512), color.g, color.r, color.b);
      pixels.show();
      delay(timeDelay);
    }
    
    if(blanking(timeDelay/5))
      return;
    pixels.setBrightness(255);
    pixels.clear();
  }
}

class LED {
  public:
    short x=0 , y=0, z=0;
    RGB color;
};

void rain(RGB color, bool randomColors, int timeDelay)
{
  timeDelay /= 5;
  
  RGB blackColor;
  
  int totalDropsNum = 32;
  LED drop[totalDropsNum];
  int dropIndex = 0;

  while(true)
  {    
      for(int n = 0; n<dropIndex; n++)
      {
        if(checkForNewData())
          return;
        
        if(drop[n].z > 1)
         setDiode(drop[n].x, drop[n].y, drop[n].z-1, blackColor);

        if(drop[n].z > 8 || drop[n].z == 0)
        {
           drop[n].x = random(8)+1;
           drop[n].y = random(8)+1;
           drop[n].z = 1;
           if(randomColors)
            drop[n].color.randColor();
           else
            drop[n].color = color; 
        }
          
        setDiode(drop[n].x, drop[n].y, drop[n].z, drop[n].color);
        drop[n].z++;
      }
      
      pixels.show();
      
      if(dropIndex < totalDropsNum-1)
        dropIndex++;
    
    delay(timeDelay);
  }
}

void falling(RGB color, bool randomColorss, int timeDelay)
{
  RGB blackColor;
  byte emptyLayers = CS;
  
  while(true)
  {
    for(int i = 1; i<=emptyLayers; i++)
    {
      if(checkForNewData())
        return;
      
      if(randomColorss)
        color.randColor();     
      if(i>1)
        setLayer(3, i-1, blackColor);
        
        setLayer(3, i, color);
        delay(timeDelay);
        pixels.show();
    }
    
    if(emptyLayers>0)
      emptyLayers--;
    else
      emptyLayers = CS+1;
  }
}

void movingCubes(int timeDelay)
{
  RGB colors[4];
  colors[0].set(255, 0, 0);
  colors[1].set(0, 255, 0);
  colors[2].set(0, 0, 255);
  colors[3].set(255, 255, 0);

  byte freeSpace = (CS/2)+1;
  byte x=1, y=1, z=1;

  setMiniCubes(x, y, z, colors, timeDelay);
  
  while(true)
  {  
    for(y = 2; y<=freeSpace; y++)
      if(setMiniCubes(x, y, z, colors, timeDelay))
        return;
    y--;
    
    for(x = 2; x<=freeSpace; x++)
      if(setMiniCubes(x, y, z, colors, timeDelay))
        return;
    x--;
    
    for(z = 2; z<=freeSpace; z++)
      if(setMiniCubes(x, y, z, colors, timeDelay))
        return;
    z--;
    
    for(y-=1; y>0; y--)
      if(setMiniCubes(x, y, z, colors, timeDelay))
        return;
    y++;
    
    for(x-=1; x>0; x--)
      if(setMiniCubes(x, y, z, colors, timeDelay))
       return;
    x++;
  
    for(z-=1; z>0; z--)
      if(setMiniCubes(x, y, z, colors, timeDelay))
        return;
    z++;
  }
}

bool setMiniCubes(byte x, byte y, byte z, RGB colors[4], int timeDelay)
{
    if(checkForNewData())
      return true;
    drawShape(x, y, z, x+3, y+3, z+3, colors[0]);
    drawShape(CS-x-2, y, CS-z-2, CS+1-x, y+3, CS+1-z, colors[3]);
    drawShape(CS-x-2, CS-y-2, z, CS+1-x, CS+1-y, z+3, colors[1]);
    drawShape(x, CS-y-2, CS-z-2, x+3, CS+1-y, CS+1-z, colors[2]);
    pixels.show();
    pixels.clear();
    delay(timeDelay);
    return false;
}

void gradient(int timeDelay)
{
  timeDelay /= 10;
  pixels.setBrightness(100);
  while(true)
  {
    if(checkForNewData())
      return;
      
    byte time = millis() >> 2;
    
    for (uint16_t i = 0; i < LEDS_NUM; i++)
    {
      byte r = time - 2*i;
      byte g = time - 4*i;
      byte b = time - 6*i;
      pixels.setPixelColor(i, g, r, b);
    }
    pixels.show();
    delay(timeDelay);
  }
  pixels.setBrightness(255);
}

void alternatingPanels(RGB color, bool randomColors, int timeDelay)
{
  RGB c1 = color;
  RGB c2;
  
  byte panelSize = 3;
  byte freeSpace = CS - panelSize + 1;
  
  while(true)
  {      
    if(randomColors)
      c1.randColor(1);
      
    c2.r = 255 - c1.r;
    c2.g = 255 - c1.g;
    c2.b = 255 - c1.b;
          
    for(byte k = 1; k<=freeSpace; k++)
    {
        if(checkForNewData())
          return;
          
        for(byte i = 2; i<=CS; i+=2)
        {
          drawShape(k, i-1, 1, panelSize+k-1, i-1, 8, c1);
          drawShape(CS+2-panelSize-k, i, 1, CS-k+1, i, 8, c2);   
        }
        pixels.show();
        pixels.clear();
        delay(timeDelay);
    }
    c1 = c2;
  }
}
