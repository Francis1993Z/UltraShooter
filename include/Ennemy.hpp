#ifndef ENNEMY_HPP_INCLUDED
#define ENNEMY_HPP_INCLUDED

#include "Player.hpp"

enum Behaviour {STANDBY, ATTACK, ESCAPE, FOLLOW};

class Ennemy
{
  public:
  virtual void Update()=0;
  void ApplyForce(float fx, float fy);
  void SetTarget(Player &NewTarget);
  float get_dRadius() const;
  int GetKillPoint() const;
  void ChangeBehaviour(Behaviour NewBehaviour);
  Ennemy* getAdresse();
  void takeDamage(unsigned int damage);
bool alive() const;
int getKillPoint() const;


  protected:
  int vie;
  int kill_point;
  Player *my_target;
  Behaviour my_behaviour;
  float d_radius, m_fx, m_fy;
  float e_mx, e_my;
};

#endif // ENNEMY_HPP_INCLUDED
