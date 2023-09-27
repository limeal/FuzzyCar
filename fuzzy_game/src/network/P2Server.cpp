/*
** KOREA UNIVERSITY PROJECT, 2023
** FuzzyCar
** File description:
** P2Server
*/

#include "P2Server.hpp"

#include "../helpers/FuzzyException.hpp"

#include <iostream>

// #define CADDR inet_ntoa(client->address.sin_addr)
// #define CPORT ntohs(client->address.sin_port)

Fuzzy::P2Server::P2Server(P2ServerType ptype, int port) : _type(ptype), _port(port)
{
    int socketfd = socket(AF_INET, ptype == TCP ? SOCK_STREAM : SOCK_DGRAM, 0);
    struct sockaddr_in address = {0};

    if (socketfd < 0)
        throw FuzzyException(FuzzyException::NETWORK, "socket() failed");

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port);

    if (!(_conn = std::make_unique<P2Connection>(socketfd, address)))
        throw FuzzyException(FuzzyException::NETWORK, "make_unique() failed");

    if ((bind(_conn->_socket, (struct sockaddr*)&_conn->_address, sizeof(_conn->_address))) < 0)
        throw FuzzyException(FuzzyException::NETWORK, "bind() failed");
    
    if (ptype == TCP && (listen(_conn->_socket, 5)) < 0)
        throw FuzzyException(FuzzyException::NETWORK, "listen() failed");

    std::cout << "Server listening on " << inet_ntoa(_conn->_address.sin_addr) << ":" << ntohs(_conn->_address.sin_port) << std::endl;
}

void Fuzzy::P2Server::AcceptConnection()
{
    int clSocket = 0;
    int len = sizeof(struct sockaddr_in);
    struct sockaddr_in in = {0};

    std::cout << "Ready to accept connection" << std::endl;
    if ((clSocket = accept(_conn->_socket, (struct sockaddr *) &in, (socklen_t *) &len)) < 0)
        throw FuzzyException(FuzzyException::NETWORK, "accept() failed");

    P2Connection connection(clSocket, in);
    _connections.push_back(connection);

    std::cout << "New connection from " << inet_ntoa(connection._address.sin_addr) << ":" << ntohs(connection._address.sin_port) << std::endl;
}

void Fuzzy::P2Server::ReceiveConnection()
{
    // Read, Write, Other...
}

void Fuzzy::P2Server::Launch()
{
    int ret;
    fd_set set, wset;

    for (;;) {
        FD_ZERO(&set);
        FD_ZERO(&wset);
        FD_SET(_conn->_socket, &set);
        FD_SET(_conn->_socket, &wset);
        if ((ret = select(FD_SETSIZE, &set, &wset, NULL, NULL)) < 0)
            continue;
        if (FD_ISSET(_conn->_socket, &set)) {
            std::cout << "New connection" << std::endl;
            AcceptConnection();
        } else  {
            std::cout << "New message" << std::endl;
        }
    }
}