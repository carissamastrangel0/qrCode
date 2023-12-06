#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "include/qrcodegen.hpp"

using namespace std;
using std::uint8_t;
using qrcodegen::QrCode;
using qrcodegen::QrSegment;

// Function prototypes
static string toSvgString(const QrCode &qr, string backgroundColor, string bitColor);

int main(int argc, char *argv[]) {
    if (argc < 5) {
        cerr << "Usage: " << argv[0] << " <URL> <Output File> <Background Color> <Bit Color>" << endl;
        return 1;
    }

    const char *URL = argv[1];

    // Check if output file can be opened
    ofstream outputFile(argv[2]);
    if (!outputFile) {
        cerr << "Error: Cannot open file " << argv[2] << endl;
        return 1;
    }

    string backgroundColor = argv[3];
    string bitColor = argv[4];

    try {
        const QrCode::Ecc errCorr = QrCode::Ecc::HIGH;
        const QrCode qr = QrCode::encodeText(URL, errCorr);

        string svgString = toSvgString(qr, backgroundColor, bitColor);
        outputFile << svgString;
    } catch (const std::exception &e) {
        cerr << "Error occurred: " << e.what() << endl;
        outputFile.close();
        return 1;
    }

    outputFile.close();
    return 0;
}

string toSvgString(const QrCode &qr, string backgroundColor, string bitColor) {
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
