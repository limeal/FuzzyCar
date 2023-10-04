/*
** KOREA UNIVERSITY PROJECT, 2023
** FuzzyCar
** File description:
** IRElement
*/

#ifndef IRELEMENT_HPP_
#define IRELEMENT_HPP_

template <typename T>
class IRElement {
    public:
        virtual ~IRElement() = default;

        virtual T getSource() = 0;
};

#endif /* !IRELEMENT_HPP_ */
