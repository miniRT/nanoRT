#include "trace.h"

void	set_face_normal(t_ray *r, t_hit_record *rec)
{
	// 광선의 벡터와 교점의 법선백터를 내적함으로써 물체의 바깥인지 안쪽인지를 판별
	rec->front_face = vdot(r->dir, rec->normal) < 0;
	// 물체의 안쪽에 부딪히면 법선 벡터를 반대로 뒤집는다.
	if (!rec->front_face)
		rec->normal = vmult(rec->normal, -1);
}
