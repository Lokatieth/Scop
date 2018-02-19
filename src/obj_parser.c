#include "../includes/scop.h"


void get_vertices_into_vbo(s_window_context *c, float *dest)
{


	int i = 0;//, j = 0;
	// int vertex_number = 0;
	char **array;
	// while (j < (int)ft_strlen(c->obj_file))
	// {
	// 	if (c->obj_file[j] == 'v' && c->obj_file[j + 1] == ' ')
	// 	vertex_number++;
	// 	j++;
	// }
	float result[c->vertex_number];
	// printf("nombre de lignes avec un vertex = %i\n", vertex_number);
	array = ft_strsplit(c->obj_file, '\n');
	while(*array++)
	{
		if(*array && *array[0] == 'v')
		{
			// printf("%s\t= ", *array);
			sscanf(*array, "v %f %f %f", &result[i], &result[i + 1], &result[i + 2]);
			dest[i] = result[i];
			dest[i + 1] = result[i + 1];
			dest[i + 2] = result[i + 2];
			// printf("result[i] = [%f], [i+1] = [%f], [i+2] =  [%f]\t \n", dest[i], dest[i+1], dest[i+2]);
			i += 3;
		}
		// *array++;
	}
// printf("-------------AVANT-------------\n");
	// for (int i = 0; i < 8; i++)
	// {
	//  	 printf("%f %f %f\n", dest[i*3], dest[i*3+1], dest[i*3+2]);
	// }
}

/*  
// TODO
// Parser plus propre pour les nombrs de face superieures a 5
*/

// int get_face_number(const char *obj_file)
// {
// 	char **array;
// 	int result;

// 	result = 0;
// 	array = ft_strsplit(obj_file, '\n');
// 	while(*array++)
// 	{
// 		if(*array && *array[0] == 'f')
// 		{
// 			if (ft_get_number_of_words(*array, ' ') == 4)
// 				result += 3;
// 			else if (ft_get_number_of_words(*array, ' ') == 5)
// 				result += 6;
// 		}
// 	}
// 	// printf("result = %i\n", result);
// 	return (result);
// }

void get_faces_into_array(s_window_context *c, GLuint *dest)
{


	int i = 0, j = 0;
	// int face_number = 0;
	char **array;
	// while (j < (int)ft_strlen(c->obj_file))
	// {
	// 	if (c->obj_file[j] == 'f' && c->obj_file[j + 1] == ' ')
	// 		face_number++;
	// 	j++;
	// }
	// printf("face number sale = [%i]\n", face_number * 6);
	// printf("face number propre = [%i]\n", get_face_number(c->obj_file));
	GLuint result[c->face_number];
	// printf("nombre de lignes avec un vertex = %i\n", face_number);
	array = ft_strsplit(c->obj_file, '\n');
	j = 1;
	while(*array++)
	{
		if(*array && *array[0] == 'f')
		{
			if (ft_get_number_of_words(*array, ' ') == 4)
			{
				sscanf(*array, "f %i %i %i", &result[j], &result[j + 1], &result[j + 2]);
				dest[i] = result[j] - 1;
				dest[i + 1] = result[j + 1] - 1;
				dest[i + 2] = result[j + 2] - 1;
				// printf("f %i %i %i\n", result[j], result[j + 1], result[j + 2]);
				// printf("[%i, %i, %i]\n\n", dest[i], dest[i + 1], dest[i + 2]);
				i += 3;
				j += 3;
			}
			else if (ft_get_number_of_words(*array, ' ') == 5)
			{
				sscanf(*array, "f %i %i %i %i", &result[j], &result[j + 1], &result[j + 2], &result[j + 3]);
				// printf("f %i %i %i %i\n", result[j], result[j + 1], result[j + 2], result[j + 3]);
				dest[i] = result[j] - 1;
				dest[i + 1] = result[j + 1] - 1;
				dest[i + 2] = result[j + 2] - 1;
				// printf("[%i, %i, %i] + ", dest[i], dest[i + 1], dest[i + 2]);

				i += 3;
				dest[i] = result[j] - 1;
				dest[i + 1] = result[j + 2] - 1;
				dest[i + 2] = result[j + 3] - 1;
				// printf("[%i, %i, %i]", dest[i], dest[i + 1], dest[i + 2]);
				i += 3;
				j += 4;
			}

			// printf("result[i] = [%f], [i+1] = [%f], [i+2] =  [%f]\t \n", result[i], result[i+1], result[i+2]);
		}
		// *array++;
	}
		
}

