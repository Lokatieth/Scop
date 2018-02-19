// #include <stdio.h>
// # define GLEW_STATIC
# include "../includes/scop.h"



  GLfloat model[16];
  GLfloat view[16];
  GLfloat projection[16];/* = {
    1.154701, 0.000000, 0.000000, 0.000000
  , 0.000000, 1.732051, 0.000000, 0.000000
  , 0.000000, 0.000000, -1.000020, -1.000000
  , 0.000000, 0.000000, -0.200002, 0.000000

  };*/
  GLfloat mat4[16];
  GLfloat matresult[16];

  
  float rot =  80 * PI / 180;

  void ft_load_shaders(GLuint *shader_programme)
  {

  const char *vertex_shader = get_whole_file_as_string("./src/shaders/vertex_shader.glsl");
  const char *fragment_shader = get_whole_file_as_string("./src/shaders/fragment_shader.glsl");

  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertex_shader, NULL);
  glCompileShader(vs);
  free((void*)vertex_shader);
  assert(check_shader_compilation(vs) == 1);
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragment_shader, NULL);
  glCompileShader(fs);
  free((void*)fragment_shader);

  assert(check_shader_compilation(fs) == 1);


  glAttachShader(*shader_programme, fs);
  glAttachShader(*shader_programme, vs);
  glLinkProgram(*shader_programme);

 
  }


//    GLuint loadTGA_glfw(const char *imagepath)
//    {

//     // Create one OpenGL texture
//     GLuint textureID;
//     glGenTextures(1, &textureID);

//     // "Bind" the newly created texture : all future texture functions will modify this texture
//     glBindTexture(GL_TEXTURE_2D, textureID);

//     // Read the file, call glTexImage2D with the right parameters
//     glfwLoadTexture2D(imagepath, 0);

//     // Nice trilinear filtering.
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//     glGenerateMipmap(GL_TEXTURE_2D);

//     // Return the ID of the texture we just created
//     return textureID;
// }

  void update_camera(s_window_context *context, float deltaTime, float *view)
  {
    int modifier;
    if (GLFW_PRESS == glfwGetKey(context->window, GLFW_KEY_LEFT_SHIFT)) 
        modifier = 10;    
    else
        modifier = 1;
    if (GLFW_PRESS == glfwGetKey(context->window, GLFW_KEY_S)) 
        translate_mat4(view, view, 0, 0, -CAMERA_SPEED * modifier);
    if (GLFW_PRESS == glfwGetKey(context->window, GLFW_KEY_W)) 
        translate_mat4(view, view, 0, 0, CAMERA_SPEED * modifier);
    if (GLFW_PRESS == glfwGetKey(context->window, GLFW_KEY_D)) 
        translate_mat4(view, view, -CAMERA_SPEED * modifier, 0, 0);
    if (GLFW_PRESS == glfwGetKey(context->window, GLFW_KEY_A)) 
        translate_mat4(view, view, CAMERA_SPEED * modifier, 0, 0);
    if (DEBUG)
    {
      printf("View Matrix = -------------\n");
      matrix_print(view);
    }
    
  }

  void init_structure(s_window_context *c)
  {
    c->obj_file = get_whole_file_as_string(OBJ_PATH);
    // c->texId = loadTGA_glfw("../src/Oren-des-neiges.tga");
    // int j = 0;
    c->vertex_number = 0;
    c->face_number = 0;
    mat4_loadIdentity(model);
    mat4_loadIdentity(view);
    // mat4_loadIdentity(projection);
    mat4_loadIdentity(mat4);
    mat4_loadIdentity(matresult);


    char **array;
    array = ft_strsplit(c->obj_file, '\n');
    while(*array++)
    {
      if(*array && *array[0] == 'v')
        c->vertex_number += 3;
      else if(*array && *array[0] == 'f')
      {
        if (ft_get_number_of_words(*array, ' ') == 4)
          c->face_number += 3;
        else if (ft_get_number_of_words(*array, ' ') == 5)
          c->face_number += 6;
      }
    }
  }

  static void draw_window(s_window_context *context)
  {
    glfwSetInputMode(context->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    init_structure(context);
    glClearColor(0.5, 0.5, 0.5, 0.0f);
    // int j = 0, vertex_number = 0;
    // int face_number = 0;
    // context->obj_file = get_whole_file_as_string(OBJ_PATH);
    // while (j < (int)ft_strlen(context->obj_file))
    // {
    //   if (context->obj_file[j] == 'v' && context->obj_file[j + 1] == ' ')
    //     vertex_number++;
    //   if (context->obj_file[j] == 'f' && context->obj_file[j + 1] == ' ')
    //     vertex_number++;
    //     j++;
    // }
    // printf("vertex_number = %i\n" , vertex_number);
    float points[context->vertex_number];
    GLuint indexes[context->face_number];

    float colours[] = {
     0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,

    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,

    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,

    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f

    };

  get_vertices_into_vbo(context, points);
  get_faces_into_array(context, indexes);

// printf("-------------APRES-------------\n");
// for (int i = 0; i < context->face_number / 3; i++)
// {
//   printf("%i %i %i\n", indexes[i*3], indexes[i*3+1], indexes[i*3+2]);
// }

  // GLuint indexes[] = {
  //   0, 1, 2,
  //   2, 3, 0,
  //   0, 4, 5, 
  //   5, 0, 1, 
  //   4, 0, 3, 
  //   3, 7, 4, 
  //   7, 6, 2, 
  //   7, 3, 2, 
  //   2, 6, 5, 
  //   2, 1, 5, 
  //   7, 6, 5, 
  //   7, 4, 5
  // };

  // get_indexed_vertices()



  // int index = 0;
  // while (index < 15) 
  // {
  //   printf("\nf %i %i %i, On va donc chercher les faces telles que. ", indexes[index], indexes[index + 1], indexes[index + 2]);
  //   printf("[%f] [%f] [%f]\n\n", points[indexes[index]], points[indexes[index + 1]], points[indexes[index + 2]]);
  //   index+=3;
  // }





    // float ratio = (float)1680/768;
    // float left = -ratio;
    // float right = ratio;
    // float bottom = -1.0f;
    // float top = 1.0f;
    // float near = 1.0f;
    // float far = 100.0f;


  // build_perspective (projection, 70, 4/3, 1, 10);
  frustum(projection, -(float)1680/1260, (float)1680/1260, -1.0, 1.0, 1.0, 1000.0);



















  // points vertex buffer object
  GLuint points_vbo = 0;
  glGenBuffers(1, &points_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_DYNAMIC_DRAW);

  // colour vertex buffer object
  GLuint colours_vbo = 0;
  glGenBuffers(1, &colours_vbo);  
  glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_DYNAMIC_DRAW);


  GLuint indexesBuffer = 0;
  glGenBuffers(1, &indexesBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexesBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_DYNAMIC_DRAW);



  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexesBuffer);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);


  GLuint shader_programme = glCreateProgram();
  ft_load_shaders(&shader_programme);
  int viewUniform = glGetUniformLocation(shader_programme, "view");
  int modelUniform = glGetUniformLocation(shader_programme, "model");
  int uniformLocation = glGetUniformLocation(shader_programme, "rotationMatrix");
  int projectionUniform = glGetUniformLocation(shader_programme, "projection");

  // printf("[%i] [%i] [%i]\n", modelUniform, viewUniform, projectionUniform);
  glUniformMatrix4fv(viewUniform, 1, GL_FALSE, view);
  glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, projection);


  // multiply_mat4(matresult, matrot, mat4);
  glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, mat4);

  // matrix_mul_scalar(mat4, mat4, 0.2);
  // scale_mat4(mat4, mat4, 0.2);
  // mat4_loadIdentity(matresult);

    multiply_mat4(view, mat4, model);
    printf("view = \n");
    matrix_print(view);
    printf("view = \n");
    matrix_print(view);
    printf("model = \n");
    // translate_mat4(model, model, 0, 0, 0);
    matrix_print(model);
    printf("projection = \n");
    matrix_print(projection);

    rotate_mat4_y(view, view, degrees_to_radians(90));


    translate_mat4(view, view, 0, 0, -10);
    // rotate_mat4_x(model, model, degrees_to_radians(180));
    // printf("matresult = \n");
    // matrix_print(matresult);
    float deltaMean = 0;
    float iterations = 0;
    while(!glfwWindowShouldClose(context->window)) {
          double xpos, ypos;
          glfwGetCursorPos(context->window, &xpos, &ypos);
          printf("x = [%f], y = [%f] \n", xpos, ypos);
          float startTimeValue = glfwGetTime();
          // wipe the drawing surface clear
          if (GLFW_PRESS == glfwGetKey(context->window, GLFW_KEY_ESCAPE)) 
              glfwSetWindowShouldClose(context->window, 1);
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          // glBindVertexArray(vao);

          float blueColor = sin(startTimeValue);
          float redColor = cos(startTimeValue);
          int rotValueUniform = glGetUniformLocation(shader_programme, "rotValueUniform");
          int timeUniform = glGetUniformLocation(shader_programme, "time");
          // float timeRot = sin(timeValue) / 2  - 0.5;
          // int rotUniform = glGetUniformLocation(shader_programme, "rotationMatrix");
          int vertexColorLocation = glGetUniformLocation(shader_programme, "ourColour");
          int mouseUniform = glGetUniformLocation(shader_programme, "mouse");
          int resolutionUniform = glGetUniformLocation(shader_programme, "resolution");
          
          rotate_mat4_y(model, model, degrees_to_radians(rot));
          // rotate_mat4_z(model, model, degrees_to_radians(rot / 2));
          // rotate_mat4_x(model, model, degrees_to_radians(rot ));

          // matrix_print(view);


          // int projectionUniform = glGetUniformLocation(shader_programme, "projection");
          // printf("[%i] [%i] [%i]\n", modelUniform, viewUniform, projectionUniform);
    


          glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, matresult);
          glUniformMatrix4fv(modelUniform, 1, GL_FALSE, model);
          glUniformMatrix4fv(viewUniform, 1, GL_FALSE, view);
          glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, projection);
          glUniform1f(rotValueUniform, blueColor);
          glUniform1f(timeUniform, startTimeValue);
          glUniform2f(mouseUniform, xpos, ypos );
          glUniform2f(resolutionUniform, 1680, 1280 );
          glUniform4f(vertexColorLocation, redColor, blueColor, redColor + blueColor, 1.0f);


          glUseProgram(shader_programme);
          // draw points 0-3 from the currently bound VAO with current in-use shader
          // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexesBuffer);
          // glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // DRAW USING THE OLD METHOD

       // Draw the triangles !
          glDrawElements(GL_TRIANGLES, sizeof(indexes), GL_UNSIGNED_INT, (GLvoid*)0);
          // glDrawElements(
          //  GL_TRIANGLES,      // mode
          //  sizeof(indexes),    // count
          //  GL_UNSIGNED_INT,   // type
          //  (void*)0           // element array buffer offset
          // );
          // update other events like input handling 
          glfwPollEvents();
          // put the stuff we've been drawing onto the display   
          glfwSwapBuffers(context->window);
          // rot++;
          float deltaTime = (glfwGetTime() - startTimeValue);
          deltaMean += deltaTime;
          iterations++;
          printf("delta = [%f], deltaMean = [%f], iterations = [%f]\n", deltaTime, deltaMean / iterations, iterations);
          printf("FPS Actuels = [%f], FPS Moyens = [%f]\n", 1 / deltaTime, 1 / (deltaMean / iterations));
          update_camera(context, deltaTime, view);
    }
  }

int main(void)
{
  assert(restart_gl_log());
  // start GL context and O/S window using the GLFW helper library
  gl_log("starting GLFW\n[%s]\n", glfwGetVersionString());
  // register the error call-back function that we wrote, above
  glfwSetErrorCallback(glfw_error_callback);
    // printf("%s\n", get_whole_file_as_string("./src/vertex_shader.glsl"));
  s_window_context context; 
	// start GL context and O/S window using the GLFW helper library
  if (!glfwInit()) {
    fprintf(stderr, "ERROR: could not start GLFW3\n");
    return 1;
  } 

  // uncomment these lines if on Apple OS X
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // glfwWindowHint(GLFW_SAMPLES, 4);
  context.window = glfwCreateWindow(1680, 1260, "Scop", /*glfwGetPrimaryMonitor()*/ NULL, NULL);
  if (!context.window) {
    fprintf(stderr, "ERROR: could not open context.window with GLFW3\n");
    glfwTerminate();
    return 1;
  }
  int width, height;
  glfwGetWindowSize(context.window, &width, &height);
  glfwSetWindowAspectRatio(context.window, width, height);
  glfwMakeContextCurrent(context.window);
                                  
  // start GLEW extension handler
  glewExperimental = GL_TRUE;
  glewInit();

  // get version info
  // const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
  // const GLubyte* version = glGetString(GL_VERSION); // version as a string
  // printf("Renderer: %s\n", renderer);
  // printf("OpenGL version supported %s\n", version);

  // tell GL to only draw onto a pixel if the shape is closer to the viewer
  glEnable(GL_DEPTH_TEST); // enable depth-testing
  // glEnable(GL_CULL_FACE);
  glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

  /* OTHER STUFF GOES HERE NEXT */
  assert(&context);
  draw_window(&context);
  // close GL context and any other GLFW resources
  glfwTerminate();
  return 0;
}

