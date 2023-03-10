#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <error.h>

int main()
{
    int shm_id, shm_id_finish;
    int *share, *share_resp_code;

    shm_id = shmget(0x2FF, sizeof(int), 0666 | IPC_CREAT);
    shm_id_finish = shmget(0x2FA, sizeof(int), 0666 | IPC_CREAT);
    if (shm_id == -1 || shm_id_finish == -1)
    {
        perror("shmget()");
        exit(1);
    }

    share = (int *)shmat(shm_id, 0, 0);
    share_resp_code = (int *)shmat(shm_id_finish, 0, 0);

    int kol = *share_resp_code;
    while (*share_resp_code != -1)
    {
        while (*share_resp_code == 200)
        {
            sleep(1);
        }
        if (*share_resp_code != -1)
        {
            printf("%d\n", *share);
            *share_resp_code = 200;
        }
    }
    return 0;
}