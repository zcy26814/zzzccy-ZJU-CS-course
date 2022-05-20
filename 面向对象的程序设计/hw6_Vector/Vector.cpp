#include <iostream>
#include <string>

template<class T>
class Vector{
    public:
        Vector();                      // creates an empty vector
        Vector(int size);              // creates a vector for holding 'size' elements
        Vector(const Vector& r);       // the copy ctor
        ~Vector();                     // destructs the vector 
        T& operator[](int index);      // accesses the specified element without bounds checking
        T& at(int index);              // accesses the specified element, throws an exception of type 'std::out_of_range' when index <0 or >=m_nSize
        int size() const;         // return the size of the container
        void push_back(const T& x);    // adds an element to the end 
        void clear();                  // clears the contents
        bool empty() const;            // checks whether the container is empty 
    private:
        void inflate();                // expand the storage of the container to a new capacity, e.g. 2*m_nCapacity
        T *m_pElements;                // pointer to the dynamically allocated storage
        int m_nSize;                   // the number of elements in the container
        int m_nCapacity;               // the number of elements that can be held in currently allocated storage
};

template<class T>
Vector<T>::Vector(){
    m_pElements = NULL;
    m_nSize = 0;
    m_nCapacity = 0;
}

template<class T>
Vector<T>::Vector(int size){
    m_nSize = 0;
    m_pElements = new T[size];
    m_nCapacity = size;
}

template<class T>
Vector<T>::Vector(const Vector& r){
    m_nSize = r.size();
    m_nCapacity = m_nSize;
    m_pElements = new T[m_nCapacity];
    for(int i = 0; i < m_nSize; i++){
        m_pElements[i] = r.m_pElements[i];
    }
}

template<class T>
Vector<T>::~Vector(){
    delete[] m_pElements;
}

template<class T>
T& Vector<T>::operator[](int index){
    return m_pElements[index];
}
template<class T>
T& Vector<T>::at(int index){
    if(index < 0 || index >= m_nSize){
        throw std::out_of_range("Out of Range");
    }
    return m_pElements[index];
}

template<class T>
int Vector<T>::size() const{
    return m_nSize;
}

template<class T>
void Vector<T>::push_back(const T& x){
    if(m_nSize == m_nCapacity){
        inflate();
    }
    m_pElements[m_nSize++] = x;
}

template<class T>
void Vector<T>::clear(){
    m_nSize = 0;
}

template<class T>
bool Vector<T>::empty() const{
    return (m_nSize == 0);
}

template<class T>
void Vector<T>::inflate(){
    if(m_nCapacity == 0) {
        m_nCapacity = 2;
        m_pElements = new T[2];
    } else {
        m_nCapacity *= 2;
        T *newpElements = new T[m_nCapacity];
        for(int i = 0; i < m_nSize; i++){
            newpElements[i] = m_pElements[i];
        }
        delete[] m_pElements;
        m_pElements = newpElements;
    }
}

int main(){
    Vector<int> vec1 = Vector<int>(), vec2 = Vector<int>(4);

    std::cout << "vec1 size is " << vec1.size() << std::endl;
    std::cout << "vec2 size is " << vec2.size() << std::endl;
    vec1.push_back(5);
    std::cout << "After push 5 to vec1" << std::endl;
    std::cout << "vec1 size is " << vec1.size() << std::endl;
    std::cout << "vec1[0] is " << vec1[0] << std::endl;
    int count;
    std::cout << "Input the num of input: " << std::endl;
    std::cin >> count;
    std::cout << "Input the number to vec2: " << std::endl;
    for(int i = 0; i < count; i++) {
        int num;
        std::cin >> num;
        vec2.push_back(num);
    }
    std::cout << "vec2 size is " << vec2.size() << std::endl;
    std::cout << "vec2 elements are ";
    for(int i = 0; i < count; i++) {
        std::cout << vec2[i] << ", ";
    }
    std::cout << std::endl;
    int index;
    std::cout << "Input the index of vec2: " << std::endl;
    std::cin >> index;
    std::cout << "With bounds checking, the index of vec2 is " << vec2.at(index) << std::endl;
    std::cout << "Without bounds checking, the index of vec2 is " << vec2[index] << std::endl;

    if(vec1.empty()){
        std::cout << "vec1 is empty." << std::endl;
    } else {
        std::cout << "vec1 is not empty. Now clear..." << std::endl;
        vec1.clear();
        if(vec1.empty()){
            std::cout << "clear successfully" << std::endl;
        }
    }

    Vector<int> vec3 = Vector<int>(vec2);
    std::cout << "vec3 size is " << vec3.size() << std::endl;
    std::cout << "vec3 elements are ";
    for(int i = 0; i < vec3.size(); i++) {
        std::cout << vec3[i] << ", ";
    }
    std::cout << std::endl;



    return 0;
}