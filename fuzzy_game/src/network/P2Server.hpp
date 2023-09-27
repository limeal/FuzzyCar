/*
** KOREA UNIVERSITY PROJECT, 2023
** FuzzyCar
** File description:
** P2Server
*/

#ifndef P2SERVER_HPP_
#define P2SERVER_HPP_

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <exception>
#include <list>
#include <memory>

#include "P2Connection.hpp"

namespace Fuzzy
{
    class P2Server {
        public:
            enum P2ServerType {
                TCP,
                UDP,
            };

            P2Server(P2ServerType type, int port);

            void Launch();

        protected:
        private:
            P2ServerType _type;
            std::unique_ptr<P2Connection> _conn;
            int _port;

            std::list<P2Connection> _connections;

            void AcceptConnection(); // Accept connection for new connection (TCP)
            void ReceiveConnection(); // Receive connection for new message
    };
}

#endif /* !P2SERVER_HPP_ */
