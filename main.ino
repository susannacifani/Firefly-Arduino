// Definizione dei pin
const int trigPin = 2;
const int echoPin = 3;
const int led1 = 9;
const int led2 = 10;

// Variabili per la distanza
long duration;
int distance;

// Variabili per l'intensità dei LED
int brightness1 = 0;
int brightness2 = 0;
int fadeAmount1 = 5;  // Step di variazione della luminosità
int fadeAmount2 = 5;

void setup() {
  // Impostazione dei pin
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

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
    // Aumenta la luminosità gradualmente fino a 255, poi diminuisci
    brightness1 += fadeAmount1;
    brightness2 += fadeAmount2;

    // Inverte la direzione del fading se si raggiunge il limite
    if (brightness1 <= 0 || brightness1 >= 255) {
      fadeAmount1 = -fadeAmount1;
    }
    if (brightness2 <= 0 || brightness2 >= 255) {
      fadeAmount2 = -fadeAmount2;
    }
  } else {
    // Se la distanza non è inferiore a 20 cm, spegni i LED
    brightness1 = 0;
    brightness2 = 0;
  }

  // Imposta la luminosità per ogni LED
  analogWrite(led1, brightness1);
  analogWrite(led2, brightness2);

  // Pausa breve per un fading graduale e evitare letture troppo frequenti
  delay(30);
}
