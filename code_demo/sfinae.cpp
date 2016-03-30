#include <iostream>
#include <vector>
#include <type_traits>

template <class T>
typename T::value_type fonction_sfinae (const T& ){
    std::cout << "Le type T::value_type a un sens " << std::endl;
    return typename T::value_type(); // je supose qu'il est default constructible mais c'est juste pour l'exemple.
}

template <class T>
void fonction_sfinae(const T& , typename T::bibi  = 1) {
     std::cout << "Le type T::bibi a un sens " << std::endl;
}

template <class T, class U = typename T::boo >
void fonction_sfinae(const T& ) {
     std::cout << "Le type T::boo a un sens " << std::endl;
}

struct booclass {
    using boo = int;
};

struct bibiclass {
    using bibi = int;
} ;

struct drame {
    using bibi = int;
    using boo = int;
} ;


int main() {
    using namespace std;
    fonction_sfinae(vector<int>());
    fonction_sfinae(booclass ());
    fonction_sfinae(bibiclass ());
    /*fonction_sfinae(drame ());
    |39|error: call of overloaded ‘fonction_sfinae(drame)’ is ambiguous|
    |39|note: candidates are:|
    |12|note: void fonction_sfinae(T, typename T::bibi) [with T = drame; typename T::bibi = int]|
    |17|note: void fonction_sfinae(T) [with T = drame; U = int]|*//*
    // fonction_sfinae(5); |44|error: no matching function for call to ‘fonction_sfinae(int)’|*/
}

