String getParam(String paramName);
void checkData();
bool checkForNewData();
void displayText(String text, int timeDelay, RGB color);
void displayChar(bool SELECTED_CHAR[CS][CS], int timeDelay);
void selectAndDisplayChar(char selectedChar, int timeDelay);
void updateDiode(int x, int y, int z, RGB color);
void updateLayer(short axis, short layer, RGB color);
void updateCube(RGB color);

bool checkForNewData()
{
   if (Serial.available() > 0) 
   {
      data = Serial.readString();
      newDataAvailable = true;
      return true;
   }
   return false;
}

void checkData()
{
  pixels.setBrightness(255);
  pixels.clear();
  pixels.show();
  
  newDataAvailable = false;
  String command = getParam("command");
  
  long hexColor = getParam("color").toInt();
  RGB color;
  color.r = hexColor >> 16;
  color.g = (hexColor & 0x00ff00) >> 8;
  color.b = (hexColor & 0x0000ff);
  
  if(command == "text")
    displayText(getParam("text"), getParam("delay").toInt(), color);
  else if(command == "cube_color")
    updateCube(color);
  else if(command == "layer_color")
    updateLayer(getParam("axis").toInt(), getParam("layer").toInt(), color);
  else if(command == "diode_color")
    updateDiode(getParam("x").toInt(), getParam("y").toInt(), getParam("z").toInt(), color);
  else if(command == "rainbow")
    rainbow(getParam("delay").toInt());
  else if(command == "expanding_cube")
    expandingCube(color, getParam("randomColors").toInt(), getParam("delay").toInt());
  else if(command == "random_cube_colors")
    randomCubeColors(getParam("delay").toInt());
  else if(command == "waving")
    waving(color, getParam("randomColors").toInt(), getParam("delay").toInt());
  else if(command == "multi_colors")
    multiColors(getParam("delay").toInt());
  else if(command == "rain")
    rain(color, getParam("randomColors").toInt(), getParam("delay").toInt());
  else if(command == "falling")
    falling(color, getParam("randomColors").toInt(), getParam("delay").toInt());
  else if(command == "moving_cubes")
    movingCubes(getParam("delay").toInt());
  else if(command == "gradient")
    gradient(getParam("delay").toInt());
  else if(command.equals("moving_panels") )
    alternatingPanels(color, getParam("randomColors").toInt(), getParam("delay").toInt());
}

String getParam(String paramName)
{
  int indexOfParam = data.indexOf(paramName + "=");
  if(indexOfParam == -1)
    return "";
  indexOfParam += paramName.length()+1;
  
  int endIndexOfParam = data.indexOf("&", indexOfParam);
  if(endIndexOfParam == -1)
    endIndexOfParam = data.length();

     return data.substring(indexOfParam, endIndexOfParam);
}
