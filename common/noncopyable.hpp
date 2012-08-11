//
//  noncopyable.hpp
//
//  Created by Andrey Kubarkov on 7/18/12.
//

#ifndef noncopyable_hpp
#define noncopyable_hpp

class noncopyable_t
{
protected:
    noncopyable_t() {}
    ~noncopyable_t() {}
private:
    noncopyable_t(const noncopyable_t &);
    const noncopyable_t & operator=(const noncopyable_t &);
};

//struct noncopyable_t {
//    noncopyable_t & operator=(const noncopyable_t&) = delete;
//    noncopyable_t(const noncopyable_t&) = delete;
//    noncopyable_t() = default;
//};

#endif
