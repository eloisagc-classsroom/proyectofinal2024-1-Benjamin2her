/*
FUNCIONES
void printDateAndTime();
void getDateAndTime();
void updateDateAndTime()
*/
void printDateAndTime() {
    // Imprimir la hora en formato HH:MM:SS
    lcd.setCursor(0, 0);
    lcd.print("  ");
    lcd.print(sH);
    lcd.print(":");
    lcd.print(sM);
    lcd.print(":");
    lcd.print(sS);

    // Imprimir la fecha en formato DD/MM/YYYY
    lcd.setCursor(0, 1);
    lcd.print("  ");
    lcd.print(sDD);
    lcd.print("/");
    lcd.print(sMM);
    lcd.print("/");
    lcd.print(sYY);
}

//Si no se está configurando la hora, actualizar los valores de la Fecha y hora
void getDateAndTime(){

  if (!setupScreen){

    DateTime now = rtc.now();
    DD = now.day();
    MM = now.month();
    YY = now.year();

    H = now.hour();
    M = now.minute();
    S = now.second();
 }
 //Actualizar las cadenas de Fecha y hora
    if (DD<10){ sDD = '0' + String(DD); } else { sDD = DD; }
    if (MM<10){ sMM = '0' + String(MM); } else { sMM = MM; }
    sYY=YY-2000;
    if (H<10){ sH = '0' + String(H); } else { sH = H; }
    if (M<10){ sM = '0' + String(M); } else { sM = M; }
    if (S<10){ sS = '0' + String(S); } else { sS = S; }
    if (AH<10){ aH = '0' + String(AH); } else { aH = AH; }
    if (AM<10){ aM = '0' + String(AM); }  else { aM = AM; }

}

void updateDateAndTime(){
    getDateAndTime();
    printDateAndTime();
}