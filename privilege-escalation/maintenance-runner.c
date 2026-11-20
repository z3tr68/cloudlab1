#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    printf("Starting system maintenance...\n");
    fflush(stdout);

    setgid(0);
    setuid(0);

    execl("/bin/bash", "bash", "-p",
          "/opt/maintenance/maintenance.sh",
          (char *)NULL);

    perror("execl");
    return 1;
}
