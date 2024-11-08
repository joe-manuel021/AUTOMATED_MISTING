//RTC
DateTime relayOnTime;
DateTime relayOffTime;

bool timer=true;
TimeSpan relayOnDuration;
long totalSeconds;

// Rotary Encoder Inputs
#define CLK 17
#define DT 16
#define SW 19

int counter = 0;
int currentStateCLK = 0;
int lastStateCLK;
String currentDir = "";
unsigned long lastButtonPress = 1;
bool buttonState = 1;
uint32_t lcdMillis = 0;

char positionedArray1[21] = {"                    "};
char positionedArray2[21] = {"                    "};
char positionedArray3[21] = {"                    "};
char positionedArray4[21] = {"                    "};
String compiledString;

String subText;
byte subTextPosition = 0;
byte textLastPosition = 0;

float selection = 1;

#define MAIN 1
#define SELECTION 2
#define THRESHOLD 3

#define RESET 4
bool refreshLCD = 1;
byte selectionPage = 1;
bool adjustThresholdState1 = 0;
bool adjustThresholdState2 = 0;

float resetSelector = 3;
float dht_Threshold_Upper = 37.5;
float dht_Threshold_Lower = 40.5;
#define TRUE 1
#define FALSE 0

float temp1;
float hum1;
float temp2;
float hum2;
float temp3;
float hum3;
float temp4;
float hum4;

float avgTemp = 0;
float avgHum = 0;

// Define the pins for the DHT22 sensors
#define DHTPIN1 14
#define DHTPIN2 27
#define DHTPIN3 26
#define DHTPIN4 25

// Define the pin for the relay
#define RELAY_PIN 32

String pumpState="OFF";
