#---------------------------------------------------------------------
# Build the cube rotation application with the trackball capability
# from Eck's camera API.
#---------------------------------------------------------------------

a.out: cubeRotationTrackball.cpp camera.cpp camera.h
	g++ cubeRotationTrackball.cpp camera.cpp -lglut -lGL -lGLU
clean:
	rm -f a.out
