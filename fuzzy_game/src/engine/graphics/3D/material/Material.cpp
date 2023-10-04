/*
** KOREA UNIVERSITY PROJECT, 2023
** FuzzyCar
** File description:
** Material
*/

#include "Material.hpp"

namespace Fuzzy {
    namespace Engine {
        Material::Material(std::string filename, int *materialCount)
        {
            _monMat = LoadMaterials(filename.c_str(), materialCount);
        }
        
        Material::Material(const Material &mat)
        {
            _monMat = mat._monMat;
        }

        Material::~Material()
        {
            UnloadMaterial(*_monMat);
        }
    }
}