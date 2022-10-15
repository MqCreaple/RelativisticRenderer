#pragma once

#include "math/math.h"

namespace gmq {

class Random {
    // TODO (rewrite the random class)
public:
    /**
     * @brief random integer in range [iMin, iMax)
     * @param iMin lower bound (inclusive)
     * @param iMax upper bound (exclusive)
     * @return Int random integer in the range
     */
    static Int randInt(Int iMin, Int iMax);
    
    /**
     * @brief generate uniform random number in [0, 1)
     * @return Float random number
     */
    static Float uniform();

    /**
     * @brief generate uniform random number in [fmin, fmax]
     * @param fmin lower bound
     * @param fmax upper bound
     * @return Float random number
     */
    static Float uniform(Float fmin, Float fmax);

    /**
     * @brief generate a random unit vector uniformly distributed on the unit sphere.
     * @return Vec3 random unit vector
     */
    static Vec3 unitVec();

    /**
     * @brief pick a random unit vector on the hemisphere (z >= 0).
     * @return Vec3 random unit vector
     */
    static Vec3 vecOnHemisphere();

    static Vec3 vecOnHemisphere(const Vec3 &normal);
private:
};

} // namespace gmq