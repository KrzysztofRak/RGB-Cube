void updateDiode(int x, int y, int z, RGB color);
void updateLayer(short axis, short layer, RGB color);
void updateCube(RGB color);

void updateDiode(int x, int y, int z, RGB color)
{
  setDiode(x, y, z, color);
  pixels.show();
}

void updateLayer(short axis, short layer, RGB color)
{
  setLayer(axis, layer, color);
  pixels.show();
}

void updateCube(RGB color)
{
  setCubeColor(color);
  pixels.show();
}
