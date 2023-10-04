/*
** KOREA UNIVERSITY PROJECT, 2023
** FuzzyCar
** File description:
** main
*/

#include <iostream>

#include "network/P2Server.hpp"
#include "engine/Engine.hpp"

int main(int ac, char **av) {
    (void)ac;
    (void)av;

    Fuzzy::Engine::Window window(Fuzzy::Engine::Vector2i(500, 500), "Fuzzy Car");

    while(!window.shouldClose()) {
        window.clearBackground(Fuzzy::Engine::Color(255, 255, 255));
        window.beginDrawing();
        window.endDrawing();
    }

    /* Fuzzy::P2Server server(Fuzzy::P2Server::TCP, 4242);

    server.Launch(); */
    return 0;
}