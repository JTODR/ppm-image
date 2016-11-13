#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef unsigned char byte;

int main() {
	size_t SIZE = 256 * 256 * 3;		//3 is for the 3 colour channels; red, green, blue
	byte* image_data = (byte*) malloc(SIZE);	//Allocating memory for image of size w: 256 & h: 256 pixels & 3 colour channels
	memset(image_data, 255, SIZE);		//Setting all allocated memory to value of 255 (ie. white), this will be first 'painted' to image in the Body

	ofstream myImage;		//output stream object
	myImage.open("image.ppm");

	if (myImage.fail())
	{
		cout << "Unable to create image.ppm" << endl;
		getchar();
		getchar();
		return 0;
	}

	const int width = 256, height = 256;

	{ //Image header - Need this to start the image properties
		myImage << "P3" << endl;						//Declare that you want to use ASCII colour values
		myImage << width << " " << height << endl;		//Declare w & h
		myImage << "255" << endl;						//Declare max colour ID
	}

	int pixel = 0;
	{ //Image Painter - sets the background and the diagonal line to the array
		for (int row = 0; row < width; row++) {
			for (int col = 0; col < height; col++) {
				
				//Background
				image_data[pixel*3] = row % 256; //red
				image_data[pixel*3 + 1] = col % 256; //green
				image_data[pixel*3 + 2] = col % 256; //blue

				//Black line - comment this out to remove diagonal black line
				image_data[col * 3 + col*(256 * 3)] = 0;
				image_data[col * 3 + col*(256 * 3) + 1] = 0;
				image_data[col * 3 + col*(256 * 3) + 2] = 0;
				
				pixel++;
			}
		}
	}

	{ //Image Body - outputs image_data array to the .ppm file, creating the image
		for (int x = 0; x < SIZE; x++) {
			int value = image_data[x];		//Sets value as an integer, not a character value
			myImage << value << " " << endl;		//Sets 3 bytes of colour to each pixel	
		}
	}

	myImage.close();

	cout << "Black diagonal line going from top left corner to bottom right corner. \n";

	free(image_data);
	image_data = NULL;

	getchar();
	getchar();

	return 0;
}