#include <iostream>
#include <fstream>
#include "EquaDiff.hpp"
#include "OdeSol.hpp"
#include <vector>
#include <cmath>



//La fonction evalError
double evalError( double numShem, double deltaT ){

//Déclaration des variables
  double err;
  double tF  = 10; //Le temps final de l'équation différentielle
  double soluexacte = -1+ sqrt( (tF * tF) + 1); //La solution exacte au temps final


  //Création d'une pointeur de type Equation
  //pour l'utilisation dans l'instance de ODE
  Equation* p;

  OdeSolver Yn(numShem,p,deltaT); //Creation de l'instance Ode en fonction de la méthode utilisée

  //Prendre la fonction membre error pour déterminer  |Y(tf) - Y(tN)| On sait que tN=10
  err = Yn.error() / std::abs( soluexacte);
  return err;
}


//La fonction principale
int main() {

  //Les conditions initiales de l'équation différentielle
  double t_0, t_f, y_0;

  t_0 = 0;  // Le temps de début de l'équation différentielle
  t_f = 10; //Le temps final de l'équation différentielle
  y_0 = 0;  //La valeur initiale de l'équation différentielle

  //Le pas de temps pour les méthodes d'Euler et de RungeKutta
  double dt = 0.1;

  //Creation d'une instance de la class equation
  Equation y( t_0 , t_f , y_0 ); //Initialisation des valeurs dans la classe


  //Teser les fonctions memebres de la classe Equation
  //tester les solutions exactes sur [0,10]
  std::cout<< "Les solutions exactes sur [0,10]:" << std::endl;
  for( int t = 0 ; t <= 10 ; t++ ){

    std::cout<< "y" << "(" << t << ")= " << y.soluExact(t) << std::endl;
  }

  std::cout<<std::endl;
  //tester les valeurs de f(t,y)
  std::cout<< "Les valeurs de f(t,y): " << std::endl;
  for( int t = 0 ; t <= 10 ; t++ ){

    std::cout << "f" << "(" << t << "," << y.soluExact(t) << ")= " << y.fTest( t,y.soluExact(t) )<< std::endl;
  }

  std::cout<<std::endl;
  //Vérifier si le temps est dépassé ou non
  double t1 = 1;
  y.finished(t1);
  std::cout<<std::endl;



  //test sur la class OdeSolver
  //Les variables pour déterminer les shémas numérique utilisée
  double e,r;
  e = 1; //Correspond à la méthode d'Euler
  r = 2;  //Correspond à la méthode de RungeKutta d'ordre2


  //Creation d'un pointeur de type Equation
    Equation* p1;

    //creation d'une instance de OdeSolver
    OdeSolver y1( e , p1 , dt ); //Utilisation de la méthode de Euler
    OdeSolver y2( r , p1 , dt ); //Utilisation de la méthode de RungeKutta



    std::cout << "Test unitaire sur les erreurs" << std::endl;
    std::cout << "error avec la methode d ' Euler: " << y1.error() << std::endl;
    std::cout << "error avec la methode de RungeKutta2: " << y2.error() << std::endl;

    std::cout<<std::endl;


  //Création d'un fichier pour afficher les solutions approximatives au temps t=10 en fonction
  //des méthodes d'Euler et de Runge Kutta d'ordre 2
  std::vector<double> yEuler (10);
  std::vector<double> yKutta (10);
  std::vector<double> dT= {0.1,0.001,0.02,0.04}; //Les différents pas de temps à prendre

  std::string("LesSolutionsDeY.dat");
  std::ofstream oFile("LesSolutionsDeY.dat");


  for(double i: dT){

      OdeSolver y3 (e, p1 ,i);//Euler avec un pas de dT
      OdeSolver y4 (r, p1 ,i);//Kutta avec un pas de dT

      yEuler.push_back (y3.run());
      yKutta.push_back (y4.run());

      std::cout<< "dt: " << i <<" \t y(Euler)=  " << yEuler.back() <<" \t y(RK2)=  " << yKutta.back() <<std::endl;

      oFile <<"dt: "<<i << " \t y(Euler)="<< yEuler.back() <<  " \t y(RK2)= "<< yKutta.back() <<" \t y(exacte)=  "<< y.soluExact(10) << std::endl;
  }

  std::cout<<std::endl;

  std::vector<double> errorEuler (10);
  std::vector<double> errorKutta (10);

  //Creation de fichier pour afficher les valeurs de la fonction error()

  std::string("LesErreursDesMethodes.dat");

  std::ofstream oFile1("LesErreursDesMethodes.dat");


  for(double i: dT){

      OdeSolver y5 (e, p1 ,i);//Euler avec un pas de dT
      OdeSolver y6 (r, p1 ,i);//Kutta avec un pas de dT

      errorEuler.push_back (y5.error());
      errorKutta.push_back (y6.error());

      //std::cout<< "dt: " << i <<"\t y(Euler)= " << errorEuler.back() <<"\t y(RK2)= " << yKutta.back() <<std::endl;

      oFile1 <<"dt: "<<i << " \t error(Euler)="<< errorEuler.back()<<  " \t error(RK2)= "<<errorKutta.back()<<std::endl;
  }

  std::cout<<std::endl;



  //test unitaire sur la fonction evalError en fonction de Euler et de RungeKutta
  std::cout<< "la fonction evalError avec la methode Euler et  " << "dt:" <<dt<<std::endl;
  std::cout<< "evalError: " << evalError(e,dt) <<std::endl;

  std::cout<<std::endl;

  std::cout<< "la fonction evalError avec la methode de RungeKutta2 et  " << "dt:" << dt << std::endl;
  std::cout<< "evalError: " << evalError(r,dt) << std::endl;

  std::cout<<std::endl;


  //creation de fichier txt pour la fonction evalError

  std::vector < double > errE (4);//La fonction evalError pour la méthode d'Euler
  std::vector < double > errR (4); //La méthode evalError pour la méthode de RungeKutta2

  std::string("errEDO.dat");
  std::ofstream oFile2 ("errEDO.dat");

    for ( double dt1: dT ){

      errE.push_back ( evalError(e,dt1) );
      errR.push_back ( evalError(r,dt1) );

      std::cout << "dt: \t" << dt1 << " \t errorEuler: " <<errE.back()<< " \t errorkutta: "<< errR.back() << std::endl;

      oFile2 <<dt1 << " \t  "<< errE.back()<<  " \t  "<<errR.back()<< std::endl;
  }
  return 0;
}
