/* Copyright (c) 2002, Nokia. All rights reserved */

template <class T>
inline const T& TStaticArrayC<T>::operator[](TInt aIndex) const
    {
    if ((aIndex >= iCount) || (aIndex < 0))
        {
        Panic(EIndexOutOfBounds);
        }

    return  iArray[aIndex];
    }

template <class T>
inline void TStaticArrayC<T>::Panic(TPanicCode aPanicCode) const
    {
    User::Panic(_L("StaticArray"), aPanicCode);
    }
