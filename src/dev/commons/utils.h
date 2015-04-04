#ifndef UTILS_H
#define UTILS_H

class Utils
{
private:
    Utils();

    static Utils *instance;

public:

    static Utils* getInstance();

    template<class T, class B> struct Derived_from {
        static void constraints(T* p) { B* pb = p; }
        Derived_from() { void(*p)(T*) = constraints; }
    };

    template<class T1, class T2> struct Can_copy {
        static void constraints(T1 a, T2 b) { T2 c = a; b = a; }
        Can_copy() { void(*p)(T1,T2) = constraints; }
    };

    template<class T1, class T2 = T1> struct Can_compare {
        static void constraints(T1 a, T2 b) { a==b; a!=b; a<b; }
        Can_compare() { void(*p)(T1,T2) = constraints; }
    };

    template<class T1, class T2, class T3 = T1> struct Can_multiply {
        static void constraints(T1 a, T2 b, T3 c) { c = a*b; }
        Can_multiply() { void(*p)(T1,T2,T3) = constraints; }
    };

    template<class T, class B> struct Where {
        static void constraints(T* p) { B* pb = p; }
        Where() { void(*p)(T*) = constraints; }
    };

};

#endif // UTILS_H
