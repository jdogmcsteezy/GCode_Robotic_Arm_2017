

/* ------------------------------------------------------------------------ --
--                                                                          --
--                        PC serial port connection object                  --
--                           for non-event-driven programs                  --
--                                                                          --
--  Modified : April 8th 2013                                               --
--  Plateform: Windows 95, 98, NT, 2000 (Win32), Win XP, Win 7              --
-- ------------------------------------------------------------------------ --
-- ------------------------------------------------------------------------ */
#ifndef TSERIAL_H
#define TSERIAL_H
#include <windows.h>
#define HANDLE void*
using namespace std;

enum serial_parity  { spNONE, spODD, spEVEN };

/* -------------------------------------------------------------------- */
/* -----------------------------  Tserial  ---------------------------- */
/* -------------------------------------------------------------------- */
class Tserial
 {

   // -------------------------------------------------------- //
  protected:
   char              port[10] ;                      // port name "com1",...
   int               rate;                          // baudrate
   serial_parity     parityMode;
   void*            serial_handle;                 // ...

  public:
   Tserial();
   ~Tserial();
   friend void operator << (Tserial& stream, char c);
   friend void operator << (Tserial& stream, char *ptr);
   friend void operator >> (Tserial& stream, char &c);
   friend void operator >> (Tserial& stream, char *ptr);
   int           connect          (const char *port_arg, int rate_arg,
                                   serial_parity parity_arg);
   void          sendChar         (char c);
   void          sendArray        (char *buffer, int len);
   char          getChar          (void);
   int           getArray         (char *buffer, int len);
   int           getNbrOfBytes    (void);
   void          disconnect       (void);

 };
#endif TSERIAL_H


