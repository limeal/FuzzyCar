/*
** KOREA UNIVERSITY PROJECT, 2023
** FuzzyCar
** File description:
** main
*/

#include <iostream>
#include <vector>

#include "Fuzzy.hpp"

int usage() {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "FuzzyCar - Help" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Usage: ./FuzzyCar <level_path> [options]" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -h, --help: Display help" << std::endl;
    std::cout << "  -s, --size x y: Set window size" << std::endl;
    std::cout << "  -p, --player path_to_progam.py: Enable AI" << std::endl;
    std::cout << "  -f, --fps fps: Set FPS" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    return 0;
}

int main(int ac, char **av) {

    // TODO: Manage options:
    // -h, --help: Display help
    // -s, --size x y: Set window size
    // -p, --player path_to_progam.py: Enable AI
    // -f, --fps fps: Set FPS

    if (ac < 2) return usage();

    try {
        SDL::Core::Init({
            std::make_shared<SDL::SDLImage>(),
            std::make_shared<SDL::SDLTtf>(),
            std::make_shared<SDL::SDLMixer>()
        });

        Fuzzy::Assets::Load();

        Fuzzy::Fuzzy fuzzy(av[1], SDL::Vector2i(512, 512));
        fuzzy.launch();
    } catch (const SDL::BaseException &e) {
        std::cerr << e.what() << std::endl;
        Fuzzy::Assets::Unload();
        SDL::Core::Quit();
        return 84;
    }
    Fuzzy::Assets::Unload();
    SDL::Core::Quit();
    return 0;
}