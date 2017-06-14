#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <map>

class Ckarta
{
  std::string Color;
  uint16_t    Value;
  std::string Figure;
  public:
  Ckarta(std::string _figure, uint16_t _value, std::string _color);
  uint16_t    getValue();
  std::string getFigure();
  std::string getColor();
};

Ckarta::Ckarta(std::string _figure, uint16_t _value, std::string _color)
  : Color(_color),
    Figure(_figure),
    Value(_value)
{}

uint16_t      Ckarta::getValue(){return Value;}
std::string   Ckarta::getFigure(){return Figure;}
std::string   Ckarta::getColor(){return Color;}

class Factory_Ckarta
{
  public:
    Ckarta* CreateInstance(std::string _figure, uint16_t _value, std::string _Color);
};

Ckarta* Factory_Ckarta::CreateInstance(std::string _figure, uint16_t _value, std::string _Color)
{
  Ckarta* obj = new Ckarta( _figure, _value, _Color);
  return obj;
}


class Player
{
 protected:
  std::string Name;
  uint16_t    Score;
  std::vector<Ckarta*> MyCard;
 public:
  Player(std::string _Name);
  virtual ~Player();
  virtual void addCard(Ckarta*);
  virtual void EraseCards();
  virtual void ViewCards() const;
  virtual void     setScore(uint16_t);
  virtual uint16_t getScore();
  virtual uint16_t check();
  virtual uint16_t move(Ckarta* NewCard){};
  virtual std::string getName();
};

Player::Player(std::string _Name)
  : Name(_Name), Score(0) {}

Player::~Player()
{
  MyCard.clear();
}

void Player::addCard(Ckarta* NewCard)
{
  MyCard.push_back(NewCard);
}

void Player::EraseCards()
{
  MyCard.clear();
}

void Player::ViewCards() const
{
  for(auto iter = MyCard.cbegin(); iter < MyCard.cend(); iter++)
    std::cout<<"Wartość: "<<(*iter)->getValue()
             <<" | Figura:  "<<(*iter)->getFigure()
             <<" | Kolor:   "<<(*iter)->getColor()
             <<std::endl;
  std::cout<<"---------------------------------"<<std::endl
             <<"Punkty: "<<Score<<std::endl;
}

void     Player::setScore(uint16_t new_value){ Score += new_value;}
uint16_t Player::getScore(){return Score;}

uint16_t Player::check()
{
  uint16_t flag=0;
  for(auto iter = MyCard.cbegin(); iter < MyCard.cend(); iter++)
  {
    if( (*iter)->getFigure() == "As" )
        flag++;
  }

  flag == 2 ? flag = 8 : flag = 0;
  return flag;
}

std::string Player::getName(){return Name;}

class DeckCards
{
  std::map<uint16_t, Ckarta*> Deck;
  Factory_Ckarta* CreateCards;
  public:
  DeckCards();
  ~DeckCards();
  Ckarta* getCkarta(const uint16_t&);
};

DeckCards::DeckCards()
{
  std::string Color[4];
  std::string Figure[13];
  CreateCards = new Factory_Ckarta;

  Color[0] =  "kier";
  Color[1] =  "pik";
  Color[2] =  "karo";
  Color[3] =  "trefl";

  for(int i = 2; i <= 10; i++)
    Figure[i-2] = char('0' + i);

  Figure[9]  = "Walet";
  Figure[10] = "Dama";
  Figure[11] = "Krol";
  Figure[12] = "As";


  for(uint16_t A = 0; A < 4; A++)
  {
    for(uint16_t i = 0; i < 9; i++)
      Deck.insert(std::pair<uint16_t, Ckarta*>( (13*A+i+1), CreateCards->CreateInstance(Figure[i], i+2, Color[A]) ) );

    Deck.insert(std::pair<uint16_t, Ckarta*>( (A*13+10), CreateCards->CreateInstance(Figure[9],  2, Color[A]) ) );
    Deck.insert(std::pair<uint16_t, Ckarta*>( (A*13+11), CreateCards->CreateInstance(Figure[10], 3, Color[A]) ) );
    Deck.insert(std::pair<uint16_t, Ckarta*>( (A*13+12), CreateCards->CreateInstance(Figure[11], 4, Color[A]) ) );
    Deck.insert(std::pair<uint16_t, Ckarta*>( (A*13+13), CreateCards->CreateInstance(Figure[12], 11, Color[A]) ) );
  }
}

Ckarta* DeckCards::getCkarta(const uint16_t& keyCard)
{
  std::map<uint16_t, Ckarta*>::iterator iter;
  iter = Deck.find(keyCard);
  return iter->second;
}


DeckCards::~DeckCards()
{
  delete CreateCards;
  for(std::map<uint16_t, Ckarta*>::iterator iter = Deck.begin(); iter != Deck.end(); iter++)
    delete iter->second;
  Deck.erase(Deck.begin(), Deck.end());
}


class Factory_Croupier;

class Croupier
{   std::string Name;
    DeckCards* AllCards;
    Croupier();
    Croupier(Croupier&);
    Croupier& operator= (Croupier&);
    std::vector<int> allRands;
    public:

    friend Factory_Croupier;
    ~Croupier();
    Ckarta* GiveCard();
    void    GivebackCard();
};

Croupier::Croupier()
  : Name("Krupier")
{
  AllCards = new DeckCards;
}

Croupier::~Croupier()
{
  delete AllCards;
}

Ckarta* Croupier::GiveCard()
{
  srand(time(NULL));

  int RandValue;
  uint16_t flag = 0;
  while(!flag)
  {
  flag = 1;
  RandValue = (rand() % 52 + 1);
  for(int i= 0; i < allRands.size() && allRands.size() ; i++)
    if(allRands.at(i) == RandValue)
    {
      flag = 0;
      break;
    }
  }
  allRands.push_back(RandValue);
  return AllCards->getCkarta((uint16_t)RandValue);
}
void Croupier::GivebackCard(){allRands.pop_back();}

class Participant : public Player
{
  uint16_t stop;
  public:
  Participant(const std::string&);
  uint16_t move(Ckarta* NewCard);
};

Participant::Participant(const std::string& _Name)
  : Player(_Name){ stop = 0;}

uint16_t Participant::move(Ckarta* NewCard)
{
 std::cout<<"Player: "<<Name<<" | "<<"Co zamierzasz zrobic? [1] - sprawdz jakie masz karty [2] - wez karte! [4] - zakoncz gre!"<<std::endl;
 char button;
 while(1)
 {
  if( getScore() >= 21 || check() )
     return 1;
  std::cin>>button;
  switch(button)
  {
   case('1'):
      ViewCards();
      break;
   case('2'):
      addCard(NewCard);
      setScore( NewCard->getValue() );
      ViewCards();
      NewCard = NULL;
      return 0;
   case('4'):
      return 1;
   }
 }
}

class Croupier_player : public Player
{
  uint16_t stop;
  public:
  Croupier_player(const std::string&);
  uint16_t move(Ckarta* NewCard);
};

Croupier_player::Croupier_player(const std::string& _Name)
  : Player(_Name){ stop = 0;}

uint16_t Croupier_player::move(Ckarta* NewCard)
{
  if( getScore() >= 21 || check() )
     return 8;
  else if(getScore() < 16)
  {
    addCard(NewCard);
    setScore( NewCard->getValue() );
   // ViewCards();
    NewCard = NULL;
    return 0;
  }
}


class Factory_Player
{
  public:
    virtual Player* Create(const std::string& ) = 0;
};

class Factory_Croupier
{
  public:
  Croupier* SingleInstance();
};

Croupier* Factory_Croupier::SingleInstance()
{
  static Croupier CROUP_static;
  return &CROUP_static;
}

class Factory_Participant : public Factory_Player
{
  public:
  Player* Create(const std::string&);
};

Player* Factory_Participant::Create(const std::string& _Name)
{
  Player* obj = new Participant(_Name);
  return obj;
}

class Factory_Croupier_player : public Factory_Player
{
  public:
  Player* Create(const std::string&);
};

Player* Factory_Croupier_player::Create(const std::string& _Name)
{
  Player* obj = new Croupier_player(_Name);
  return obj;
}

class Game
{
  std::map<uint16_t,Factory_Player*> Type_Gamers;
  Croupier*            Croupier_Engine;
  int* final_score;
  std::vector<Player*> Gamers;
  public:
  Game();
  ~Game();
  uint16_t WhoPlay();
  uint16_t WhoWin();
  void run();

};

Game::Game()
{
  Type_Gamers.insert(std::pair<uint16_t, Factory_Player*>(0, new Factory_Participant));
  Type_Gamers.insert(std::pair<uint16_t, Factory_Player*>(1, new Factory_Croupier_player));

  Factory_Croupier F_crp;
  Croupier_Engine = F_crp.SingleInstance();

  std::cout<<"Rozpocznij gre wybierajac: [0] gre lokalna lub [1] gre przez siec: "<<std::endl;
  char button='2';
  while(button != '0')
  {
    std::cin>>button;
    if(button == '1')
       std::cout<<"Gra przez siec jest jeszcze niedostepna, prosze wybrac opcje [0]"<<std::endl;
  }
  int Num=0;
  std::cout<<"Ilosc graczy (1-4): ";
  std::cin>>Num;
  std::string players_name[Num];

  auto Factory_method = Type_Gamers.find(1);
  Gamers.push_back(Factory_method->second->Create("Krupier"));
  Factory_method = Type_Gamers.find(0);

  for(int i=0; i < Num; i++)
  {
    std::cin.clear();
    std::cout<<"Wybierz nazwe gracza "<<i+1<<": ";
    std::cin>>players_name[i];
    Gamers.push_back( Factory_method->second->Create(players_name[i]) );
  }

  std::cout<<"Lista graczy: "<<std::endl;
  for(unsigned i=0; i< Num+1 ; i++)
    std::cout<<"Gracz "<<i<<": "<<Gamers[i]->getName()<<std::endl;
}

Game::~Game()
{
  for(auto iter = Type_Gamers.begin(); iter != Type_Gamers.end(); iter++)
    delete iter->second;
  for(std::vector<Player*>::iterator iter = Gamers.begin(); iter < Gamers.end(); iter++)
    delete *iter;
//  delete Croupier_Engine;
}

uint16_t Game::WhoPlay()
{
  int flag = 0;
  for(int i = 0; i < Gamers.size(); i++)
    if(*(final_score+i) )
      flag++;
  return Gamers.size() - (flag+1);
}

uint16_t Game::WhoWin()
{
  std::map<std::string, uint16_t> List_Score;
  for(int i=0; i < Gamers.size(); i++)
    List_Score.insert( std::pair<std::string, uint16_t>(Gamers[i]->getName() ,Gamers[i]->getScore() ) );
  for(auto iter = List_Score.cbegin(); iter != List_Score.cend(); iter++)
    std::cout<<"Player "<<iter->first<<": "<<iter->second<<std::endl;
}


void Game::run()
{
  std::cout<<"Gra rozpoczeta! "<<std::endl<<std::endl;

  Ckarta* NewCard = NULL;
  int amountGamers = Gamers.size();

  for(int i = 0; i < amountGamers; i++)
  {
    int re=0;
    while(re < 2)
    {
      NewCard = Croupier_Engine->GiveCard();
      Gamers[i]->addCard(NewCard);
      Gamers[i]->setScore(NewCard->getValue());
      NewCard = NULL;
      re++;
    }
  }

  final_score = new int[amountGamers];
//memset(final_score, 0, amountGamers);
  for(int i=0; i<amountGamers; i++)
    *(final_score+i) = Gamers[i]->check();

  int Crp_win=0;
  while( WhoPlay() )
  {
    for(int i=0; i< amountGamers && !(*(final_score+i)); i++)
    {
      *(final_score + i) = Gamers[i]->move( Croupier_Engine->GiveCard() );
      if(Gamers[i]->check() == 8 || *final_score)
      {
        Crp_win = 1;
        goto endloop;
      }
    }
  }

endloop:

  if(Crp_win)
    std::cout<<"Krupier wygyrwa! Oczko!"<<std::endl;
  else
    WhoWin();
  std::cout<<"Gra zakonczona. Zapraszmy ponownie!"<<std::endl;
  delete[] final_score;
}

int main()
{
  Game start0_7;
  start0_7.run();
}

