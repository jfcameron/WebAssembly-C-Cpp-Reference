// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_MEMORY_AUTH_VECTOR_H
#define GDK_MEMORY_AUTH_VECTOR_H

#include <iosfwd>
#include <memory>
#include <vector>

namespace gdk
{
    ///\brief Vector that strongly owns its data. Data can only be inserted via rvalue references,
    /// data can only be accessed via weak_ptrs.
    template<typename T>
    class auth_vector final
    {
    public:
        using iterator               = typename std::vector<T>::iterator;
        using const_iterator         = typename std::vector<T>::const_iterator;
        using reverse_iterator       = typename std::vector<T>::reverse_iterator;
        using const_reverse_iterator = typename std::vector<T>::const_reverse_iterator;
        using size_type              = typename std::vector<T>::size_type;
        using value_type             = typename std::vector<T>::value_type;
        using false_type             = bool;
        using T_weakptr              = typename std::weak_ptr<T>;
        using T_const_weakptr        = const typename std::weak_ptr<T>;
        
    private:
        std::vector<T> m_Vector;
        
    public:
        ///\name Iterators
        ///\{
        iterator begin() {return m_Vector.begin();}
        const_iterator begin() const {return m_Vector.begin();}
        iterator end() {return m_Vector.end();}
        const_iterator end() const {return m_Vector.end();}
        reverse_iterator rbegin() {return m_Vector.rbegin();}
        const_reverse_iterator rbegin() const {return m_Vector.rbegin();}
        const_iterator cbegin() const {return m_Vector.cbegin();}
        const_iterator cend() const {return m_Vector.cend();}
        const_reverse_iterator crbegin() const {return m_Vector.crbegin();}
        const_reverse_iterator crend() const {return m_Vector.crend();}
        ///\}
        
        ///\name Capacity
        ///\{
        size_type size() const {return m_Vector.size();}
        size_type max_size() const {return m_Vector.max_size();}
        void resize (size_type n) {return m_Vector.resize(n);}
        void resize (size_type n, const value_type& val) {return m_Vector.resize(n,val);}
        size_type capacity() const {m_Vector.capacity();}
        bool empty() const {return m_Vector.empty();}
        void reserve (size_type n) {m_Vector.reserve(n);}
        void shrink_to_fit(){m_Vector.shrink_to_fit();}
        ///\}

        ///\name Element access
        ///\{
        T_weakptr operator[] (const size_type &n) {return T_weakptr(m_Vector[n]);}
        T_const_weakptr operator[] (const size_type &n) const {return T_weakptr(m_Vector[n]);}
        T_weakptr at (const size_type &n) {return T_weakptr(m_Vector.at(n));}
        T_const_weakptr at (const size_type &n) const {return T_weakptr(m_Vector.at(n));}
        T_weakptr front() {return T_weakptr(m_Vector.front());}
        T_const_weakptr front() const {return T_const_weakptr(m_Vector.front());}
        T_weakptr back() {return T_weakptr(m_Vector.back());}
        T_const_weakptr back() const {return T_const_weakptr(m_Vector.back());}
        ///\}
        
        ///\name Modifiers
        ///\{
        void assign(const size_type &n, T &&val) {m_Vector.assign(n,std::make_shared<T>(std::move(val)));}
        void push_back(T &&val) {m_Vector.push_back(std::make_shared<T>(std::move(val)));}
        void pop_back() {m_Vector.pop_back();}
        iterator insert(const_iterator &position, T &&val) {return m_Vector.insert(position,std::make_shared<T>(std::move(val)));}
        iterator insert(const_iterator &position, size_type &n, T &&val) {return m_Vector.insert(position,n,std::make_shared<T>(std::move(val)));}
        iterator erase(const_iterator &position) {return m_Vector.erase(position);}
        iterator erase(const_iterator &first, const_iterator &last) {return m_Vector.erase(first, last);}
        void swap(std::vector<T> &x){m_Vector.swap(x.m_Vector);}
        void clear() {m_Vector.clear();}
        ///\}
        
        ///\name Mutating operators
        ///\{
        auth_vector& operator=(const auth_vector &) = delete;
        auth_vector& operator=(auth_vector &&) = delete;
        ///\}
        
        ///\name Constructors, destructors
        ///\{
        auth_vector() = default;
        auth_vector(const auth_vector&) = delete;
        auth_vector(auth_vector&&) = default;
        ~auth_vector() = default;
        ///\}
    };
}

#endif
