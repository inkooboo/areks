//
//  subsystem.hpp
//  subsystems
//
//  Created by Andrey Kubarkov on 7/27/12.
//

#ifndef __SUBSYSTEM_HPP__
# define __SUBSYSTEM_HPP__

/** @class subsystem_t
 * @brief Interface for managed subsystem.
 */
class subsystem_t
{
public:
    virtual void start() {}
    virtual void stop() {}
    
    virtual inline ~subsystem_t() = 0;
};

// Implementation

inline subsystem_t::~subsystem_t()
{
}

#endif //__SUBSYSTEM_HPP__
