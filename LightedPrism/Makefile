#---------------------------------------------------------------------
# Build the cube rotation application with the trackball capability
# from Eck's camera API.
#---------------------------------------------------------------------

a.out: lighted-prism.cpp camera.cpp camera.h
	clear && g++ lighted-prism.cpp camera.cpp -lglut -lGL -lGLU
clean:
	rm -f a.out
