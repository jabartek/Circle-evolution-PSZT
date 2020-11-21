# Circle-evolution-PSZT
This is a project for PSZT (Artificial Intelligence) class at WUT


## Compilation
Just:

    scons
should work. Just make sure that you have *SFML-2.5.1* in *lib/*. 

## Running the program
To start the program run

    bin/PSZT_SFML PATH_TO_CONFIG

The program cannot be run without config file. If running on Windows, please put SFML's .dll's in bin/ as we are using static linking.

## Configuration file specification
The program can only run with a config file provided. The specification for the file is as follows:

	NUMBER_OF_RECTANGLES
	//start of rectangle data - has to be provided for every rectangle
	X_POSITION_OF_UPPER_LEFT_CORNER
	Y_POSITION_OF_UPPER_LEFT_CORNER
	RECTANGLE_WIDTH
	RECTANGLE_HEIGHT
	//end of rectangle data
	MAXIMUM_CIRCLE_RADIUS_FOR_1ST_ITERATION
	//initial spawn area data - it is always a rectangle
	MINIMUM_X_COORDINATE
	MAXIMUM_X_COORDINATE
	MINIMUM_Y_COORDINATE
	MAXIMUM_Y_COORDINATE
    //end of initial spawn area
    WINDOW_WIDTH //visual only. Circles may leave the window, as can the rectangles
    WINDOW_HEIGHT
    POPULATION_SIZE
    ITERATION_NUMBER
    RADIUS_MUTATION_STRENGTH
    POSITION_MUTATION_STRENGTH
    MUTATION_THRESHOLD //specifies how often it is the radius that mutates (for position it is 1 (minus) the value)
    ELITE_SIZE //specified as a fraction of total population
    OUTPUT_FILE_PATH
    SAVE_IMAGES ('T' if you want to save images to img/; any other non-whitespace value otherwise)
    ¡IMPORTANT! New line character is required at the end of configuration

Newlines (apart from the final one) can be replaced with any whitespace characters. //'s are used as a comment in the specification, but aren't accepted by the program. 
Sample configuration files, as used for the experiments, can be found in *data/*