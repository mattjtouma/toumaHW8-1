// Example invocation: control_GPIO gpio_out_number state gpio_in_number
// where gpio_out_number => GPIO number to control
//	 state => high or low
// 	 gpio_in_number => GPIO number to read
//
// Currently, the build file sets the pinmodes for the input and output pins.
// The only pins supported are 60 for output, and 46 for input.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define PATH "/sys/class/gpio/"

int main(int argc, char* argv[]){

	// Error checking
	if (argc < 4){
		cout << "Usage is: control_GPIO gpio_out_number state gpio_in_number" << endl;
		cout << "gpio_out_number => GPIO number to control" << endl;
		cout << "state => high or low" << endl;
		cout << "gpio_in_number => GPIO number to read" << endl;

		return 2;
	}

	// get the output pin from the first command line argument
	string output_pin = argv[1];
	cout << "output pin: " << output_pin << endl;

	// get the desired output state from the second command line argument
	string state = argv[2];
	cout << "state: " << state << endl;

	// get the input pin from the thrid command line argument
	string input_pin = argv[3];
	cout << "input pin: " << input_pin << endl;

	// concatenate "gpio" with the output pin
	string output_gpio = "gpio" + output_pin;
	//cout << "output GPIO: " << output_gpio << endl;

	// concatenate "gpio" with the input pin
	string input_gpio = "gpio" + input_pin;
	//cout << "input GPIO: " << input_gpio << endl;

	// Create filepaths to the input and output GPIOs
	string output_filepath = PATH + output_gpio;
	string input_filepath = PATH + input_gpio;

	//cout << "output_filepath: " << output_filepath << endl;
	//cout << "input_filepath: " << input_filepath << endl;

	// Write output pin high or low
	// create an fstream object called output_file
	fstream output_file;
	// Open the value file in write mode
	output_file.open((output_filepath + "/value").c_str(), fstream::out);

	// Depending on what the input state was, set the desired value
	if (state == "high")
		output_file << "1" << endl;
	else if (state == "low")
		output_file << "0" << endl;
	else
		cout << "Unknown state. State can be either high or low" << endl;
	// close the file
	output_file.close();

	// Read input pin
	string line;
	// create an fstream object called input_file
	fstream input_file;
	// opent the value file in read mode
	input_file.open((input_filepath + "/value").c_str(), fstream::in);
	// use getline to read the contents of value
	while(getline(input_file, line)){
		// display the contents to the console
		cout << "Button value: " << line << endl;
	}
	// close the file
	input_file.close();

	return 0;

}
