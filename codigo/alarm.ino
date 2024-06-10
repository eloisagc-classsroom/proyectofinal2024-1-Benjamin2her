// Frecuencias de las notas para la melodía
int melody[] = {600, 800, 1000, 1200};

// Índice para recorrer la melodía
int i = 0;

// Intervalo de tiempo entre cambios de notas (en milisegundos)
long interval = 300;

// Bandera para indicar si la alarma debe sonar
bool turnItOn = false;

// Tiempo de referencia para controlar el intervalo
unsigned long previousMillis = 0;

// Estado de la alarma (no se usa en este fragmento)
bool alarm_state = false;

void callAlarm() {
    // Comprueba si es el momento de activar la alarma
    if (aM == sM && aH == sH && S >= 0 && S <= 10) {
        turnItOn = true;
    } else if (S >= 20) {
        turnItOn = false;
        alarmOn = true;
        delay(50);
    }

    // Si la alarma debe sonar
    if (turnItOn) {
        // Obtiene el tiempo actual en milisegundos
        unsigned long currentMillis = millis();

        // Comprueba si ha pasado el intervalo de tiempo definido
        if (currentMillis - previousMillis > interval) {
            // Actualiza el tiempo de referencia
            previousMillis = currentMillis;

            // Emite la nota actual de la melodía
            tone(buzzer, melody[i], 100);

            // Pasa a la siguiente nota
            i++;
            if (i > 3) {
                // Reinicia el índice si ha alcanzado el final de la melodía
                i = 0;
            }

            // Imprime en el monitor serie
            Serial.println("00000");
        }
    } else {
        // Si la alarma no debe sonar, se apaga el buzzer
        noTone(buzzer);
    }
}
