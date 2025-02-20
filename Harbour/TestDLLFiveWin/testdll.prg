#include "hbdyn.ch"
#include "FiveWin.ch"

function Main()
   local nId, nRetCode
   hLib = hb_libLoad( "\go-dll\DLL\mydll.dll" )
   if ! Empty( hLib )
      ? "mydll loaded"

      nId = LoadDLL()
      ? "Calling mydll " + If( nId > 0, "Succeeded!", "Failed!" )
      ? CallGoal( nId )
      ? "Adding 2 and 3 = " + str(CallAdd( 2, 3 ))
      hb_libFree( hLib )
   endif


   MsgInfo( "ok from EXE" )

return nil


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

  
function CallAdd( a, b )

return hb_DynCall( { "Add", hLib, hb_bitOr( HB_DYN_CALLCONV_STDCALL, HB_DYN_CTYPE_LONG ),;
                            HB_DYN_CTYPE_LONG, HB_DYN_CTYPE_LONG }, a, b )