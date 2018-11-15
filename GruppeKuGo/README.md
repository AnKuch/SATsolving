# SAT Solving  

Gruppe KuGo : Andrea Kuchar (10389540) ; Bob Godar (10708175)
 

Das Projekt1 wurde auf einem iMac mit OS 10.13.6 erstellt und getestet.
Dabei wurde CodeLigth und WxWidgets (3.0.4) benutzt.
Bei der Installation von WxWidgets unbedingt auf die zusätzlichen Flags -std=c++11 -stdlib=libc++" CPPFLAGS="-stdlib=libc++" LIBS=-lc++ achten. 
Abweichend von den übrigen Installationshinweisen von WxWidgets sieht der configure Befehl so aus : 
../configure --disable-shared --enable-unicode --with-cocoa --with-macosx-version-min=10.7 --with-macosx-sdk=/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk CXXFLAGS="-std=c++11 -stdlib=libc++" CPPFLAGS="-stdlib=libc++" LIBS=-lc++ 

In manchen Fällen muss auch --disable-mediactrl gesetzt werden.

Als letzte Stolperfalle gilt in Codelight zu beachten, dass die Anweisung $(wx-config ...)$ nicht ausgeführt wird. Die Anweisung muss separat ins Terminal eingegeben werden um dann das Resultat dann anstelle von $()$ zu setzen. 
Das gilt für den Compiler als auch den Linker. 
Als Compiler wurde g++ (gcc Version 8.2.0) benutzt. 

Als zusätzlich zu formular.cnf wird die Datei OutPico.txt benötigt, damit PicoSat seine Ergebnisse reinschreiben kann. 

 