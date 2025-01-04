#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;


int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
   
    

    sf::Texture texture;
    texture.loadFromFile("/Users/fortnitekorea/Desktop/SFML-Projects/Moving_Sprite/—Pngtree—character pixel art man_6178368.png");
    //setup our sprite with a texture
    sf::Sprite sprite(texture);
    sprite.setScale(.3, .3);
    double x = 50;
    double y = 50;

    bool drawCircle = false; // Flag to track if the circle should be drawn

    // Start the game loop
    while (window.isOpen())
    {
        sprite.setPosition(x,y);
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed){
                cout << "Window Closed Successfully.\n";
                window.close();
            }           
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            y -= .2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            y += .2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            x -= .2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            x += .2;
        }
 
        // Clear screen
        window.clear();
        //draw sprites
        window.draw(sprite);
        // Update the window
        window.display();
    }
 
    return EXIT_SUCCESS;
}