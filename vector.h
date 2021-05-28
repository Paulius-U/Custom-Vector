#pragma once

template <class T> 
class vector 
{
    public:
        typedef T value_type;
        typedef std::allocator<T> allocator;
        typedef size_t size_type;
        typedef value_type& value;
        typedef T* iterator;
        typedef const T* constantos_iteratorius;

        vector() { create(); }
        explicit vector(size_type n, const T& val = T{}) { create(n, val); }
        vector(std::initializer_list<T> list); 
        vector(const vector& v) { create(v.begin(), v.end()); } 
        ~vector() { uncreate(); }
        vector& operator=(const vector&);       

        value at( size_type i );
        T& operator[](size_type i) { return data[i]; }
        value front() { return *data; }
        value back() { return*(available - 1); }

        iterator begin() noexcept { return data; }
        constantos_iteratorius begin() const noexcept { return data; }
        iterator end() noexcept { return available; }
        constantos_iteratorius end() const noexcept { return available; }

        bool empty() const { return (begin() == end()); }
        size_type size() const { return available - data; }
        size_type capacity() const { return limitas - data; }
        void reserve( size_type new_cap );
        void shrink_to_fit();

        void clear();
        iterator insert( constantos_iteratorius b, const T& value );
        iterator erase( iterator b );
        void push_back(const T& val);
        void pop_back();
        void resize( size_type count );
        void swap( vector<T>& other ) noexcept;
    private:    
        iterator data;        
        iterator available;       
        iterator limitas;       

        allocator alloc;

        void create();        
        void create(size_type, const T&);  
        void create(constantos_iteratorius, constantos_iteratorius);
        void uncreate();     
        void growTwice();     
        void unchecked_append(const T&);   
};

template <class T> 
vector<T>::vector(std::initializer_list<T> list) 
{
    data = alloc.allocate(list.size());
    limitas = available = std::uninitialized_copy(list.begin(), list.end(), data);
}

template <class T> 
void vector<T>::create()
{
    data = available = limitas = nullptr;
}

template <class T> 
void vector<T>::create(size_type n, const T& val) 
{
    data = alloc.allocate(n); 
    limitas = available = data + n;
    std::uninitialized_fill(data, limitas, val);
}

template <class T>
void vector<T>::create(constantos_iteratorius i, constantos_iteratorius j) 
{    
    data = alloc.allocate(j - i);
    limitas = available = std::uninitialized_copy(i, j, data);
}

template <class T> 
void vector<T>::uncreate()
{
    if (data) {   
        iterator it = available;
        while (it != data)
            alloc.destroy(--it);      
        alloc.deallocate(data, limitas - data);    
        }
    data = limitas = available = nullptr; 
}

template <class T> 
vector<T>& vector<T>::operator=(const vector& rhs) 
{
    if (&rhs != this) {     
        uncreate();
        create(rhs.begin(), rhs.end());
    }
    return *this;
}

template <class T> 
void vector<T>::growTwice() 
{ 
    size_type new_size = std::max((limitas - data) * 2, ptrdiff_t(1));   
    reserve(new_size);
}

template <class T> 
void vector<T>::unchecked_append(const T& val) 
{    
    alloc.construct(available++, val);
}

template <class T>
typename vector<T>::value vector<T>::at( size_type i ) 
{
    if (i < size() && i >= 0)
        return data[i]; 
    else throw std::out_of_range {"vector::at"};
}

template <class T> 
void vector<T>::reserve( size_type new_capacity ) 
{
    if (new_capacity > capacity()) {
        iterator new_data = alloc.allocate(new_capacity);    
        iterator new_available = std::uninitialized_copy(data, available, new_data);   
        uncreate();
        data = new_data;    
        available = new_available;     
        limitas = data + new_capacity;
    }
}

template <class T> 
void vector<T>::shrink_to_fit() 
{
    if (available != limitas) {
        alloc.deallocate(available, limitas - available);
        limitas = available;
    }
}

template <class T> 
void vector<T>::clear() 
{ 
    iterator it = available;
    while (it != data)
        alloc.destroy(--it);
    available = data;
}

template <class T> 
typename vector<T>::iterator vector<T>::insert( constantos_iteratorius b, const T& value ) 
{
    if (b < data || b >= available)
        throw std::out_of_range{ "vector::insert" };
    int a = 0;
    for (iterator i = data; i < b; i++)
        a++;

    size_type new_size = size() + 1;
    iterator new_data = alloc.allocate(new_size);
    iterator new_available = std::uninitialized_copy(data, available + 1, new_data);

    new_data[a] = value;
    int after_pos = a + 1;
    int new_last = size() + 1;

    for (int i = after_pos; i < new_last; i++)
        new_data[i] = data[i - 1];
    
    uncreate();
    data = new_data;
    available = new_available;
    limitas = data + new_size;

    return data + a;
}

template <class T> 
typename vector<T>::iterator vector<T>::erase( iterator b ) 
{
    if (b < data || b >= available)
        throw std::out_of_range{ "vector::erase" };

    for (iterator i = b; i < available-1; i ++)
        *i = *(i+1); 

    available --;       
    return b;
}

template <class T> 
void vector<T>::push_back(const T& val)
{
    if (available == limitas)        
        growTwice();            
    unchecked_append(val) ; 
}


template <class T> 
void vector<T>::pop_back()
{
    iterator it = available;           
    alloc.destroy(--it);
    available--;
}


template <class T> 
void vector<T>::resize( size_type count ) 
{
    if (count < 0 || count > size())
        throw std::invalid_argument{ "vector::resize" };
    while (begin() + count != available)
        alloc.destroy(--available);
}

template <class T>
void vector<T>::swap( vector<T>& other ) noexcept 
{
    iterator temp = data;
    data = other.data;
    other.data = temp;

    temp = available;
    available = other.available;
    other.available = temp;

    temp = limitas;
    limitas = other.limitas;
    other.limitas = temp;
}
