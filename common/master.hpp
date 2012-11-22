//
//  master.hpp
//  subsystems
//
//  Created by Andrey Kubarkov on 7/27/12.
//

#ifndef __MASTER_HPP__
# define __MASTER_HPP__

# include "subsystem.hpp"
# include "noncopyable.hpp"

# include <vector>
# include <cassert>
# include <memory>

/** @class master_t
 * @brief Subsystems manager.
 * @note
 * Only one instance of this class can be created
 * and only once during program execution.
 */
class master_t : private noncopyable_t
{
public:
    template <typename SubsystemType>
    inline void add_managed_subsystem(SubsystemType *instance = 0); // instance can be used in case of virtual inheritance
    
    template <typename SubsystemType, typename Arg1>
    inline void add_unmanaged_subsystem(Arg1 arg);
    
    template <typename SubsystemType>
    inline void add_external_subsystem(SubsystemType *raw_pointer);
    
    template <typename SubsystemType>
    static inline SubsystemType & subsystem();
    
    inline void start();
    inline void stop();
    
    inline master_t();
    
private:
    std::vector<std::unique_ptr<subsystem_t>> m_subsystems;
};

// Implementation

inline void master_t::start()
{
    //for (auto &subsystem : m_subsystems)
    //{
    //    subsystem->start();
    //}
    for (auto it = m_subsystems.begin(); it != m_subsystems.end(); ++it)
    {
        (*it)->start();
    }
}

inline void master_t::stop()
{
    //for (auto &subsystem : m_subsystems)
    //{
    //    subsystem->stop();
    //}
    for (auto it = m_subsystems.begin(); it != m_subsystems.end(); ++it)
    {
        (*it)->stop();
	}
}

inline master_t::master_t()
{
    static bool was_created = false;
    assert(!was_created && "Object of type master_t can be created only once!");
    was_created = true;
}

namespace internal
{
    template <typename SubsystemType>
    inline SubsystemType ** subsystem_instance()
    {
        static SubsystemType *instance = 0;
        return &instance;
    }
    
    template <typename SubsystemType>
    struct unmanaged_holder_t : public subsystem_t
    {
        template <typename Arg1>
        inline unmanaged_holder_t(Arg1 arg1) : holder(arg1) {}
        SubsystemType holder;
    };
}

template <typename SubsystemType>
inline void master_t::add_managed_subsystem(SubsystemType *existing_instance)
{
    SubsystemType **instance = internal::subsystem_instance<SubsystemType>();
    assert(*instance == 0 && "Instance for this subsystem was already added!");
    
    if (existing_instance)
    {
        *instance = existing_instance;
    }
    else
    {
        *instance = new SubsystemType();
    }
    m_subsystems.push_back(std::unique_ptr<subsystem_t>(*instance));
}

template <typename SubsystemType, typename Arg1>
inline void master_t::add_unmanaged_subsystem(Arg1 arg1)
{
    SubsystemType **instance = internal::subsystem_instance<SubsystemType>();
    assert(*instance == 0 && "Instance for this subsystem was already added!");
    
    internal::unmanaged_holder_t<SubsystemType> *unmanaged_holder = new internal::unmanaged_holder_t<SubsystemType>(arg1);
    *instance = &(unmanaged_holder->holder);
    m_subsystems.push_back(std::unique_ptr<subsystem_t>(unmanaged_holder));
}

template <typename SubsystemType>
inline void master_t::add_external_subsystem(SubsystemType *raw_pointer)
{
    SubsystemType **instance = internal::subsystem_instance<SubsystemType>();
    assert(*instance == 0 && "Instance for this subsystem was already added!");
    
    *instance = raw_pointer;
}

template <typename SubsystemType>
inline SubsystemType & master_t::subsystem()
{
    SubsystemType **instance = internal::subsystem_instance<SubsystemType>();
    assert(*instance != 0 && "Instance for this  subsystem was never added!");
    
    return **instance;
}

#endif //__MASTER_HPP__
