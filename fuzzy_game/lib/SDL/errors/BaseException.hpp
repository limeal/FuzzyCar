/*
** KOREA UNIVERSITY PROJECT, 2023
** FuzzyCar
** File description:
** FuzzyException
*/

#pragma once

#include <exception>
#include <string>

namespace SDL {
    class BaseException : public std::exception {
        public:

            BaseException(std::string const &_content) : _content(
                std::string("[SDL -> BaseException]: ") + _content
            ) {};

            const char *what() const throw() { return _content.c_str(); };
        protected:
        private:
            std::string _content;
    };
}
