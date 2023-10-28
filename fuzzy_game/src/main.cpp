/*
** KOREA UNIVERSITY PROJECT, 2023
** FuzzyCar
** File description:
** main
*/

#include <iostream>
#include <vector>

#include "Fuzzy.hpp"

int main(int ac, char **av) {

    try {
        SDL::Core::Init();

        SDL::Core::InitModules({
            std::make_shared<SDL::SDLImage>(),
            std::make_shared<SDL::SDLTtf>(),
            std::make_shared<SDL::SDLMixer>()
        });

        Fuzzy::Assets::Load();

        Fuzzy::Fuzzy fuzzy;
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