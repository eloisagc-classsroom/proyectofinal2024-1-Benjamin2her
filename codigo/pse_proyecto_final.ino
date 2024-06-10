#include "DHT.h"            // Sensor de Temperatura y Humedad
#include <LiquidCrystal.h> // Pantalla LCD
#include <RTClib.h>       // Reloj a Tiempo Real
#include <Wire.h>        
#include <EEPROM.h>     // Memoria o algo así, tengo que revisar
#include "IRremote.h" //Fue necesario MODIFICAR IRTimer.hpp
#include "RemoteCodes.h" //Codigos Del Control Remoto

/* === SENSOR DE TEMPERATURA Y HUMEDAD ===*/
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int temperature;
int humidity;   
/* === CARACTERES PERSONALIZADOS (grado °)=== */
byte degreeSymbol[] = {
    B00111, 
    B00101, 
    B00111, 
    B00000, 
    B00000, 
    B00000, 
    B00000, 
    B00000
};


/* === RELOJ A TIEMPO REAL === */
RTC_DS3231 rtc;

/* === VARIABLES FECHA Y HORA === */
int H = 12, M = 0, S=0, DD = 1, MM = 1, YY = 2024;
String sDD, sMM, sYY;
String sH, sM, sS;

/* === VARIABLES ALARMA === */
int AH=12, AM=0;
String aH, aM;

/* === PANTALLA LCD 16x2 ===*/
// PINES
const int 
    rs = 12, 
    en = 11,
    d4 = 6, 
    d5 = 5, 
    d6 = 4, 
    d7 = 3;
// INICIALIZACIÓN
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//PANTALLA DE CONFIGURACION 
bool setupScreen = false;

/* === SENSOR INFRARROJO === */
const int receiver = 9;
IRrecv irrecv(receiver);
uint32_t last_decodedRawData = 0;


/* === Alarma === */
const int buzzer = 7;
bool alarmOn = false;
/* === PROTOTIPOS DE FUNCIONES === */
//FECHA Y HORA
void printDateAndTime();
void updateDateAndTime();
void getDateAndTime();

//TEMPERATURA Y HUMEDAD
void updateWeatherData();
void printWeatherData();

//Configuración Hora y Alarma
void dateAndTimeSetup();



// FUNCION SETUP SOLO SE EJECUTA UNA VEZ
void setup() {
    Serial.begin(9600);
    // RECUPERA EL VALOR DE LA HORA Y MINUTO DE ALARMA
    AH = EEPROM.read(0);
    AM = EEPROM.read(1);

    //SE ASEGURA QUE ESTE DENTRO DEL RANGO DE HORAS Y MINUTOS
    AH = (AH > 23) ? 0 : AH;
    AM = (AM > 59) ? 0 : AM;
    
    // INICIA EL RECEPTOR INFRARROJO
    irrecv.enableIRIn();

    // INICIA EL SENSOR DE TEMPERATURA Y HUMEDAD
    dht.begin();
    updateWeatherData();

    // INICIA EL RELOJ DE TIEMPO REAL
    if (!rtc.begin()) {
        // EN CASO DE NO ENCONTRARSE SE QUEDA EN UN BUCLE INFINITO
        lcd.println("Modulo RTC 3231 no encontrado!");
        while (1) {
        };
    }
    // INICIA LA PANTALLA LCD 16x2
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    
    //CREA EL CARACTER DE GRADO
    lcd.createChar(0, degreeSymbol);
    delay(1000);

}
// CICLO INFINITO
void loop() {
    // Variables estáticas para mantener el tiempo de la última actualización
    static unsigned long lastUpdateTime = 0;
    static unsigned long lastWeatherUpdateTime = 0;

    // Verifica si se ha recibido una señal del receptor IR
    if (irrecv.decode()) {
        // Comprueba cuál botón del control remoto se ha presionado
        switch (irrecv.decodedIRData.decodedRawData) {
        case ST_REPT: // Botón para cambiar la configuración
            Serial.print("Detecte func");
            setupScreen = true; // Activa la pantalla de configuración
            dateAndTimeSetup(); // Llama a la función de configuración de fecha y hora
            break;
        case POWER: // Botón para encender/apagar la alarma
            alarmOn = !alarmOn; // Cambia el estado de la alarma
            break;
        default:
            break;
        }

        // Prepara el receptor IR para la siguiente señal
        irrecv.resume();
    }

    // Obtiene el tiempo actual en milisegundos
    unsigned long currentMillis = millis();
    
    // Actualiza la hora cada segundo
    if (currentMillis - lastUpdateTime >= 1000) {
        lcd.setCursor(11, 0); // Mueve el cursor del LCD a la posición deseada

        // Verifica si la alarma está encendida
        if (alarmOn) {
            lcd.print("A"); // Muestra una "A" en el LCD si la alarma está encendida
            callAlarm(); // Llama a la función para activar la alarma
        } else {
            lcd.print(" "); // Muestra un espacio en el LCD si la alarma está apagada
        }

        lastUpdateTime = currentMillis; // Actualiza el tiempo de la última actualización
        updateDateAndTime(); // Actualiza la fecha y la hora
        printWeatherData(); // Muestra los datos meteorológicos
    }
}
