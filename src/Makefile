OS=$(shell uname -s)

GXX=g++
CXXFLAGS = -O2 -g
EXEC=princ
SRC= $(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)

ifeq ($(OS),Darwin) 
  LDFLAGS  = -L/usr/X11R6/lib
  LDLIBS   = -lX11 -lXi -lXmu -framework OpenGL -framework GLUT -I/usr/local/include/libpng12 -lpng12 -lz -lGL -lGLU -lm  -framework Cocoa 
else 
  LDFLAGS  = -L/usr/X11R6/lib 
  LDLIBS   = -lX11  -lglut -lGL -lGLU -lm
endif 

.PHONY:	run	clean

all: out os $(EXEC)

out:
	@echo le systeme detecte est:\"$(OS)\"

os:
	@if [ "`uname -s`" = "Darwin" ] ; then  echo "#define MAC" >os.h ; else  echo "#define LINUX" >os.h ; fi

$(EXEC):  $(OBJ) 
	$(GXX)  $(CXXFLAGS) -o  $@ $^ $(LDFLAGS) $(LDLIBS)

%.o: %.cpp
	$(GXX)   $(CXXFLAGS)  -o $@    -c $< 



run:	$(EXEC)
	./$(EXEC)

clean: 
	rm *.o os.h


cleanall:
	rm *.o *~ ./$(EXEC) os.h
	
	

