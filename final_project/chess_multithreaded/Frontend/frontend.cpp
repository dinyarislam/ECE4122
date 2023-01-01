/*
Author: Dinyar Islam
Class: ECE4122

Description: Final Project

What is the purpose of this file?
Application that uses SFML to create a simple pacman game.
*/

#include <sstream>
#include <SFML/Graphics.hpp>
#include "iostream"
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
//#include "MtEngine.h"

using namespace sf;
using namespace std;

/*
 *  TIle class
 *  */
class Tile
{
public:
    Sprite tile; // tile sprite
    bool piecePresent = false; // does tile have a chess piece on it
    bool light; // type of tile light/dark
    std::string notation; // chess notation for tile
    // constructor
    Tile(){}
};

int main()
{
    // Create a video mode object
    VideoMode vm(1260, 1088);

    // Create and open a window for the game
    RenderWindow window(vm, "Chess");

    //ADD CODE
    // Create a video mode object for start menu
    VideoMode vm2(630, 544);

    // Create and open a window for the game start menu
    RenderWindow window2(vm2, "Start Menu");

    // Background for window2
    RectangleShape textureWindow2Background;
    textureWindow2Background.setFillColor(Color::Red);
    textureWindow2Background.setPosition(100,100);
    textureWindow2Background.setSize(Vector2f(625, 540));

    // start flag
    bool startFlag = false;
    //
    // Make the light tile texture
    Texture textureLightTile;
    textureLightTile.loadFromFile("../resources1/blue_light.jpeg");

    // Make the dark tile texture
    Texture textureDarkTile;
    textureDarkTile.loadFromFile("../resources1/blue_dark.jpeg");

    // Make movement board
    Texture textureMoveBoard;
    textureMoveBoard.loadFromFile("../resources1/move_record_gray.png");

    Sprite spriteMoveBoard;
    spriteMoveBoard.setTexture(textureMoveBoard);
    spriteMoveBoard.setScale(0.9, 1);
    spriteMoveBoard.setPosition(1088,5);

    // tile coordinates
    int light_tile_x = 0;
    int light_tile_y = 0;
    int dark_tile_x = 128;
    int dark_tile_y = 0;

    // light tiles
    Sprite lightTiles[32];
    for (int i = 0; i < 32; i++)
    {
        if (!(i % 8) && i != 0)
        {
            light_tile_x = 0;
        } else if (!(i % 4) && i != 0)
        {
            light_tile_x = 128;
        }
        if (!(i % 4) && i != 0)
        {
            light_tile_y += 128;
        }
        lightTiles[i].setTexture(textureLightTile);
        lightTiles[i].setScale(0.5,0.5);
        lightTiles[i].setPosition(light_tile_x, light_tile_y);
        light_tile_x += 256;
    }

    // dark tiles
    Sprite darkTiles[32];
    for (int i = 0; i < 32; i++)
    {
        if (!(i % 8) && i != 0)
        {
            dark_tile_x = 128;
        } else if (!(i % 4) && i != 0)
        {
            dark_tile_x = 0;
        }
        if (!(i % 4) && i != 0)
        {
            dark_tile_y += 128;
        }
        darkTiles[i].setTexture(textureDarkTile);
        darkTiles[i].setScale(0.5,0.5);
        darkTiles[i].setPosition(dark_tile_x, dark_tile_y);
        dark_tile_x += 256;
    }

    // vector for storing all tiles
    vector<Sprite> tiles;
    int lightTileIdx = 0;
    int darkTileIdx = 0;
    // starting from top left corner
    for (int i = 0; i < 64; i++)
    {
        if (i % 2)
        {
            tiles.push_back(darkTiles[darkTileIdx]);
            darkTileIdx++;
        }
        else
        {
            tiles.push_back(lightTiles[lightTileIdx]);
            lightTileIdx++;
        }
    }

    // vector for storing and initializing tile objects
    vector<Tile> tileObjs;
    Tile tempTileObj;
    int letterIdx = 1; // A - H for notation
    int numIdx = 8; // 1 - 8 for notation
    // starting from top left corner
    for (int i = 0; i < 64; i++)
    {
        // set tile sprite
        tempTileObj.tile = tiles[i];

        // does tile have a piece
        if (numIdx == 1 || numIdx == 2 || numIdx == 7 || numIdx == 8)
        {
            tempTileObj.piecePresent = true;
        }

        // set tile type
        if (i % 2)
        {
            tempTileObj.light = false;
        }
        else
        {
            tempTileObj.light = true;
        }

        // set notation
        if (letterIdx == 1)
        {
            tempTileObj.notation = "a" + to_string(numIdx);
        }
        else if (letterIdx == 2)
        {
            tempTileObj.notation = "b" + to_string(numIdx);
        }
        else if (letterIdx == 3)
        {
            tempTileObj.notation = "c" + to_string(numIdx);
        }
        else if (letterIdx == 4)
        {
            tempTileObj.notation = "d" + to_string(numIdx);
        }
        else if (letterIdx == 5)
        {
            tempTileObj.notation = "e" + to_string(numIdx);
        }
        else if (letterIdx == 6)
        {
            tempTileObj.notation = "f" + to_string(numIdx);
        }
        else if (letterIdx == 7)
        {
            tempTileObj.notation = "g" + to_string(numIdx);
        }
        else if (letterIdx == 8)
        {
            tempTileObj.notation = "h" + to_string(numIdx);
        }

        // add to vector
        tileObjs.push_back(tempTileObj);

        // update notation indices
        if ((i%8) == 7 && i != 0)
        {
            letterIdx = 1;
            numIdx--;
        }
        else
        {
            letterIdx++;
        }
    }

//    for (int i = 0; i < 64; i++)
//    {
//        std::cout << tileObjs[i].notation << endl;
//    }

    std::cout << tileObjs[63].notation << endl;
    // Make a white pieces
    Texture textureWhiteKing;
    Texture textureWhiteQueen;
    Texture textureWhiteRook;
    Texture textureWhiteBishop;
    Texture textureWhiteKnight;
    Texture textureWhitePawn;

    textureWhiteKing.loadFromFile("../resources2/WhiteKing.png");
    Sprite spriteWhiteKing;
    spriteWhiteKing.setTexture(textureWhiteKing);
    spriteWhiteKing.setScale(0.4, 0.4);
    spriteWhiteKing.setPosition(512,896);

    textureWhiteQueen.loadFromFile("../resources2/WhiteQueen.png");
    Sprite spriteWhiteQueen;
    spriteWhiteQueen.setTexture(textureWhiteQueen);
    spriteWhiteQueen.setScale(0.4, 0.4);
    spriteWhiteQueen.setPosition(384,896);

    textureWhiteRook.loadFromFile("../resources2/WhiteRook.png");
    Sprite spriteWhiteRookDark;
    spriteWhiteRookDark.setTexture(textureWhiteRook);
    spriteWhiteRookDark.setScale(0.4, 0.4);
    spriteWhiteRookDark.setPosition(0,896);
    Sprite spriteWhiteRookLight;
    spriteWhiteRookLight.setTexture(textureWhiteRook);
    spriteWhiteRookLight.setScale(0.4, 0.4);
    spriteWhiteRookLight.setPosition(896,896);

    textureWhiteBishop.loadFromFile("../resources2/WhiteBishop.png");
    Sprite spriteWhiteBishopDark;
    spriteWhiteBishopDark.setTexture(textureWhiteBishop);
    spriteWhiteBishopDark.setScale(0.4, 0.4);
    spriteWhiteBishopDark.setPosition(256,896);
    Sprite spriteWhiteBishopLight;
    spriteWhiteBishopLight.setTexture(textureWhiteBishop);
    spriteWhiteBishopLight.setScale(0.4, 0.4);
    spriteWhiteBishopLight.setPosition(640,896);

    textureWhiteKnight.loadFromFile("../resources2/WhiteKnight.png");
    Sprite spriteWhiteKnightDark;
    spriteWhiteKnightDark.setTexture(textureWhiteKnight);
    spriteWhiteKnightDark.setScale(0.4, 0.4);
    spriteWhiteKnightDark.setPosition(768,896);
    Sprite spriteWhiteKnightLight;
    spriteWhiteKnightLight.setTexture(textureWhiteKnight);
    spriteWhiteKnightLight.setScale(0.4, 0.4);
    spriteWhiteKnightLight.setPosition(128,896);

    textureWhitePawn.loadFromFile("../resources2/WhitePawn.png");
    Sprite spriteWhitePawn[8];
    int whitePawnX = 0;
    int whitePawnY = 0;
    for (int i = 0; i < 8; i++)
    {
        spriteWhitePawn[i].setTexture(textureWhitePawn);
        spriteWhitePawn[i].setScale(0.4,0.4);
        spriteWhitePawn[i].setPosition(whitePawnX, 768);
        whitePawnX += 128;
    }

    // Make black pieces
    Texture textureBlackKing;
    Texture textureBlackQueen;
    Texture textureBlackRook;
    Texture textureBlackBishop;
    Texture textureBlackKnight;
    Texture textureBlackPawn;

    textureBlackKing.loadFromFile("../resources2/BlackKing.png");
    Sprite spriteBlackKing;
    spriteBlackKing.setTexture(textureBlackKing);
    spriteBlackKing.setScale(0.4, 0.4);
    spriteBlackKing.setPosition(512,0);

    textureBlackQueen.loadFromFile("../resources2/BlackQueen.png");
    Sprite spriteBlackQueen;
    spriteBlackQueen.setTexture(textureBlackQueen);
    spriteBlackQueen.setScale(0.4, 0.4);
    spriteBlackQueen.setPosition(384,0);

    textureBlackRook.loadFromFile("../resources2/BlackRook.png");
    Sprite spriteBlackRookDark;
    spriteBlackRookDark.setTexture(textureBlackRook);
    spriteBlackRookDark.setScale(0.4, 0.4);
    spriteBlackRookDark.setPosition(896,0);
    Sprite spriteBlackRookLight;
    spriteBlackRookLight.setTexture(textureBlackRook);
    spriteBlackRookLight.setScale(0.4, 0.4);
    spriteBlackRookLight.setPosition(0,0);

    textureBlackBishop.loadFromFile("../resources2/BlackBishop.png");
    Sprite spriteBlackBishopDark;
    spriteBlackBishopDark.setTexture(textureBlackBishop);
    spriteBlackBishopDark.setScale(0.4, 0.4);
    spriteBlackBishopDark.setPosition(640,0);
    Sprite spriteBlackBishopLight;
    spriteBlackBishopLight.setTexture(textureBlackBishop);
    spriteBlackBishopLight.setScale(0.4, 0.4);
    spriteBlackBishopLight.setPosition(256,0);

    textureBlackKnight.loadFromFile("../resources2/BlackKnight.png");
    Sprite spriteBlackKnightDark;
    spriteBlackKnightDark.setTexture(textureBlackKnight);
    spriteBlackKnightDark.setScale(0.4, 0.4);
    spriteBlackKnightDark.setPosition(128,0);
    Sprite spriteBlackKnightLight;
    spriteBlackKnightLight.setTexture(textureBlackKnight);
    spriteBlackKnightLight.setScale(0.4, 0.4);
    spriteBlackKnightLight.setPosition(768,0);

    textureBlackPawn.loadFromFile("../resources2/BlackPawn.png");
    Sprite spriteBlackPawn[8];
    int blackPawnX = 0;
    int blackPawnY = 0;
    for (int i = 0; i < 8; i++)
    {
        spriteBlackPawn[i].setTexture(textureBlackPawn);
        spriteBlackPawn[i].setScale(0.4,0.4);
        spriteBlackPawn[i].setPosition(blackPawnX, 128);
        blackPawnX += 128;
    }

    // Make font
    Font font;
    font.loadFromFile("../fonts/Lekton-Bold.ttf");

    // ADD CODE
    // Make Title Text
    Text titleText;
    titleText.setString("Chess");
    titleText.setFont(font);
    titleText.setCharacterSize(100);
    titleText.setFillColor(Color::White);
    titleText.setOutlineColor(Color::Cyan);
    titleText.setOutlineThickness(4);
    titleText.setPosition(200,0);

    // Make start difficulty text
    int difficultyLevel = 0;
    bool difficultySelected = false;
    Text difficultyLevelText;
    difficultyLevelText.setFont(font);
    difficultyLevelText.setCharacterSize(30);
    difficultyLevelText.setString("Enter Difficulty Level using number pad:"
                              "\n\n     1      2      3      4      5"
                              "\n    Easy         Medium         Hard");
    difficultyLevelText.setPosition(10,400);
    difficultyLevelText.setFillColor(Color::Yellow);
    //

    // ADD CODE
    // Make board texture text
    bool textureSelected = false;
    std::string textureInputStr;
    Text textureChoiceText;
    textureChoiceText.setFont(font);
    textureChoiceText.setCharacterSize(30);
    textureChoiceText.setString("        Choose tile texture type:");
    textureChoiceText.setPosition(10,200);
    textureChoiceText.setFillColor(Color::White);

    Text textureChoiceTextBlue;
    textureChoiceTextBlue.setFont(font);
    textureChoiceTextBlue.setCharacterSize(30);
    textureChoiceTextBlue.setString("       BLUE(b)");
    textureChoiceTextBlue.setPosition(10,250);
    textureChoiceTextBlue.setFillColor(Color::Blue);


    Text textureChoiceTextBrown;
    textureChoiceTextBrown.setFont(font);
    textureChoiceTextBrown.setCharacterSize(30);
    textureChoiceTextBrown.setString("        RED(r)");
    textureChoiceTextBrown.setPosition(180,250);
    textureChoiceTextBrown.setFillColor(Color::Red);

    Text textureChoiceTextGray;
    textureChoiceTextGray.setFont(font);
    textureChoiceTextGray.setCharacterSize(30);
    textureChoiceTextGray.setString("        GRAY(g)");
    textureChoiceTextGray.setPosition(320,250);
    textureChoiceTextGray.setFillColor(Color::White);
    //

    // ADD CODE
    // Make piece shadow text
    bool pieceShadowSelected = false;
    Text pieceShadowText;
    pieceShadowText.setFont(font);
    pieceShadowText.setCharacterSize(30);
    pieceShadowText.setString("        Choose piece texture type:"
                              "\n        Shadow(s)     No Shadow(N)");
    pieceShadowText.setPosition(10,310);
    pieceShadowText.setFillColor(Color::White);

    // Make piece color text
    bool pieceColorSelected = false;
    Text pieceColorText;
    pieceColorText.setFont(font);
    pieceColorText.setCharacterSize(30);
    pieceColorText.setString("               Choose color:"
                             "\n            White(w)     Black(b)");
    pieceColorText.setPosition(10,120);
    pieceColorText.setFillColor(Color::White);


    // board text
    Text boardText[16];
    int boardTextX = 1044;
    int boardTextY = 64;
    for (int i = 0; i < 8; i++)
    {
        boardText[i].setFont(font);
        if (i == 0)
        {
            boardText[i].setString("8");
        }
        else if (i == 1)
        {
            boardText[i].setString("7");
        }
        else if (i == 2)
        {
            boardText[i].setString("6");
        }
        else if (i == 3)
        {
            boardText[i].setString("5");
        }
        else if (i == 4)
        {
            boardText[i].setString("4");
        }
        else if (i == 5)
        {
            boardText[i].setString("3");
        }
        else if (i == 6)
        {
            boardText[i].setString("2");
        }
        else if (i == 7)
        {
            boardText[i].setString("1");
        }
        boardText[i].setCharacterSize(20);
        boardText[i].setPosition(boardTextX, boardTextY);
        boardTextY += 128;
    }
    boardTextX = 64;
    boardTextY = 1044;
    for (int i = 8; i < 16; i++)
    {
        boardText[i].setFont(font);
        if (i == 8)
        {
            boardText[i].setString("a");
        }
        else if (i == 9)
        {
            boardText[i].setString("b");
        }
        else if (i == 10)
        {
            boardText[i].setString("c");
        }
        else if (i == 11)
        {
            boardText[i].setString("d");
        }
        else if (i == 12)
        {
            boardText[i].setString("e");
        }
        else if (i == 13)
        {
            boardText[i].setString("f");
        }
        else if (i == 14)
        {
            boardText[i].setString("g");
        }
        else if (i == 15)
        {
            boardText[i].setString("h");
        }
        boardText[i].setCharacterSize(20);
        boardText[i].setPosition(boardTextX, boardTextY);
        boardTextX += 128;
    }

    //
    RectangleShape selectTile;
    selectTile.setFillColor(Color::Transparent);
    selectTile.setOutlineColor(Color::Red);
    selectTile.setOutlineThickness(5);
    selectTile.setPosition(2000, 2000);
    selectTile.setSize(Vector2f(128,128));

    //mte::Engine eng;

    // when window is open
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();


            // check which tile was clicked
            if (event.type == sf::Event::MouseButtonPressed)
            {
                for (int i = 0; i < 64; i++)
                {
                    if (tileObjs[i].tile.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        selectTile.setPosition(tileObjs[i].tile.getPosition().x, tileObjs[i].tile.getPosition().y);
                        cout << tileObjs[i].notation << endl;
                        printf("%f,%f\n", tileObjs[i].tile.getPosition().x, tileObjs[i].tile.getPosition().y);
                    }
                }
            }
        }
        //ADD CODE
        while (window2.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window2.close();
        }

        window2.clear();
        //

        window.clear();

        //Draw tiles
        for (int i = 0; i < 64; i++)
        {
            window.draw(tileObjs[i].tile);
        }

        // Draw white pieces
        window.draw(spriteWhiteKing);
        window.draw(spriteWhiteQueen);
        window.draw(spriteWhiteRookDark);
        window.draw(spriteWhiteRookLight);
        window.draw(spriteWhiteBishopDark);
        window.draw(spriteWhiteBishopLight);
        window.draw(spriteWhiteKnightDark);
        window.draw(spriteWhiteKnightLight);
        for (int i = 0; i < 8; i++)
        {
            window.draw(spriteWhitePawn[i]);
        }

        //Draw black pieces
        window.draw(spriteBlackKing);
        window.draw(spriteBlackQueen);
        window.draw(spriteBlackRookDark);
        window.draw(spriteBlackRookLight);
        window.draw(spriteBlackBishopDark);
        window.draw(spriteBlackBishopLight);
        window.draw(spriteBlackKnightDark);
        window.draw(spriteBlackKnightLight);
        for (int i = 0; i < 8; i++)
        {
            window.draw(spriteBlackPawn[i]);
        }

        // Draw board text
        for (int i = 0; i < 16; i++)
        {
            window.draw(boardText[i]);
        }
        // Draw Movement board
        window.draw(spriteMoveBoard);

        // Draw selection tile
        window.draw(selectTile);

        // ADD CODE
        // close start menu
        if (difficultySelected && Keyboard::isKeyPressed(Keyboard::Return))
        {
            startFlag = true;
            window2.close();
        } else {
            window2.draw(difficultyLevelText);
            window2.draw(textureChoiceText);
            window2.draw(textureChoiceTextBlue);
            window2.draw(textureChoiceTextBrown);
            window2.draw(textureChoiceTextGray);
            window2.draw(pieceShadowText);
            window2.draw(pieceColorText);
            window2.draw(titleText);
            if (!pieceColorSelected)
            {
                if (Keyboard::isKeyPressed(Keyboard::B)) {
                    pieceColorSelected = true;
                    //playerColourWhite = false;
                    pieceColorText.setString("               Choose color\n                   Black");
                } else if (Keyboard::isKeyPressed(Keyboard::W)) {
                    pieceColorSelected = true;
                    //playerColourWhite = true;
                }
            }
            if (!textureSelected)
            {
                if (Keyboard::isKeyPressed(Keyboard::B)) {
                    textureInputStr = "blue";
                    textureSelected = true;
                    textureChoiceTextBrown.setFillColor(Color::Transparent);
                    textureChoiceTextGray.setFillColor(Color::Transparent);
                    difficultyLevelText.setOutlineColor(Color::Blue);
                } else if (Keyboard::isKeyPressed(Keyboard::R)) {
                    textureInputStr = "red";
                    textureSelected = true;
                    textureChoiceTextBlue.setFillColor(Color::Transparent);
                    textureChoiceTextGray.setFillColor(Color::Transparent);
                    difficultyLevelText.setOutlineColor(Color::Red);
                    textureLightTile.loadFromFile("../resources1/brown_light.jpeg");
                    textureDarkTile.loadFromFile("../resources1/brown_dark.jpeg");
                } else if (Keyboard::isKeyPressed(Keyboard::G)) {
                    textureInputStr = "gray";
                    textureSelected = true;
                    textureChoiceTextBrown.setFillColor(Color::Transparent);
                    textureChoiceTextBlue.setFillColor(Color::Transparent);
                    difficultyLevelText.setOutlineColor(Color::White);
                    textureLightTile.loadFromFile("../resources1/gray_light.jpeg");
                    textureDarkTile.loadFromFile("../resources1/gray_dark.jpeg");
                }
            }
            if (!pieceShadowSelected)
            {
                if (Keyboard::isKeyPressed(Keyboard::S)) {
                    pieceShadowSelected =true;
                    pieceShadowText.setString("        Choose piece texture type:"
                                              "\n                 Shadow(s)");
                    textureWhiteKing.loadFromFile("../resources2/w_king_png_shadow_256px.png");
                    spriteWhiteKing.setScale(0.5,0.5);
                    textureWhiteQueen.loadFromFile("../resources2/w_queen_png_shadow_256px.png");
                    spriteWhiteQueen.setScale(0.5,0.5);
                    textureWhiteBishop.loadFromFile("../resources2/w_bishop_png_shadow_256px.png");
                    spriteWhiteBishopLight.setScale(0.5,0.5);
                    spriteWhiteBishopDark.setScale(0.5,0.5);
                    textureWhiteRook.loadFromFile("../resources2/w_rook_png_shadow_256px.png");
                    spriteWhiteRookLight.setScale(0.5,0.5);
                    spriteWhiteRookDark.setScale(0.5,0.5);
                    textureWhiteKnight.loadFromFile("../resources2/w_knight_png_shadow_256px.png");
                    spriteWhiteKnightLight.setScale(0.5,0.5);
                    spriteWhiteKnightDark.setScale(0.5,0.5);
                    textureWhitePawn.loadFromFile("../resources2/w_pawn_png_shadow_256px.png");
                    for (int i = 0; i < 8; i++)
                    {
                        spriteWhitePawn[i].setScale(0.5,0.5);
                    }

                    textureBlackKing.loadFromFile("../resources2/b_king_png_shadow_256px.png");
                    spriteBlackKing.setScale(0.5,0.5);
                    textureBlackQueen.loadFromFile("../resources2/b_queen_png_shadow_256px.png");
                    spriteBlackQueen.setScale(0.5,0.5);
                    textureBlackBishop.loadFromFile("../resources2/b_bishop_png_shadow_256px.png");
                    spriteBlackBishopLight.setScale(0.5,0.5);
                    spriteBlackBishopDark.setScale(0.5,0.5);
                    textureBlackRook.loadFromFile("../resources2/b_rook_png_shadow_256px.png");
                    spriteBlackRookLight.setScale(0.5,0.5);
                    spriteBlackRookDark.setScale(0.5,0.5);
                    textureBlackKnight.loadFromFile("../resources2/b_knight_png_shadow_256px.png");
                    spriteBlackKnightLight.setScale(0.5,0.5);
                    spriteBlackKnightDark.setScale(0.5,0.5);
                    textureBlackPawn.loadFromFile("../resources2/b_pawn_png_shadow_256px.png");
                    for (int i = 0; i < 8; i++)
                    {
                        spriteBlackPawn[i].setScale(0.5,0.5);
                    }

                } else if (Keyboard::isKeyPressed(Keyboard::N)) {
                    pieceShadowSelected =true;
                    pieceShadowText.setString("        Choose piece texture type:"
                                              "\n               No Shadow(s)");
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Num1))
            {
                difficultyLevel = 1 + 1;
            } else if (Keyboard::isKeyPressed(Keyboard::Num2)) {
                difficultyLevel = 2 + 1;
            } else if (Keyboard::isKeyPressed(Keyboard::Num3)) {
                difficultyLevel = 3 + 1;
            } else if (Keyboard::isKeyPressed(Keyboard::Num4)) {
                difficultyLevel = 4 + 1;
            } else if (Keyboard::isKeyPressed(Keyboard::Num5)) {
                difficultyLevel = 5 + 1;
            }
            if (pieceColorSelected && textureSelected && pieceShadowSelected && !difficultySelected && difficultyLevel > 0)
            {
                difficultySelected = true;
                textureChoiceText.setFillColor(Color::Transparent);
                textureChoiceTextBrown.setFillColor(Color::Transparent);
                textureChoiceTextBlue.setFillColor(Color::Transparent);
                textureChoiceTextGray.setFillColor(Color::Transparent);
                pieceShadowText.setFillColor(Color::Transparent);
                pieceColorText.setFillColor(Color::Transparent);
                difficultyLevelText.setString("PRESS ENTER TO START"
                                              "\n\n     Color: " + textureInputStr + "\n    Difficulty: " + to_string(difficultyLevel - 1));
                difficultyLevelText.setCharacterSize(50);
                difficultyLevelText.setPosition(70, 200);
                difficultyLevelText.setOutlineThickness(2);
            }
        }
        window2.display();
        //

        window.display();
    }
}