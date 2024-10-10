//--------------------------------------------------------------------------
// Developer -- Bryan Crawley, et al.
// Course ----- CS3233
// Project ---- Class demo: Lighted Cube
// Due date --- N/A
// 
// Draw a cube, and light it with one light source. Set reflectivity
// attributes for the faces of the cube. Use default attributes for the
// light source.
//--------------------------------------------------------------------------

#ifdef _WIN32
    #include <GL/glut.h>
#elif __linux__
    #include <GL/glut.h>
#elif __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#endif

//--------------------------------------------------------------------------
// display()
//
// Handler for window-repaint event. Call back when the window first appears
// and whenever the window needs to be re-painted.
//--------------------------------------------------------------------------

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);
    glMatrixMode(GL_MODELVIEW);

    // Use these points for the vertices of the cube.
    int point[][3] = {
        {0,0,0}, {0,0,1}, {0,1,0}, {0,1,1},
        {1,0,0}, {1,0,1}, {1,1,0}, {1,1,1}
    };

    // Use this material for all the vertices of the cube. If we wanted
    // to, we could set the material for each vertex individually. We
    // don't want to for this application.
    float cube_color[] = { 0.7f, 0.0f, 0.7f, 1.0f };   // Go Bisons!
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, cube_color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, cube_color);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0F);

    // Adjust the location and orientation of the cube so we can observe
    // its 3-dimensional nature.
    glRotatef(50.0f, 1.0f, 1.0f, 1.0f);
    //glTranslatef(-0.5f, -0.5f, -0.5f);

	glBegin(GL_TRIANGLE_FAN);
		glNormal3i(0, 0, 1);       // Front face
		glVertex3iv(point[3]);
		glVertex3iv(point[1]);
		glVertex3iv(point[5]);
		glVertex3iv(point[7]);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
		glNormal3i(1, 0, 0);       // Right face
		glVertex3iv(point[7]);
		glVertex3iv(point[5]);
		glVertex3iv(point[4]);
		glVertex3iv(point[6]);
   glEnd();

	glBegin(GL_TRIANGLE_FAN);
		glNormal3i(0, 0, -1);      // Back face
		glVertex3iv(point[6]);
		glVertex3iv(point[4]);
		glVertex3iv(point[0]);
		glVertex3iv(point[2]);
   glEnd();

	glBegin(GL_TRIANGLE_FAN);
		glNormal3i(-1, 0, 0);      // Left face
		glVertex3iv(point[2]);
		glVertex3iv(point[0]);
		glVertex3iv(point[1]);
		glVertex3iv(point[3]);
   glEnd();

	glBegin(GL_TRIANGLE_FAN);
		glNormal3i(0, 1, 0);       // Top face
		glVertex3iv(point[2]);
		glVertex3iv(point[3]);
		glVertex3iv(point[7]);
		glVertex3iv(point[6]);
   glEnd();

	glBegin(GL_TRIANGLE_FAN);
		glNormal3i(0, -1, 0);      // Bottom face
		glVertex3iv(point[0]);
		glVertex3iv(point[4]);
		glVertex3iv(point[5]);
		glVertex3iv(point[1]);
   glEnd();

   glFlush();  // Render now
}

//--------------------------------------------------------------------------
// init()
//
// This functions does various initializations. It should be called before
// starting the main loop.
//--------------------------------------------------------------------------

void init()
{
    glEnable(GL_LIGHTING);    // Enable lighting.
    glEnable(GL_LIGHT0);      // Turn on a light. Use default light attributes.
    glEnable(GL_NORMALIZE);   // OpenGL will make all normal vectors into unit normals
    return;
}

//--------------------------------------------------------------------------
// main()
//
// Create a window for drawing and start the main loop. Also, do various
// initializations.
//--------------------------------------------------------------------------

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Lighted Cube With Rotation");
    glutDisplayFunc(display);
    init();         // Various initializations; mostly lighting.
    glutMainLoop();
    return 0;
}
