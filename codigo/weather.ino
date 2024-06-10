/*
PROTOTIPOS
void updateWeatherData();
void printWeatherData();
*/

// ACTUALIZA LOS VALORES DE TEMPERATURA Y HUMEDAD EN EL SENSOR DHT11
void updateWeatherData() {
    temperature = dht.readTemperature(); // Read temperature in *C (default)
    humidity = dht.readHumidity();    // Read humidity %
}

// IMPRIME LOS VALORES DE TEMPERATURA Y HUMEDAD EN LA PANTALLA LCD 16x2
void printWeatherData() {
    // IMPRIMIR TEMPERATURA: e.g: 28°C
    lcd.setCursor(12, 0);
    lcd.print(temperature);
    lcd.setCursor(14, 0);
    lcd.write(byte(0));
    lcd.print("C");
    // IMPRIMIR PORCENTAJE DE HUMEDAD
    lcd.setCursor(12, 1);
    lcd.print(humidity);
    lcd.print(" %");
}
