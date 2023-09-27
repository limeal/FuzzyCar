/*
** KOREA UNIVERSITY PROJECT, 2023
** FuzzyCar
** File description:
** P2Connection
*/

#ifndef P2CONNECTION_HPP_
#define P2CONNECTION_HPP_

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <exception>

namespace Fuzzy {
    class P2Connection {
        public:
            P2Connection(int const socket, struct sockaddr_in const address) : _socket(socket), _address(address) {};
            ~P2Connection() { close(_socket); };

            int _socket;
            struct sockaddr_in _address;
        protected:
        private:
    };
}

#endif /* !P2CONNECTION_HPP_ */
