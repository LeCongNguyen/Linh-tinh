#include <EEPROM.h>

String data = "{abcde1234567890}";

void setup()
{
  Serial.begin(115200);
  EEPROM.begin(512);
  delay(1000);

  clearEEPROM();
  saveToEEPROM(data);
  String x = readFromEEPROM();
  Serial.print(x);
}

void loop()
{
}

void clearEEPROM()
{
  int i = 512;
  while (i >= 0)
  {
    EEPROM.write(i, 0);
    i--;
  }
}

void saveToEEPROM(String newData)
{
  int size = newData.length() + 1;
  char temp[size];
  int i;
  newData.toCharArray(temp, size); // convert String to char
  for (i = 0; i < size; i++)
  {
    EEPROM.write(i, temp[i]);
  }
}

String readFromEEPROM()
{
  char savedData[512];
  int i = 0;
  while (i >= 0)
  {
    savedData[i] = EEPROM.read(i);
    if (savedData[i] == 125) // 125 là mã ASCII của ký tự '}'
    {
      break;
    }
    else
    {
      i++;
    }
  }
  //Ghép nối các phần tử của mảng char thành một chuỗi String
  String result;        
  for (i = 0; i <= 512; i++)
  {
    if (savedData[i] == 125)
    {
      result += savedData[i];
      break;
    }
    else
    {
      result += savedData[i];
    }
  }
  return result;
}