#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 2

#define RED_LED 8
#define GREEN_LED 9
#define WHITE_LED 10

int redValue = 0;
int greenValue = 0;
int blueValue = 0;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(WHITE_LED, OUTPUT);

  // Set frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.begin(9600);
}

void loop() {

  // -------- READ RED --------
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  redValue = pulseIn(sensorOut, LOW);

  // -------- READ GREEN --------
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  greenValue = pulseIn(sensorOut, LOW);

  // -------- READ BLUE --------
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blueValue = pulseIn(sensorOut, LOW);

  // Print values for debugging
  Serial.print("R: "); Serial.print(redValue);
  Serial.print("  G: "); Serial.print(greenValue);
  Serial.print("  B: "); Serial.println(blueValue);

  // -------- TURN OFF ALL LEDs --------
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(WHITE_LED, LOW);

  // -------- SMART DETECTION LOGIC --------

  // No object (ambient / nothing)
  if (redValue > 400 && greenValue > 400 && blueValue > 380) {
    // Do nothing (all LEDs OFF)
  }

  // RED
  else if (redValue < 300) {
    digitalWrite(RED_LED, HIGH);
  }

  // GREEN (fixed)
  else if (greenValue < 380 && greenValue < redValue) {
    digitalWrite(GREEN_LED, HIGH);
  }

  // BLUE
  else if (blueValue < 350) {
    digitalWrite(WHITE_LED, HIGH);
  }

  delay(300);
}