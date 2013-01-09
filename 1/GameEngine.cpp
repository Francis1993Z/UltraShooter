#include "GameEngine.hpp"

using namespace std;
using namespace sf;

GameEngine::GameEngine(unsigned int LF, unsigned int HF, unsigned int BM)
{
    LargeurFenetre=LF;
    HauteurFenetre=HF;
App.Create(VideoMode(LargeurFenetre, HauteurFenetre, BM), "SFML");
App.SetFramerateLimit(60);
Running=true;
}

int GameEngine::func()
{
return 0;
}

int GameEngine::Run()
{

        Player Me(LargeurFenetre/2, HauteurFenetre/2, sf::Color(0,0,0,0), 20.00f, 5.00f, sf::Color::Blue, MACHINEGUN, App, ImgManager);

    HUD Interface(&Me, sf::Vector2f(10, HauteurFenetre-35), App);

    std::vector<Bullet> BulletArray;

    std::vector<Ennemi> EnnemiArray;

    sf::Clock addEnnemi, Bouttontime;

    sf::Vector2f MousePosition;

const float normal_Delay=0.15f;
float DelayPourcentage=100;
float current_Delay=DelayPourcentage*normal_Delay/100;
Me.SetDelayAnimation(current_Delay);
     while(Running)
    {

        while(App.IsOpened())
        {
current_Delay=DelayPourcentage*normal_Delay/100;

            MousePosition.x=App.GetInput().GetMouseX();
            MousePosition.y=App.GetInput().GetMouseY();


            while (App.GetEvent(Event))///Events
            {

                if (Event.Type == Event::Closed)///Boutton X
                {
                    App.Close();
                    Running=false;
                }

                else if(Event.Key.Code == sf::Key::E)///Changement pour arme suivante
                {

                if(Bouttontime.GetElapsedTime()>=0.15)//Temps d'intervalle avant d'agir car l'execution est très rapide
                {//                                      ce qui peut donné 50 actions alors qu'on a appuyé que 0.5s
                    //cout<<"I have pressed space key"<<endl;
            Me.NextWeapon();
            Bouttontime.Reset();
            }
                }///Fin Changement arme suivante
                                else if(Event.Key.Code == sf::Key::Q)///Changement pour arme précédante
                {

                if(Bouttontime.GetElapsedTime()>=0.15)//Temps d'intervalle avant d'agir car l'execution est très rapide
                {//                                      ce qui peut donné 50 actions alors qu'on a appuyé que 0.5s
                    //cout<<"I have pressed space key"<<endl;
            Me.PreviousWeapon();
            Bouttontime.Reset();
            }
                }///Fin Changement arme précédante
             else if(Event.Key.Code == sf::Key::Add)
                {
                DelayPourcentage++;
                Me.SetDelayAnimation(current_Delay);
                }
             else if(Event.Key.Code == sf::Key::Subtract)
                {
                DelayPourcentage--;
                Me.SetDelayAnimation(current_Delay);
                }
                else if (Event.Key.Code == sf::Key::F1)///Capture d'écran
{
    sf::Image Screen = App.Capture();
    Screen.SaveToFile("screenshot.jpg");
}


        }///Fin des Event
/*-------------------------------------------------------------------------------------------------------------------*/
///Ajout d'ennemis
            if(addEnnemi.GetElapsedTime()>0.5f)//Fréquence
            {

                int w=LargeurFenetre, h=HauteurFenetre;
                sf::Vector2f newpos;//Position aléatoire
                newpos.x=sf::Randomizer::Random(0, w);
                newpos.y=sf::Randomizer::Random(0, h);
                EnnemiArray.push_back(Ennemi(newpos.x, newpos.y, sf::Color(0,0,0,0), sf::Randomizer::Random(5, 30), 10.00f, sf::Color::Red));
                EnnemiArray.back().ChangeBehaviour(ATTACK);
EnnemiArray.back().SetTarget(Me);
//cout<<EnnemiArray.back().MyAdress()<<endl;
                addEnnemi.Reset();
            }
/*-------------------------------------------------------------------------------------------------------------------*/
            Me.UpdateEvent(App);
            Interface.Update();

/*-------------------------------------------------------------------------------------------------------------------*/
///Shooting phase
if(Me.ReadyToShoot()==true)
{
    Me.Shoot(BulletArray, MousePosition);
}
/*-------------------------------------------------------------------------------------------------------------------*/
///Mouvement des ennemis
  for(unsigned int q=0; q<EnnemiArray.size(); q++)
                {
                EnnemiArray.at(q).Update();
                }
/*-------------------------------------------------------------------------------------------------------------------*/
///Mouvement des projectiles
            for(unsigned int i=0; i<BulletArray.size(); i++)
            {
                BulletArray.at(i).UpdatePosition();


                if(BulletArray.at(i).CIO()==true)//Suppresion des projectiles hors de l'écran
                {
                    //BulletArray.at(i).~Bullet();
                    BulletArray.erase(BulletArray.begin() + i);
                }

            }
/*-------------------------------------------------------------------------------------------------------------------*/
            for(unsigned int l=0; l<BulletArray.size(); l++)///Détection des collisions entre ennemis et projectiles
            {
                for(unsigned int q=0; q<EnnemiArray.size(); q++)
                {

                    float br=BulletArray.at(l).GetRayon();//Rayon d'une balle
                    float er=EnnemiArray.at(q).GetRayon();//Rayon d'un ennemie
                    float h=Distance_v2f(BulletArray.at(l).GetPosition(), EnnemiArray.at(q).GetPosition());//Distance entre un ennemi et une balle

                    if(h <= br+er)
                    {

                        BulletArray.erase(BulletArray.begin() + q);
                        Me.AddPoint(EnnemiArray.at(q).GetKillPoint());
                        EnnemiArray.erase(EnnemiArray.begin() + q);
                        break;
                    }
                }

            }
/*-------------------------------------------------------------------------------------------------------------------*/
            for(unsigned int f=0; f<EnnemiArray.size(); f++)///Détection collision entre Ennemy et Joueur
            {
                float pr=Me.GetRayon();//Mon rayon
                float er=EnnemiArray.at(f).GetRayon();//Rayon d'un ennemie
                float h=Distance_v2f(Me.GetPosition(), EnnemiArray.at(f).GetPosition());//Distance entre un ennemi et le joueur

                if(h <= pr+er)
                {

                    if(Me.Immunity()==false)
                    {
                        Me.Death();
                    }
                }
            }
/*-------------------------------------------------------------------------------------------------------------------*/
///Phase de dessin
            App.Clear(Color(255,255,255));

            //App.Draw(Me.GetShape());
            App.Draw(Me.GetAnim());

            for(unsigned int v=0; v<BulletArray.size(); v++)//Ennemis
            {
                App.Draw(BulletArray.at(v).GetProjectileSprite());
            }
            for(unsigned int k=0; k<EnnemiArray.size(); k++)//Projectiles
            {
                App.Draw(EnnemiArray.at(k).GetShape());
            }

            App.Draw(Interface.GetLifeString());
            App.Draw(Interface.GetScoreString());

            if(Interface.ShowIndicatorX()==true) App.Draw(Interface.GetIndicatorShapeX());
            if(Interface.ShowIndicatorY()==true) App.Draw(Interface.GetIndicatorShapeY());
            if(Interface.ShowGameOver()==true) App.Draw(Interface.GetGameOverString());

            App.Display();//Render
            /*-------------------------------------------------------------------------------------------------------------------*/
        }///Fin de boucle App.Isopened(), execution de la fenetre

    }///Fin de boucle Running(execution)
cout<<"end"<<endl;
    return 0;
}
