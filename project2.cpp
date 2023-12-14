#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

struct Image
{
    struct Header
    {
        char idLength;
        char colorMapType;
        char dataTypeCode;
        short colorMapOrigin;
        short colorMapLength;
        char colorMapDepth;
        short xOrigin;
        short yOrigin;
        short width;
        short height;
        char bitsPerPixel;
        char imageDescriptor;
    };
    struct Pixel
    {
        unsigned char blue = 0;
        unsigned char green = 0;
        unsigned char red = 0;
    };

    Header header;
    vector<Pixel> pixels;
    Image(){};
    // overloaded constructor that allows constructing an image from rgb channels of other images
    Image(Image &red, Image &green, Image &blue)
    {

        // sizes need to match
        if (red.pixels.size() == green.pixels.size() && green.pixels.size() == blue.pixels.size())
        {

            // copy header
            header = red.header;

            // set the color channels accordingly
            for (auto i = 0; i < red.pixels.size(); i++)
            {
                Pixel newPixel;
                newPixel.blue = blue.pixels[i].blue;
                newPixel.green = green.pixels[i].green;
                newPixel.red = red.pixels[i].red;
                pixels.push_back(newPixel);
            }
        }
    }
};
void readImage(string fileName, Image &x)
{
    x.pixels.clear();
    // Reading header
    ifstream file(fileName, ios_base::binary);
    if (!file.is_open())
    {
        throw invalid_argument("File does not exist");
    }
    else
    {
        file.read((char *)&x.header.idLength, 1);
        file.read((char *)&x.header.colorMapType, 1);
        file.read((char *)&x.header.dataTypeCode, 1);
        file.read((char *)&x.header.colorMapOrigin, 2);
        file.read((char *)&x.header.colorMapLength, 2);
        file.read((char *)&x.header.colorMapDepth, 1);
        file.read((char *)&x.header.xOrigin, 2);
        file.read((char *)&x.header.yOrigin, 2);
        file.read((char *)&x.header.width, 2);
        file.read((char *)&x.header.height, 2);
        file.read((char *)&x.header.bitsPerPixel, 1);
        file.read((char *)&x.header.imageDescriptor, 1);
        // Reading pixels
        for (int i = 0; i < (x.header.height * x.header.width); i++)
        {
            unsigned char blue = 0;
            unsigned char green = 0;
            unsigned char red = 0;
            file.read((char *)&blue, sizeof(blue));
            file.read((char *)&green, sizeof(green));
            file.read((char *)&red, sizeof(red));

            Image::Pixel temp;
            temp.blue = blue;
            temp.green = green;
            temp.red = red;

            x.pixels.push_back(temp);
        }
    }
}
void writeImage(string fileName, Image &x)
{
    ofstream file(fileName, ios_base::binary);
    file.write((char *)&x.header.idLength, 1);
    file.write((char *)&x.header.colorMapType, 1);
    file.write((char *)&x.header.dataTypeCode, 1);
    file.write((char *)&x.header.colorMapOrigin, 2);
    file.write((char *)&x.header.colorMapLength, 2);
    file.write((char *)&x.header.colorMapDepth, 1);
    file.write((char *)&x.header.xOrigin, 2);
    file.write((char *)&x.header.yOrigin, 2);
    file.write((char *)&x.header.width, 2);
    file.write((char *)&x.header.height, 2);
    file.write((char *)&x.header.bitsPerPixel, 1);
    file.write((char *)&x.header.imageDescriptor, 1);
    // Reading pixels
    for (int i = 0; i < (x.header.height * x.header.width); i++)
    {
        file.write((char *)&x.pixels.at(i).blue, sizeof(x.pixels.at(i).blue));
        file.write((char *)&x.pixels.at(i).green, sizeof(x.pixels.at(i).green));
        file.write((char *)&x.pixels.at(i).red, sizeof(x.pixels.at(i).red));
    }
}
Image addition(Image &one, Image &two)
{
    Image three;
    for (int i = 0; i < one.pixels.size(); i++)
    {
        unsigned int blue = 0;
        unsigned int green = 0;
        unsigned int red = 0;
        if (one.pixels.at(i).blue + two.pixels.at(i).blue < 255)
        {
            blue = one.pixels.at(i).blue + two.pixels.at(i).blue;
        }
        else
        {
            blue = 255;
        }
        if (one.pixels.at(i).green + two.pixels.at(i).green < 255)
        {
            green = one.pixels.at(i).green + two.pixels.at(i).green;
        }
        else
        {
            green = 255;
        }
        if (one.pixels.at(i).red + two.pixels.at(i).red < 255)
        {
            red = one.pixels.at(i).red + two.pixels.at(i).red;
        }
        else
        {
            red = 255;
        }
        Image::Pixel add;
        add.blue = blue;
        add.green = green;
        add.red = red;
        three.pixels.push_back(add);
    }
    three.header.idLength = one.header.idLength;
    three.header.colorMapType = one.header.colorMapType;
    three.header.dataTypeCode = one.header.dataTypeCode;
    three.header.colorMapOrigin = one.header.colorMapOrigin;
    three.header.colorMapLength = one.header.colorMapLength;
    three.header.xOrigin = one.header.xOrigin;
    three.header.yOrigin = one.header.yOrigin;
    three.header.width = one.header.width;
    three.header.height = one.header.height;
    three.header.bitsPerPixel = one.header.bitsPerPixel;
    three.header.imageDescriptor = one.header.imageDescriptor;
    return three;
}
Image subtraction(Image &one, Image &two)
{
    Image three;
    for (int i = 0; i < one.pixels.size(); i++)
    {
        unsigned int blue = 0;
        unsigned int green = 0;
        unsigned int red = 0;
        if (one.pixels.at(i).blue - two.pixels.at(i).blue > 0)
        {
            blue = one.pixels.at(i).blue - two.pixels.at(i).blue;
        }
        else
        {
            blue = 0;
        }
        if (one.pixels.at(i).green - two.pixels.at(i).green > 0)
        {
            green = one.pixels.at(i).green - two.pixels.at(i).green;
        }
        else
        {
            green = 0;
        }
        if (one.pixels.at(i).red - two.pixels.at(i).red > 0)
        {
            red = one.pixels.at(i).red - two.pixels.at(i).red;
        }
        else
        {
            red = 0;
        }
        Image::Pixel add;
        add.blue = blue;
        add.green = green;
        add.red = red;
        three.pixels.push_back(add);
    }

    three.header.idLength = one.header.idLength;
    three.header.colorMapType = one.header.colorMapType;
    three.header.dataTypeCode = one.header.dataTypeCode;
    three.header.colorMapOrigin = one.header.colorMapOrigin;
    three.header.colorMapLength = one.header.colorMapLength;
    three.header.xOrigin = one.header.xOrigin;
    three.header.yOrigin = one.header.yOrigin;
    three.header.width = one.header.width;
    three.header.height = one.header.height;
    three.header.bitsPerPixel = one.header.bitsPerPixel;
    three.header.imageDescriptor = one.header.imageDescriptor;
    return three;
}
Image multiplication(Image &one, Image &two)
{
    Image three;
    for (int i = 0; i < one.pixels.size(); i++)
    {
        float blue = 0.0f;
        float green = 0.0f;
        float red = 0.0f;
        blue = ((one.pixels.at(i).blue / 255.0f) * (two.pixels.at(i).blue / 255.0f));
        green = ((one.pixels.at(i).green / 255.0f) * (two.pixels.at(i).green / 255.0f));
        red = ((one.pixels.at(i).red / 255.0f) * (two.pixels.at(i).red / 255.0f));
        Image::Pixel add;
        add.blue = (unsigned char)(blue * 255.0f + 0.5f);
        add.green = (unsigned char)(green * 255.0f + 0.5f);
        add.red = (unsigned char)(red * 255.0f + 0.5f);
        three.pixels.push_back(add);
    }

    three.header.idLength = one.header.idLength;
    three.header.colorMapType = one.header.colorMapType;
    three.header.dataTypeCode = one.header.dataTypeCode;
    three.header.colorMapOrigin = one.header.colorMapOrigin;
    three.header.colorMapLength = one.header.colorMapLength;
    three.header.xOrigin = one.header.xOrigin;
    three.header.yOrigin = one.header.yOrigin;
    three.header.width = one.header.width;
    three.header.height = one.header.height;
    three.header.bitsPerPixel = one.header.bitsPerPixel;
    three.header.imageDescriptor = one.header.imageDescriptor;
    return three;
}
Image screen(Image &one, Image &two)
{
    Image three;
    for (int i = 0; i < one.pixels.size(); i++)
    {
        Image::Pixel pix;
        float blue = 0.0f;
        float green = 0.0f;
        float red = 0.0f;

        blue = (((1 - ((1 - (one.pixels.at(i).blue / 255.0f)) * (1 - (two.pixels.at(i).blue / 255.0f)))) * 255.0f) + 0.5f);
        green = (((1 - ((1 - (one.pixels.at(i).green / 255.0f)) * (1 - (two.pixels.at(i).green / 255.0f)))) * 255.0f) + 0.5f);
        red = (((1 - ((1 - (one.pixels.at(i).red / 255.0f)) * (1 - (two.pixels.at(i).red / 255.0f)))) * 255.0f) + 0.5f);
        pix.blue = (unsigned char)blue;
        pix.green = (unsigned char)green;
        pix.red = (unsigned char)red;
        three.pixels.push_back(pix);
    }
    three.header.idLength = one.header.idLength;
    three.header.colorMapType = one.header.colorMapType;
    three.header.dataTypeCode = one.header.dataTypeCode;
    three.header.colorMapOrigin = one.header.colorMapOrigin;
    three.header.colorMapLength = one.header.colorMapLength;
    three.header.xOrigin = one.header.xOrigin;
    three.header.yOrigin = one.header.yOrigin;
    three.header.width = one.header.width;
    three.header.height = one.header.height;
    three.header.bitsPerPixel = one.header.bitsPerPixel;
    three.header.imageDescriptor = one.header.imageDescriptor;

    return three;
}
Image overlay(Image &one, Image &two)
{
    for (int i = 0; i < one.pixels.size(); i++)
    {
        float blueOne = (one.pixels.at(i).blue / 255.0f);
        float greenOne = (one.pixels.at(i).green / 255.0f);
        float redOne = (one.pixels.at(i).red / 255.0f);
        float blueTwo = (two.pixels.at(i).blue / 255.0f);
        float greenTwo = (two.pixels.at(i).green / 255.0f);
        float redTwo = (two.pixels.at(i).red / 255.0f);
        if (blueTwo <= 0.5)
        {
            blueTwo = (unsigned char)(((2 * blueOne * blueTwo) * 255.0f) + 0.5f);
        }
        else
        {
            blueTwo = (unsigned char)((1 - (2 * (1 - blueOne) * (1 - blueTwo))) * 255.0f + 0.5f);
        }
        if (greenTwo <= 0.5)
        {
            greenTwo = (unsigned char)(((2 * greenOne * greenTwo) * 255.0f) + 0.5f);
        }
        else
        {
            greenTwo = (unsigned char)((1 - (2 * (1 - greenOne) * (1 - greenTwo))) * 255.0f + 0.5f);
        }
        if (redTwo <= 0.5)
        {
            redTwo = (unsigned char)(((2 * redOne * redTwo) * 255.0f) + 0.5f);
        }
        else
        {
            redTwo = (unsigned char)((1 - (2 * (1 - redOne) * (1 - redTwo))) * 255.0f + 0.5f);
        }
        one.pixels.at(i).blue = (unsigned char)blueTwo;
        one.pixels.at(i).green = (unsigned char)greenTwo;
        one.pixels.at(i).red = (unsigned char)redTwo;
    }
    return one;
}
bool checkPics(Image &one, Image &two)
{
    for (int i = 0; i < one.pixels.size(); i++)
    {
        if (one.pixels.at(i).blue != two.pixels.at(i).blue)
        {
            return false;
        }
        if (one.pixels.at(i).green != two.pixels.at(i).green)
        {
            return false;
        }
        if (one.pixels.at(i).red != two.pixels.at(i).red)
        {
            return false;
        }
    }
    return true;
}
void addColor(Image &x, int blue, int green, int red)
{

    for (int i = 0; i < x.pixels.size(); i++)
    {
        if (x.pixels.at(i).blue + blue > 255)
        {
            x.pixels.at(i).blue = 255;
        }
        else if (x.pixels.at(i).blue + blue < 0)
        {
            x.pixels.at(i).blue = 0;
        }
        else
        {
            x.pixels.at(i).blue += blue;
        }
        if (x.pixels.at(i).green + green > 255)
        {
            x.pixels.at(i).green = 255;
        }
        else if (x.pixels.at(i).green + green < 0)
        {
            x.pixels.at(i).green = 0;
        }
        else
        {
            x.pixels.at(i).green += green;
        }
        if (x.pixels.at(i).red + red > 255)
        {
            x.pixels.at(i).red = 255;
        }
        else if (x.pixels.at(i).red + red < 0)
        {
            x.pixels.at(i).red = 0;
        }
        else
        {
            x.pixels.at(i).red += red;
        }
    }
}
void scaleBlue(Image &x, int scaleFactor)
{
    for (int i = 0; i < x.pixels.size(); i++)
    {
        if (x.pixels.at(i).blue * scaleFactor > 255)
        {
            x.pixels.at(i).blue = 255;
        }
        else if (x.pixels.at(i).blue * scaleFactor < 0)
        {
            x.pixels.at(i).blue = 0;
        }
        else
        {
            x.pixels.at(i).blue *= scaleFactor;
        }
    }
}
void scaleGreen(Image &x, int scaleFactor)
{
    for (int i = 0; i < x.pixels.size(); i++)
    {
        if (x.pixels.at(i).green * scaleFactor > 255)
        {
            x.pixels.at(i).green = 255;
        }
        else if (x.pixels.at(i).green * scaleFactor < 0)
        {
            x.pixels.at(i).green = 0;
        }
        else
        {
            x.pixels.at(i).green *= scaleFactor;
        }
    }
}
void scaleRed(Image &x, int scaleFactor)
{
    for (int i = 0; i < x.pixels.size(); i++)
    {
        if (x.pixels.at(i).red * scaleFactor > 255)
        {
            x.pixels.at(i).red = 255;
        }
        else if (x.pixels.at(i).red * scaleFactor < 0)
        {
            x.pixels.at(i).red = 0;
        }
        else
        {
            x.pixels.at(i).red *= scaleFactor;
        }
    }
}
Image onlyRed(Image &x)
{
    Image returner;
    for (int i = 0; i < x.pixels.size(); i++)
    {
        x.pixels.at(i).green = x.pixels.at(i).red;
        x.pixels.at(i).blue = x.pixels.at(i).red;
    }
    returner = x;
    returner.header.idLength = x.header.idLength;
    returner.header.colorMapType = x.header.colorMapType;
    returner.header.dataTypeCode = x.header.dataTypeCode;
    returner.header.colorMapOrigin = x.header.colorMapOrigin;
    returner.header.colorMapLength = x.header.colorMapLength;
    returner.header.xOrigin = x.header.xOrigin;
    returner.header.yOrigin = x.header.yOrigin;
    returner.header.width = x.header.width;
    returner.header.height = x.header.height;
    returner.header.bitsPerPixel = x.header.bitsPerPixel;
    returner.header.imageDescriptor = x.header.imageDescriptor;
    return returner;
}
Image onlyBlue(Image &x)
{
    Image returner;
    for (int i = 0; i < x.pixels.size(); i++)
    {
        x.pixels.at(i).green = x.pixels.at(i).blue;
        x.pixels.at(i).red = x.pixels.at(i).blue;
    }
    returner = x;
    returner.header.idLength = x.header.idLength;
    returner.header.colorMapType = x.header.colorMapType;
    returner.header.dataTypeCode = x.header.dataTypeCode;
    returner.header.colorMapOrigin = x.header.colorMapOrigin;
    returner.header.colorMapLength = x.header.colorMapLength;
    returner.header.xOrigin = x.header.xOrigin;
    returner.header.yOrigin = x.header.yOrigin;
    returner.header.width = x.header.width;
    returner.header.height = x.header.height;
    returner.header.bitsPerPixel = x.header.bitsPerPixel;
    returner.header.imageDescriptor = x.header.imageDescriptor;
    return returner;
}
Image onlyGreen(Image &x)
{
    Image returner;
    for (int i = 0; i < x.pixels.size(); i++)
    {
        x.pixels.at(i).red = x.pixels.at(i).green;
        x.pixels.at(i).blue = x.pixels.at(i).green;
    }
    returner = x;
    returner.header.idLength = x.header.idLength;
    returner.header.colorMapType = x.header.colorMapType;
    returner.header.dataTypeCode = x.header.dataTypeCode;
    returner.header.colorMapOrigin = x.header.colorMapOrigin;
    returner.header.colorMapLength = x.header.colorMapLength;
    returner.header.xOrigin = x.header.xOrigin;
    returner.header.yOrigin = x.header.yOrigin;
    returner.header.width = x.header.width;
    returner.header.height = x.header.height;
    returner.header.bitsPerPixel = x.header.bitsPerPixel;
    returner.header.imageDescriptor = x.header.imageDescriptor;
    return returner;
}
Image combine(Image &red, Image &green, Image &blue)
{
    Image combined;
    combined.header.idLength = red.header.idLength;
    combined.header.colorMapType = red.header.colorMapType;
    combined.header.dataTypeCode = red.header.dataTypeCode;
    combined.header.colorMapOrigin = red.header.colorMapOrigin;
    combined.header.colorMapLength = red.header.colorMapLength;
    combined.header.xOrigin = red.header.xOrigin;
    combined.header.yOrigin = red.header.yOrigin;
    combined.header.width = red.header.width;
    combined.header.height = red.header.height;
    combined.header.bitsPerPixel = red.header.bitsPerPixel;
    combined.header.imageDescriptor = red.header.imageDescriptor;

    for (int i = 0; i < red.pixels.size(); i++)
    {
        Image::Pixel x;
        x.red = red.pixels.at(i).red;
        x.green = green.pixels.at(i).green;
        x.blue = blue.pixels.at(i).blue;
        combined.pixels.push_back(x);
    }
    return combined;
}
Image flip(Image &x)
{
    Image toReturn;
    for (int i = x.pixels.size() - 1; i >= 0; i--)
    {
        toReturn.pixels.push_back(x.pixels.at(i));
    }
    toReturn.header.idLength = x.header.idLength;
    toReturn.header.colorMapType = x.header.colorMapType;
    toReturn.header.dataTypeCode = x.header.dataTypeCode;
    toReturn.header.colorMapOrigin = x.header.colorMapOrigin;
    toReturn.header.colorMapLength = x.header.colorMapLength;
    toReturn.header.xOrigin = x.header.xOrigin;
    toReturn.header.yOrigin = x.header.yOrigin;
    toReturn.header.width = x.header.width;
    toReturn.header.height = x.header.height;
    toReturn.header.bitsPerPixel = x.header.bitsPerPixel;
    toReturn.header.imageDescriptor = x.header.imageDescriptor;

    return toReturn;
}

void printHelp()
{
    cout << "Project 2: Image Processing, Spring 2023\n"
         << endl;
    cout << "Usage:" << endl;
    cout << "\t./project2.out [output] [firstImage] [method] [...]" << endl;
}

void printMissingArg()
{
    cout << "Missing argument." << endl;
}

void printInvalidMethod()
{
    cout << "Invalid method name." << endl;
}

bool validateTGA(string filename)
{
    if (filename.size() < 5)
        return false;
    if (filename.substr(filename.size() - 4) != ".tga")
        return false;
    return true;
}

void printInvalidFileName()
{
    cout << "Invalid file name." << endl;
}

void printInvalidNumber()
{
    cout << "Invalid argument, expected a number." << endl;
}

bool validateCommand(string command)
{

    // list of valid commands
    vector<string> validCommands = {
            "multiply", "subtract", "overlay",
            "screen", "addred", "addblue",
            "addgreen", "combine", "onlyred",
            "onlyblue", "onlygreen", "flip",
            "scalered", "scalegreen", "scaleblue"};
    return find(validCommands.begin(), validCommands.end(), command) != validCommands.end();
}

bool oneNumberCommand(string command)
{
    return command == "addred" || command == "addgreen" ||
           command == "addblue" || command == "scalered" ||
           command == "scaleblue" || command == "scalegreen";
}

bool oneImageCommand(string command)
{
    return command == "multiply" || command == "subtract" ||
           command == "overlay" || command == "screen";
}

bool noArgsCommands(string command)
{
    return command == "onlyred" || command == "onlygreen" ||
           command == "onlyblue" || command == "flip";
}

int main(int argc, char *argv[])
{

    Image tracker;
    string outputFile;
    string inputFile;
    string command;

    // help or not enough arguments
    if (argc < 2 || argv[1] == "--help")
    {
        printHelp();
        return 0;
    }
    else
    {

        // output file
        if (argv[1] && validateTGA(argv[1]))
        {
            outputFile = argv[1];
        }
        else
        {
            printInvalidFileName();
            return 0;
        }

        // input file
        if (argv[2] && validateTGA(argv[2]))
        {
            inputFile = argv[2];
        }
        else
        {
            printInvalidFileName();
            return 0;
        }

        // look for first command
        if (argv[3] && validateCommand(argv[3]))
        {

            command = argv[3];
        }
        else
        {
            printInvalidMethod();
            return 0;
        }

        // load file and set tracker to inputfile image
        readImage(inputFile, tracker);

        if (argc > 2)
        {

            for (auto i = 3; i < argc; i++)
            {

                // get the command
                command = argv[i];

                // single image commands
                if (oneImageCommand(command) || oneNumberCommand(command))
                {

                    // need one other argument
                    if (argv[i + 1])
                    {

                        // single image commands
                        if (oneImageCommand(command))
                        {

                            // validate name of file
                            if (validateTGA(argv[i + 1]))
                            {

                                Image img;
                                readImage(argv[i + 1], img);
                                if (command == "multiply")
                                {
                                    tracker = multiplication(tracker, img);
                                }
                                else if (command == "subtract")
                                {
                                    tracker = subtraction(tracker, img);
                                }
                                else if (command == "overlay")
                                {
                                    tracker = overlay(tracker, img);
                                }
                                else if (command == "screen")
                                {
                                    tracker = screen(tracker, img);
                                }
                                // skip ahead 1
                                i++;
                            }
                            else
                            {
                                printInvalidFileName();
                                return 0;
                            }
                        }
                            // single number commands
                        else
                        {
                            try
                            {

                                int num = std::stoi(argv[i + 1]);

                                if (command == "addred")
                                {
                                    addColor(tracker, 0, 0, num);
                                }
                                else if (command == "addgreen")
                                {
                                    addColor(tracker, 0, num, 0);
                                }
                                else if (command == "addblue")
                                {
                                    addColor(tracker, num, 0, 0);
                                }
                                else if (command == "scalered")
                                {
                                    scaleRed(tracker, num);
                                }
                                else if (command == "scalegreen")
                                {
                                    scaleGreen(tracker, num);
                                }
                                else if (command == "scaleblue")
                                {
                                    scaleBlue(tracker, num);
                                }
                                // skip ahead 1
                                i++;
                            }
                            catch (...)
                            {
                                printInvalidNumber();
                                return 0;
                            }
                        }
                    }
                    else
                    {
                        printMissingArg();
                        return 0;
                    }
                }

                    // no arguments
                else if (noArgsCommands(command))
                {
                    if (command == "onlyred")
                    {
                        tracker = onlyRed(tracker);
                    }
                    else if (command == "onlygreen")
                    {
                        tracker = onlyGreen(tracker);
                    }
                    else if (command == "onlyblue")
                    {
                        tracker = onlyBlue(tracker);
                    }
                    else if (command == "flip")
                    {
                        tracker = flip(tracker);
                    }
                }

                else if (command == "combine")
                {
                    // needs two arguments
                    if (argv[i + 1] && validateTGA(argv[i + 1]))
                    {
                        if (argv[i + 2] && validateTGA(argv[i + 2]))
                        {
                            Image img;
                            readImage(argv[i + 1], img);
                            Image img2;
                            readImage(argv[i + 2], img2);
                            Image result(tracker, img, img2);
                            tracker = result;
                            // skip 2 ahead
                            i += 2;
                        }
                        else
                        {
                            printInvalidFileName();
                            return 0;
                        }
                    }
                    else
                    {
                        printInvalidFileName();
                        return 0;
                    }
                }
            }

            // write tracker to outputFile
            cout << "writing result image to file : " << outputFile << endl;
            writeImage(outputFile, tracker);
        }
    }

    return 0;
}