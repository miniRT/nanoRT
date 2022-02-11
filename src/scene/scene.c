#include "scene.h"

// void print_vec(t_vec3 vec3)
// {
//     printf ("x : %f, y :%f, z : %f\n", vec3.x, vec3.y, vec3.z);
// }

t_camera    camera(t_canvas *canvas, t_point3 orig)
{
    t_camera    cam;
    double      focal_len;
    double      viewport_height;
    t_vec3      temp;

    viewport_height = 2.0;
    focal_len = 1.0;
    cam.orig = orig;
    cam.viewport_h = viewport_height;
    cam.viewport_w = viewport_height * canvas->aspect_ratio;
    cam.focal_len = focal_len;
    cam.horizontal = vec3(cam.viewport_w, 0, 0);
    cam.vertical = vec3(0, cam.viewport_h, 0);
    // print_vec(cam.horizontal);
    // print_vec(cam.vertical);

    // 왼쪽 아래 코너점 좌표, origin - horizontal / 2 - vertical / 2 - vec3(0,0,focal_length)
    // cam.left_bottom = vminus(vminus(vminus(cam.orig, vdivide(cam.horizontal, 2)),
    //                            vdivide(cam.vertical, 2)), vec3(0, 0, focal_len));
    temp = vminus(cam.orig, vdivide(cam.horizontal, 2));
    temp = vminus(temp, vdivide(cam.vertical, 2));
    temp = vminus(temp, vec3(0, 0, focal_len));
    cam.left_bottom = temp;

    return (cam);
}