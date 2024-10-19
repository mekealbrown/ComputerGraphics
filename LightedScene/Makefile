#---------------------------------------------------------------------
# Build the cube rotation application with the trackball capability
# from Eck's camera API.
#---------------------------------------------------------------------

a.out: scene.cpp camera.cpp camera.h
	clear && g++ scene.cpp camera.cpp shapes.cpp -lglut -lGL -lGLU
clean:
	rm -f a.out
