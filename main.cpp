/* -----------------------------------------------------------------;
 * $source   : / $
 * $revision : 1.0 $
 * $author   : wyr@null.co.za $
 * $date     : 2016/03/28 01:04:00 SAST $
 * $desc     : $
 * $log      : $
 *
 * -----------------------------------------------------------------;
 */

#include "main.h"

//------------------------------------------------------------------;
//
//------------------------------------------------------------------;

int init (void) {

   int      i, num_vertex, width, height;
   float   *vertex;
   unsigned char *data;
   float    rmax;
   vec3     min, max;

   vec4 plane_s = { 1.0, 0.0, 0.0, 0.0 };
   vec4 plane_t = { 0.0, 1.0, 0.0, 0.0 };
   vec4 plane_r = { 0.0, 0.0, 1.0, 0.0 };
   vec4 plane_q = { 0.0, 0.0, 0.0, 1.0 };

   glClearDepth    (1);
   glEnable        (GL_DEPTH_TEST);
   glDepthFunc     (GL_LEQUAL);
   glEnable        (GL_LIGHT0);
   glPointSize     (4);

   glTexGenfv      (GL_S, GL_EYE_PLANE, plane_s);
   glTexGenfv      (GL_T, GL_EYE_PLANE, plane_t);
   glTexGenfv      (GL_R, GL_EYE_PLANE, plane_r);
   glTexGenfv      (GL_Q, GL_EYE_PLANE, plane_q);

   glTexGeni       (GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
   glTexGeni       (GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
   glTexGeni       (GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
   glTexGeni       (GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);

   glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   glTexImage2D    (GL_TEXTURE_2D, 0, GL_RGB, SIZE, SIZE, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	
   glGenTextures   (1, (GLuint *)&texture_id);
   glBindTexture   (GL_TEXTURE_2D, texture_id);

   if((data = load_jpeg("data/ground.jpg", &width, &height))) {
      
      glTexParameterf   (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameterf   (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      gluBuild2DMipmaps (GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
      free(data);
   }

 //vertex = load_3ds("data/untitled.3ds",&num_vertex);
 //vertex = load_3ds("data/booth-1.3ds",&num_vertex);
 //vertex = load_3ds("data/scene-1.3ds",&num_vertex);

   vertex = load_3ds("data/scene-1.3ds", &num_vertex);

   if(!vertex) return -1;

   v_set(999999,999999,999999,min);
   v_set(-999999,-999999,-999999,max);

   for(i = 0; i < num_vertex; i++) {
      int j;
      float *v = &vertex[i << 3];

      for(j = 0; j < 3; j++) {
         if(min[j] > v[j]) min[j] = v[j];
	 if(max[j] < v[j]) max[j] = v[j];
      }
   }

   v_add(min,max,min);
   v_scale(min,0.5,min);

   for(i = 0; i < num_vertex; i++) {
      v_sub(&vertex[i << 3],min,&vertex[i << 3]);
   }
   for(i = 0, rmax = 0; i < num_vertex; i++) {
      float r = sqrt(v_dot(&vertex[i << 3],&vertex[i << 3]));
      if(r > rmax) {
         rmax = r;
      }
   }
   rmax = 0.8 / rmax;
   for(i = 0; i < num_vertex; i++) {
      v_scale(&vertex[i << 3],rmax,&vertex[i << 3]);
   }
	
   lamp_id = glGenLists(1);

   glNewList(lamp_id,GL_COMPILE);
   glTranslatef(-2.0,0.0,0.77);
   glBegin(GL_TRIANGLES);

   for(i = 0; i < num_vertex; i++) {
      glNormal3fv((float*)&vertex[i << 3] + 3);
      glVertex3fv((float*)&vertex[i << 3]);
   }
   glEnd();
   glEndList();

   vertex = load_3ds("data/untitled-2.3ds", &num_vertex);

   if(!vertex) return -1;
	
   ground_id = glGenLists(1);
   glNewList(ground_id,GL_COMPILE);
   glBegin(GL_TRIANGLES);

   for(i = 0; i < num_vertex; i++) {
      glTexCoord2fv((float*)&vertex[i << 3] + 6);
      glNormal3fv((float*)&vertex[i << 3] + 3);
      glVertex3fv((float*)&vertex[i << 3]);
   }
   glEnd();
   glEndList();
	
   image = (unsigned char *) malloc(SIZE * SIZE * 4);
	
   return 1;
}

//------------------------------------------------------------------;

float getfps (void) {

   return 1;
}

//------------------------------------------------------------------;

void blur (unsigned char *in,
           int            size) {
}

//------------------------------------------------------------------;

void render (void) {
}

//------------------------------------------------------------------;

void idle (void) {

   static int   frames;
   static float time;
   float        ifps;
   vec3         v;
   vec4         q0, q1, q2;
   matrix       m;

   ifps = 1.0 / getfps();
	
   if(!my_pause) angle += ifps * 360.0 / 4.0;
	
   v_set(sin(angle * DEG2RAD / 3), cos(angle * DEG2RAD / 7), 2, light);
	
   v_set       (0, 0, 1, v);
   q_set       (v, psi, q0);
   v_set       (0, 1, 0, v);
   q_set       (v, phi, q1);
   q_multiply  (q0, q1, q2);
   q_to_matrix (q2, m);
   v_set       (dist, 0, 0, camera);
   v_transform (camera, m, camera);
   v_add       (camera, mesh, camera);
	
   frames++;
   time += ifps;

   if(time > 1.0) {
      printf ("%d frames %.2f fps\n", frames, (float)frames / time);
      frames = 0;
      time   = 0;
   }
}

//------------------------------------------------------------------;

void keyboard (int key) {

   switch(key) {
      case SDLK_ESCAPE :
         SDL_Quit();
         exit(0);
         break;
      case SDLK_SPACE:
         my_pause = !my_pause;
         break;
      case SDLK_b:
         my_blur = !my_blur;
         break;
      case SDLK_w:
         my_wireframe ^= 1;
         if (my_wireframe) {
            glDisable     (GL_LIGHTING);
            glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
         }else{
            glEnable      (GL_LIGHTING);
            glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
         }      
         break;
      case SDLK_l:
         my_lighting ^= 1;
         if (my_lighting) {
            glDisable     (GL_LIGHTING);
         }else{
            glEnable      (GL_LIGHTING);
         }                 
         break;
   }
}

//------------------------------------------------------------------;

void mouse (int button,
            int state,
            int x,
            int y) {

   if (button == 4) dist -= 0.5;
   if (button == 5) dist += 0.5;
   if (dist < 1.5)  dist = 1.5;
   if (dist > 10)   dist = 10;

   psi += (x - WIDTH / 2) * 0.2;
   phi += (y - HEIGHT / 2) * 0.2;

   if(phi < -89) phi = -89;
   if(phi > 89) phi = 89;
}

//------------------------------------------------------------------;

void m_io_console ( void ) {

    // Allocate a console so we can output some useful information.
    AllocConsole();

    // Get the handle for STDOUT's file system.
    HANDLE stdOutputHandle = GetStdHandle( STD_OUTPUT_HANDLE );

    // Redirect STDOUT to the new console by associating STDOUT's file 
    // descriptor with an existing operating-system file handle.
    int hConsoleHandle = _open_osfhandle( (intptr_t)stdOutputHandle, _O_TEXT );
    FILE *pFile = _fdopen( hConsoleHandle, "w" );
    *stdout = *pFile;
    setvbuf( stdout, NULL, _IONBF, 0 );

    // This call ensures that iostream and C run-time library operations occur  
    // in the order that they appear in source code.
    std::ios::sync_with_stdio();
}

int main ( int   argc, 
           char* args[] ) {

   m_io_console ();

   printf ("%i\n", 0);

/**
   SDL_Surface *screen;
   int done;
	
   SDL_Init (SDL_INIT_VIDEO);
   screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_OPENGL);

   if (!screen) {
      printf("couldn`t set video mode: %s\n", SDL_GetError());
      SDL_Quit();
      exit(1);
   }
	
   if(init() != 0) return 1;
	
   SDL_ShowCursor(SDL_DISABLE);
   SDL_WarpMouse(WIDTH / 2,HEIGHT / 2);
	
   done = 0;

   while(!done) {
      SDL_Event event;

      while(SDL_PollEvent(&event)) {
         switch(event.type) {
            case SDL_QUIT:
               done = 1;
               break;
            case SDL_KEYDOWN:
               keyboard(event.key.keysym.sym);
               break;
            case SDL_MOUSEMOTION:
               mouse(0, 0, event.motion.x, event.motion.y);
               break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
               mouse (event.button.button, event.button.state, event.button.x, event.button.y);
               break;
         }
      }
      SDL_WarpMouse(WIDTH / 2,HEIGHT / 2);
      idle();
      render();
   }
   SDL_Quit();
**/

   return 0;
}
