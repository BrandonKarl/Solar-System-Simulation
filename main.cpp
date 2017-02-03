/**
 * @file main.cpp
 * @copyright 2016
 * @author Brandon Karl & Ryan DeLosh
 * @date 4/19/2016
 * @version 1.0
 *
 * @brief This file contains the initialization of the simulation.
 *
 * @section
 *
 * This file checks the command line for the correct number of arguments,
 * which must be 3. The first argument being the file name, second being
 * the length of time and the third being the change in time. Once the 
 * number of arguments has been verified, it creates a window and runs the
 * simulation in a try/catch block, making sure no errors occur with the
 * values.
 
 * testing
 */


#include "./spaceobjects/spaceobjects.hpp" // Spaceobject class to make bodies
#include "./universe/universe.hpp" // Universe class to hold the bodies and do simulation
int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Not enough arguments given" << std::endl;
        exit(1);
    }
    sf::Vector2f window_size;
    window_size.x = 800;
    window_size.y = 800;
    try {
        Universe myUniverse(window_size, atof(argv[1]), atof(argv[2])); // Makes universe with time and delta time

        std::cin >> myUniverse; // Gets information from standard in, in this case "./planets/planets.txt"

        myUniverse.runSimulation(); // Runs simulation
    }catch (std::invalid_argument ia) {
        std::cerr << ia.what() << std::endl; // Catch block for invalid arguments
    }catch (std::runtime_error re) {
        std::cerr << re.what() << std::endl; // Catch block for runtime errors
    }
    return 0;
}
