/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** Map
*/

#include "Map.hpp"

#include <fstream>

namespace Fuzzy
{
    Map::Map(std::string filename, char picon, char icon) : _size(0, 0), _picon(picon), _cicon(icon)
    {
        std::ifstream file(filename);

        if (!file.is_open())
            throw std::runtime_error("Cannot open file " + filename);
        
        std::string line = "";
        int rows = 0, cols = 0;
        while (std::getline(file, line)) {
            // Parse the line
            if (!cols) cols = line.size();

            for (size_t i = 0; i < line.size(); i++) {
                if (line[i] == _cicon)
                    _elements.push_back(std::make_pair(Map::ElementType::CAR, Vector2d(i, rows)));
                else if (line[i] == _picon)
                    _elements.push_back(std::make_pair(Map::ElementType::PCAR, Vector2d(i, rows)));
            }
            rows++;
        }

        _size = Vector2d(cols, rows);
        file.close();
    }
}