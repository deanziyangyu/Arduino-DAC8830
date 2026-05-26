#include <DAC8830.h>
#include <SPI.h>

DAC8830::DAC8830()
{
}

void DAC8830::writeDAC(uint16_t value)
{
  digitalWrite(DAC8830_CS_PIN, LOW);
  delayMicroseconds(12);
  SPI.transfer(high);
  SPI.transfer(low);
  delayMicroseconds(12);
  digitalWrite(DAC8830_CS_PIN, HIGH);
}

void DAC8830::setReference(int16_t value)
{
  DAC8830_REFERENCE_MV = value;
}

void DAC8830::setMillivolts(uint16_t value)
{
  if (DAC8830_REFERENCE_MV <= 0)
  {
    writeDAC(0);
  }
  else if (value > DAC8830_REFERENCE_MV)
  {
    writeDAC(65535);
  }
  else
  {
    float x = (65535.00 / DAC8830_REFERENCE_MV);
    writeDAC((int)(x * value));
  }
}

void DAC8830::setMillivolts10(uint16_t value)
{
  if (DAC8830_REFERENCE_MV <= 0)
  {
    writeDAC(0);
  }
  else if (value > (DAC8830_REFERENCE_MV * 10))
  {
    writeDAC(65535);
  }
  else
  {
    float x = (65535.00 / (DAC8830_REFERENCE_MV * 10));
    writeDAC((int)(x * value));
  }
}


#if defined(ESP32) || defined(ESP8266)

void DAC8830::begin(uint8_t clk_pin, uint8_t mosi_pin, uint8_t cs_pin)
{
  DAC8830_CLK_PIN = clk_pin;
  DAC8830_MOSI_PIN = mosi_pin;
  DAC8830_CS_PIN = cs_pin;
  DAC8830_REFERENCE_MV = -1;

  SPI.begin(DAC8830_CLK_PIN, NULL, DAC8830_MOSI_PIN);
  SPI.setDataMode(SPI_MODE0);

  pinMode(DAC8830_CS_PIN, OUTPUT);
  digitalWrite(DAC8830_CS_PIN, HIGH);
}

#else

void DAC8830::begin(uint8_t cs_pin)
{
  DAC8830_CLK_PIN = 0;
  DAC8830_MOSI_PIN = 0;
  DAC8830_CS_PIN = cs_pin;
  DAC8830_REFERENCE_MV = -1;

  SPI.begin();
  SPI.setDataMode(SPI_MODE0);

  pinMode(DAC8830_CS_PIN, OUTPUT);
  digitalWrite(DAC8830_CS_PIN, HIGH);
}

#endif
