#pragma once
#include <iostream>
#include <ctime>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class Menu {
public:
    Font font;
    Text title;
    Text crawlText;
    Text options[4];
    Sprite leftWing;
    Sprite rightWing;
    SoundBuffer buffer;
    Sound sound;

    Menu();
    void display_menu();
};

Menu::Menu()
{
    font.loadFromFile("assets/fonts/spaceage.ttf");
    title.setFont(font);
    title.setString("SPACE INVADER");
    title.setCharacterSize(72);
    title.setFillColor(Color::White);
    title.setPosition(200, 300);

    font.loadFromFile("assets/fonts/TradeGothicBold.ttf");
    crawlText.setFont(font);
    crawlText.setString("IT IS A PERIOD OF CIVIL WAR...");
    crawlText.setCharacterSize(24);
    crawlText.setFillColor(Color::Yellow);
    crawlText.setPosition(275, 400);

    options[0].setFont(font);
    options[0].setString("New Game");
    options[0].setCharacterSize(48);
    options[0].setFillColor(Color::White);
    options[0].setPosition(300, 400);

    options[1].setFont(font);
    options[1].setString("Highscores");
    options[1].setCharacterSize(48);
    options[1].setFillColor(Color::White);
    options[1].setPosition(295, 475);

    options[2].setFont(font);
    options[2].setString("View Credits");
    options[2].setCharacterSize(48);
    options[2].setFillColor(Color::White);
    options[2].setPosition(280, 550);

    options[3].setFont(font);
    options[3].setString("Exit");
    options[3].setCharacterSize(48);
    options[3].setFillColor(Color::White);
    options[3].setPosition(363, 625);

    Texture tex;

    buffer.loadFromFile("assets/sounds/selectOption.wav");
    sound.setBuffer(buffer);
}

void Menu::display_menu() {
    RenderWindow window(VideoMode(800, 800), "Space Shooter");

    Image cursorImage;
    cursorImage.loadFromFile("assets/images/cursor.png");
    Cursor cursor;
    cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), { 0, 0 });
    window.setMouseCursor(cursor);

    FloatRect titleRect = title.getLocalBounds();
    title.setPosition(400 - titleRect.width / 2, 100);

    // Starwars
    crawlText.setString(R"(
Our         galaxy      is         attacked by  enemies.

The enemy invaders beat our squad, they destroyed all of

galactica.     

Space team  is  waiting   for your order.

Please command       the      ship to protect the galaxy

and     the                  surrounding      asteroids.

)");

    crawlText.setFillColor(Color::Yellow);
    crawlText.setCharacterSize(24);
    crawlText.setPosition(400, 700);
    crawlText.setOrigin(crawlText.getLocalBounds().width / 2, 0);

    float crawlSpeed = 1.0f;
    float crawlPosY = 800.0;

    
    while (crawlText.getPosition().y > -crawlText.getLocalBounds().height) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        crawlPosY -= crawlSpeed;
        crawlText.setPosition(400, crawlPosY);

        window.clear();
        window.draw(crawlText);
        window.draw(title);
        window.display();

    }

    Clock clock;
    RectangleShape fade;
    fade.setPosition(Vector2f(0, 0));
    fade.setFillColor(Color(0, 0, 0, 0));
    fade.setSize(Vector2f(800, 600));
    for (int i = 0; i <= 255; i++) {
        fade.setFillColor(Color(0, 0, 0, i));
        window.draw(fade);
        window.display();
        sleep(seconds(0.01));
        clock.restart();
    }

    for (int i = 255; i >= 0; i--) {
        fade.setFillColor(Color(0, 0, 0, i));
        window.draw(fade);
        window.display();
        clock.restart();
    }

    int selectedOption = 0;
    Text tempOptions[4];
    for (int i = 0; i < 4; i++) {
        tempOptions[i] = options[i];
    }
    tempOptions[selectedOption].setFillColor(Color::Cyan);

    std::string playerName;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Up) {
                    sound.play();
                    if (selectedOption > 0) {
                        selectedOption--;
                    }
                }
                if (event.key.code == Keyboard::Down) {
                    sound.play();
                    if (selectedOption < 3) {
                        selectedOption++;
                    }
                }
                if (event.key.code == Keyboard::Return) {
                    switch (selectedOption) {
                    case 0:
                        // Do start game
                        window.close();
                        break;
                    case 1:
                        // Do highscores
                        break;
                    case 2:
                        // Do credits
                        break;
                    case 3:
                        window.close();
                        break;
                    }
                }
            }
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePosition = Mouse::getPosition(window);
                    if (mousePosition.x >= options[0].getPosition().x && mousePosition.x <= options[0].getPosition().x + options[0].getLocalBounds().width &&
                        mousePosition.y >= options[0].getPosition().y && mousePosition.y <= options[0].getPosition().y + options[0].getLocalBounds().height) {
                        window.close();
                        // Do start game
                    }

                    if (mousePosition.x >= options[1].getPosition().x && mousePosition.x <= options[1].getPosition().x + options[1].getLocalBounds().width &&
                        mousePosition.y >= options[1].getPosition().y && mousePosition.y <= options[1].getPosition().y + options[1].getLocalBounds().height) {
                        // Do highscore
                    }

                    if (mousePosition.x >= options[2].getPosition().x && mousePosition.x <= options[2].getPosition().x + options[2].getLocalBounds().width &&
                        mousePosition.y >= options[2].getPosition().y && mousePosition.y <= options[2].getPosition().y + options[2].getLocalBounds().height) {
                        // Do credits
                    }

                    if (mousePosition.x >= options[3].getPosition().x && mousePosition.x <= options[3].getPosition().x + options[3].getLocalBounds().width &&
                        mousePosition.y >= options[3].getPosition().y && mousePosition.y <= options[3].getPosition().y + options[3].getLocalBounds().height) {
                        window.close();
                    }
                }
            }
        }

        for (int i = 0; i < 4; i++) {
            if (i == selectedOption) {
                tempOptions[i].setFillColor(Color::Cyan);
            }
            else {
                tempOptions[i].setFillColor(Color::White);
            }
        }

        window.clear();
        window.draw(title);
        for (int i = 0; i < 4; i++) {
            if (i == selectedOption) {
                options[i].setFillColor(Color::Cyan);
            }
            else {
                options[i].setFillColor(Color::White);
            }
            window.draw(options[i]);
        }
        
        window.display();
    }
}
