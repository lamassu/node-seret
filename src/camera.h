int camera_on(char *dev_name, uint32_t width, uint32_t height);
void camera_off(int fd);
void start_capturing(int fd);
void stop_capturing(int fd);
void capture_frame(int fd, char *result_buf, size_t result_size);
