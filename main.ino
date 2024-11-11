// Definizione dei pin
const int trigPin = 2;
const int echoPin = 3;
const int led1 = 9;
const int led2 = 10;
const int led3 = 11;  // Aggiunto terzo LED
const int led4 = 6;   // Aggiunto quarto LED

// Variabili per la distanza
long duration;
int distance;

// Variabili per l'intensità dei LED
int brightness1 = 0;
int brightness2 = 0;
int brightness3 = 0;
int brightness4 = 0;
int fadeAmount = 5;  // Incremento per il fading

// Stati per il fade in/fade out dei LED
bool fadeIn1 = true;
bool fadeIn2 = true;
bool fadeIn3 = true;
bool fadeIn4 = true;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  Serial.begin(9600);
}

void fade(int &brightness, int pin, bool &fadeInState) {
  if (fadeInState) {
    brightness += fadeAmount;
    if (brightness >= 255) {
      brightness = 255;
      fadeInState = false; // Cambia lo stato per iniziare il fade out
    }
  } else {
    brightness -= fadeAmount;
    if (brightness <= 0) {
      brightness = 0;
      fadeInState = true; // Cambia lo stato per iniziare il fade in
    }
  }
  analogWrite(pin, brightness);
}

void fadeOutOnly(int &brightness, int pin) {
  if (brightness > 0) {
    brightness -= fadeAmount;
    brightness = constrain(brightness, 0, 255);
    analogWrite(pin, brightness);
  }
}

void loop() {
  // Misurazione della distanza con il sensore a ultrasuoni
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distanza: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Gestione del fading continuo per i LED in base alla distanza
  if (distance < 40) {
    fade(brightness1, led1, fadeIn1);
    fade(brightness2, led2, fadeIn2);
  } else {
    fadeOutOnly(brightness1, led1);
    fadeOutOnly(brightness2, led2);
  }

  if (distance < 20) {
    fade(brightness3, led3, fadeIn3);
    fade(brightness4, led4, fadeIn4);
  } else {
    fadeOutOnly(brightness3, led3);
    fadeOutOnly(brightness4, led4);
  }

  delay(30);  // Ritardo per stabilizzare il fading
}
