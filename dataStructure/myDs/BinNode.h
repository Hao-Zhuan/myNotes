#pragma once
#define stature(p) ((p)?(p)->height:-1)
typedef enum { r, b } RBColor;

template<typename T>struct BinNode{
	T data;
	BinNode<T>* parent;
	BinNode<T>* lc;
	BinNode<T>* rc;
	int height;
	RBColor color;

	BinNode():parent(nullptr),lc(nullptr),rc(nullptr),height(0),color(r){}

	BinNode(T e, BinNode<T>* parent = nullptr, BinNode<T>* lc = nullptr, BinNode<T>* rc = nullptr,  int h = 0;RBColor c=r):
		data(e),lc(lc),rc(rc),parent(parent),height(h),color(c){}
	int size();
	BinNode<T>* insertLc(T const&);
	BinNode<T>* insertRc(T const&);
	BinNode<T>* succ();
	template<typename VST>void travLevel(VST&);
	template<typename VST>void travRe(VST&);
	template<typename VST>void travIn(VST&);
	template<typename VST>void travPost(VST&);
	bool operator<(BinNode const& bn) { return data < bn.data; }
	bool operator==(BinNode const& bn) { return data == bn.data; }

};

template<typename T>BinNode<T>* BinNode<T>::insertLc(T const& e) { return lc = new BinNode(e, this); }
template<typename T>BinNode<T>* BinNode<T>::insertRc(T const& e) { return rc = new BinNode(e, this); }