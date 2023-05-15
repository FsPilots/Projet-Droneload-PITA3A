#ifndef C_PILOTE_H
#define C_PILOTE_H


#include "Radio.h"
#include "Camera.h"
#include "Profile.h"

#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include  <windows.h>

//valeurs mesur�es de throttle

#define StationnaryThrottleValue 30
#define ClimbThrottleValue 35
#define LandThrottleValue 20
#define ClimbTime 3000


//differentes valeurs d'etat du pilote
#define IDLE 0
#define TAKINGOFF 2
#define INFLIGHT 4
#define LANDING 8
#define STABILIZED 16
#define READINGQR 32
#define PASSGATE 64

#define PILOTELOOPTIME 50

class C_Pilote
{
    private:
        int m_state ;
        double m_FilteredAltitude ;
        double m_FilteredCenter_x;
        double m_FilteredCenter_y;
        double m_AphaFiltrage ;
        double m_AltitudeConsigne ;
        double m_CenterConsigne_x;
        double m_CenterConsigne_y;
        double m_PID_P ;
        double m_PID_D ;
        double m_PID_P_Center ;
        double m_PID_D_Center ;
        bool m_finish ;
        int m_PreviousTime ;
        double m_PreviousError ;
        int m_ThrolleCmd ;
        int m_RollCmd;

        int m_PreviousTimeCenter ;
        double m_PreviousErrorCenter_x ;
        double m_PreviousErrorCenter_y ;


        bool m_AltIsToBeStabilised ;
        void AltitudeStabilisation() ;

        C_Profile m_TakeOffProfile ;
        C_Profile m_LandingProfile ;

    public:
        C_Pilote();
        virtual ~C_Pilote();

        pthread_t m_MoveThread;            //thread pour effectuer des mouvements pr�d�finis ( decoller , atterir , avancer d'un metre ...)--> comme on ne decolle pas en mem temps d'atterir , on aura jamais deux fontions de ce type en meme temps
        pthread_t m_CenterThread;          //thread pour effectuer des controles du drone en temps r�el ( centrer , stabiliser ...)
        pthread_mutex_t m_PilotMutex ;

        // fonction principale � lancer dans une thread
        void StartAutoPiloteLoop() ; //tourne tout le temps , fait soit rien , soit stabilisation altitude , soit centrer .....
        void StopAutoPiloteLoop() ;  //possibilit� d'arreter l'autopilote ( normalement pas utilis�)
        void ToggleAltitudeStabilisation() ;


        // actions pr�d�finies
        void Takeoff( ) ;
        void Landing( ) ;
        void Translate ( int i_NbTranslate );
        void ReadQR();
        void PassGate();
        int m_Activity;




        //controles en temps r�el
        void Center() ;
        void Stabilise();                 //fonction pour stabiliser le drone par flux optique si les r�sultats du lidar ne sont pas satifaisants


        int GetState() { return m_state ; } ;
        int GetActivity() { return m_Activity ; } ;
        void SetActivity(int i_Activity){m_Activity=i_Activity;};
        void SetState(int i_State){m_state=i_State;};


        int GetAltutudeConsigne () {return m_AltitudeConsigne;};
        void SetAltitudeConsigne(int i_AltitudeConsigne){m_AltitudeConsigne=i_AltitudeConsigne;};




};

#endif // C_PILOTE_H
