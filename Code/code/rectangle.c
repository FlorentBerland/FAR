#include "../headers/rectangle.h"

r_point r_sup_gauche(r_rect r)
{
	return r_point_vers_abs((r_point){ -r.rec.l/2, r.rec.h/2 }, r);
}

r_point r_sup_droit(r_rect r)
{
	return r_point_vers_abs((r_point){ r.rec.l/2, r.rec.h/2 }, r);
}

r_point r_inf_gauche(r_rect r)
{
	return r_point_vers_abs((r_point){ -r.rec.l/2, -r.rec.h/2 }, r);
}

r_point r_inf_droit(r_rect r)
{
	return r_point_vers_abs((r_point){ r.rec.l/2, -r.rec.h/2 }, r);
}

r_point r_centre(r_rect rect)
{
	return rect.rec.centre;
}

float r_angle(r_rect rect)
{
	return rect.angle;
}

rectangle_p r_t_vers_p(rectangle_t t)
{
	rectangle_p p;
	p.p1.x = t.centre.x - t.l/2;
	p.p1.y = t.centre.y + t.h/2;
	p.p2.x = p.p1.x + t.l;
	p.p2.y = p.p1.y - t.h;
	return p;
}

rectangle_t r_p_vers_t(rectangle_p p)
{
	rectangle_t t;
	t.centre.x = (p.p1.x+p.p2.x)/2;
	t.centre.y = (p.p1.y+p.p2.y)/2;
	t.l = p.p2.x - p.p1.x;
	t.h = p.p1.y - p.p2.y;
	return t;
}

r_rect r_p_vers_rect(rectangle_p p)
{
	return r_t_vers_rect(r_p_vers_t(p));
}

r_rect r_t_vers_rect(rectangle_t t)
{
	r_rect rect;
	rect.rec = t;
	rect.angle = 0.0f;
	return rect;
}

r_rect r_rotation_abs(r_rect r, r_point p, float a)
{
	r_rect pivot = r_translation_abs(REC_ORIGINE, (r_vecteur)p); // Rectangle au centre de rotation
	r_rect relatif = r_rect_vers_rel(r, pivot); // Calcul de r par rapport à pivot
	pivot = r_orienter_rel(pivot, a); // Rotation de pivot
	return r_rect_vers_abs(relatif, pivot); // Remise de relatif en coordonnees absolues
}

r_rect r_rotation_rel(r_rect r, r_point p, float a)
{
	return r_rotation_abs(r, r_point_vers_abs(p, r), a);
}

r_rect r_orienter_abs(r_rect rect, float angle)
{
	rect.angle = angle;
	return rect;
}

r_rect r_orienter_rel(r_rect rect, float angle)
{
	rect.angle += angle;
	return rect;
}

r_rect r_translation_abs(r_rect rect, r_vecteur v)
{
	rect.rec.centre.x += v.x;
	rect.rec.centre.y += v.y;
	return rect;
}

r_rect r_translation_rel(r_rect rect, r_vecteur v)
{
	return (r_rect){ (rectangle_t){ r_point_vers_abs((r_point)v, rect),
		rect.rec.l, rect.rec.h }, rect.angle };
}

r_point r_point_vers_abs(r_point p, r_rect r)
{
	float a = r_arg((r_vecteur)p); // Angle du point par rapport au rectangle
	a += r.angle;
	float m = r_module((r_vecteur)p);
	return (r_point){ m*sin(a)+r.rec.centre.x, m*cos(a)+r.rec.centre.y };
}

r_point r_point_vers_rel(r_point p, r_rect r)
{
	r_vecteur v = (r_vecteur){ p.x-r.rec.centre.x, p.y-r.rec.centre.y };
	float a = r_arg(v);
	a -= r.angle; // Angle du point par rapport au rectangle
	float m = r_module(v);
	return (r_point){ m*sin(a), m*cos(a) };
}

r_rect r_rect_vers_abs(r_rect r1, r_rect r2)
{
	return (r_rect){ (rectangle_t){ r_point_vers_abs(r1.rec.centre, r2), r1.rec.l, r1.rec.h},
		r1.angle+r2.angle };
}

r_rect r_rect_vers_rel(r_rect r1, r_rect r2)
{
	return (r_rect){ (rectangle_t){ r_point_vers_rel(r1.rec.centre, r2), r1.rec.l, r1.rec.h },
		r1.angle-r2.angle };
}

bool r_pt_dans_rec(r_rect rect, r_point pt)
{
	r_point point = r_point_vers_rel(pt, rect);

	return (point.x>=(-rect.rec.l/2)) && (point.x<=(rect.rec.l/2)) &&
		(point.y>=(-rect.rec.h/2)) && (point.y<=(rect.rec.h/2));
}

bool r_croisent(r_rect r1, r_rect r2)
{
	// r1 et r2 se croisent <=> r2 a au moins un de ses points dans r1
	// ou r2 a au moins un de ses points dans r1
	return r_pt_dans_rec(r1, r_sup_gauche(r2)) || r_pt_dans_rec(r1, r_sup_droit(r2)) ||
		r_pt_dans_rec(r1, r_inf_gauche(r2)) || r_pt_dans_rec(r1, r_inf_droit(r2)) ||
		r_pt_dans_rec(r2, r_sup_gauche(r1)) || r_pt_dans_rec(r2, r_sup_droit(r1)) ||
		r_pt_dans_rec(r2, r_inf_gauche(r1)) || r_pt_dans_rec(r2, r_inf_droit(r1));
}

bool r_recouvre(r_rect r1, r_rect r2)
{
	// r1 recouvre r3 <=> r1 contient tous les points de r3
	return r_pt_dans_rec(r1, r_sup_gauche(r2)) && r_pt_dans_rec(r1, r_sup_droit(r2)) &&
		r_pt_dans_rec(r1, r_inf_gauche(r2)) && r_pt_dans_rec(r1, r_inf_droit(r2));
}

float r_module(r_vecteur v)
{
	return sqrt(v.x*v.x + v.y*v.y);
}

float r_arg(r_vecteur v)
{
	return atan2(v.x, v.y);
}

float r_radians(float a)
{
	return a*PI/180.0;
}

float r_degres(float a)
{
	return a*180.0/PI;
}

r_vecteur r_creer_vecteur(r_point p1, r_point p2)
{
	return (r_vecteur){ p2.x-p1.x, p2.y-p1.y };
}