#define DATALEN 4096
int main(int argc, char **argv);
void handle_error(int dev);
int read_data(int dev, FILE *fd);
void write_cmd(int dev, char *command);
