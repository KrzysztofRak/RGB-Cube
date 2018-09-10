void setDiode(int x, int y, int z, RGB color)
{
  int index = (8-z)*64; // Z axis selection

  if(z%2==0) // X axis selection
     index += (x-1)*8;
  else
     index += (8-x)*8;

  if((x%2==0 && z%2==0) || (x%2!=0 && z%2!=0)) // Y axis selection
      index += (y-1);   
  else
      index += (8-y);
      
  pixels.setPixelColor(index, color.g, color.r, color.b);
}

void setCubeColor(RGB color)
{
  for(short i = 0; i<LEDS_NUM; i++)
    pixels.setPixelColor(i, color.g, color.r, color.b);
} 

void setColumnX(int x, int z, RGB color)
{
  for(int y = 1; y<=CS; y++)
    setDiode(x, y, z, color);
}

void setColumnY(int y, int z, RGB color)
{
  for(int x = 1; x<=CS; x++)
    setDiode(x, y, z, color);
}

void setColumnZ(int x, int y, RGB color)
{
  for(int z = 1; z<=CS; z++)
    setDiode(x, y, z, color);
}

void setLayer(short axis, short layer, RGB color)
{
  if(axis==1) // X LAYER
  {
    for(int y = 1; y<=CS; y++)
     for(int z = 1; z<=CS; z++)
        setDiode(layer, y, z, color);
  }
  else if(axis==2) // Y LAYER
  {
    for(int x = 1; x<=CS; x++)
      for(int z = 1; z<=CS; z++)
        setDiode(x, layer, z, color);
  }
  else if(axis==3) // Z LAYER
  {
    for(int x = 1; x<=CS; x++)
      for(int y = 1; y<=CS; y++)
        setDiode(x, y, layer, color);
  }
}

void drawShape(byte x1, byte y1, byte z1, byte x2, byte y2, byte z2, RGB color)
{
  for(byte x=x1; x<=x2; x++)
      for(byte y=y1; y<=y2; y++)
        for(byte z=z1; z<=z2; z++)
          setDiode(x, y, z, color);
}

