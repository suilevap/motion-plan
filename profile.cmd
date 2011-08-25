"C:\Program Files\Microsoft Visual Studio 9.0\Team Tools\Performance Tools\vsinstr.exe" Release\MotionPlan.dll
"C:\Program Files\Microsoft Visual Studio 9.0\Team Tools\Performance Tools\vsperfcmd.exe" /start:trace /output:MotionPlan.vsp
Release\Test.exe
"C:\Program Files\Microsoft Visual Studio 9.0\Team Tools\Performance Tools\vsperfcmd.exe" /shutdown
"C:\Program Files\Microsoft Visual Studio 9.0\Team Tools\Performance Tools\vsperfreport.exe" MotionPlan.vsp /output:c:\temp /summary:all