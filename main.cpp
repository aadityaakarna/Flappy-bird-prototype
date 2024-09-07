#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

const float GRAVITY = 800.0f;
const float FLAP_FORCE = -400.0f;
const float PIPE_SPEED = 300.0f;
const float PIPE_WIDTH = 80.0f;
const float PIPE_GAP = 200.0f;
const float SPAWN_INTERVAL = 2.0f;
const string HIGH_SCORE_FILE = "highscore.txt";

class Bird {
public:
    Bird(float x, float y) {
        shape.setSize(sf::Vector2f(50.0f, 35.0f));
        shape.setFillColor(sf::Color::Yellow);
        shape.setPosition(x, y);
        velocity.y = 0.0f;
    }
    void update(float deltaTime) {
        velocity.y += GRAVITY * deltaTime;
        shape.move(0, velocity.y * deltaTime);

        if (shape.getPosition().y + shape.getSize().y > 800) {
            shape.setPosition(shape.getPosition().x, 800 - shape.getSize().y);
            velocity.y = 0;
        }
        if (shape.getPosition().y < 0) {
            shape.setPosition(shape.getPosition().x, 0);
            velocity.y = 0;
        }
    }

    void flap() {
        velocity.y = FLAP_FORCE;
    }

    sf::RectangleShape shape;
    sf::Vector2f velocity;
};

class Pipe {
public:
    Pipe(float x, float gapY) {
        topPipe.setSize(sf::Vector2f(PIPE_WIDTH, gapY));
        topPipe.setFillColor(sf::Color::Green);
        topPipe.setPosition(x, 0);

        bottomPipe.setSize(sf::Vector2f(PIPE_WIDTH, 800.0f - gapY - PIPE_GAP));
        bottomPipe.setFillColor(sf::Color::Green);
        bottomPipe.setPosition(x, gapY + PIPE_GAP);
    }

    void update(float deltaTime) {
        topPipe.move(-PIPE_SPEED * deltaTime, 0);
        bottomPipe.move(-PIPE_SPEED * deltaTime, 0);
    }

    sf::RectangleShape topPipe;
    sf::RectangleShape bottomPipe;
};

bool checkCollision(const sf::RectangleShape& bird, const sf::RectangleShape& pipe) {
    return bird.getGlobalBounds().intersects(pipe.getGlobalBounds());
}

int loadHighScore() {
    ifstream file(HIGH_SCORE_FILE);
    int highScore = 0;
    if (file.is_open()) {
        file >> highScore;
        file.close();
    }
    return highScore;
}

void saveHighScore(int score) {
    ofstream file(HIGH_SCORE_FILE);
    if (file.is_open()) {
        file << score;
        cout << score << endl;
        file.close();
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Flappy Bird");
    window.setFramerateLimit(120);

    Bird bird(150, 300);
    vector<Pipe> pipes;

    sf::Clock clock;
    sf::Time timeSinceLastSpawn = sf::Time::Zero;
    sf::Time gameOverTime = sf::Time::Zero;
    bool gameOver = false;

    srand(static_cast<unsigned>(time(nullptr)));

    int score = 0;
    int highScore = loadHighScore();

   
    sf::Texture gameOverTexture;
    if (!gameOverTexture.loadFromFile("./accest/gameOver.jpg")) {
        cerr << "Error loading game over texture" << endl;
        return 1;
    }

    sf::Sprite gameOverSprite;
    float xdir = 0, ydir = 0;
    gameOverSprite.setTexture(gameOverTexture);
    xdir = window.getSize().x / gameOverSprite.getGlobalBounds().width;
    ydir = window.getSize().y / gameOverSprite.getGlobalBounds().height;
    gameOverSprite.setScale(xdir, ydir); // Adjust position as needed

    
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("./accest/back.jpeg")) {
        cerr << "Error loading background texture" << endl;
        return 1;
    }

    sf::Sprite backgroundSprite;
    int xdire = 0, ydire = 0;
    backgroundSprite.setTexture(backgroundTexture);
    xdire = window.getSize().x/backgroundSprite.getGlobalBounds().width;
    ydire = window.getSize().y/backgroundSprite.getGlobalBounds().height;
    backgroundSprite.setPosition(sf::Vector2f(0.f, 0.f));
    backgroundSprite.setScale(xdire * 1.2,ydire * 1.3);


    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        timeSinceLastSpawn += deltaTime;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space && !gameOver) {
                    bird.flap();
                }
            }
        }

        if (!gameOver) {
            bird.update(deltaTime.asSeconds());

            if (timeSinceLastSpawn.asSeconds() > SPAWN_INTERVAL) {
                float gapY = static_cast<float>(rand() % (600 - static_cast<int>(PIPE_GAP)));
                pipes.emplace_back(800, gapY);
                timeSinceLastSpawn = sf::Time::Zero;
            }

            for (auto& pipe : pipes) {
                pipe.update(deltaTime.asSeconds());
            }

            pipes.erase(
                remove_if(pipes.begin(), pipes.end(), [](const Pipe& pipe) {
                    return pipe.topPipe.getPosition().x + PIPE_WIDTH < 0;
                    }),
                pipes.end()
            );

            for (const auto& pipe : pipes) {
                if (checkCollision(bird.shape, pipe.topPipe) || checkCollision(bird.shape, pipe.bottomPipe)) {
                    if (score > highScore) {
                        highScore = score;
                        saveHighScore(highScore);
                    }

                    gameOver = true;
                    gameOverTime = sf::Time::Zero;
                }
            }
        }
        else {
            gameOverTime += deltaTime;

            if (gameOverTime.asSeconds() > 1.0f) {
                window.close();
            }
        }

        window.clear();
        window.draw(backgroundSprite);
        window.draw(bird.shape);
        for (const auto& pipe : pipes) {
            window.draw(pipe.topPipe);
            window.draw(pipe.bottomPipe);
        }

        if (gameOver) {
            window.draw(gameOverSprite);
        }

        window.display();
    }

    return 0;
}
