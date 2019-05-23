// © 2018 Joseph Cameron - All Rights Reserved

#ifndef JFC_DATASTRUCTURES_FINAL_ACTION_H
#define JFC_DATASTRUCTURES_FINAL_ACTION_H

//TODO: separarate imp from int

namespace jfc
{
    /// \brief generic raii wrapper for non-pointer types (e.g: OpenGL handles, LibClang cursors)
    ///
    /// \description use this to enforce cleanup of "handles", "indexes" etc. at the end of their life. the various non pointer pointer types seen in C APIs like OpenGL, libclang, etc.
    /// based directly off of the example class of the same name in the RAII section of the CPP Core guidlines: https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#Re-finally
    /// for pointer types, prefer the standard unique and shared ptr wrappers.
    template<typename T>
    class final_action final
    {
    public:
        using deleter_type = std::function<void(T &)>;

    private:
        T m_Item; //!< The wrapped instance of T

        deleter_type m_Deleter; //!< The action to be called at destructor time. This is your opportunity to clean up after T

    public:
        T &get() { return m_Item; }

        final_action(T &aItem, deleter_type aDeleter)
        : m_Item(aItem)
        , m_Deleter(aDeleter)
        {}

        ~final_action()
        {
            m_Deleter(m_Item);
        }
    };
}

#endif
