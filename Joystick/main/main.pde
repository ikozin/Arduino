import processing.serial.*;

Serial port;

void setup()
{
  rectMode(CORNERS);
  textMode(MODEL);
  size(320, 240);
}

void draw()
{
  drawSelector();
}

String[] a = { "COM1", "COM2", "COM3", "COM4", "COM5" }; 
int borderSize = 2;
int margin = 10;
int textHeight = 16;
void drawSelector()
{
  StringList selectList = new StringList();
  int index = 0;
  for (String name : a)//Serial.list())
  {
    if (index > 9) break;
    selectList.append(String.format("%s: %s", index++, name));
  }
  printArray(selectList);
  stroke(0);
  fill(0);
  textSize(textHeight);
  int x = margin; 
  int y = margin + textHeight;
  for (String item : selectList)
  {
    text(item, x, y);
    y += (margin >> 1) + textHeight;
  }
}
