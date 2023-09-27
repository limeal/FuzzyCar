/*
** KOREA UNIVERSITY PROJECT, 2023
** FuzzyCar
** File description:
** main
*/

#include <iostream>

#include "network/P2Server.hpp"

int main(int ac, char **av) {
    (void)ac;
    (void)av;

    Fuzzy::P2Server server(Fuzzy::P2Server::TCP, 4242);

    server.Launch();
    return 0;
}