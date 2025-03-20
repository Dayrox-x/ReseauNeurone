/**
 * \file save.h
 * \brief Fonctions de sauvegarde et de chargement d'un reseau de neurones
 * \author Claire Besançon
 * \date 20/03/2025
 */

 #include "neuron.h"
 #include "population.h"
 
 /**
  * \fn void save(Couche *reseau)
  * \brief Sauvegarder les données du réseau de neurones
  * \param reseau
  * Réseau de neurones -> pointeur sur la première couche du réseau
  */
 void save(Couche *reseau);
 
 
 /**
  * \fn void read(Couche *reseau)
  * \brief Récupérer les données du dernier réseau de neurones sauvegardé
  * \param reseau
  * Réseau de neurones -> pointeur sur la première couche du réseau
  */
 void read(Couche *reseau);