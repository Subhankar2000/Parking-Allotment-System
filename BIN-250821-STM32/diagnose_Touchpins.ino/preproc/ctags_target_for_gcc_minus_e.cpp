# 1 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_741966\\diagnose_Touchpins.ino"
# 1 "C:\\Users\\SUBHAN~2\\AppData\\Local\\Temp\\arduino_modified_sketch_741966\\diagnose_Touchpins.ino"
HardwareSerial Serial6(36, 37);
void showpins(int A, int D, int value, const char *msg)
{
    Serial6.print(msg);
    Serial6.print(" (A" + String(A - A0) + ", D" + String(D) + ") = ");
    Serial6.println(value);
}
void setup()
{
    int i, j, value, Apins[2], Dpins[2], Values[2], found = 0;
    Serial6.begin(9600);
    Serial6.println("Making all control and bus pins INPUT_PULLUP");
    Serial6.println("Typical 30k Analog pullup with corresponding pin");
    Serial6.println("would read low when digital is written LOW");
    Serial6.println("e.g. reads ~25 for 300R X direction");
    Serial6.println("e.g. reads ~30 for 500R Y direction");
    Serial6.println("");
    for (i = A0; i < A5; i++) pinMode(i, 0x2);
    for (i = 2; i < 10; i++) pinMode(i, 0x2);
    for (i = A0; i < A4; i++) {
        for (j = 5; j < 10; j++) {
            pinMode(j, 0x1);
            digitalWrite(j, 0x0);
            value = analogRead(i); // ignore first reading
            value = analogRead(i);
            if (value < 100) {
                showpins(i, j, value, "Testing :");
                if (found < 2) {
                    Apins[found] = i;
                    Dpins[found] = j;
                    Values[found] = value;
                    found++;
                }
            }
            pinMode(j, 0x2);
        }
    }
    if (found == 2) {
        Serial6.println("Diagnosing as:-");
        for (i = 0; i < 2; i++) {
            showpins(Apins[i], Dpins[i], Values[i], (Values[i] < Values[!i]) ? "XM,XP: " : "YP,YM: ");
        }
    }
}

void loop()
{
    // put your main code here, to run repeatedly:

}
