#ifndef FONCTION_CONTENEUR_HPP
#define FONCTION_CONTENEUR_HPP

// ne marche pas pour les maps car contains(maMapDeIntInt, int) ne matche pas contains(maMapDeIntInt,pair<int,int>)
template<class ConteneurTemplate>
bool contains ( ConteneurTemplate& conteneur, typename ConteneurTemplate::value_type& value)
{
    return std::find(conteneur.begin(),conteneur.end(),value) != conteneur.end();
}

template<class MapTemplate>
bool contains ( MapTemplate& uneMap,const typename MapTemplate::key_type& value)
{
    return uneMap.find(value) != uneMap.end();
}

#endif // FONCTION_CONTENEUR_HPP
