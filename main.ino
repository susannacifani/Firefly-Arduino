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
int brightness3 = 0;  // Luminosità per il terzo LED
int brightness4 = 0;  // Luminosità per il quarto LED
int fadeAmount1 = 5;  // Step di variazione della luminosità
int fadeAmount2 = 5;
int fadeAmount3 = 5;  // Step di variazione per il terzo LED
int fadeAmount4 = 5;  // Step di variazione per il quarto LED

// Variabile per gestire il ritardo tra i LED
bool led1Acceso = false;
unsigned long tempoLed1Acceso = 0;
const int ritardoLed2 = 600;  // Ritardo di 600 ms per accendere il secondo LED

void setup() {
  // Impostazione dei pin
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);  // Impostazione del terzo LED
  pinMode(led4, OUTPUT);  // Impostazione del quarto LED

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

  // Accensione graduale dei LED se la distanza è inferiore a 40 cm
  if (distance < 40) {
    // Aumenta la luminosità gradualmente fino a 255, poi diminuisci per led1
    brightness1 += fadeAmount1;

    // Inverte la direzione del fading se si raggiunge il limite per led1
    if (brightness1 <= 0 || brightness1 >= 255) {
      fadeAmount1 = -fadeAmount1;
    }

    // Salva il tempo in cui led1 ha iniziato ad accendersi
    if (!led1Acceso) {
      tempoLed1Acceso = millis();
      led1Acceso = true;
    }

    // Aumenta la luminosità di led2 solo dopo un ritardo specifico
    if (millis() - tempoLed1Acceso >= ritardoLed2) {
      brightness2 += fadeAmount2;

      // Inverte la direzione del fading se si raggiunge il limite per led2
      if (brightness2 <= 0 || brightness2 >= 255) {
        fadeAmount2 = -fadeAmount2;
      }
    }

    // Accensione e fading del terzo LED se la distanza è inferiore a 20 cm
    if (distance < 20) {
      brightness3 += fadeAmount3;

      // Inverte la direzione del fading se si raggiunge il limite per led3
      if (brightness3 <= 0 || brightness3 >= 255) {
        fadeAmount3 = -fadeAmount3;
      }

      // Accensione e fading del quarto LED
      brightness4 += fadeAmount4;

      // Inverte la direzione del fading se si raggiunge il limite per led4
      if (brightness4 <= 0 || brightness4 >= 255) {
        fadeAmount4 = -fadeAmount4;
      }
    } else {
      // Se la distanza è maggiore di 20 cm, spegni gradualmente il terzo e quarto LED
      if (brightness3 > 0) {
        brightness3 -= fadeAmount3;
        if (brightness3 < 0) {
          brightness3 = 0;
        }
      }

      if (brightness4 > 0) {
        brightness4 -= fadeAmount4;
        if (brightness4 < 0) {
          brightness4 = 0;
        }
      }
    }
  } else {
    // Se la distanza non è inferiore a 40 cm, spegni gradualmente tutti i LED
    if (brightness1 > 0) {
      brightness1 -= abs(fadeAmount1);
      if (brightness1 < 0) {
        brightness1 = 0;
      }
    }

    if (brightness2 > 0) {
      brightness2 -= abs(fadeAmount2);
      if (brightness2 < 0) {
        brightness2 = 0;
      }
    }

    if (brightness3 > 0) {
      brightness3 -= abs(fadeAmount3);
      if (brightness3 < 0) {
        brightness3 = 0;
      }
    }

    if (brightness4 > 0) {
      brightness4 -= abs(fadeAmount4);
      if (brightness4 < 0) {
        brightness4 = 0;
      }
    }

    led1Acceso = false; // Resetta lo stato per la prossima accensione
  }

  // Imposta la luminosità per ogni LED
  analogWrite(led1, brightness1);
  analogWrite(led2, brightness2);
  analogWrite(led3, brightness3);
  analogWrite(led4, brightness4);

  // Pausa breve per un fading graduale e evitare letture troppo frequenti
  delay(30);
}
