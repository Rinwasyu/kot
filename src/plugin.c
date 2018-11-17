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