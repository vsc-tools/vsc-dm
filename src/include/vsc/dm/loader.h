/*
 * loader.h
 *
 *  Created on: Feb 14, 2022
 *      Author: mballance
 */
#include <dlfcn.h>
#include <stdio.h>
#include "vsc/dm/IVsc.h"


static vsc::IVsc *get_vsc(const char *path) {
	static vsc::IVsc *prv_vsc = 0;

	if (!prv_vsc) {
		void *dlh = dlopen(path, RTLD_LAZY);

		if (!dlh) {
			fprintf(stdout, "libvsc Error: failed to load library %s: %s\n",
					path, dlerror());
		} else {
			void *vsc_f = dlsym(dlh, "ivsc");

			if (!vsc_f) {
				fprintf(stdout, "libvsc Error: failed to find symbol ivsc in library %s: %s\n",
						path, dlerror());
			} else {
				void *vsc_h = ((void *(*)())vsc_f)();
				prv_vsc = reinterpret_cast<vsc::IVsc *>(vsc_h);
			}
		}
	}

	return prv_vsc;
}




