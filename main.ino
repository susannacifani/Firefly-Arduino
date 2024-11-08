// Definizione dei pin
const int trigPin = 2;
const int echoPin = 3;
const int led1 = 9;
const int led2 = 10;
const int led3 = 11;


// Variabile per la distanza
long duration;
int distance;

// Variabile per l'intensità dei LED
int brightness = 0;
int fadeAmount = 15;  // Step di variazione della luminosità

void setup() {
  // Impostazione dei pin
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  // Avvio della comunicazione seriale per debugging
  Serial.begin(9600);
}

void loop() {
  // Invio del segnale dal pin trig
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Lettura del segnale in arrivo sul pin echo
  duration = pulseIn(echoPin, HIGH);
  
  // Calcolo della distanza in cm
  distance = duration * 0.034 / 2;

  // Stampa della distanza sul monitor seriale
  Serial.print("Distanza: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Accensione graduale dei LED se la distanza è inferiore a 20 cm
  if (distance < 20) {
    // Aumenta la luminosità gradualmente fino a 255
    brightness = min(brightness + fadeAmount, 255);
  } else {
    // Diminuisci la luminosità gradualmente fino a 0
    brightness = max(brightness - fadeAmount, 0);
  }

  // Imposta la luminosità per ogni LED
  analogWrite(led1, brightness);
  analogWrite(led2, brightness);
  analogWrite(led3, brightness);


  // Pausa breve per un fading graduale e evitare letture troppo frequenti
  delay(30);
}
