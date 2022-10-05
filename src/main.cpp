
#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Adafruit_AW9523.h>

byte hello[] = {0x04, 0x62, 0x98, 0x02, 0x19, 0x6C, 0x80, 0x00, 0x00, 0x00};

MFRC522 mfrc522(10, 9);

byte lastUid[10];

Adafruit_AW9523 aw;

#define LED_PIN_START 1
#define LED_PIN_COUNT 8
uint8_t led_pins[] = {1, 2, 3, 4, 5, 6, 7, 12};
uint8_t led_pin_index = LED_PIN_START;

void printUuid(byte uuid[])
{
  for (int i = 0; i < 10; i++)
  {
    Serial.print(uuid[i], HEX);
    Serial.print(" ");
  }
  Serial.println("");
}

bool uidEqual(byte left[], byte right[])
{
  for (int i = 0; i < 10; i++)
  {
    if (left[i] != right[i])
    {
      return false;
    }
  }
  return true;
}

void copyUid(byte from[], byte to[])
{
  for (int i = 0; i < 10; i++)
  {
    to[i] = from[i];
  }
}

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    delay(1); // wait for serial port to open

  Serial.println("beginning");

  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("rfc works");

  // LED Driver stuff
  if (!aw.begin(0x58))
  {
    Serial.println("AW9523 not found? Check wiring!");
    //    while (1) delay(10);  // halt forever
  }
  Serial.println("aw works");

  Serial.println("AW9523 found!");

  for (int i = 0; i <= LED_PIN_COUNT; i++)
  {
    aw.pinMode(led_pins[i], AW9523_LED_MODE); // set to constant current drive!
  }

  for (int i = 0; i <= LED_PIN_COUNT; i++)
  {
    Serial.print("Turning on light at index ");
    Serial.print(i, DEC);
    Serial.print(": ");
    Serial.println(led_pins[i], DEC);
    aw.analogWrite(led_pins[i], 255);
    delay(1000);
    aw.analogWrite(led_pins[i], 0);
  }

  // RFID scanner
  pinMode(7, OUTPUT);

  Serial.println("setup");
}

void loop()
{
  if (!Serial)
  {
    return;
  }
  // Serial.println("loop");

  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  Serial.println("new card present");

  if (!mfrc522.PICC_ReadCardSerial())
  { // Since a PICC placed get Serial and continue
    return;
  }

  if (uidEqual(mfrc522.uid.uidByte, lastUid))
  {
    return;
  }

  Serial.println("new serial read");
  copyUid(mfrc522.uid.uidByte, lastUid);
  mfrc522.PICC_DumpToSerial(&mfrc522.uid);

  printUuid(mfrc522.uid.uidByte);
  printUuid(lastUid);

  if (uidEqual(lastUid, hello))
  {
    Serial.println("Hello!");
    //    digitalWrite(7, HIGH);
    // Loop from 0 to 255 and then wrap around to 0 again
    Serial.print("Turning on light at index");
    Serial.print(led_pin_index, DEC);
    Serial.print(": ");
    Serial.println(led_pins[led_pin_index], DEC);
    aw.analogWrite(led_pins[++led_pin_index], 255);
    if (led_pin_index >= LED_PIN_COUNT)
    {
      led_pin_index = LED_PIN_START;
    }
  }
  else
  {
    //    digitalWrite(7, LOW);
    aw.analogWrite(led_pins[led_pin_index], 0);
  }
}