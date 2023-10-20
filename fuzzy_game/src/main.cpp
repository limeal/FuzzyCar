/*
** KOREA UNIVERSITY PROJECT, 2023
** FuzzyCar
** File description:
** main
*/

#include <iostream>
#include <vector>

// ./fuzzy map1.txt
#include "functional/Map.hpp"
#include "functional/Game.hpp"

int main(int ac, char **av) {
    
    if (ac != 2) {
        std::cerr << "Usage: " << av[0] << " <map>" << std::endl;
        return 84;
    }

    Fuzzy::Map map(av[1]);
    Fuzzy::Game game(map);
    
    //map.print();
    game.start();
    return 0;
}