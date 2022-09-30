#include "OdeSol.hpp"
#include "EquaDiff.hpp"
#include <iostream>
#include <cmath>


//yN représente la solution obtenue en utlisant soit la méthode d'Euler
//Ou la méthode de Runge Kutta


// La méthode d'Euler explicite
void OdeSolver:: oneStepEuler(){

      yNP1 = yN + dt * p3->fTest( tN , yN ); //utiliationd u pointeur p3 afin de prendre l'équation f(t,y)
      yN   =  yNP1;
      //tN+=dt; //Le pas de temps tN
}


// La méthode de RungeKutta d'ordre 2
void OdeSolver::oneStepRK2(){

  double k1;
  double k2;

    k1 = p3-> fTest( tN, yN );
    k2 = p3-> fTest( tN+ (0.5) * dt , yN+ (0.5) * dt * k1 );

    yNP1 = yN + dt * k2;
    yN   =   yNP1; //Changement de la valeur de yN
      //tN += dt; //Le pas de temps
}


//Le constructeur qui initialise les données

OdeSolver::OdeSolver( double numShem , Equation* p6 , double dt1 ){

  //Je n'arrive pas à comprendre en quoi sert le pointeur Equation dans l'argument du constructeur.
  //Je ne l'ai donc pas utlisé

  yN = 0;//Initialisation de yn
  tN = 0;//Initialisation de tn
  dt = dt1;//Initialisation du pas de temps

  p3->fTest(tN,yN);//Le pointeur de la classe Ode pointe vers fTest

  numShema = numShem;
}


//LA fonciton qui permet de déterminer la solution approchée
//en fonction de la méthode d'Euler ou de RungeKutta d'ordre 2

double& OdeSolver::run(){


  //Si la variable correspond au shéma d'Euler
  if( numShema == 1 ){

    //En utlisant la boucle while j'obtiens un dt> 10 qui est le temps final de l'équation différentielle.
    //Par exemple si dt=0.1 tN= 10.1 alors que j'aurais voulu que tN=10

    //J'opte donc pour une boucle for avec un pas de dt.
    //Et j'attribut tN à la valeur de i.(Pour faire en sorte que tN=+dt)

    //while (  tN < tf ){
      //oneStepEuler();
        //tN+=dt;
        //std::cout<<"tN Euler:"<<tN<<std::endl;
    //}



    for ( double i = tN; i < 10 ; i += dt ){ //Tant que le temps ne dépasse pas de le temps final executer la méthode
        oneStepEuler();
        tN = i;                             //Si dt=0.1 alors  tN={0.1 , 0.2 ,0.3 , ...... ,10}
        //std::cout<<"tN Euler:"<<tN<<std::endl;
    }
  }


  //Si la variable correspond au shméa de RungeKutta
  else if( numShema == 2 ){
    //while (tN < 10){
      //oneStepRK2();
    //}

    for ( double i = tN; i < 10 ; i += dt ){ //Tant que le temps ne dépasse pas de le temps final executer la méthode
        oneStepRK2();
        tN = i;
    }
  }

  return yN;
}



//La fonction qui calcul l'erreur commises en =tre la solution approche yN et
//la solution exacte
double OdeSolver::error(){

  run(); //Appliquer la méthode run afin de déterminer yN
  //Ici tN =10
  return std::abs ( (-1+ sqrt( (tN) *(tN) +1)) -yN );
}
