#include <OLEDDisplay.h>
#include "qrcodegen.h"

// https://www.qrcode.com/en/about/version.html QR version overview
#define QRENCODE_VERSION_MIN (1)
#define QRENCODE_VERSION_MAX (7) // should work up to 11 (61 x 61)

int resolution = 0;
int maxScale = 1;
uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];

bool QRGen(OLEDDisplay *display, char* message) {

    // Make and print the QR Code symbol

    bool rc = qrcodegen_encodeText(message, tempBuffer, qrcode, qrcodegen_Ecc_LOW,
            qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
    if(rc) {
        resolution = qrcodegen_getSize(qrcode);
        while((maxScale + 1) * resolution < display->height()) {
            maxScale++;
        }
    }
    return rc;
}

void QRRender(OLEDDisplay *display, int x, int y){
    int renderResolution = resolution * maxScale;
    int offsetX = x + (display->height() - renderResolution) / 2;
    int offsetY = y + (display->height() - renderResolution) / 2;

    display->fillRect(offsetX - 2, offsetY - 2, renderResolution + 4, renderResolution + 4);

    // draw QR Code
    for (char x = 0; x < renderResolution; x++) {
        for (char y = 0; y < renderResolution; y++) {
            display->setPixelColor(offsetX + x, offsetY + y, qrcodegen_getModule(qrcode, x / maxScale, y / maxScale) ? BLACK : WHITE);
        }
    }
}
