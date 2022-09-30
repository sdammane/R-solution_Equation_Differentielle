#ifndef _ODESOL_HPP_
#define _ODESOL_HPP_
#include "EquaDiff.hpp"



class OdeSolver{

public:

  OdeSolver(double ,Equation *,double);//Constructeur qui initialise le pas de temps et le schéma numérique

  double& run(); //détermine la solution approchée yN

  double error(); //Fonction qui retroune l'erreur entre yN et la solution exacte


private:

  //La variable décrivant les schémas numériques
  double numShema;  // numShema = 1 correspond à la méthode d'Euler numShema = 2 à RungeKutta2
  Equation* p3;//Le pointeur pointe vers la méthode de f(tN,yN)

  double tN;//Le temps actuel de la résolution

  double dt;//Le pas de temps pour déterminer yN
  double yN;//La solution approchée au temps tN
  double yNP1; //variable utilisé pour la méthode de Euler et de RungeKutta2

  //Les méthodes numériques pour détemriner la solution approchée
  void oneStepEuler();
  void oneStepRK2();
};

#endif
