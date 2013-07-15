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
  int getKillPoint() const;
  int getVie() const;
  unsigned int getDamage() const;
  float get_dRadius() const;
  void ChangeBehaviour(Behaviour NewBehaviour);
  Ennemy* getAdresse();
  void takeDamage(unsigned int damage);
  bool alive() const;
  float getSpeed() const;
  void subirDegats(unsigned int p_damage);


  protected:
  int vie;
  int damage;
  int kill_point;
  Player *my_target;
  Behaviour my_behaviour;
  float d_radius, m_fx, m_fy;
  float e_m,e_mx, e_my;
};

#endif // ENNEMY_HPP_INCLUDED
