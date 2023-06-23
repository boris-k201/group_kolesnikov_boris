#ifndef SINGLETON_H
#define SINGLETON_H

// Для использования необходимо унаследоваться от этого класса с модификатором public,
// сделать конструкторы и деструкторы приватными и прописать
// friend class Singleton<ClassName>

///
/// \brief The Singleton class От него наследуются Game и MyTcpServer
///
template <class T> class Singleton {
protected:
    ///
    /// \brief p_instance Указатель на единственный объект класса
    ///
    static inline T * p_instance = nullptr;
    ///
    /// \brief Singleton Конструктор класса
    ///
    Singleton();
    ///
    /// \brief Singleton Конструктор копирования класса
    ///
    Singleton(const Singleton& );
    ///
    /// \brief operator = Оператор присваивания класса
    /// \return
    ///
    Singleton& operator = (Singleton &);
public:
    ///
    /// \brief getInstance Метод получения указателя на объект класса
    /// \return Указатель на объект класса
    ///
    static T* getInstance();
};

// Определение в заголовочном файле, так как этого требует шаблонная функция.

template<class T>
Singleton<T>::Singleton() {}

template<class T>
T* Singleton<T>::getInstance() {
    if (!p_instance)
        p_instance = new T();
    return p_instance;
}

#endif // SINGLETON_H
