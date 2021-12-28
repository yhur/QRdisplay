#include <SSD1306.h>
#include <qrdisplay.h>
SSD1306  display(0x3c, 4, 5);

void setup() {
    display.init();
    display.clear();

    //char msg[] = "WIFI:S:IoT518;T:WEP;P:password;;";
    //char msg[] = "WIFI:S:YourAP;;;;";
    char msg[] = "https://google.com/";
 
    QRGen(&display, msg);

    QRRender(&display, 1, 1);
    display.display();
}

void loop() {

}
