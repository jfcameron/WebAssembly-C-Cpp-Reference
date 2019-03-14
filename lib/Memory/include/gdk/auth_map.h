// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_MEMORY_AUTH_MAP_H
#define GDK_MEMORY_AUTH_MAP_H

#include <iosfwd>
#include <map>
#include <memory>

namespace gdk
{
    /// \brief Map that strongly owns its data. 
    ///
    /// \detailed insertion can only be done via rvalue reference,
    /// map data can only be accessed via weak_ptr
    template<typename KeyT, typename ValueT> class auth_map final
    {
    public:
        using iterator =               typename std::map<KeyT, std::shared_ptr<ValueT>>::iterator;
        using const_iterator =         typename std::map<KeyT, std::shared_ptr<ValueT>>::const_iterator;
        using reverse_iterator =       typename std::map<KeyT, std::shared_ptr<ValueT>>::reverse_iterator;
        using const_reverse_iterator = typename std::map<KeyT, std::shared_ptr<ValueT>>::const_reverse_iterator;
        using mapped_type =            typename std::map<KeyT, std::shared_ptr<ValueT>>::mapped_type;
        using key_type =               typename std::map<KeyT, std::shared_ptr<ValueT>>::key_type;
        using value_type =             typename std::map<KeyT, std::shared_ptr<ValueT>>::value_type;
        using size_type =              typename std::map<KeyT, std::shared_ptr<ValueT>>::size_type;
        using mapped_type_weakptr =    typename std::weak_ptr<ValueT>;
        using mapped_type_sharedptr =  typename std::shared_ptr<ValueT>;
            
    private:
        std::map<KeyT, mapped_type_sharedptr> m_Map;

    public:
        ///\name Iterators
        ///\{
        iterator               begin()         {return m_Map.begin();  }
        const_iterator         begin()   const {return m_Map.begin();  }
        const_iterator         cbegin()  const {return m_Map.cbegin(); }
        reverse_iterator       rbegin()        {return m_Map.rbegin(); }
        const_reverse_iterator rbegin()  const {return m_Map.rbegin(); }
        const_reverse_iterator crbegin() const {return m_Map.crbegin();}
            
        iterator               end()         {return m_Map.end();  }
        const_iterator         end()   const {return m_Map.end();  }
        const_iterator         cend()  const {return m_Map.cend(); }
        reverse_iterator       rend()        {return m_Map.rend(); }
        const_reverse_iterator rend()  const {return m_Map.rend(); }
        const_reverse_iterator crend() const {return m_Map.crend();}
        ///\}

        ///\name Capacity 
        ///\{
        bool      empty()    const {return m_Map.empty();   }
        size_type size()     const {return m_Map.size();    }
        size_type max_size() const {return m_Map.max_size();}
        ///\}
            
        ///\name Element access
        ///\{
        mapped_type_weakptr operator[] (const key_type& k) {return mapped_type_weakptr(m_Map[k]);}
        mapped_type_weakptr operator[] (key_type&& k)      {return mapped_type_weakptr(m_Map[k]);}
            
        mapped_type_weakptr&       at (const key_type& k)       {return mapped_type_weakptr(m_Map.at(k));}
        const mapped_type_weakptr& at (const key_type& k) const {return mapped_type_weakptr(m_Map.at(k));}
        ///\}
            
        ///\name Modifiers
        ///\{
        void insert (const KeyT &aKey, ValueT &&aValue) {m_Map.insert({aKey,std::make_shared<ValueT>(std::move(aValue))});}
        void erase (const KeyT &aKey) {m_Map.erase(aKey);}
        void swap (auth_map& x) {m_Map.swap(x.m_Map);}
        void clear() {m_Map.clear();}
        ///\}
            
        ///\name Operations
        ///\{
        iterator find (const key_type& k) {return m_Map.find(k);}
        const_iterator find (const key_type& k) const {return m_Map.find(k);}
        size_type count (const key_type& k) const {m_Map.count(k);}
        iterator lower_bound (const key_type& k) {return m_Map.lower_bound(k);}
        const_iterator lower_bound (const key_type& k) const {return m_Map.lower_bound(k);}
        iterator upper_bound (const key_type& k) {return m_Map.upper_bound(k);}
        const_iterator upper_bound (const key_type& k) const {return m_Map.upper_bound(k);}
        std::pair<const_iterator,const_iterator> equal_range (const key_type& k) const {m_Map.equal_range(k);}
        std::pair<iterator,iterator> equal_range (const key_type& k) {m_Map.equal_range(k);}
        ///\}
            
        ///\name Mutating operators
        ///\{
        auth_map &operator=(const auth_map &) = delete;
        auth_map &operator=(auth_map &&) = delete;
        ///\}
            
        // Constructors, destructors
        ///\{
        auth_map() = default;
        auth_map(const auth_map&) = delete;
        auth_map(auth_map&&) = default;
        ~auth_map() = default;
        ///\}
    };
}

#endif
