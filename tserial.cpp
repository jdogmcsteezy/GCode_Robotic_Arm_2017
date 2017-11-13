

/*--------------------------------------------------------------------------
-- Plateform: Windows 95, 98, NT, 2000 (Win32), Win XP, Win 7/8           --
---------------------------------------------------------------------------- */
#include <string>
#include <iostream>
#include "tserial.h"
using namespace std;

/* -------------------------------------------------------------------- */
/* -------------------------    Tserial   ----------------------------- */
/* -------------------------------------------------------------------- */
Tserial::Tserial()
{
 parityMode       = spNONE;
 port[0]          = 0;
 rate             = 0;
 serial_handle    = INVALID_HANDLE_VALUE;
}

/* -------------------------------------------------------------------- */
/* --------------------------    ~Tserial     ------------------------- */
/* -------------------------------------------------------------------- */
Tserial::~Tserial()
{
 if (serial_handle!= (INVALID_HANDLE_VALUE))
  CloseHandle(serial_handle);
 serial_handle = INVALID_HANDLE_VALUE;
}
/* -------------------------------------------------------------------- */
/* --------------------------    disconnect   ------------------------- */
/* -------------------------------------------------------------------- */
void Tserial::disconnect(void)
{
 if (serial_handle!=INVALID_HANDLE_VALUE)
  CloseHandle(serial_handle);
 serial_handle = INVALID_HANDLE_VALUE;
}
/* -------------------------------------------------------------------- */
/* --------------------------    connect      ------------------------- */
/* -------------------------------------------------------------------- */
int  Tserial::connect          (char *port_arg, int rate_arg, serial_parity parity_arg)
{
 int erreur;
 DCB  dcb;
 COMMTIMEOUTS cto = { 0, 0, 0, 0, 0 };

 /* --------------------------------------------- */
 if (serial_handle!=INVALID_HANDLE_VALUE)
  CloseHandle(serial_handle);
 serial_handle = INVALID_HANDLE_VALUE;

 erreur = 0;

 if (port_arg!=0)
  {
   strncpy(port, port_arg, 10);
   rate      = rate_arg;
   parityMode= parity_arg;
   memset(&dcb,0,sizeof(dcb));

   /* -------------------------------------------------------------------- */
   // set DCB to configure the serial port
   dcb.DCBlength       = sizeof(dcb);

   /* ---------- Serial Port Config ------- */
   dcb.BaudRate        = rate;

   switch (parityMode)
    {
     case spNONE:
      dcb.Parity      = NOPARITY;
      dcb.fParity     = 0;
      break;
     case spEVEN:
      dcb.Parity      = EVENPARITY;
      dcb.fParity     = 1;
      break;
     case spODD:
      dcb.Parity      = ODDPARITY;
      dcb.fParity     = 1;
      break;
    }


   dcb.StopBits        = TWOSTOPBITS;
   dcb.ByteSize        = 7;

   dcb.fOutxCtsFlow    = 0;
   dcb.fOutxDsrFlow    = 0;
   dcb.fDtrControl     = DTR_CONTROL_DISABLE;
   dcb.fDsrSensitivity = 0;
   dcb.fRtsControl     = RTS_CONTROL_DISABLE;
   dcb.fOutX           = 0;
   dcb.fInX            = 0;

   /* ----------------- misc parameters ----- */
   dcb.fErrorChar      = 0;
   dcb.fBinary         = 1;
   dcb.fNull           = 0;
   dcb.fAbortOnError   = 0;
   dcb.wReserved       = 0;
   dcb.XonLim          = 2;
   dcb.XoffLim         = 4;
   dcb.XonChar         = 0x13;
   dcb.XoffChar        = 0x19;
   dcb.EvtChar         = 0;

   /* -------------------------------------------------------------------- */
   serial_handle = CreateFileA(port, GENERIC_READ | GENERIC_WRITE,
                                0, NULL, OPEN_EXISTING,NULL,NULL);
   cout << serial_handle << endl;

   // opening serial port
   if (serial_handle    != INVALID_HANDLE_VALUE)
    {
     if (!SetCommMask(serial_handle, 0))
      erreur = 1;

     // set timeouts
     if (!SetCommTimeouts(serial_handle,&cto))
      erreur = 2;

     // set DCB
     if (!SetCommState(serial_handle,&dcb))
      erreur = 4;
    }
   else
    erreur = 8;
  }
 else
  erreur = 16;


 /* --------------------------------------------- */
 if (erreur!=0)
  {
   CloseHandle(serial_handle);
   serial_handle = INVALID_HANDLE_VALUE;
  }
 return(erreur);
}


/* -------------------------------------------------------------------- */
/* --------------------------    sendChar     ------------------------- */
/* -------------------------------------------------------------------- */
void Tserial::sendChar(char data)
{
 sendArray(&data, 1);
}

/* -------------------------------------------------------------------- */
/* --------------------------    sendArray    ------------------------- */
/* -------------------------------------------------------------------- */
void Tserial::sendArray(char *buffer, int len)
{
  unsigned long result;

  if (serial_handle!=INVALID_HANDLE_VALUE)
  WriteFile(serial_handle, buffer, len, &result, NULL);
}

/* -------------------------------------------------------------------- */
/* --------------------------    getChar      ------------------------- */
/* -------------------------------------------------------------------- */
char Tserial::getChar(void)
{
  char c;
  getArray(&c, 1);
  return(c);
}

/* -------------------------------------------------------------------- */
/* --------------------------    getArray     ------------------------- */
/* -------------------------------------------------------------------- */
int  Tserial::getArray         (char *buffer, int len)
{
  unsigned long read_nbr;
  read_nbr = 0;
  if (serial_handle!=INVALID_HANDLE_VALUE)
  {
   ReadFile(serial_handle, buffer, len, &read_nbr, NULL);
  }
 return((int) read_nbr);
}
/* -------------------------------------------------------------------- */
/* --------------------------    getNbrOfBytes ------------------------ */
/* -------------------------------------------------------------------- */
int Tserial::getNbrOfBytes    (void)
{
 struct _COMSTAT status; //Com port status
 int             n;      //Queue iterator
 unsigned long   etat;
 n = 0;
  if (serial_handle!=INVALID_HANDLE_VALUE)
  {
    ClearCommError(serial_handle, &etat, &status);
    n = status.cbInQue;
  }
 return(n);
}

void operator << (Tserial& stream, char c)
{
  stream.sendArray(&c, 1);
}

void operator << (Tserial& stream, char *ptr)
{
  int len = 0;
  char* array;
  array = ptr;
  while (*ptr != '\0')
  {
   len++;
   ptr++;
  }
  stream.sendArray(array,len);
  stream.sendChar(0x0d);
  stream.sendChar(0x0a);
}
void operator >> (Tserial& stream, char &c)
{
  c = stream.getChar();
}

void operator >> (Tserial& stream, char *ptr)
{
  int len = 0;
  char * array;
  array =  ptr;
  while (*ptr != '\0')
  {
   stream.getArray(array,len);
  }
}


