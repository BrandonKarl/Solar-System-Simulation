/**
 * @file universe.hpp
 * @copyright 2016
 * @author Brandon Karl & Ryan DeLosh
 * @date 4/19/2016
 * @version 1.0
 *
 * @brief This file contains the class declaration
 * for the Universe class.
 *
 * @section
 *  
 */
#include "../spaceobjects/spaceobjects.hpp"
#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>


/**
 * @brief Class Universe
 * Is an object that is in charge of running the simulation
 * -- Ryan DeLosh is in charge of this class --
 */
class Universe {
 public:
/**
 * @brief Constructor
 * @param int universe_size, double universe_radius, vector2f Window_Size
 */
    Universe(sf::Vector2f window_size, double time, double deltTime);
/**
 * @brief Stores the Universe radius
 * @param double universe_radius
 * @return void
 */
    void setUniverseRadius(double univ_radius);
/**
 * @brief Stores the window size
 * @param Vector2f window size
 * @return void
 */
    void setWindowSize(sf::Vector2f windowSize);
/**
 * @brief Returns the universe_size that is stored
 * @param None
 * @return int universe_size
 */
    int getUniverseSize();
/**
 * @brief Returns the universe_size that is stored
 * @param int universe_size
 * @return None
 */
    int setUniverseSize(int val);
/**
 * @brief Returns the universe_radius that is stored
 * @param None
 * @return double universe_radius
 */
    double getUniverseRadius();
/**
 * @brief Returns the window_size that is stored
 * @param None
 * @return Vector2f window_size
 */
    sf::Vector2f getWindowSize();
/**
 * @brief Runs the full simulation
 * @param int argc, char *argv[]
 * @return int whether it completed or not
 */
    int runSimulation();
/**
 * @brief Sets the force in the universe
 * @param body 1 body 2
 * @return sf::Vector2f
 */
    sf::Vector2f Force(Body p1, Body p2);
/**
 * @brief Sets the Acceleration files
 * @param Vector2f acceleration
 * @return void
 */
    double getDeltTime();
/**
 * @brief Pushes a Planet to the Vector
 * @param Body
 * @return void
 */
    void pushPlanet(Body *planet);
/**
 * @brief Overloaded extraction operator
 * @param istream& in, Body& body
 * @return istream& in
 */
    friend std::istream& operator >> (std::istream& in, Universe& universe);

 private:
    std::vector<Body> bVect_;  ///< A vector that hold Body objects
    std::vector<Star> sVect_;  ///< A vector that holds Star Objects
    std::vector<Star> sMVect_;  ///< Vector of moving stars
    double elapsedTime_;  ///< Holds the current elapsed time
    double time_;  ///< Holds the time until the simulation completes
    double deltTime_;  ///< Holds the change in time per step
    int univ_size_;  ///< Holds the size of the universe
    double univ_radius_;  ///< Holds the radius of the universe;
    sf::Vector2f window_size_;  ///< Holds the coordinates for the window size
};
#endif
