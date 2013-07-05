#ifndef ENNEMY_HPP_INCLUDED
#define ENNEMY_HPP_INCLUDED

#include "Player.hpp"

enum Behaviour {STANDBY, ATTACK, ESCAPE, FOLLOW};

class Ennemy
{
  public:
  virtual void Update()=0;
  void SetTarget(Player &NewTarget);
  int GetKillPoint() const;
  void ChangeBehaviour(Behaviour NewBehaviour);
  Ennemy* getAdresse();

  protected:
  int vie;
  int point;
  Player *my_target;
  Behaviour my_behaviour;
};

#endif // ENNEMY_HPP_INCLUDED
