#ifndef _VAM_H
#define _VAM_H

typedef struct vam vam_t;

vam_t *vam_new(double *p, int n);
int vam_sample(vam_t *v);
void vam_free(vam_t *v);

#endif
