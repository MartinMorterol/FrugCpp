#ifndef ITERATEUR_FONCTEUR_HPP
#define ITERATEUR_FONCTEUR_HPP

#include <functional>
#include "paramInfo.hpp"


/**
\class UnWrappe
\brief Classe foncteur qui retourne la référence contenu dans le wrapper passé en param
\details La class sert à "dé-wrapper" un wrapper, si vous avez un bon nom je suis preneur.
*/

namespace std {
    template<class T>
    struct UnWrappe
    {
        typedef T value_type;
        T& operator()(std::reference_wrapper<T> refWrap ) const { return refWrap.get(); }
    };

    // on a besoin de l'opérateur == pour faire des truc comme find sur un vecteur<wrap>
    // il faut aussi que T ait ==;
    template<class T>
    bool operator==(std::reference_wrapper<T> un, std::reference_wrapper<T> deux)
    {
        return un.get()==deux.get();
    }
}



/**
\class FoncteurIterator
\brief Classe permétant d'ajouter une méthode dans le déférancement de l'itérateur
\details Innitalement concus pour itérer sur un conteneur de ref_wrap sans avoir à faire le .get()

TODO : REFACTORISER POUR QU'ON PUISSE UTILISER UN FONCTEUR DANS UNE STD::FONCTION ET PAS QUE UN TYPE
CF : INDICE_TO_CASE
*/

// tout ça c'est pour un static assert qui marche pas comme il devrait.
// je garde en attente de l'avis d'un pro :p
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
    static_assert(is_iterator<IteratorTemplate>::value,"Le type IteratorTemplate doit etre un itérateur");

     private :
        //using typeDeRetour = decltype(typeRetour(std::declval<FoncteurTemplate>()));
       // using typeDuParam  = decltype(typeParam<0>(std::declval<FoncteurTemplate>()));

        IteratorTemplate iterateur;
        //std::function<typeDeRetour(typeDuParam)> foncteur;
        FoncteurTemplate foncteur;

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


/**
NE MARCHE PAS POUR L'INSTANT
*//*
template <class Terrain>
struct indiceToCase
{
    std::reference_wrapper<Terrain> terrain;
    indiceToCase(std::reference_wrapper<Terrain> monTerrain) : terrain(monTerrain) {}
    Case& operator()(std::size_t indice) { return terrain.get().getCase(indice); }
};*/


#endif // ITERATEUR_FONCTEUR_HPP
