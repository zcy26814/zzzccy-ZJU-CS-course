#pragma once
#include "stdafx.h"
#include <climits>
#include <cstddef>   //ptrdiff_t size_t
#include<new> //placement new
#include<iostream>
using namespace std;
#define BUFFER_SIZE 1024

template <typename T>
struct block {
	block *next;
};   //代表内存里的一个小区块，并以此为分配的单位，大小为sizeof(T)


template <typename T>
class buffer
{
private:
	static const size_t blockSize = sizeof(T);     //一个block大小
	unsigned char* body = new unsigned char[blockSize * BUFFER_SIZE];//开辟一个buffer的空间,并以body为首地址

public:  //接口定义
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	buffer() {};
	pointer blockaddress(size_type count) {//以block为单位得到每次分配空间的地址
		return reinterpret_cast<pointer>(body + blockSize * count);
	}
	buffer * next;   //下一个指针
};


template <typename T>
class memorypool {
public:
	//接口定义
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	memorypool(memorypool &&memorypool) = delete;   //移动构造函数
	memorypool(const memorypool &memorypool) {};    //拷贝函数
	memorypool& operator =(memorypool &&memorypool) = delete;   //移动赋值函数
	memorypool& operator =(const memorypool &memorypool) = delete;  //删除默认拷贝构造函数
	memorypool() {
		firstbuffer->next = NULL;
		freeSlots = NULL;   //初始时没有空的内存
	}
	~memorypool()
	{
		while (firstbuffer != nullptr) {
			buffer<T> *temp = firstbuffer;
			firstbuffer = firstbuffer->next;
			delete temp;     //逐个释放空间
		}
		while (overmem != nullptr) {
			pointer temp = reinterpret_cast<pointer> (overmem);  //强制转化为pointer类型
			overmem = overmem->next;
			::operator delete(temp);    //通过底层的删除方式实现释放
		}
	}
	pointer allocate(size_type n) {
		if (n == 1) {
			if (freeSlots != nullptr) {  //如果链表中存在空间，那么就调用此处的空间
				block<T> *temp = freeSlots;
				freeSlots = freeSlots->next;
				return reinterpret_cast<pointer>(temp);
			}
			else if (buffercount + 1 >= BUFFER_SIZE) {  //如果链表为空且当前buffer已满，那么就向系统调用新的buffer
				buffer<T>*p = new buffer<T>;
				p->next = firstbuffer->next;
				firstbuffer->next = p;
				currentbuffer = p;  //当前buffer为新申请的buffer p
				buffercount = 0;   //初始化索引
			}
			return currentbuffer->blockaddress(buffercount++);  //返回首地址，同时索引加一
		}
		else {
			if (n > BUFFER_SIZE)
			{   //对于n直接超过一个buffer上限的情况，直接调用new，不使用memory pool
				pointer temp = (pointer)::operator new (sizeof(T)*n);
				block<T> * temp1 = reinterpret_cast<block<T> *>(temp);  //转换类型
				temp1->next = overmem;
				overmem =temp1;   //将空间分配情况存入链表
				return temp;    //返回该空间的初始地址
			}
			else if (buffercount + n >= BUFFER_SIZE) {  //如果当前buffer未满，但是要分配的空间与当前使用相加大于总空间数，那么直接开辟新buffer，将此buffer剩余的空间全部转移到freeSlots链表中
				buffer<T>*p = new buffer<T>;
				p->next = firstbuffer->next;
				firstbuffer->next = p;
				int k = buffercount;
				while (k < buffercount) {
					block<T> * temp = reinterpret_cast<block<T> *>(currentbuffer->blockaddress(k));
					temp->next = freeSlots;
					freeSlots = temp;  //没有用完的部分前置
					k++;
				} 
				buffercount = 0;  //初始化索引
				currentbuffer = p; //当前buffer为新申请的buffer p
			}
			buffercount += n;
			return currentbuffer->blockaddress(buffercount - n);  // 返回分配的内存的首地址
		}
	}

	void deallocate(pointer p, size_type n) {
		if (p != nullptr) {    //对于释放的空间，直接放置在链表中，注意前置
			block<T> *temp = reinterpret_cast<block<T> *>(p);
			temp->next = freeSlots;
			freeSlots = temp;
		}
	}
	void construct(pointer p, value_type value) {
		new (p) T(value); //在已申请的内存空间上构造对象
	}
	void destroy(pointer p) {
		p->~T();   //析构对象
	}
	pointer address(reference x) {  //返回非常量引用类型变量地址
		return (pointer)&x;
	}
	const_pointer address(reference x) const {  //返回常量引用类型变量地址
		return (const_pointer)&x;
	}
	size_type max_size() const {       // 计算最大可分配的内存
		return size_type(UINT_MAX / sizeof(T));
	}
	void newElement(value_type value)   //从内存池申请一个对象所需空间，并调用对象的构造函数
	{
		pointer temp = allocate();
		construct<value_type>(temp, value);
		return temp;
	}

	void deleteElement(pointer p)    //析构对象，将内存空间归还给内存池
	{
		if (p != nullptr)
		{
			p->~value_type();
			deallocate(p, 1);
		}
	}
private:
	block<T>* freeSlots;  //用来存放空白的内存空间，每次有新的空间被释放时，添加到此指针的前面
	block<T>* overmem = NULL; //存放超出buffer大小的内存
	buffer<T> * firstbuffer = new buffer<T>;   //buffer首地址
	buffer<T> * currentbuffer = NULL;   //存放当前buffer地址
	size_type buffercount = BUFFER_SIZE;  //索引，表示当前buffer消耗掉的block数
};


template<typename T>
class MyAllocator {
private:	
	allocator<T> *rebindMyAllocator= NULL;   //调用标准allocator生成rebindMyAllocator
	memorypool<T> mp;

public:
	//接口定义
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	template<class U>
	struct rebind {
		typedef MyAllocator<U> other;
	};
	MyAllocator() {};
	template <class U>
	MyAllocator(const MyAllocator<U> &other)
	{
		if (!std::is_same<T, U>::value)
			rebindMyAllocator = new allocator<T>();
	}
	~MyAllocator() {
		delete rebindMyAllocator;
	}
	pointer allocate(size_type n, const void *hint = 0)  //标准的allocate及其接口
	{

		if (rebindMyAllocator)
			return rebindMyAllocator->allocate(n, hint);
		T* temp = mp.allocate(n);
		return temp;
	}
	void deallocate(pointer p, size_type n)    //标准的deallocate及其接口
	{
		if (rebindMyAllocator) {
			rebindMyAllocator->deallocate(p, n);
			return;
		}
		mp.deallocate(p, n);
	}
	void construct(pointer p, value_type value) {
		mp.construct(p, value);
	}
	void destroy(pointer p) {
		mp.destroy(p);
	}
	pointer address(reference x) {  //返回非常量引用类型变量地址
		mp.address(x);
	}
	const_pointer address(reference x) const {  //返回常量引用类型变量地址
		mp.address(x);
	}
	size_type max_size() const {       // 计算最大可分配的内存
		return size_type(UINT_MAX / sizeof(T));
	}
	void newElement(value_type value)   //从内存池申请一个对象所需空间，并调用对象的构造函数
	{
		mp.newElement(value);
	}

	void deleteElement(pointer p)    //析构对象，将内存空间归还给内存池
	{
		mp.deleteElement(p);
	}
};