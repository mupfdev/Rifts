// Header LST.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __LST_H__
#define __LST_H__

template <class T>
class Link
	{
public:
	inline Link();
	inline Link(T aT);
public:
	Link *iNext;
	T iT;
	}; 

template <class T>
class List
	{   
public:
	inline List();
	inline int Size() const;
	inline T& operator [] (const int aNum) const;
	inline void Add(T aT);
	virtual void Externalize(ostream& out)=0;
	inline void Destroy();
	inline ~List();
private:
	Link<T> *iFirst;		
	};

template <class T> 
class ObjectList : public List<T>	// List of object pointers
	{   
public:
	inline virtual void Externalize(ostream& out);
	inline void Destroy();
	};

template <class T> inline Link<T>::Link()
	{
	iNext=NULL;
	}

template <class T> inline Link<T>::Link(T aT)
	{
	iT=aT;
	iNext=NULL;
	}

template <class T> inline List<T>::List()
	{
	iFirst=NULL;
	}

template <class T> inline int List<T>::Size() const
	{
	int size=0;
	Link<T> *link=iFirst;
	while (link!=NULL)
		{
		link=link->iNext;
		size++;
		}
	return size;
	}

template <class T> inline T& List<T>::operator [] (const int aNum) const
	{
	int num=0;
	Link<T> *link=iFirst;
	while (num!=aNum)
		{
		link=link->iNext;
		num++;
		}
	return link->iT;
	}

template <class T> inline void List<T>::Add(T aT)
	{
	Link<T> *link;
	if (iFirst==NULL)
		iFirst=new Link<T>(aT);
	else
		{
		link=iFirst;
		while (link->iNext!=NULL)
			link=link->iNext; 
		link->iNext=new Link<T>(aT);
		}
	}

template <class T> inline void List<T>::Destroy()
	{
	Link<T> *link=iFirst,*next;
	while (link!=NULL)
		{
		next=link->iNext;
		delete link;
		link=next;
		}
	iFirst=NULL;
	}

template <class T> inline List<T>::~List (void)
	{
	Destroy();
	}

template <class T> inline void ObjectList<T>::Externalize(ostream& out)
	{
	int32 size=Size(),i;
	out.write ((char*) &size,sizeof(size));
	for (i=0;i<size;i++)
		(*this)[i]->Externalize(out);
	}

template <class T> inline void ObjectList<T>::Destroy()
	{
	int size=Size(),i;
	for (i=0;i<size;i++)
		delete (*this)[i];
	List<T>::Destroy();
	}

#endif
