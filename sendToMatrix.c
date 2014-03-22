/***********************************************************************
 *          HDMI Switch Matrix Controller 1.0 by                       *
 *                      eL_Bart0(-[at]-)dietunichtguten.org            * 
 *                                                                     *
 * 		       	     Released under the GPL 2.0                        *
 *       (http://www.gnu.org/licenses/gpl-2.0.html)                    *
 *                                                                     *
 *      Developed for and tested with: Ligawo(R) HDMI Matrix 4x2       *
 * This software and its author are in now way affiliated with Ligawo  *
 *                                                                     *
 *                        Compiled and tested with:                    *
 *        i586-mingw32msvc-cc sendToMatrix.c -o sendToMatrix.exe       *
 *                                                                     *
 *                                                                     *
 *                                 Usage:                              *
 *                   sendToMatrix.exe COM-Port COMMAND                 *
 *   (Run the tool without parameters for more commands and examples)  *
 *                                                                     *
 ***********************************************************************/ 

#include <windows.h>
#include <stdio.h>

void showParams(void)
{
	fprintf(stderr,"HDMI Switch Matrix Controller 1.0 by eL_Bart0(-[at]-)dietunichtguten.org\n\n");
	fprintf(stderr,"Usage sendToMatrix.exe COM-Port COMMAND.\n");
	fprintf(stderr,"E.g.: sendToMatrix.exe com3 LED\n");
	fprintf(stderr,"Toggles the state of the LED display on Ligawo(R) HDMI Matrix 4x2\n\n");
	fprintf(stderr,"Available commands for the Ligawo(R) HDMI Matrix are:\n"); 
	fprintf(stderr,"A1, A2, A3, A4, B1, B2, B3, B4, PW, 2C, 5C, CLE, MT, SA, SB, LED, SAV\n\n");
	fprintf(stderr,"Refer to the switches manual for their function.\n"); 
	fprintf(stderr,"This tool could possibly work with other HDMI switch\n\n");
	fprintf(stderr,"matrices which support serial communication over USB.\n\n");
	fprintf(stderr,"Feel free to contact me if you come accross a similar\n");
	fprintf(stderr,"designed device which is not yet supported.\n\n");
	fprintf(stderr,"Should your switchs manual list other codes, just give them a try\n\n");
	fprintf(stderr,"Basically this tool forwards every command directly over COM port.\n\n");
}

int closeCOMHandle(HANDLE h)
{
	fprintf(stderr,"Closing COM port...");
	
	if (CloseHandle(h) == 0) 
	{
	    fprintf(stderr,"failed.\n");
	} else 
	{
	    fprintf(stderr,"OK.\n");
	}
	    
	return 1;
} 
 
int main(int argc, char **argv)
{
	
    if (argc < 2) 
    {
        showParams();
	return 1;
    }
	
    // declare handle, dcb and timeout struct
    HANDLE h;
    DCB dcb = {0};
    COMMTIMEOUTS timeouts = {0};
         
    // opening the COM port
    fprintf(stderr, "Opening COM port (%s)...",argv[1]);
    h = CreateFile(argv[1], GENERIC_READ|GENERIC_WRITE, 0, NULL,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
              
    // when we could not open the serial port                     
    if (h == INVALID_HANDLE_VALUE)
    {
        fprintf(stderr, "failed.\n");
        return 1;
    } else 
    {
    	fprintf(stderr, "OK.\n");
    }
     
    // getting size of dcb
    dcb.DCBlength = sizeof(dcb);
    
    // retrieve device state
    fprintf(stderr, "Retrieving COM state...");
        
    if (GetCommState(h, &dcb) == 0)
    {
        fprintf(stderr, "failed.\n");
        return closeCOMHandle(h);
    } else 
    {
	fprintf(stderr, "OK.\n");
    }
    
    // setting COM port connection properties
    dcb.BaudRate = 57600;
    dcb.fBinary = 1;
    dcb.fDtrControl = DTR_CONTROL_ENABLE;
    dcb.fRtsControl = RTS_CONTROL_ENABLE;
    dcb.Parity = NOPARITY;
    dcb.StopBits = ONESTOPBIT;
    dcb.ByteSize = 8;
    
    fprintf(stderr, "Setting COM state...");
    
    // setting state of the com port
    if(SetCommState(h, &dcb) == 0)
    {
        fprintf(stderr, "failed.\n");
        return closeCOMHandle(h);
    } else
    {
	fprintf(stderr,"OK.\n");	
    }
 
    // setting COM port timeout properties
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    
    fprintf(stderr, "Setting COM timeouts...");
    
    if(SetCommTimeouts(h, &timeouts) == 0)
    {
        fprintf(stderr, "failed.\n");
        return closeCOMHandle(h);
    } else
    {
	fprintf(stderr,"OK.\n");
    }
 
    // saving the count of bytes written to the COM port
    DWORD bytes_written;
    
    // getting the command to send to the COM port from the command line
    char command[strlen(argv[2])+2]; 
 
    // appending line feed and carriage return to the command
    sprintf(command,"%s\r\n",argv[2]); 
    
    fprintf(stderr, "Sending command (%s) to COM port...",argv[2]);
    
    // writing the command to the COM port
    if (!WriteFile(h, command, strlen(command), &bytes_written, NULL)) 
    {
	fprintf(stderr, "failed.\n");
        return closeCOMHandle(h);
    } else 
    {
        fprintf(stderr,"OK (%d bytes sent).\n",bytes_written);
        closeCOMHandle(h);
        return 0;
    }
}


