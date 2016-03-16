#pragma once


class Engine;
class Object
{
public:
    Engine* GameEngine;
protected:
    template<class T, class U>
    T Cast(U original)
    {
        return dynamic_cast<T>(original);
    }
    template<class T, class U>
    T SCast(U original)
    {
        return static_cast<T>(original);
    }
};
