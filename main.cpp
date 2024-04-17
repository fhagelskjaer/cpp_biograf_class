#include <string>
#include <vector> 
#include <iostream>

class Saede
{
    public:
    int _nr;
    Saede(){}
    Saede(int nr)
    {
        _nr = nr;
    }
};

class Raekke
{
    public:
    int _nr;
    std::vector<Saede> _saede;
    Raekke(){}
    Raekke(int nr)
    {
      _nr = nr;
    }
    void addSaede(int nr)
    {
       _saede.push_back(Saede(nr));
    }
};

class Sal
{
    public:
    int _nr;
    std::vector<Raekke> _raekke;
    Sal(){}
    Sal(int nr)
    {
      _nr = nr;
    }
    void addRaekke(int nr)
    {
       _raekke.push_back(Raekke(nr));
    }
};

class Film
{
    public:
    std::string _navn;
    int _laengde;
    Film(){}
      Film(std::string navn, int laengde)
      {
          _navn = navn;
          _laengde = laengde;
      } 
};

class Reservation
{
  public:
  Saede _saede;
  Reservation(const Saede& saede)
  {
    _saede = saede;
  }
};

// bool vector_contains(v, x){
//   return std::find(v.begin(), v.end(), x) != v.end();
// }


class Forestilling
{

  std::vector<Reservation> _reservationliste;

  public:
  Film _film;
  Sal _sal;
  int _starttid;

  
  Forestilling(){}

  Forestilling(const Film& film, const Sal& sal, int starttid)
  {
      _film = film;
      _sal = sal;
      _starttid = starttid;
  }

  bool addReservation(const Saede& saede){
        bool reserved = false;
        for(int k = 0; k < _reservationliste.size(); k++){
          if( _reservationliste[k]._saede._nr == saede._nr) {
            reserved = true;
            break;
          }
        }
        if( reserved ){
          return false;
        }
        _reservationliste.push_back(Reservation(saede));
        return true;
  }

  void printUnreservedSeats(){
    for(int i = 0; i < _sal._raekke.size(); i++){
      for(int j = 0; j < _sal._raekke[i]._saede.size(); j++){
        bool reserved = false;
        for(int k = 0; k < _reservationliste.size(); k++){
          if( _reservationliste[k]._saede._nr == _sal._raekke[i]._saede[j]._nr) {
            reserved = true;
            break;
          }
        }
        if( !reserved ){
          std::cout << _sal._raekke[i]._nr << " " << _sal._raekke[i]._saede[j]._nr << std::endl;
        }

        }
      }
  }


};

// class Reservation
// {
//   Forestilling _forestilling;
//   std::vector<Saede> _saede;

//   Reservation(const Forestilling& forestilling, std::vector<Saede> saede)
//   {
//       _forestilling = forestilling;
//       _saede = saede;
//   }
// };


class Controller
{

    public:

    std::vector<Sal> salliste;
    std::vector<Forestilling> forestillingliste;
    std::vector<Film> filmliste;
    

   bool addFilm(std::string name, int laengde){  
       filmliste.push_back(Film(name, laengde));
       return true;
   }

   void getFilmList(){
      for(int i = 0; i < filmliste.size(); i++){
        std::cout << i << " " << filmliste[i]._navn << std::endl;
      }
   }

   bool addSal(int nr){
        
        salliste.push_back(Sal(nr));
        for(int i = 0; i < 10; i++){
            salliste.back().addRaekke(i);
            for(int j = 0; j < 10; j++){
                salliste.back()._raekke.back().addSaede(j);
            }
        }
   
       return true;       
   }

   bool addForestilling(int film_idx, int sal_idx, int startid){  
       forestillingliste.push_back(Forestilling(filmliste[film_idx], salliste[sal_idx], startid));
       return true;
   }

  void getForestilling(){
      for(int i = 0; i < forestillingliste.size(); i++){
        std::cout << i << " " << forestillingliste[i]._film._navn << " in " << forestillingliste[i]._sal._nr << " at " << forestillingliste[i]._starttid << std::endl;
      }
  }

   bool addReservation(int forestilling_idx, int rn, int sn){  
       return forestillingliste[forestilling_idx].addReservation( forestillingliste[forestilling_idx]._sal._raekke[rn]._saede[sn]);
   }

};



int main(int argc, char**argv)
{
  Controller c;

  c.addSal(1);
  c.addSal(2);

  c.addFilm("diehard",10);  
  c.addFilm("lotr",15);
  c.addFilm("7s",40);

  c.getFilmList();

  c.addForestilling(0,0,0);
  c.addForestilling(0,1,0);
  c.addForestilling(1,1,10);
  c.addForestilling(1,1,25);

  c.forestillingliste[0].printUnreservedSeats();

  c.getForestilling();

  std::cout << "break" << std::endl;

  std::cout << c.addReservation(0, 0, 0) << std::endl;
  std::cout << c.addReservation(0, 0, 1) << std::endl;
  std::cout << c.addReservation(0, 0, 2) << std::endl;
  std::cout << c.addReservation(0, 0, 3) << std::endl;
  std::cout << c.addReservation(0, 0, 4) << std::endl;

  std::cout << c.addReservation(0, 0, 4) << std::endl;
  std::cout << c.addReservation(0, 0, 4) << std::endl;
  std::cout << c.addReservation(0, 0, 4) << std::endl;

  c.forestillingliste[0].printUnreservedSeats();
  
  return 0;
}
