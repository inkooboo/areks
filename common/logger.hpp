//
//  logger.hpp
//  areks
//
//  Created by inkooboo on 9/7/12.
//
//

# include "defs.hpp"

# include <sstream>

#ifndef areks_logger_hpp
#define areks_logger_hpp

struct LogOnDestruction
{
    LogOnDestruction(LogOnDestruction &other)
    {
        m_ss_ptr = other.m_ss_ptr;
        other.m_ss_ptr = 0;
    }
    
    LogOnDestruction(const char *class_name, const char *function_name)
    {
        m_ss_ptr = new std::stringstream;
        (*m_ss_ptr) << "[" << class_name << "] " << function_name << ": ";
    }
    
    template <typename T>
    LogOnDestruction operator << (const T &value)
    {
        if (m_ss_ptr)
        {
            (*m_ss_ptr) << value;
        }
        return *this;
    }
    
    ~LogOnDestruction()
    {
        if (m_ss_ptr)
        {
            CCLOG("%s", m_ss_ptr->str().c_str());

            delete m_ss_ptr;
        }
    }
    std::stringstream *m_ss_ptr;
};

#define DEFINE_LOGGER(class_name) static const char* log_impl_class_name() { return #class_name; }
#define log() LogOnDestruction(log_impl_class_name(), __FUNCTION__)
    

#endif
