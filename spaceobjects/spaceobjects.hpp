/**
 * @file spaceobjects.hpp
 * @copyright 2016
 * @author Brandon Karl & Ryan DeLosh
 * @date 4/19/2016
 * @version 1.0
 *
 * @brief This file contains the class declarations
 * for the SpaceObject, Planet and Star classes.
 *
 * @section
 *  
 */
#ifndef SPACEOBJECTS_HPP
#define SPACEOBJECTS_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>

/**
 * @brief Class SpaceObject
 * Is an object in space that is inherited by both 
 * the Body and Star Classes
 * -- Brandon Karl is in charge of this class --
 */
class SpaceObject: public sf::Drawable {
 public:
/**
 * @brief Constructor
 * @param A 2 coordinate vector that initiates the objects position &
 *      The Texture for the object
 */
    SpaceObject();
/**
 * @brief Returns current object position
 * @param None
 * @return Vector2f pos
 */
    sf::Vector2f getPos() const;
/**
 * @brief Sets the objects position
 * @param Vector2f Val
 * @return void
 */
    void setPos(sf::Vector2f val);
/**
 * @brief Sets the new objects position
 * @param double Val
 * @return void
 */
    void setNewPos(double seconds);
/**
 * @brief Returns the currently stored velocity value
 * @param None
 * @return Vector2f velocity
 */
    sf::Vector2f getVelocity();
/**
 * @brief Sets the objects velocity
 * @param Vector2f Val
 * @return void
 */
    void setVelocity(sf::Vector2f val);
/**
 * @brief Sets the Velocity of the object
 * @param Vector2f val
 * @return void
 */
    void setNewVelocity(double seconds);
/**
 * @brief Sets the new Acceleration
 * @param None
 * @return void
 */
    void setNewAccel();
/**
 * @brief Sets the Acceleration
 * @param Vector2f acceleration
 * @return void
 */
    void setAcceleration(sf::Vector2f accel);
/**
 * @brief Returns the currently stored acceleration value
 * @param None
 * @return Vector2f acceleration
 */
    sf::Vector2f getAccel();
/**
 * @brief Returns the currently stored force value
 * @param None
 * @return Vector2f force
 */
    sf::Vector2f getForce();
/**
 * @brief Sets the Force of the object
 * @param Vector2f val
 * @return void
 */
    void setForce(sf::Vector2f val);
/**
 * @brief Returns the objects mass
 * @param None
 * @return double mass
 */
    double getMass();
/**
 * @brief Sets the mass
 * @param Double val
 * @return void
 */
    void setMass(double val);
/**
 * @brief Overloaded virtual function from sf::Drawable
 * @param RenderTarget &target, RenderStates state
 * @return void
 */
    virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const;
/**
 * @brief Returns the Origin
 * @param None
 * @return sf::Vector2f
 */
    sf::Vector2f getOriginPos() const;
/**
 * @brief Sets the Origin Pos
 * @param None
 * @return void
 */
    void setOriginPos(sf::Vector2f origin);
/**
 * @brief Sets the window size in the body
 * @param sf::Vector2f window_size
 * @return void
 */
    void setWindSize(sf::Vector2f window_size);
    /**
 * @brief Gets the window size in the body
 * @param None
 * @return sf::Vector2f window_size
 */
    sf::Vector2f getWindSize();
/**
 * @brief Sets the Universe size in the body
 * @param double univ_radius
 * @return void
 */
    void setUniv_radius(double univ_radius);
/**
 * @brief Gets the Universe size in the body
 * @param None
 * @return double univ_radius
 */
    double getUniv_radius();
/**
 * @brief Sets the starting position of the space objects
 * @param None
 * @return void
 */
    void setUpPos();
/**
 * @brief Sets the name
 * @param string name
 * @return void
 */
    void setName(std::string name);

 /**
 * @brief gets the name
 * @param string name
 * @return void
 */
    std::string getName();

 private:
    sf::Vector2f position_, originPos_;  ///< Holds the position of the object
    sf::Vector2f velocity_, force_;  ///< Holds the velocity and force
    double mass_;  ///< Holds the mass of the object
    sf::Vector2f accel_;  ///< Holds the Acceleration value
    double univ_radius_;  ///< Holds the radius of the universe;
    sf::Vector2f window_size_;  ///< Holds the coordinates for the window size
    std::string name_;
};

/**
 * @brief Class Body
 * Is an object that inherits from the SpaceObject Class
 * -- Brandon Karl is in charge of this class --
 */
class Body: public SpaceObject {
 public:
/**
 * @brief Constructor that uses a 2 coordinate vector that initiates 
 *      the objects position & the filename so the Texture can be 
 *      loaded to the object. These files are both passed to the 
 *      SpaceObject Constructor.
 * @param Vector2f position, String filename
 */
    Body();
/**
 * @brief Overloaded extraction operator
 * @param istream& in, Body& body
 * @return istream& in
 */
    friend std::istream& operator >> (std::istream& in, Body& body);
/**
 * @brief Moves the object according to the time given
 * @param double seconds
 * @return void
 */
    void step(double seconds);

 private:
};

/**
 * @brief Class Star
 * Is an object that inherits from the SpaceObjectClass
 * -- Ryan DeLosh is in charge of this class --
 */
class Star: public SpaceObject {
 public:
/**
 * @brief Constructor Takes the window size and then calculates a random location 
 *      and size for the star within the window.
 * @param Vector2f Window Size
 */
    explicit Star(sf::Vector2f window_size);
/**
 * @brief Gives a star a random Position
 * @param None
 * @return void
 */
    void randPos();
/**
 * @brief Moves a given star.
 * @param Vector2f Window Size
 * @return void
 */
    void starMove();
/**
 * @brief Retrieve the size of the star;
 * @param none
 * @return int
 */
    int getStarSize() const;
/**
 * @brief Overloaded virtual function from sf::Drawable
 * @param RenderTarget &target, RenderStates state
 * @return void
 */
    virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const;

 private:
    int starSize_;
};
#endif
