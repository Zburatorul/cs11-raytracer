.PHONY : clean doc depend parser jpeg all

BOOST_INC = /usr/include/boost/

CPPFLAGS = -I$(BOOST_INC) -g


SRCS = main.cc scene.cc parser.cc scene_objects/objects.cc

OBJS = main.o scene.o parser.o scene_objects/objects.o

all : $(OBJS)
	g++ $(CPPFLAGS) -o tracer $(OBJS)

render	:	
		chmod u+x tracer
		./tracer 400 scene.txt &> debug.log
  
clean :  	
		rm -f debug.log scene.ppm img.jpg
		rm -fR *.o *~
		rm -fR scene_objects/*.o
		rm -fR scene_objects/*~
		rm -fR docs

doc	:	Doxyfile
		doxygen

jpeg	:	
		pnmtojpeg scene.ppm > img.jpg

depend : 
		makedepend --$(SRCS)

# DO NOT DELETE THIS LINE -- make depend depends on it
