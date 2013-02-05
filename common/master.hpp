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
    template <typename SubsystemType, typename ImplSubsystemType = SubsystemType>  // ImplSubsystemType can be used in case of virtual inheritance
    inline void add_managed_subsystem();
    
    template <typename SubsystemType, typename... Args>
    inline void add_unmanaged_subsystem(Args ...args);
    
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
    for (auto &subsystem : m_subsystems)
    {
        subsystem->start();
    }
}

inline void master_t::stop()
{
    for (auto &subsystem : m_subsystems)
    {
        subsystem->stop();
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
        template <typename... Args>
        inline unmanaged_holder_t(Args ...args) : holder(args...) {}
        SubsystemType holder;
    };
}

template <typename SubsystemType, typename ImplSubsystemType>
inline void master_t::add_managed_subsystem()
{
    SubsystemType **instance = internal::subsystem_instance<SubsystemType>();
    assert(*instance == 0 && "Instance for this subsystem was already added!");
    
    *instance = new ImplSubsystemType();
    
    m_subsystems.push_back(std::unique_ptr<subsystem_t>(*instance));
}

template <typename SubsystemType, typename... Args>
inline void master_t::add_unmanaged_subsystem(Args ...args)
{
    SubsystemType **instance = internal::subsystem_instance<SubsystemType>();
    assert(*instance == 0 && "Instance for this subsystem was already added!");
    
    internal::unmanaged_holder_t<SubsystemType> *unmanaged_holder = new internal::unmanaged_holder_t<SubsystemType>(args...);
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
