/*
 * Copyright 2018 Rinwasyu
 * 
 * This file is part of kot.
 * 
 * Kot is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Kot is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

struct Plugin {
	void (*init)(struct Plugin *);
};

void plugin_init(struct Plugin *plugin) {
	DIR *dir;
	struct dirent *dirent;
	
	if ((dir = opendir("plugin")) == NULL) return;
	
	while ((dirent = readdir(dir)) != NULL) {
		char *ext = strstr(dirent->d_name, ".");
		if (ext != NULL && strcmp(".so", ext) == 0) {
			char *path = strjoin("plugin/", dirent->d_name);
			void *handle;
			void (*init)();
			if ((handle = dlopen(path, RTLD_LAZY)) != NULL) {
				if ((init = dlsym(handle, "init")) != NULL) {
					init();
				}
			}
			free(path);
			dlclose(handle);
		}
	}
}

struct Plugin plugin = {
	plugin_init
};