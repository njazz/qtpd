# qtpd
Qt-based GUI for Puredata. 
Very early prototype, temporary repository.
Meanwhile check out this Pd library/build:
https://github.com/uliss/pure-data

Key concepts for this project:
-----------------------------

   - Separate UI classes, no drawing in pd externals should be used 
   - Separated UI 'client' and pd 'server', possible connection over network
   - MVC architecture for 'client' app
   - GUI features on 'client':
      * Grid/object alignment. 
      * Zoom
      * Text search. 
      * Simplified objects set without duplicate features
      * Object properties handling  
   - Python scripting; Pd and 'client' app API for python


Autogenerated docs:
https://njazz.github.io/qtpd/html/



this work is based on / includes:
---------------------------------
   - Pd vanilla (github.com/pure-data/)
   - libpd (https://github.com/libpd)
   - CICM Wrapper library (https://github.com/CICM/CicmWrapper)
   - Cream library (https://github.com/CICM/CreamLibrary)
   - hcs library (https://puredata.info/downloads/hcs)
   - comport object
   - FAUSTDSP (http://faust.grame.fr)
   - pddoc (https://github.com/uliss/pddoc)
   - PythonQt (http://pythonqt.sourceforge.net/)
