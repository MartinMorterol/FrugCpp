#ifndef ITERATEUR_FONCTEUR_HPP
#define ITERATEUR_FONCTEUR_HPP

#include <functional>
#include "paramInfo.hpp"


// Un petit coup de SFINAE 
template<typename T, typename = void>
struct is_iterator
{
   static constexpr bool value = false;
};

template<typename T>
struct is_iterator< T, typename std::enable_if<
                                                !std::is_same<
                                                            typename std::iterator_traits<T>::value_type, void
                                                            >::value
                                              >::type
                  >
{
   static constexpr bool value = true;
};

template <class IteratorTemplate, class FoncteurTemplate>
class FoncteurIterator
{
    // On est gentil avec l'utilisateur
    static_assert(is_iterator<IteratorTemplate>::value,"Le type IteratorTemplate doit etre un itérateur");

     private :

        // Le probleme : 
        using typeDeRetour =               ?????????????? 
        using typeDuParam  =               ??????????????

        // la solution : 
        // using typeDeRetour = decltype(typeRetour(std::declval<FoncteurTemplate>()));
        // using typeDuParam  = decltype(typeParam<0>(std::declval<FoncteurTemplate>())); 


        // Le reste
        IteratorTemplate iterateur;
        std::function<typeDeRetour (typeDuParam ) > foncteur;

    public:
        // on veux itérer sur une conteneur sans avoir a re-coder son comportement, du coup on le garde en
        // attribut et on l'intéroge à chaque opération.
        FoncteurIterator(IteratorTemplate a):  iterateur(a) , foncteur(FoncteurTemplate()){}; //Si on un constructeur par defaut
        FoncteurIterator(IteratorTemplate a, FoncteurTemplate ft):  iterateur(a) , foncteur(ft){}; // si on a un constructeur par copie


        // les méthodes ou on fait rien de particulier
        bool operator!=(FoncteurIterator &i2) const { return iterateur != i2.iterateur; }
        FoncteurIterator<IteratorTemplate,FoncteurTemplate>& operator++() { iterateur++; return *this; }
        void operator+=(int b) { iterateur += b; }
        /// Je suis par sur du type de retour car j'ai pas bien l'idée de l'usage
        /// il faudrait peut etre retourner un "foncteurIterator"
        decltype(IteratorTemplate()-IteratorTemplate()) operator-(const FoncteurIterator &i2) const { return iterateur - i2.iterateur; }

        // les méthodes qui utilisent les foncteurs

        typeDeRetour operator*() const { return foncteur(*iterateur);}
        typeDeRetour operator->() const {return operator*();  }

};


/*

Le foncteur qui va bien pour notre cas

*/

namespace std {
    template<class T>
    struct UnWrappe
    {
        typedef T value_type;
        T& operator()(std::reference_wrapper<T> refWrap ) { return refWrap.get(); }
    };

    // on a besoin de l'opérateur == pour faire des truc comme find sur un vecteur<wrap>
    // il faut aussi que T ait ==;
    template<class T>
    bool operator==(std::reference_wrapper<T> un, std::reference_wrapper<T> deux)
    {
        return un.get()==deux.get();
    }
}


#endif // ITERATEUR_FONCTEUR_HPP
