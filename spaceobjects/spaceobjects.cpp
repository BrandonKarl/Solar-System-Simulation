/**
 * @file spaceobjects.cpp
 * @copyright 2016
 * @author Brandon Karl & Ryan DeLosh
 * @date 4/19/2016
 * @version 1.0
 *
 * @brief This file contains the implementations for
 * the SpaceObject class and it's child classes, Body
 * and Star.
 *
 * @section
 * 
 *
 *  
 */
#include "spaceobjects.hpp"
#include <string>
    SpaceObject::SpaceObject() {
    }
/**
 * @brief Returns current object position
 * @param None
 * @return Vector2f pos
 */
    sf::Vector2f SpaceObject::getPos() const {
        return position_;
    }
/**
 * @brief Sets the objects position
 * @param Vector2f Val
 * @return void
 */
    void SpaceObject::setNewPos(double seconds) {
        sf::Vector2f pos;
        (pos.x) = ((getPos().x) + (seconds * (getVelocity().x)));
        (pos.y) = ((getPos().y) + (seconds * (getVelocity().y)));
        setPos(pos);
    }
/**
 * @brief Returns the currently stored velocity value
 * @param None
 * @return Vector2f velocity
 */
    sf::Vector2f SpaceObject::getVelocity() {
        return velocity_;
    }
/**
 * @brief Sets the New Velocity of the object
 * @param Vector2f val
 * @return void
 */
    void SpaceObject::setNewVelocity(double seconds) {
        sf::Vector2f velo;
        (velo.x) = ((getVelocity().x) + (seconds * (getAccel().x)));
        (velo.y) = ((getVelocity().y) + (seconds * (getAccel().y)));
        setVelocity(velo);
    }
/**
 * @brief Sets the new Acceleration
 * @param None
 * @return void
 */
    void SpaceObject::setNewAccel() {
        sf::Vector2f accel;
        (accel.x) = ((getForce().x) / (mass_));
        (accel.y) = ((getForce().y) / (mass_));
        setAcceleration(accel);
    }
/**
 * @brief Returns the currently stored acceleration value
 * @param None
 * @return Vector2f acceleration
 */
    sf::Vector2f SpaceObject::getAccel() {
        return accel_;
    }
/**
 * @brief Sets the Acceleration
 * @param Vector2f acceleration
 * @return void
 */
    void SpaceObject::setAcceleration(sf::Vector2f accel) {
        accel_ = accel;
    }
/**
 * @brief Returns the objects mass
 * @param None
 * @return double mass
 */
    double SpaceObject::getMass() {
        return mass_;
    }
/**
 * @brief Sets the mass
 * @param Double val
 * @return void
 */
    void SpaceObject::setMass(double val) {
        mass_ = val;
    }
/**
 * @brief Overloaded virtual function from sf::Drawable
 * @param RenderTarget &target, RenderStates state
 * @return void
 */
    void SpaceObject::draw(sf::RenderTarget &target,
    sf::RenderStates state) const {
        sf::Texture texture;
        sf::Sprite sprite;
        if (!texture.loadFromFile(name_))
            throw std::runtime_error("Error: Could not load texture");
        sprite.setTexture(texture);
        sprite.setPosition(originPos_);
        target.draw(sprite, state);
    }
/**
 * @brief Returns the Origin Pos
 * @param None
 * @return sf::Vector2f
 */
    sf::Vector2f SpaceObject::getOriginPos() const {
        return originPos_;
    }
/**
 * @brief Sets the Origin Pos
 * @param sf::Vector2f
 * @return void
 */
    void SpaceObject::setOriginPos(sf::Vector2f origin) {
        originPos_ = origin;
    }
/**
 * @brief Sets the starting position of the space objects
 * @param None
 * @return void
 */
    void SpaceObject::setUpPos() {
        sf::Vector2f velo;
        sf::Vector2f pos;
        (pos.x) = ((window_size_.x / 2) + (((position_.x) / univ_radius_)
        * window_size_.x / 2));
        (pos.y) = (window_size_.y / 2) - (((position_.y) / univ_radius_)
        * (window_size_.y / 2));
        setOriginPos(pos);
    }
/**
 * @brief Returns the currently stored force value
 * @param None
 * @return Vector2f force
 */
    sf::Vector2f SpaceObject::getForce() {
        return force_;
    }
/**
 * @brief Sets the window size in the body
 * @param sf::Vector2f window_size
 * @return void
 */
    void SpaceObject::setWindSize(sf::Vector2f window_size) {
        window_size_ = window_size;
    }
    /**
 * @brief Gets the window size in the body
 * @param None
 * @return sf::Vector2f window_size
 */
    sf::Vector2f SpaceObject::getWindSize() {
        return window_size_;
    }
/**
 * @brief Sets the Universe size in the body
 * @param sf::Vector2f univ_radius
 * @return void
 */
    void SpaceObject::setUniv_radius(double univ_radius) {
        univ_radius_ = univ_radius;
    }
/**
 * @brief Gets the Universe size in the body
 * @param None
 * @return double univ_radius
 */
    double SpaceObject::getUniv_radius() {
        return univ_radius_;
    }
/**
 * @brief Sets the Force of the object
 * @param Vector2f val
 * @return void
 */
    void SpaceObject::setForce(sf::Vector2f val) {
        force_ = val;
    }
/**
* @brief Sets the objects position
* @param Vector2f Val
* @return void
*/
    void SpaceObject::setPos(sf::Vector2f val) {
        position_ = val;
    }
/**
* @brief Sets the objects velocity
* @param Vector2f Val
* @return void
*/
    void SpaceObject::setVelocity(sf::Vector2f val) {
        velocity_ = val;
    }
/**
 * @brief Sets the name
 * @param string name
 * @return void
 */
    void SpaceObject::setName(std::string name) {
        name_ = name;
    }

 /**
 * @brief gets the name
 * @param string name
 * @return void
 */
    std::string SpaceObject::getName() {
        return name_;
    }

/**
 * @brief Constructor that uses a 2 coordinate vector that initiates 
 *      the objects position & the filename so the Texture can be 
 *      loaded to the object. These files are both passed to the 
 *      SpaceObject Constructor.
 * @param Vector2f position, String filename
 */
    Body::Body() {
    }
/**
 * @brief Overloaded extraction operator
 * @param istream& in, Body& body
 * @return istream& in
 */
    std::istream& operator >> (std::istream& in, Body& body) {
            sf::Vector2f pos;
            sf::Vector2f vel;
            sf::Vector2f accel;
            double mass;
            std::string name;
            in >> (pos.x);
            in >> (pos.y);
            in >> (vel.x);
            in >> (vel.y);
            in >> mass;
            in >> name;
            body.setName(name);
            body.setPos(pos);
            body.setVelocity(vel);
            body.setMass(mass);
            return in;
    }
/**
 * @brief Moves the object according to the time given
 * @param double seconds
 * @return void
 */
    void Body::step(double seconds) {
        setNewAccel();
        setNewVelocity(seconds);
        setNewPos(seconds);
        setUpPos();
    }
/**
 * @brief Constructor Takes the window size and then calculates a random location 
 *      and size for the star within the window.
 * @param Vector2f Window Size
 */
    Star::Star(sf::Vector2f window_size) {
        setWindSize(window_size);
        starSize_ = (rand() % 4);
        randPos();
    }
/**
 * @brief Gives a star a random Position
 * @param None
 */
    void Star::randPos() {
        sf::Vector2f startPos;
        sf::Vector2f window_Size = getWindSize();
        startPos.x = rand() % static_cast<int>(window_Size.x);
        startPos.y = rand() % static_cast<int>(window_Size.y);
        setPos(startPos);
    }
/**
 * @brief Moves a given star.
 * @param Vector2f Window Size
 */
    void Star::starMove() {
        sf::Vector2f movePos;
        sf::Vector2f window_Size = getWindSize();
        movePos = getPos();
        movePos.y = movePos.y -0.01;

        if (movePos.y <=0) {
            movePos.y = (window_Size.y);
        }
        setPos(movePos);
    }
/**
 * @brief Retrieve the size of the star;
 * @param none
 * @return int
 */
    int Star::getStarSize() const {
        return starSize_;
    }

/**
 * @brief Overloaded virtual function from sf::Drawable
 * @param RenderTarget &target, RenderStates state
 * @return void
 */
    void Star::draw(sf::RenderTarget &target, sf::RenderStates state) const {
        sf::CircleShape star;
        int sSize = getStarSize();
        star.setRadius(sSize);
        star.setOutlineColor(sf::Color::White);
        star.setFillColor(sf::Color::Yellow);
        star.setOutlineThickness(1);
        star.setPosition(getPos());
        target.draw(star, state);
    }
