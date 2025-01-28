#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <string.h>
using namespace std;

class Animation{
public:
    Animation() = default;
    Animation(int x, int y, int width, int height){
        texture.loadFromFile("/Users/fortnitekorea/Desktop/SFML-Projects/Moving_Sprite/DS DSi - Dragon Quest 6 Realms of Revelation - Guard of Gallows Moor Gate.png");
        for(int i = 0; i < nFrames; i++){
            frames[i] = {x + i * width, y,width,height};
        }
    }

    void ApplyToSprite(sf::Sprite& s){
        s.setTexture(texture);
        s.setTextureRect(frames[iFrame]);
    }

    void Update(float dt){
        time += dt;
        while(time >= holdTime){
            time -= holdTime;
            Advance();
        }
    }

private:
    void Advance(){
        if (forward) {
            if (++iFrame >= nFrames - 1) {
                forward = false;
            }
        } else {
            if (--iFrame <= 0) {
                forward = true;
            }
        }
    }
private:
    static constexpr int nFrames = 3;
    static constexpr float holdTime = 0.1f;
    sf::Texture texture;
    sf::IntRect frames[nFrames];
    int iFrame = 0;
    float time = 0.0f;
    bool forward = true; // Direction flag for back-and-forth animation
};

class Character{
private:
    enum class AnimationIndex{
        WalkingUp,
        WalkingDown,
        WalkingLeft,
        WalkingRight,
        Count
    };
public:
    Character(const sf::Vector2f& pos) 
        : pos(pos)
    {      
        sprite.setTextureRect({0,0,33,32});
        animations[int(AnimationIndex::WalkingDown)] = Animation(0, 96, 33,32);
        animations[int(AnimationIndex::WalkingLeft)] = Animation(0, 32, 33,32);
        animations[int(AnimationIndex::WalkingRight)] = Animation(0, 64, 33,32);
        animations[int(AnimationIndex::WalkingUp)] = Animation(0, 0, 33,32);

        sprite.setScale(3, 3);
    }
    void Draw(sf::RenderTarget& rt) const{      
        rt.draw(sprite);
    }
    void SetDirection(const sf::Vector2f& dir){
        vel = dir * speed;
        if(dir.x > 0.0f){
            curAnimation = AnimationIndex::WalkingRight;
        }else if(dir.x < 0.0f){
            curAnimation = AnimationIndex::WalkingLeft;
        }else if(dir.y > 0.0f){
            curAnimation = AnimationIndex::WalkingUp;
        }else if(dir.y < 0){
            curAnimation = AnimationIndex::WalkingDown;
        }
    }
    void Update(float dt) {
        pos += vel * dt;  // Update position based on velocity and elapsed time
        animations[int(curAnimation)].Update(dt);  // Update the current animation
        animations[int(curAnimation)].ApplyToSprite(sprite);  // Apply the current animation to the sprite
        sprite.setPosition(pos);  // Set the sprite's position
    }


private:
    static constexpr float speed = 50.0f;
    sf::Vector2f pos;
    sf::Vector2f vel = {0.0f,0.0f};
    sf::Sprite sprite;
    Animation animations[int (AnimationIndex::Count)];
    AnimationIndex curAnimation = AnimationIndex::WalkingUp;

};

int main()
{
    // Create the main window
    int windowLength = 800;
    int windowHeight = 600;
    sf::RenderWindow window(sf::VideoMode(windowLength, windowHeight), "SFML window");
   
    
    //Creating the sprite
    Character player({100.0f, 100.0f});
      

    //timepoint for delta time measurement
    auto tp =  chrono::steady_clock::now();

    // Start the game loop
    while (window.isOpen())
    {

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
        //get dt
        float dt;
        {
            const auto new_tp =  chrono::steady_clock::now();
            dt = chrono::duration<float>(new_tp - tp).count();
            tp = new_tp;
        }
    

        
        //handle input
        sf::Vector2f dir = {0.0f, 0.0f};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            dir.y -= 8;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            dir.y += 8;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            dir.x -= 8;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            dir.x += 8;
        }
        player.SetDirection(dir);
        //update model
        player.Update(dt);
 
        //clearing and displaying everything continuously until we stop the program
        //order of things drawn matters
        window.clear();// Clear screen
        player.Draw(window);//draw sprite 
        window.display();// Update the window
    }
 
    return EXIT_SUCCESS;
}