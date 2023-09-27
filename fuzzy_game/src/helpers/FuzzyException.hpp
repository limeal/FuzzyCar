/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** FuzzyException
*/

#ifndef FUZZYEXCEPTION_HPP_
#define FUZZYEXCEPTION_HPP_

#include <exception>
#include <string>

namespace Fuzzy {
    class FuzzyException : public std::exception {
        public:
            enum FuzzyExceptionType {
                NETWORK,
            };

            FuzzyException(const FuzzyExceptionType &type, std::string const &_content) : _content(
                std::string("[FuzzyException]: ") + _content
            ) {};

            const char *what() const throw() { return _content.c_str(); };
        protected:
        private:
            std::string _content;
    };
}

#endif /* !FUZZYEXCEPTION_HPP_ */
