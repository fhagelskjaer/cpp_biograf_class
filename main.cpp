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
  Raekke _raekke;
  bool _solgt;
  std::string _kunderef;

  Reservation(const Saede& saede, const Raekke& raekke, std::string kunderef)
  {
    _saede = saede;
    _raekke = raekke;
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

  bool addReservation(const Saede& saede, const Raekke& raekke, std::string kunderef){
        bool reserved = false;
        for(int k = 0; k < _reservationliste.size(); k++){
          if( _reservationliste[k]._saede._nr == saede._nr && 
               _reservationliste[k]._raekke._nr == raekke._nr ) {
            reserved = true;
            break;
          }
        }
        if( reserved ){
          return false;
        }
        _reservationliste.push_back(Reservation(saede, raekke, kunderef));
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

  void printUnreservedSeats(){
    for(int i = 0; i < _sal._raekke.size(); i++){
      for(int j = 0; j < _sal._raekke[i]._saede.size(); j++){
        bool reserved = false;
        for(int k = 0; k < _reservationliste.size(); k++){
          if( _reservationliste[k]._saede._nr == _sal._raekke[i]._saede[j]._nr && 
              _reservationliste[k]._raekke._nr == _sal._raekke[i]._nr  ) {
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

    for(int i = 0; i < _sal._raekke.size(); i++){
      for(int j = 0; j < _sal._raekke[i]._saede.size(); j++){
        sumseats += 1;
      }
    }
    return double(_reservationliste.size())/double(sumseats);
  }


};

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

   bool addForestilling(int film_idx, int sal_idx, int startid, int pris){  
       forestillingliste.push_back(Forestilling(filmliste[film_idx], salliste[sal_idx], startid, pris));
       return true;
   }

  void getForestilling(){
      for(int i = 0; i < forestillingliste.size(); i++){
        std::cout << i << " " << forestillingliste[i]._film._navn << " in " << forestillingliste[i]._sal._nr << " at " << forestillingliste[i]._starttid << std::endl;
      }
  }

   bool addReservation(int forestilling_idx, int rn, int sn, std::string kunderef){  
       return forestillingliste[forestilling_idx].addReservation(forestillingliste[forestilling_idx]._sal._raekke[rn]._saede[sn],
                                                                  forestillingliste[forestilling_idx]._sal._raekke[rn], kunderef);
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
  Controller c;

  c.addSal(1);
  c.addSal(2);

  c.addFilm("diehard",10);  
  c.addFilm("lotr",15);
  c.addFilm("7s",40);

  c.getFilmList();

  c.addForestilling(0, 0, 0, 15);
  c.addForestilling(0, 1, 0, 12);
  c.addForestilling(1, 1, 10, 20);
  c.addForestilling(1, 1, 25, 15);

  c.forestillingliste[0].printUnreservedSeats();

  c.getForestilling();

  std::cout << "break" << std::endl;

  std::cout << c.addReservation(0, 0, 0, "john") << std::endl;
  std::cout << c.addReservation(0, 0, 1, "john") << std::endl;
  std::cout << c.addReservation(0, 0, 2, "henrik") << std::endl;

  std::cout << c.addReservation(0, 0, 3, "bettina") << std::endl;
  std::cout << c.addReservation(0, 0, 4, "bettina") << std::endl;

  std::cout << c.addReservation(0, 0, 4, "bettina") << std::endl;
  std::cout << c.addReservation(0, 1, 4, "bettina") << std::endl;
  std::cout << c.addReservation(0, 1, 4, "bettina") << std::endl;

  c.forestillingliste[0].printUnreservedSeats();
  
  std::cout << "billetpris " << c.betalBillet(0, "bettina") << std::endl;
  std::cout << "billetpris " << c.betalBillet(0, "bettina") << std::endl;

  std::cout << "forestillingIndkomst " << c.forestillingIndkomst(0) << std::endl;
  std::cout << "udregnSamletNoshows " << c.udregnSamletNoshows() << std::endl;
  std::cout << "getReserved " << c.getReserved(0) << std::endl;


  return 0;
}
