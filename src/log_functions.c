
# include "../includes/scop.h"
int check_shader_compilation(GLuint shader_index)
{
  int params = -1;
  int max_length = 2048;
  int actual_length = 0;
  char shader_log[2048];
  glGetShaderiv(shader_index, GL_COMPILE_STATUS, &params);
  if (GL_TRUE != params) {
    fprintf(stderr, "ERROR: GL shader index %i did not compile\n", shader_index);
    glGetShaderInfoLog(shader_index, max_length, &actual_length, shader_log);
    printf("shader info log for GL index %u:\n%s\n", shader_index, shader_log);
    return (0); // or exit or something
  }
  return (1);
}
int restart_gl_log() {
  FILE* file = fopen(GL_LOG_FILE, "w");
  if(!file) {
    fprintf(stderr,
      "ERROR: could not open GL_LOG_FILE log file %s for writing\n",
      GL_LOG_FILE);
    return 0;
  }
  time_t now = time(NULL);
  char* date = ctime(&now);
  fprintf(file, "GL_LOG_FILE log. local time %s\n", date);
  fclose(file);
  return 1;
}

int gl_log(const char* message, ...) {
  va_list argptr;
  FILE* file = fopen(GL_LOG_FILE, "a");
  if(!file) {
    fprintf(
      stderr,
      "ERROR: could not open GL_LOG_FILE %s file for appending\n",
      GL_LOG_FILE
    );
    return 0;
  }
  va_start(argptr, message);
  vfprintf(file, message, argptr);
  va_end(argptr);
  fclose(file);
  return 1;
}

int gl_log_err(const char* message, ...) {
  va_list argptr;
  FILE* file = fopen(GL_LOG_FILE, "a");
  if(!file) {
    fprintf(stderr,
      "ERROR: could not open GL_LOG_FILE %s file for appending\n",
      GL_LOG_FILE);
    return 0;
  }
  va_start(argptr, message);
  vfprintf(file, message, argptr);
  va_end(argptr);
  va_start(argptr, message);
  vfprintf(stderr, message, argptr);
  va_end(argptr);
  fclose(file);
  return 1;
}

void glfw_error_callback(int error, const char* description) {
  gl_log_err("GLFW ERROR: code %i msg: %s\n", error, description);
}