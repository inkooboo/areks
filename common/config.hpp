//
//  config.hpp
//  config
//
//  Created by Andrey Kubarkov on 7/18/12.
//

#ifndef config_config_hpp
#define config_config_hpp

#include "noncopyable.hpp"

#include <string>
#include <sstream>
#include <fstream>
#include <map>

class config_t : private noncopyable_t
{
public:
    
    enum store_policy
    {
          store_on_destruction
        , store_each_change
        , store_never
    };
    
    inline explicit config_t(const char *file_name = "", store_policy policy = store_never);
    inline explicit config_t(const std::string &source);
    inline ~config_t();
    
    template <typename T>
    inline void set(const char *name, const T &value);
    
    template <typename T>
    inline T get(const char *name) const;
    
private:
    inline void store();
    inline void load(std::istream &input);
    
    inline static std::string escape(const std::string &str);
    inline static std::string unescape(const std::string &str);
    
    const std::string m_file_name;
    const store_policy m_policy;
    std::map<std::string, std::string> m_properties;
};



// implementation

inline config_t::config_t(const char *file_name, store_policy policy)
    : m_file_name(file_name)
    , m_policy(policy)
{
    if (m_file_name.empty())
    {
        return;
    }
    
    std::ifstream f(m_file_name.c_str(), std::ios_base::in);
    
    if (!f.is_open())
    {
        return;
    }
    
    load(f);
}

inline config_t::config_t(const std::string &source)
    : m_file_name("")
    , m_policy(store_never)
{
    std::istringstream input(source);
    
    load(input);
}

inline config_t::~config_t()
{
    if (store_on_destruction == m_policy)
    {
        store();
    }
}

template <typename T>
inline void config_t::set(const char *name, const T &value)
{
    std::stringstream ss;
    ss << value;
    m_properties[name] = ss.str();
    
    if (store_each_change == m_policy)
    {
        store();
    }
}

template <typename T>
inline T config_t::get(const char *name) const
{
    T ret;
    
    std::stringstream ss;    
    auto prop_it = m_properties.find(name);
    if (prop_it != m_properties.end())
    {
        ss << prop_it->second;
    }
    ss >> ret;
    
    return ret;
}

template <>
inline std::string config_t::get<std::string>(const char *name) const
{
    std::string ret;
    
    auto prop_it = m_properties.find(name);
    if (prop_it != m_properties.end())
    {
        ret = prop_it->second;
    }
    
    return ret;
}


inline void config_t::store()
{
    if (m_file_name.empty())
    {
        return;
    }
    
    std::ofstream f(m_file_name.c_str(), std::ios_base::out | std::ios_base::trunc);
    
    //for (auto &property : m_properties)
    //{
    //    f << escape(property.first) << " " << escape(property.second) << std::endl;
    //}
    for (auto it = m_properties.begin(); it != m_properties.end(); ++it)
    {
        f << escape(it->first) << " " << escape(it->second) << std::endl;
    }
}

inline void config_t::load(std::istream &input)
{
    while (!input.eof()) 
    {
        std::string line;
        std::getline(input, line, '\n');
        
        size_t space = line.find(' ');
        if (std::string::npos == space)
        {
            continue;
        }
        
        std::string name = unescape(line.substr(0, space));
        std::string value = unescape(line.substr(space + 1, line.length() - space - 1));
        
        m_properties[name].swap(value);
    }
}

inline std::string config_t::escape(const std::string &str)
{
    std::string ret;
    ret.reserve(str.length() * 2);
    
    size_t i = 0;
    while (i < str.length())
    {
        switch (str[i])
        {
            case ' ' : {
                ret += "%0";
                break;
            }
            case '\n' : {
                ret += "%1";
                break;
            }
            case '%' : {
                ret += "%2";
                break;
            }
            default : {
                ret += str[i];
                break;
            }
        }
        ++i;
    }
    return ret;
}

inline std::string config_t::unescape(const std::string &str)
{
    std::string ret;
    ret.reserve(str.length());
    
    size_t i = 0;
    while (i < str.length())
    {
        switch (str[i])
        {
            case '%' : {
                ++i;
                switch (str[i])
                {
                    case '0' : {
                        ret += ' ';
                        break;
                    }
                    case '1' : {
                        ret += '\n';
                        break;
                    }
                    case '2' : {
                        ret += '%';
                        break;
                    }
                }                
                break;
            }
            default : {
                ret += str[i];
                break;
            }
        }
        ++i;
    }
    return ret;
}


#endif
