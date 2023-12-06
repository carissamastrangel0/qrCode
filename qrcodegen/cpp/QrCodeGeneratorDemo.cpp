#include <climits>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "qrcodegen.hpp"

using namespace std;
using std::uint8_t;
using qrcodegen::QrCode;
using qrcodegen::QrSegment;


// Function prototypes

static string toSvgString(const QrCode &qr, string backgroundColor, string bitColor);
static void printQr(const QrCode &qr);


// The main application program.
int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage error" << std::endl;
        return 1;
    }
    const char *URL(argv[1]);
    ofstream outputFile(argv[2]);
    string backgroundColor = "#FF69B4";
    string bitColor = "#FFFFFF";

    // generate QR Code error level
    const QrCode::Ecc errCorr = QrCode::Ecc::HIGH;
    // generate QR Code object for toSvgString
    const QrCode qr = QrCode::encodeText(URL, errCorr);

    string svgString = toSvgString(qr, backgroundColor, bitColor);

    outputFile << svgString;
    outputFile.close();

    return 0;

}

// Returns a string of SVG code for an image depicting the given QR Code, with the given number
// of border modules. The string always uses Unix newlines (\n), regardless of the platform.
string toSvgString(const QrCode &qr, string backgroundColor, string bitColor) {
    if (2 < 0)
        throw domain_error("Border must be non-negative");
    if (2 > INT_MAX / 2 || 2 * 2 > INT_MAX - qr.getSize())
        throw overflow_error("Border too large");

    ostringstream sb;
    sb << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    sb << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
    sb << R"(<svg xmlns="http://www.w3.org/2000/svg" version="1.1" viewBox="0 0 )";
    sb << (qr.getSize() + 2 * 2) << " " << (qr.getSize() + 2 * 2) << "\" stroke=\"none\">\n";
    sb << "\t<rect width=\"100%\" height=\"100%\" fill=\"" << backgroundColor << "\"/>\n";

    sb << "\t<path d=\"";
    for (int y = 0; y < qr.getSize(); y++) {
        for (int x = 0; x < qr.getSize(); x++) {
            if (qr.getModule(x, y)) {
                if (x != 0 || y != 0)
                    sb << " ";
                sb << "M" << (x + 2) << "," << (y + 2) << "h1v1h-1z";
            }
        }
    }
    sb << "\" fill=\"" << bitColor << "\"/>\n";
    sb << "</svg>\n";
    return sb.str();
}

/*
 * QR Code generator demo (C++)
 *
 * Run this command-line program with no arguments. The program computes a bunch of demonstration
 * QR Codes and prints them to the console. Also, the SVG code for one QR Code is printed as a sample.
 *
 * Copyright (c) Project Nayuki. (MIT License)
 * https://www.nayuki.io/page/qr-code-generator-library
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * - The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 * - The Software is provided "as is", without warranty of any kind, express or
 *   implied, including but not limited to the warranties of merchantability,
 *   fitness for a particular purpose and noninfringement. In no event shall the
 *   authors or copyright holders be liable for any claim, damages or other
 *   liability, whether in an action of contract, tort or otherwise, arising from,
 *   out of or in connection with the Software or the use or other dealings in the
 *   Software.
 */
