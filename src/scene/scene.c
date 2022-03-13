#include "scene.h"

// static void print_vec(t_vec3 vec3)
// {
//     printf ("x : %f, y : %f, z : %f\n", vec3.x, vec3.y, vec3.z);
// }

double get_fov_from_argument(double degrees)
{
    return (degrees * M_PI / 180);
}

t_camera    camera(void)
{
    t_camera    cam;
    double      focal_len;
    double      viewport_height;
    double      theta;

    t_vec3      temp;
    t_vec3      rev_horizontal;
    t_vec3      rev_vertical;
    t_vec3      vec_focal_len;

    theta = get_fov_from_argument(120);
    viewport_height = 4.0;
    focal_len = 1;
    cam.orig = orig;
    cam.focal_len = focal_len;

    cam.left_bottom = temp;

    return (cam);
}