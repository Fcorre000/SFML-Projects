#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

sf::Vector2f Normalize(const sf::Vector2f& rVector){
    float fLenghth = sqrt(rVector.x*rVector.x + rVector.y*rVector.y);
    sf::Vector2f vNormalizedVector(rVector.x / fLenghth, rVector.y / fLenghth);
    return vNormalizedVector;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML works!");

    sf::Texture playerTexture;
    playerTexture.loadFromFile("MainCharacter.png");
    sf::Sprite player(playerTexture);
    player.setScale(.2,.2);
    player.setOrigin(600,600);

    sf::Texture enemyTexture;
    enemyTexture.loadFromFile("Enemy.png");
    sf::Sprite enemy(enemyTexture);
    enemy.setPosition(500,400);
    enemy.setScale(.2,.2);
    enemy.setOrigin(600,600);

    sf::Texture weaponTexture;
    weaponTexture.loadFromFile("WeaponPack.png");
    sf::Sprite weapon(weaponTexture);
    weapon.setPosition(100,100);
    weapon.setTextureRect({0,100,34,34});//{starting x-co0rd, y-coord, width, height}
    weapon.setScale(2,2);
    weapon.setOrigin(16,16);

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Time timeSinceLastFrame = clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        sf::Vector2f vRequestedPlayerMovement(0.0f, 0.0f);
        float fSpeed = 400.0f;
        //gather player input
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            vRequestedPlayerMovement += sf::Vector2f(0.0f, -1.0f);//x,y coord

        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            vRequestedPlayerMovement += sf::Vector2f(1.0f, 0.0f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            vRequestedPlayerMovement += sf::Vector2f(0.0f, 1.0f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            vRequestedPlayerMovement += sf::Vector2f(-1.0f, 0.0f);
        }
        //uses sf function move, takes vector, and using 
        //timeSincelastFrame var to keep fps normal
        player.move(vRequestedPlayerMovement * timeSinceLastFrame.asSeconds() * fSpeed);

        sf::Vector2f vMousePosition = (sf::Vector2f)sf::Mouse::getPosition(window);//must cast to vector
        sf::Vector2f vPlayerToMouse = vMousePosition - player.getPosition();

        sf::Vector2f vPlayerToMouseNormalized = Normalize(vPlayerToMouse);

        weapon.setPosition(player.getPosition() + vPlayerToMouseNormalized * 100.0f);

        window.clear();
        window.draw(player);
        window.draw(enemy);
        window.draw(weapon);
        window.display();
    }

    return 0;
}