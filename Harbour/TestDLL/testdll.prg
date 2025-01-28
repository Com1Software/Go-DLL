#include "hbdyn.ch"

static hLib

//----------------------------------------------------------------//

function Main()

   local nId, nRetCode

   hLib = hb_libLoad( "\go-dll\DLL\mydll.dll" )

   if ! Empty( hLib )
      ? "mydll loaded"

      nId = LoadDLL()
      ? "Calling mydll " + If( nId > 0, "Succeeded!", "Failed!" )
      ? CallGoal( nId )
      hb_libFree( hLib )
   endif

return nil

//----------------------------------------------------------------//

function LoadDLL( cCommandLine, nBufferSize, nEncryption, nTickle )

   hb_default( @cCommandLine, "Hey There" )
   hb_default( @nBufferSize, 0 )
   hb_default( @nEncryption, 0 )
   hb_default( @nTickle, 0 )

return hb_DynCall( { "SayHello", hLib, hb_bitOr( HB_DYN_CALLCONV_STDCALL, HB_DYN_CTYPE_LONG ),;
                   HB_DYN_CTYPE_CHAR_PTR, HB_DYN_CTYPE_LONG, HB_DYN_CTYPE_LONG, HB_DYN_CTYPE_LONG },;
                   cCommandLine, nBufferSize, nEncryption, nTickle )    


//----------------------------------------------------------------//

function CallGoal( nId )

return hb_DynCall( { "SayHello", hLib, hb_bitOr( HB_DYN_CALLCONV_STDCALL, HB_DYN_CTYPE_CHAR_PTR ),;
                   HB_DYN_CTYPE_LONG }, nId )    

