#include "scene.h"

static void print_vec(t_vec3 vec3)
{
    printf ("x : %f, y :%f, z : %f\n", vec3.x, vec3.y, vec3.z);
}

t_camera    camera(t_canvas *canvas, t_point3 orig)
{
    t_camera    cam;
    double      focal_len;
    double      viewport_height;

    t_vec3      temp;
    t_vec3      rev_horizontal;
    t_vec3      rev_vertical;
    t_vec3      vec_focal_len;

    viewport_height = 2.0;
    focal_len = 1.0;
    cam.orig = orig;
    cam.viewport_h = viewport_height;
    cam.viewport_w = viewport_height * canvas->aspect_ratio;
    cam.focal_len = focal_len;
    cam.horizontal = vec3(cam.viewport_w, 0, 0);
    cam.vertical = vec3(0, cam.viewport_h, 0);

    // 왼쪽 아래 코너점 좌표, origin - (horizontal / 2) - (vertical / 2) - (vec3(0,0,focal_length))
    // cam.left_bottom = vminus(vminus(vminus(cam.orig, vdivide(cam.horizontal, 2)),
    //                            vdivide(cam.vertical, 2)), vec3(0, 0, focal_len));
    // temp = vminus(cam.orig, vdivide(cam.horizontal, 2));
    // temp = vminus(temp, vdivide(cam.vertical, 2));
    // temp = vminus(temp, vec3(0, 0, focal_len));
    temp = cam.orig;
    rev_horizontal = vdivide(cam.horizontal, 2);
    rev_vertical = vdivide(cam.vertical, 2);
    vec_focal_len = vec3(0, 0, focal_len);

    print_vec(temp); // x : 0.000000, y :0.000000, z : 0.000000
    temp = vminus(temp, rev_horizontal);
    print_vec(temp); // x : -1.333333, y :0.000000, z : 0.000000
    temp = vminus(temp, rev_vertical);
    print_vec(temp); // x : -1.333333, y :-1.000000, z : 0.000000
    temp = vminus(temp, vec_focal_len);
    print_vec(temp); // x : -1.333333, y :-1.000000, z : -1.000000


    cam.left_bottom = temp;

    return (cam);
}