#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

//function to control the sprite using the WASD keys
void handleSpriteMovement(double &x, double &y, const sf::FloatRect &spriteBounds, int windowLength, int windowHeight){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (y > 0)) {
        y -= 8;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (y + spriteBounds.height < windowHeight) ) {
        y += 8;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (x > 0)) {
        x -= 8;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (x + spriteBounds.width) < windowLength) {
        x += 8;
    }
}

int main()
{
    // Create the main window
    int windowLength = 800;
    int windowHeight = 600;
    sf::RenderWindow window(sf::VideoMode(windowLength, windowHeight), "SFML window");
   
    
    //Creating the sprite
    sf::Texture texture;
    texture.loadFromFile("/Users/fortnitekorea/Desktop/SFML-Projects/Moving_Sprite/—Pngtree—character pixel art man_6178368.png");
    sf::Sprite sprite(texture);//setup our sprite with a texture
    sprite.setScale(.2, .2);//shrink the sprite to fit window
    double x = (windowLength / 3);//to be adjusted if sprite size is changed
    double y = (windowHeight / 3);//to be adjusted if sprite size is changed
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();// Get the sprite's size


    //object for timing/fps
    sf::Clock clock; 
    window.setFramerateLimit(60);

    // Start the game loop
    while (window.isOpen())
    {
        //compute frame time
        float currentTime = clock.restart().asSeconds();//returns time object and stored as a float
        float fps = 1.0f/(currentTime);
        cout << "fps: " << fps << "\n";

        sprite.setPosition(x,y);//sets initial position of sprite
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
        handleSpriteMovement(x, y, spriteBounds, windowLength, windowHeight);//movement with WASD keys
        
 
        //clearing and displaying everything continuously until we stop the program
        //order of things drawn matters
        window.clear();// Clear screen
        window.draw(sprite);//draw sprite 
        window.display();// Update the window
    }
 
    return EXIT_SUCCESS;
}