[![Build Status](https://travis-ci.org/njazz/tilde.svg?branch=master)](https://travis-ci.org/njazz/tilde)

# tilde~
New integrated GUI for Puredata based on Qt.  
  
Early prototype, temporary repository.  
Meanwhile check out this Pd library/build:  
https://github.com/uliss/pure-data

Key concepts / roadmap for this project:
-----------------------------

   - Seperate UI 'client' and 'server' parts of the application.  
   For now the app is built as 'pd-library' and the itself. Later it is supposed to have the possibility to split these parts over the network, to have no-gui option etc.
   - Separate UI classes, simple communication with puredata objects
   - MVC architecture for 'client' app
   - Simplified UI object set without duplicate features. Unified property system for all objects
   - Pd Vanilla patch compatibility (import, limited export)
   - GUI features on 'client':
      * Grid/object alignment 
      * Zoom
      * Text search 
      * Unified object properties handling 
      * extended undo / clipboard operation, patchcord connection options
   - embedded Python.  
   'Client' - based python api includes:
      * creating/deleting/editing objects/patchcords/properties
      * UI extensions api - adding toolbars-menus etc
      * Python modules - use Qt, OpenGL, numPy, OFx, etc
      * UI script object 
      runs scripts on 'client' side and has inlets/outlets to connect to its puredata patch. 
   


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
