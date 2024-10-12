Main points
1. .Net 8  '<IlcGenerateWin32Resources>false</IlcGenerateWin32Resources>' if not  link error
2. static lib

add in cpp
#pragma comment(lib, "NativeLibrary.lib")
//#pragma comment(lib, "bootstrapperdll.obj")
#pragma comment(lib, "System.Globalization.Native.Aot.lib")
#pragma comment(lib, "System.IO.Compression.Native.Aot.lib")
#pragma comment(lib, "Runtime.VxsortEnabled.lib")
#pragma comment(lib, "Runtime.WorkstationGC.lib")
#pragma comment(lib, "eventpipe-enabled.lib")

#pragma comment(lib, "ncrypt.lib")


"bootstrapperdll.obj" 
Add it in VS, otherwise the link fails and no error is reported, and a null pointer is reported when running.

