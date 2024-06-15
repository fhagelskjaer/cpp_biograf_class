#include <string>
#include <vector> 
#include <iostream>

class Saede
{
    public:
    int _nr;
    int _rnr;
    Saede(){}
    Saede(int nr, int rnr)
    {
        _nr = nr;
        _rnr = rnr;
    }
};

class Sal
{
    public:
    int _nr;
    std::vector<Saede> _saede;
    Sal(){}
    Sal(int nr)
    {
      _nr = nr;
    }
    void addSaede(int nr, int rnr)
    {
       _saede.push_back(Saede(nr, rnr));
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
  bool _solgt;
  std::string _kunderef;

  Reservation(const Saede& saede, std::string kunderef)
  {
    _saede = saede;
    _kunderef = kunderef;
    _solgt = false;
  }
  void betalBillet(){
    _solgt = true;
  }

};

class Forestilling
{
 
  public:
  std::vector<Reservation> _reservationliste;
  Film _film;
  Sal _sal;
  int _starttid;
  int _pris;

  
  Forestilling(){}

  Forestilling(const Film& film, const Sal& sal, int starttid, int pris)
  {
      _film = film;
      _sal = sal;
      _starttid = starttid;
      _pris = pris;
  }

  bool addReservation(const Saede& saede, std::string kunderef){
        bool reserved = false;
        for(int k = 0; k < _reservationliste.size(); k++){
          if( _reservationliste[k]._saede._nr == saede._nr && 
               _reservationliste[k]._saede._rnr == saede._rnr ) {
            reserved = true;
            break;
          }
        }
        if( reserved ){
          return false;
        }
        _reservationliste.push_back(Reservation(saede, kunderef));
        return true;
  }

  int betalReservation(std::string kunderef){
    int sum = 0;
    for(int k = 0; k < _reservationliste.size(); k++){ 
      if( (!_reservationliste[k]._solgt) && _reservationliste[k]._kunderef == kunderef){
        _reservationliste[k].betalBillet();
        sum += _pris;
      }   
    }
    return sum;
  }

  std::vector<Saede> getUnreservedSeats(){
    std::vector<Saede> tempSaedeListe;

    for(int i = 0; i < _sal._saede.size(); i++){
        bool reserved = false;
        for(int k = 0; k < _reservationliste.size(); k++){
          if( _reservationliste[k]._saede._nr == _sal._saede[i]._nr && 
              _reservationliste[k]._saede._rnr == _sal._saede[i]._rnr  ) {
            reserved = true;
            break;
          }
        }
        if( !reserved ){
          tempSaedeListe.push_back(_sal._saede[i]);
          //std::cout << _sal._raekke[i]._nr << " " << _sal._raekke[i]._saede[j]._nr << std::endl; //slemt
        }

        }
      return tempSaedeListe;
  }

  int getTotalSales(){
    int sum = 0;
    for(int k = 0; k < _reservationliste.size(); k++){
      if(_reservationliste[k]._solgt){
        sum += _pris;
      }
    }
    return sum;
  }

  int getNoshows(){
    int sumsshow = 0;
    for(int k = 0; k < _reservationliste.size(); k++){
      // std::cout << _reservationliste[k]._kunderef << " " << _reservationliste[k]._solgt << std::endl;
      if(_reservationliste[k]._solgt){
        sumsshow += 1;
      }
    }
    return sumsshow;
  }

  double getReserved(){
    if(_reservationliste.size() == 0)
      return 0;

    int sumseats = 0;

    for(int i = 0; i < _sal._saede.size(); i++){
        sumseats += 1;
    }
    return double(_reservationliste.size())/double(sumseats);
  }


};

class Biograf
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

   bool addSal(int nr, int antal_raekker, int antal_saeder){
        salliste.push_back(Sal(nr));
        for(int i = 0; i < antal_raekker; i++){
            for(int j = 0; j < antal_saeder; j++){
                salliste.back().addSaede(1+j, 1+i);
            }
        }
   
       return true;       
   }

   bool addForestilling(int film_idx, int sal_idx, int startid, int pris){  
       forestillingliste.push_back(Forestilling(filmliste[film_idx], salliste[sal_idx], startid, pris));
       return true;
   }

  void getForestilling(){
      for(int i = 0; i < forestillingliste.size(); i++){
        std::cout << i << " " << forestillingliste[i]._film._navn << " in " << forestillingliste[i]._sal._nr << " at " << forestillingliste[i]._starttid << std::endl;
      }
  }

   bool addReservation(int forestilling_idx, int sn, std::string kunderef){
       return forestillingliste[forestilling_idx].addReservation(forestillingliste[forestilling_idx]._sal._saede[sn], kunderef);
   }


   int forestillingIndkomst(int forestilling_idx){
      return forestillingliste[forestilling_idx].getTotalSales();
   }

   int udregnSamletIndkomst(){
      int sum = 0;
      for(int i = 0; i < forestillingliste.size(); i++){
        sum += forestillingliste[i].getTotalSales();
      }
      return sum;
   }

   double udregnSamletNoshows(){
      int sumshow = 0;
      int sumreserved = 0;

      for(int i = 0; i < forestillingliste.size(); i++){
        sumshow += forestillingliste[i].getNoshows();
        sumreserved += forestillingliste[i]._reservationliste.size();
      }
      if(sumreserved == 0)
        return -1;
      return double(sumreserved-sumshow)/double(sumreserved);
   }

  void printUnreservedSeats(int forestilling_idx){
    std::vector<Saede> tempSaedeListe = forestillingliste[forestilling_idx].getUnreservedSeats();
    for(int i = 0; i < tempSaedeListe.size(); i++){
      std::cout << "idx: " << i << " rknr " << tempSaedeListe[i]._rnr << " saedenr " << tempSaedeListe[i]._nr << std::endl;
    }
  }

   double getReserved(int forestilling_idx){
    return forestillingliste[forestilling_idx].getReserved();
   }

   int betalBillet(int forestilling_idx, std::string kunderef)
   {
      return forestillingliste[forestilling_idx].betalReservation(kunderef);
   }


};

int main(int argc, char**argv)
{
  Biograf bio;

  bio.addSal(1, 5, 5);
  bio.addSal(2, 10, 10);

  bio.addFilm("diehard",10);  
  bio.addFilm("lotr",15);
  bio.addFilm("7s",40);

  bio.getFilmList();

  bio.addForestilling(0, 0, 0, 15);
  bio.addForestilling(0, 1, 0, 12);
  bio.addForestilling(1, 1, 10, 20);
  bio.addForestilling(1, 1, 25, 15);


  bio.getForestilling();

  bio.printUnreservedSeats(0);

  std::cout << "break" << std::endl;

  std::cout << bio.addReservation(0, 0, "john") << std::endl;
  std::cout << bio.addReservation(0, 1, "john") << std::endl;
  std::cout << bio.addReservation(0, 2, "henrik") << std::endl;
  std::cout << bio.addReservation(0, 3, "bettina") << std::endl;
  std::cout << bio.addReservation(0, 4, "bettina") << std::endl;

  std::cout << bio.addReservation(0, 4, "bettina") << std::endl;
  std::cout << bio.addReservation(0, 4, "bettina") << std::endl;
  
  std::cout << bio.addReservation(0, 5, "bettina") << std::endl;

  bio.printUnreservedSeats(0);

  std::cout << "billetpris " << bio.betalBillet(0, "bettina") << std::endl;
  std::cout << "billetpris " << bio.betalBillet(0, "bettina") << std::endl;

  std::cout << "forestillingIndkomst " << bio.forestillingIndkomst(0) << std::endl;
  std::cout << "udregnSamletNoshows " << bio.udregnSamletNoshows() << std::endl;
  std::cout << "getReserved " << bio.getReserved(0) << std::endl;


  return 0;
}
