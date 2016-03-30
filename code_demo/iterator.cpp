#include <iostream>
#include <vector>
#include <type_traits>

#include "../code/src/iterateurFoncteur.hpp" 
struct Bidon {
    int a = 5 ;
    int b = 6 ;
    int c = 7 ;

    std::vector<std::reference_wrapper<int>> vec;


    Bidon() {
        vec.push_back(std::ref(a));
        vec.push_back(std::ref(b));
        vec.push_back(std::ref(c));
    }

    // Le parcourt des cases
    using iterator = FoncteurIterator<std::vector<std::reference_wrapper<int>>::iterator,std::UnWrappe<int>>;
    using const_iterator = FoncteurIterator<std::vector<std::reference_wrapper<int>>::const_iterator,std::UnWrappe<int>>;

    inline iterator begin()                     { return iterator(vec.begin());         }
    inline const_iterator begin() const         { return const_iterator(vec.begin());   }
    inline iterator end()                       { return iterator(vec.end());           }
    inline const_iterator end() const           { return const_iterator(vec.end());     }
};

struct BidonMoche {
    int a = 5 ;
    int b = 6 ;
    int c = 7 ;

    std::vector<std::reference_wrapper<int>> vec;


    BidonMoche() {
        vec.push_back(std::ref(a));
        vec.push_back(std::ref(b));
        vec.push_back(std::ref(c));
    }

    // Le parcourt des cases
    using iterator = std::vector<std::reference_wrapper<int>>::iterator;
    using const_iterator = std::vector<std::reference_wrapper<int>>::const_iterator;

    inline iterator begin()                     { return iterator(vec.begin());         }
    inline const_iterator begin() const         { return const_iterator(vec.begin());   }
    inline iterator end()                       { return iterator(vec.end());           }
    inline const_iterator end() const           { return const_iterator(vec.end());     }
};

int main() {
    using namespace std;
    Bidon bidon;
    for ( auto val : bidon ){
        cout << val << " ";
    }
    cout << endl;
    for (const auto& val : bidon ){
        cout << val << " ";
    }
    cout << endl;
    cout << "La version sans mon iterateur" << endl;
    BidonMoche bidonMoche;
    for ( auto val : bidonMoche ){
        cout << val.get() << " ";
    }
    cout << endl;
    for (const auto& val : bidonMoche ){
        cout << val.get() << " ";
    }
    cout << endl;
}
 
