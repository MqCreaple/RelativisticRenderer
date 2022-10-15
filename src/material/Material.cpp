#include "material/Material.h"
#include "material/DiffuseMaterial.h"

namespace gmq {

const std::shared_ptr<Material> Material::DEFAULT = std::make_shared<DiffuseMaterial>(1.0);

} // namespace gmq