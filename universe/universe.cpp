/**
 * @file universe.cpp
 * @copyright 2016
 * @author Brandon Karl & Ryan DeLosh
 * @date 4/19/2016
 * @version 1.0
 *
 * @brief This file contains implementation of
 * the Universe class.
 *
 * @section
 *
 *  
 */
#include "universe.hpp"
#include <vector>
 /**
 * @brief Constructor
 * @param int universe_size, double universe_radius, vector2f Window_Size
 */
    Universe::Universe(sf::Vector2f window_size,
    double myTime, double deltTime) {
        window_size_ = window_size;
        time_ = myTime;
        if (time_ < 0)
            throw std::invalid_argument(
            "Error: Simulation duration is less than zero");
        deltTime_ = deltTime;
        if (deltTime_ < 0)
            throw std::invalid_argument(
            "Error: Change in time is less than zero");
        elapsedTime_ = 0;

        for (int i = 0; i < 50; i++) {
            Star aStar(window_size_);
            sVect_.push_back(aStar);
        }
        for (int i = 0; i < 50; i++) {
            Star aStar(window_size_);
            sMVect_.push_back(aStar);
        }
    }
/**
 * @brief Stores the Universe radius
 * @param double universe_radius
 * @return void
 */
    void Universe::setUniverseRadius(double univ_radius) {
        univ_radius_ = univ_radius;
    }
/**
 * @brief Stores the window size
 * @param Vector2f window size
 * @return void
 */
    void Universe::setWindowSize(sf::Vector2f windowSize) {
        window_size_ = windowSize;
    }
/**
 * @brief Returns the universe_size that is stored
 * @param None
 * @return int universe_size
 */
    int Universe::getUniverseSize() {
        return univ_size_;
    }
/**
 * @brief Returns the universe_size that is stored
 * @param int universe_size
 * @return None
 */
    int Universe::setUniverseSize(int val) {
        univ_size_ = val;
    }
/**
 * @brief Returns the universe_radius that is stored
 * @param None
 * @return double universe_radius
 */
    double Universe::getUniverseRadius() {
        return univ_radius_;
    }
/**
 * @brief Returns the window_size that is stored
 * @param None
 * @return Vector2f window_size
 */
    sf::Vector2f Universe::getWindowSize() {
        return window_size_;
    }
/**
 * @brief Runs the full simulation
 * @param int argc, char *argv[]
 * @return int whether it completed or not
 */
    int Universe::runSimulation() {
        sf::Text timestamp;
        sf::Font font;
        sf::Vector2f totalForce;
        sf::SoundBuffer buffer;
        sf::Sound bgMusic;
        if (!(font.loadFromFile("./music_and_font/TT_Bricks.ttf")))
            throw std::runtime_error("Error: Could not open font");
        if (!buffer.loadFromFile("./music_and_font/music.wav"))
            throw std::runtime_error("Error: Could not open sound file");
        bgMusic.setBuffer(buffer);
        bgMusic.play();
        bgMusic.setVolume(100);
        bgMusic.setLoop(true);

        timestamp.setFont(font);
        timestamp.setScale(1.0f, 1.0f);
        timestamp.setPosition(0.0f, 0.0f);

        sf::RenderWindow window(sf::VideoMode(window_size_.x,
        window_size_.y), "The Universe");
        while (window.isOpen()) {
            sf::Event event;
            // Handles the Music for the simulation
            int vol = 50;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2) && vol > 0) {
                vol -= 10;
                bgMusic.setVolume(vol);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3) && vol < 100) {
                vol += 10;
                bgMusic.setVolume(vol);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1) && vol == 0) {
                bgMusic.setVolume(vol);
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)
            && vol != 0) {
                bgMusic.setVolume(0);
            }
            // End of Music controls

            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    break;
                }
            }
            for (std::vector<Body>::iterator iter = bVect_.begin();
            iter != bVect_.end(); iter++) {
                iter->setUpPos();
                window.draw(*iter);
            }
            if (elapsedTime_ < time_) {
                for (std::vector<Body>::iterator iter1 = bVect_.begin();
                iter1 != bVect_.end(); ++iter1) {
                    sf::Vector2f net_Force;
                    for (std::vector<Body>::iterator iter2 = bVect_.begin();
                    iter2 != bVect_.end(); ++iter2) {
                        if (iter1->getName() != iter2->getName()) {
                            totalForce = Force(*iter1, *iter2);
                            net_Force.x = net_Force.x + totalForce.x;
                            net_Force.y = net_Force.y + totalForce.y;
                        }
                    }
                    iter1->setForce(net_Force);
                }
                // Draws the stars to the screen
                for (std::vector<Star>::iterator iStar = sVect_.begin();
                iStar != sVect_.end(); iStar++) {
                    window.draw(*iStar);
                }
                for (std::vector<Star>::iterator iStar2 = sMVect_.begin();
                iStar2 != sMVect_.end(); iStar2++) {
                    iStar2->starMove();
                    window.draw(*iStar2);
                }
                // Draws the Planets to the screen
                for (std::vector<Body>::iterator iter3 = bVect_.begin();
                iter3 != bVect_.end(); iter3++) {
                    iter3->step(deltTime_);
                    window.draw(*iter3);
                }
                std::cout << elapsedTime_ << std::endl;
                std::stringstream stream;
                stream << elapsedTime_;
                timestamp.setString(stream.str());
                elapsedTime_ +=deltTime_;
            }

            window.draw(timestamp);
            window.display();
            window.clear();
        }
        std::cout << "Name:      " << "Coordinates:" << std::endl;
        for (std::vector<Body>::iterator printP = bVect_.begin();
        printP != bVect_.end(); printP++) {
            std::cout << printP->getName() << "    " << printP->getPos().x
            << " , " << printP->getPos().y << std::endl;
        }
        std::cout << std::endl;
        std::cout << "SimulationTime:   " << "ScheduledTime: " << std::endl;
        std::cout << elapsedTime_ << "               " << time_ << std::endl;
    }
/**
 * @brief Sets the force in the universe
 * @param body 1 body 2
 * @return sf::Vector2f
 */
    sf::Vector2f Universe::Force(Body p1, Body p2) {
        sf::Vector2f planet_force;
        double grav = (-6.67e-11);
        double totalForce, dx, dy, radius, radius_squared;

        dx = (((p1.getPos()).x) - ((p2.getPos()).x));
        dy = (((p1.getPos()).y) - ((p2.getPos()).y));

        radius_squared = pow(dx, 2) + pow(dy, 2);
        radius = sqrt(radius_squared);

        totalForce = ((grav) * (p1.getMass()) * (p2.getMass()))
        / (radius_squared);

        planet_force.x = totalForce * (dx/radius);
        planet_force.y = totalForce * (dy/radius);

        return planet_force;
    }


/**
 * @brief Returns the currently stored Change in Time
 * @param None
 * @return Double deltTime
 */
    double Universe::getDeltTime() {
        return deltTime_;
    }
/**
 * @brief Pushes a Planet to the Vector
 * @param Body
 * @return void
 */
    void Universe::pushPlanet(Body *planet) {
        bVect_.push_back(*planet);
    }
/**
 * @brief Overloaded extraction operator
 * @param istream& in, Body& body
 * @return istream& in
 */
    std::istream& operator >> (std::istream& in, Universe& universe) {
        int numP;
        double univ_radius;
        in >> numP;
        in >> univ_radius;
        universe.setUniverseSize(numP);
        universe.setUniverseRadius(univ_radius);
        for (int i = 0; i < numP; i++) {
            Body *planet = new Body();
            planet->setUniv_radius(univ_radius);
            planet->setWindSize(universe.getWindowSize());
            in >> *planet;
            universe.pushPlanet(planet);
        }
    }
