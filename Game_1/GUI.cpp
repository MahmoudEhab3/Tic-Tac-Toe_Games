#include<string>
#include <vector>
#include "BoardGame_Classes.hpp"
using namespace std ;

bool isPointInsideRect(const sf::Vector2i& point, const sf::RectangleShape& rect) {
    sf::Vector2f rectPos = rect.getPosition();
    sf::Vector2f rectSize = rect.getSize();

    return (point.x >= rectPos.x && point.x <= rectPos.x + rectSize.x &&
            point.y >= rectPos.y && point.y <= rectPos.y + rectSize.y);
}

int minimax(X_O_Board& board, int depth, bool isMaximizing) {
    if (board.is_winner()) {
        return isMaximizing ? -1 : 1;
    } else if (board.is_draw()) {
        return 0;
    }

    if (isMaximizing) {
        int bestScore = -1000;
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 5; y++) {
                if (board.is_valid_move(x, y)) {
                    board.update_board(x, y, 'X');
                    int score = minimax(board, depth + 1, false);
                    board.remove_board(x, y);
                    bestScore = std::max(score, bestScore);
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 5; y++) {
                if (board.is_valid_move(x, y)) {
                    board.update_board(x, y, 'O');
                    int score = minimax(board, depth + 1, true);
                    board.remove_board(x, y);
                    bestScore = std::min(score, bestScore);
                }
            }
        }
        return bestScore;
    }
}

void win_draw_over( sf::RenderWindow& screen , bool win , bool draw  , char winner ){
    screen.setTitle("Results") ;
    sf::Text inputText;
    sf::Font font ; font.loadFromFile("TTF.ttf") ;

    inputText.setFont(font) ;
    inputText.setCharacterSize(40);
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition(310, 260);
    if ( win ){
        ( winner == 'X' ) ? inputText.setString( "PLayer X wins !" ) : inputText.setString("Player O wins !") ;
    } else if ( draw ) {
        inputText.setString("The Gamed ended in A draw ") ;
    }

    while ( screen.isOpen() ){
        sf::Event evnt ;
        while ( screen.pollEvent(evnt) ) {
            switch (evnt.type) {
                case sf::Event::Closed :
                    screen.close() ;
                    break;
                case sf::Event::MouseButtonPressed :
                    screen.close() ;
                    break;
            }
        }
        screen.clear() ;
        screen.draw(inputText) ;
        screen.display() ;
    }
}

void game_1 ( sf::RenderWindow& screen , int is_ai ) {
    screen.setTitle("normal XO game by Dr Mohamed El Ramly ") ;
    vector<vector<sf::RectangleShape>> blocks ( 3 , vector<sf::RectangleShape> ( 3 , sf::RectangleShape( sf::Vector2f(100.0f , 100.0f)) ) ) ;
    X_O_Board board ;

    float total_x = 3 * ( 100 + 30 ) - 30 ;
    float total_y = 3 * ( 100 + 30 ) - 30 ;

    float start_x = ( screen.getSize().x - total_x ) / 2.0f ;
    float start_y = ( screen.getSize().y - total_y ) / 2.0f ;

    for ( int i = 0 ; i < 3 ; i++ ){
        for ( int j = 0 ; j < 3 ; j++ ){
            blocks[i][j].setPosition( start_x + (j * ( 130.0f )) , start_y + i * ( 130.0f ) ) ;
        }
    }

    sf::Texture textures[2] { sf::Texture() , sf::Texture() } ;
    textures[0].loadFromFile( "../textures/X.png") ;
    textures[1].loadFromFile( "../textures/O.png") ;
    char player[2] = { 'X' , 'O' }; bool turn = false ;

    bool draw = false , win = false , AI = ( is_ai == 2 );
    while ( screen.isOpen() && !draw && !win  ){
        sf::Event evnt ;
        while ( screen.pollEvent(evnt)){
            switch (evnt.type) {
                case sf::Event::Closed :
                    screen.close() ;
                    break;
                case sf::Event::MouseButtonPressed :
                    for ( int i = 0 ; i < 3 ; i++ ){
                        for ( int j = 0 ; j < 3 ; j++ ){
                            if (isPointInsideRect( sf::Mouse::getPosition(screen) , blocks[i][j] ) ){
                                if ( board.update_board( i , j , player[turn] ) ){
                                    blocks[i][j].setTexture(&textures[turn]) ;
                                    turn = !turn ;
                                }
                            }
                        }
                    }
                    break;
            }
        }
        if ( AI && turn && !board.game_is_over() ) {
            while ( turn) {
                int x = (int) (rand() / (RAND_MAX + 1.0) * 3);
                int y = (int) (rand() / (RAND_MAX + 1.0) * 3);
                if (board.update_board(x, y, player[turn])) {
                    blocks[x][y].setTexture(&textures[turn]);
                    turn = !turn ;
                }
            }
        }

        for ( int i = 0 ; i < 3 ; i++ ){
            for ( int j = 0 ; j < 3 ; j++ ) {
                if (isPointInsideRect(sf::Mouse::getPosition(screen), blocks[i][j])) {
                    blocks[i][j].setFillColor(sf::Color::Green);
                } else {
                    blocks[i][j].setFillColor(sf::Color::White);
                }
            }
        }
        if ( board.is_winner() ) {
            win = true ;
        }
        if ( board.is_draw() ) {
            draw = true ;
        }

        screen.clear() ;
        for ( int i = 0 ; i < 3 ; i++ ){
            for ( int j = 0 ; j < 3 ; j++ ) {
                screen.draw(blocks[i][j]);
            }
        }
        screen.display() ;
    }
    win_draw_over( screen , win , draw  , player[!turn] ) ;
}

void game_2 ( sf::RenderWindow& window , int is_ai ) {
    window.setTitle("pyramidic XO game by Elkholy id:20220037") ;

    const int cubeSize = 100 ;
    const int gap = 30 ;
    const int rows = 3;
    const int columns = 5;

    sf::Texture X ; X.loadFromFile( "X.png") ;
    sf::Texture O ; O.loadFromFile( "O.png") ;

    std::vector<std::vector<sf::RectangleShape>> cubes ( rows , std::vector<sf::RectangleShape>( columns , sf::RectangleShape() ) ) ;

    float totalWidth = columns * (cubeSize + gap) - gap;
    float totalHeight = rows * (cubeSize + gap) - gap;


    float startX = (window.getSize().x - totalWidth) / 2.0f;
    float startY = (window.getSize().y - totalHeight) / 2.0f;

    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < columns; ++column) {
            if ( column < 2 - row || column > 2 + row )
                continue;
            sf::RectangleShape cube(sf::Vector2f(cubeSize, cubeSize));
            cube.setPosition(startX + (cubeSize + gap) * column, startY + (cubeSize + gap) * row);
            cubes[row][column] = cube ;
        }
    }
    X_O_Board board ;

    sf::Texture textures[2] { sf::Texture() , sf::Texture() } ;
    textures[0].loadFromFile( "../textures/X.png") ;
    textures[1].loadFromFile( "../textures/O.png") ;
    char player[2] = { 'X' , 'O' }; bool turn = false ;
    bool win = false , draw = false , AI = ( is_ai == 2 );
    while (window.isOpen() && !win && !draw ) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if ( event.type == sf::Event::MouseButtonPressed ){
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 5 ; ++j) {
                            if (isPointInsideRect(sf::Mouse::getPosition(window), cubes[i][j])) {
                                if (board.update_board(i, j, player[turn])) {
                                    cubes[i][j].setTexture(&textures[turn]);
                                    turn =!turn;
                                }
                            }
                    }
                }
            }
        }
        if ( board.is_winner() ) {
            win = true ;
            break;
        }
        if ( AI && turn && !board.game_is_over() ) {
            // Initialize best score to negative infinity and best move to an invalid move
            int bestScore = -1000;
            std::pair<int, int> bestMove = {-1, -1};

            // Loop through all cells
            for (int x = 0; x < 3; x++) {
                for (int y = 0; y < 5; y++) {
                    // Check if the cell is empty
                    if (board.is_valid_move(x, y)) {
                        // Make the move
                        board.update_board(x, y, player[turn]);

                        // Compute the score of the current board state
                        int score = minimax(board, 0, false);

                        // Undo the move
                        board.remove_board(x, y);

                        // If the computed score is greater than the best score, update the best score and best move
                        if (score > bestScore) {
                            bestScore = score;
                            bestMove = {x, y};
                        }
                    }
                }
            }

            // Make the best move
            if (bestMove.first != -1 && bestMove.second != -1) {
                board.update_board(bestMove.first, bestMove.second, player[turn]);
                cubes[bestMove.first][bestMove.second].setTexture(&textures[turn]);
                turn = !turn;
            }
        }


        for ( int i = 0 ; i < 3 ; i++ ){
            for ( int j = 0 ; j < 5 ; j++ ) {
                if (isPointInsideRect(sf::Mouse::getPosition(window), cubes[i][j])) {
                    cubes[i][j].setFillColor(sf::Color::Green);
                } else {
                    cubes[i][j].setFillColor(sf::Color::White);
                }
            }
        }

        if ( board.is_winner() ) {
            win = true ;
        }
        if ( board.is_draw() ) {
            draw = true ;
        }

        window.clear();

        for ( auto cube : cubes ){
            for ( auto cube_ : cube ){
                window.draw(cube_) ;
            }
        }

        window.display();
    }

    win_draw_over( window , win , draw ,  player[!turn] ) ;
}



int main() {

    // window for choosing the game ;

    int chc {0} ;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Choose a game" , sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize  );

    vector<sf::RectangleShape> games ;
    games.emplace_back( sf::Vector2f ( 100.0f , 100.0f ) ) ;
    games.emplace_back( sf::Vector2f ( 100.0f , 100.0f ) ) ;
    games.emplace_back( sf::Vector2f ( 100.0f , 100.0f ) ) ;
    games.emplace_back( sf::Vector2f ( 100.0f , 100.0f ) ) ;

    vector<sf::Texture> textures ;
    sf::Texture game1 ; game1.loadFromFile( "../textures/Game1.png") ;
    textures.push_back(game1) ;
    sf::Texture game2 ; game2.loadFromFile( "../textures/Game2.png") ;
    textures.push_back(game2) ;
    sf::Texture game3 ; game3.loadFromFile( "../textures/Game3.png") ;
    textures.push_back(game3) ;
    sf::Texture game4 ; game4.loadFromFile( "../textures/Game4.png") ;
    textures.push_back(game4) ;

    float total_w = 4 * ( 100 + 50 ) - 50 ;
    float total_h = 100 ;

    float start_x = ( window.getSize().x - total_w ) / 2.0f ;
    float start_y = ( window.getSize().y - total_h ) / 2.0f ;

    for ( int i = 0 ; i < 4 ; i++ ){
        games[i].setPosition( start_x + ( 150 ) * i , start_y ) ;
        games[i].setTexture(&textures[i]) ;
    }

    while ( window.isOpen() && !chc ) {
        sf::Event evnt ;
        while ( window.pollEvent(evnt) ) {
            switch (evnt.type) {
                case sf::Event::Closed  :
                    window.close() ;
                    break;
                case sf::Event::MouseButtonPressed :
                    for ( int i = 0 ; i < 4 ; i++ ){
                        if ( isPointInsideRect( sf::Mouse::getPosition(window) , games[i] ) ){
                            chc = i + 1 ;
                        }
                    }
                    break;
            }
        }

        for ( int i = 0 ; i < 4 ; i++ ){
            if ( isPointInsideRect( sf::Mouse::getPosition(window) , games[i] ) ){
                games[i].setFillColor( sf::Color::Green ) ;
            } else {
                games[i].setFillColor( sf::Color::White ) ;
            }
        }
        window.clear() ;
        for ( int i = 0 ; i < 4 ; i++ ){
            window.draw(games[i]) ;
        }
        window.display() ;
    }

    vector<sf::RectangleShape> human_AI ;
    human_AI.emplace_back( sf::Vector2f ( 100.0f , 100.0f ) ) ;
    human_AI.emplace_back( sf::Vector2f ( 100.0f , 100.0f ) ) ;

    vector<sf::Texture> hu_Ai_texture ;
    sf::Texture human ; human.loadFromFile("../textures/human.png") ;
    sf::Texture Ai ; Ai.loadFromFile("../textures/ai.png") ;
    hu_Ai_texture.push_back(human) ;
    hu_Ai_texture.push_back(Ai) ;

    for ( int i = 0 ; i < 2 ; i++ ){
        human_AI[i].setTexture(&hu_Ai_texture[i]) ;
    }

    total_w = 2 * ( 100 + 50 ) - 50 ;
    total_h = 100 ;

    start_x = ( window.getSize().x - total_w ) / 2.0f ;
    start_y = ( window.getSize().y - total_h ) / 2.0f ;

    for ( int i = 0 ; i < 2 ; i++ ){
        human_AI[i].setPosition( start_x + (float)i * ( 150.0f ) , start_y ) ;
    }

    int is_ai = 0 ;
    while ( window.isOpen() && !is_ai ) {
        sf::Event evnt ;
        while ( window.pollEvent(evnt) ){
            switch ( evnt.type )  {
                case sf::Event::Closed :
                    window.close() ;
                    break;
                case sf::Event::MouseButtonPressed :
                    for ( int i = 0 ; i < human_AI.size() ; i++ ){
                        if (isPointInsideRect( sf::Mouse::getPosition( window ) , human_AI[i] )) {
                            if ( i == 0 ){
                                is_ai = 1 ;
                            } else {
                                is_ai = 2 ;
                            }
                        }
                    }
            }
        }
        for ( int i = 0 ; i < 2 ; i++ ){
            if ( isPointInsideRect( sf::Mouse::getPosition(window) , human_AI[i] ) ){
                human_AI[i].setFillColor( sf::Color::Green ) ;
            } else {
                human_AI[i].setFillColor( sf::Color::White ) ;
            }
        }
        window.clear() ;
        for ( int i = 0 ; i < 2 ; i++ ){
            window.draw(human_AI[i]) ;
        }
        window.display() ;
    }

    if ( !chc )
        return 0 ;

    switch (chc) {
        case 1 :
            game_1(window , is_ai ) ;
            break;
        case 2 :
            game_2(window , is_ai ) ;
            break;
        case 3 :
            break;
        case 4 :
            break;
        default:
            break;
    }
    return 0 ;
}

