/*
    mydyn.prg
    compile: hbmk2 mydyn
*/

#include "hbdyn.ch"
#define MAX_PATH 260

PROCEDURE Main()

   #if defined( __PLATFORM__WINDOWS )

   LOCAL hLib, nResult, cVolume, cVolumeName, nNameSize, nSerial, cSerial

    cVolume := "C:\"
    cVolumeName := SPACE(MAX_PATH+1)
    nSerial := 0
    nNameSize := MAX_PATH+1
   
    SetColor( "G+/N" )
    CLS
   
    ? "Get volume info using Kernel32.dll --> GetVolumeInformationA"
    ?
   hLib := hb_libLoad( "Kernel32.dll" )
   
    IF ! Empty( hLib )
   
        ? "Kernel32.dll loaded!"
       
        nResult := hb_DynCall( { "GetVolumeInformationA", hLib, HB_DYN_CALLCONV_STDCALL }, ;
                                cVolume     ,;
                                @cVolumeName, ;
                                nNameSize   , ;
                                @nSerial    , ;
                                0, 0, 0, 0 )

        ? "Calling GetVolumeInformationA: " + Iif( nResult > 0, "Succeeded!", "Failed!" )
       
        // always unload DLL when done!
        ? "Unloading DLL:",  hb_libFree( hLib )
        ?
        cVolumeName := Alltrim( cVolumeName )
        cSerial     := hb_NumToHex( nSerial )
        ? "Volume:", cVolumeName
        ? "Serial:", Stuff( cSerial, 5, 0, "-" )
       
    ELSE
   
        ? "Kernel32.dll failed to load!"
       
    ENDIF
   
    #else
   
        ? "Windows only code! Cannot run on this platform."
       
   #endif

   RETURN
