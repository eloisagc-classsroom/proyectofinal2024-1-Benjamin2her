void dateAndTimeSetup(){
    // Bandera para salir del bucle
    bool salir = false;

    // Banderas para los botones de aumentar y disminuir
    bool upButton = false;
    bool downButton = false;

    // Contador para las opciones de configuración
    int btnCount = 1;

    // Enumeración de las opciones de configuración
    enum opciones {
        SetHour = 1, SetMinute, SetDay, SetMonth, SetYear, SetAlarmHour, SetAlarmMinute, SaveAndQuit
    };

    // Lambda function para actualizar valores con retardo
    auto updateAndDelay = [&](int &timeValue, int maxVal, int minVal) {
        // Si se presionó el botón de aumentar
        if (upButton == true) {
            // Incrementa el valor, volviendo al mínimo si se supera el máximo
            timeValue = (timeValue < maxVal) ? timeValue + 1 : minVal;
            delay(250);
        }
        // Si se presionó el botón de disminuir
        if (downButton == true) {
            // Decrementa el valor, volviendo al máximo si se baja del mínimo
            timeValue = (timeValue > minVal) ? timeValue - 1 : maxVal;
            delay(250);
        }
        // Restablece las banderas de los botones
        upButton = false;
        downButton = false;
    };

    // Bucle principal para la configuración
    while (!salir) {
        // Comprueba si se ha recibido una señal del receptor IR
        if (irrecv.decode()) {
            Serial.println("SETUP> tecla: ");
            Serial.println(irrecv.decodedIRData.decodedRawData, HEX);
            switch (irrecv.decodedIRData.decodedRawData) {
            case VOL_PLUS:
                upButton = true;
                downButton = false;
                break;
            case VOL_MINUS:
                downButton = true;
                upButton = false;
                break;
            case FAST_FORWARD:
                btnCount = (btnCount < SaveAndQuit) ? btnCount + 1 : btnCount;
                break;
            case FAST_BACK:
                btnCount = (btnCount > SetHour) ? btnCount - 1 : btnCount;
                break;
            default:
                upButton = false;
                downButton = false;
                break;
            }
            // Prepara el receptor IR para la siguiente señal
            irrecv.resume();
        }

        // Gestiona las opciones de configuración según el valor de btnCount
        switch (btnCount) {
            case SetHour:
                lcd.setCursor(3, 0);
                lcd.print("_");
                delay(50);
                updateAndDelay(H, 23, 0);
                updateDateAndTime();
                break;

            case SetMinute:
                lcd.setCursor(6, 0);
                lcd.print("_");
                delay(50);
                updateAndDelay(M, 59, 0);
                updateDateAndTime();
                break;

            case SetDay:
                lcd.setCursor(3, 1);
                lcd.print("_");
                delay(50);
                updateAndDelay(DD, 31, 1);
                updateDateAndTime();
                break;

            case SetMonth:
                lcd.setCursor(6, 1);
                lcd.print("_");
                delay(50);
                updateAndDelay(MM, 12, 1);
                updateDateAndTime();
                break;

            case SetYear:
                lcd.setCursor(9, 1);
                lcd.print("_");
                delay(50);
                updateAndDelay(YY, 2999, 2000);
                updateDateAndTime();
                break;

            case SetAlarmHour:
                lcd.setCursor(0, 0);
                lcd.print("SET ALARM ");
                delay(50);
                updateAndDelay(AH, 23, 0);
                getDateAndTime();
                lcd.setCursor(3, 1);
                lcd.print("_");
                delay(100);
                lcd.setCursor(2, 1);
                lcd.print(aH);
                lcd.print(":");
                lcd.print(aM);
                lcd.print("   ");
                break;

            case SetAlarmMinute:
                lcd.setCursor(0, 0);
                lcd.print("SET ALARM");
                delay(50);
                updateAndDelay(AM, 59, 0);
                getDateAndTime();
                lcd.setCursor(6, 1);
                lcd.print("_");
                delay(100);
                lcd.setCursor(2, 1);
                lcd.print(aH);
                lcd.print(":");
                lcd.print(aM);
                lcd.print("   ");
                break;

            case SaveAndQuit:
                // Ajusta el RTC con los valores actuales
                rtc.adjust(DateTime(YY, MM, DD, H, M, S));
                setupScreen = false;
                salir = true;
                // Guarda la hora de la alarma en la EEPROM
                EEPROM.write(0, AH);
                EEPROM.write(1, AM);
                break;

            default:
                break;
        }
        delay(50);
    }
}
